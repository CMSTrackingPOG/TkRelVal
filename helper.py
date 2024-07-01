# -*- coding: utf-8 -*-
import os
import subprocess
import sys
import re
import Levenshtein
import difflib
import itertools
from collections import OrderedDict
from multiprocessing import Pool,cpu_count
import threading
from common.utils import *

sys.path.insert(0,'/afs/cern.ch/user/a/abulla/CMSSW_14_0_0/src/TkRelVal/collisions')

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def ask_to_continue():
    print("Do you want to continue? [y/n]")
    answer = input().lower()
    if answer == "n" or answer == "no":
        print("Exiting...")
        exit()
    elif answer == "y" or answer == "yes":
        print("Continuing...")

# 1. Crea un ticket Kerberos (kinit) e verifica che sia valido
def verify_kerberos_ticket():
    try:
        # Esegue il comando klist per verificare i ticket Kerberos
        subprocess.check_output(['klist'])
        return True
    except subprocess.CalledProcessError:
        return False

# 2. Esegue il comando 'auth-get-sso-cookie' per ottenere il cookie SSO
def get_sso_cookie(url):
    try:
        # Esegue il comando 'auth-get-sso-cookie' e salva il risultato nel file 'ssocookie_temp.txt'
        subprocess.check_output(['auth-get-sso-cookie', '-o', 'ssocookie_temp.txt', '-u', url])
        return True
    except subprocess.CalledProcessError:
        return False

# 3. Legge l'HTML usando cURL e il cookie SSO e lo memorizza in un file
def read_html_with_cookie(url, output_file):
    try:
        # Legge l'HTML utilizzando cURL e il cookie salvato nel file 'ssocookie_temp.txt'
        subprocess.check_output(['curl', '-L', '--cookie', 'ssocookie_temp.txt', url, '-o', output_file])
        return True
    except subprocess.CalledProcessError:
        return False


def filter_substring_list(iList):
    filtered_list = []

    for item in iList:
        is_substring = False
        for other_item in iList:
            if item != other_item and item in other_item:
                is_substring = True
                break
        if not is_substring:
            filtered_list.append(item)

    # iList = filtered_list
    return filtered_list


def search_keywords_in_html(results, html_content, keyword, pattern=None, new_pattern_used = False):
    # Create a regular expression pattern for the keyword
    # (?i) makes the pattern case-insensitive
    # (?<!data-) excludes matches that start with "data-"
    # \s* matches any number of whitespace characters
    # [^<\n\s.|]+ matches any number of characters that are not "<", "\n", whitespace, "|" or "." (i.e. the value of the attribute)
    ## i'm looking for the words in keywords basically 
    if pattern is None:
        pattern = re.compile(r'(?i)(?<!data-){}:\s*([^<\n\s.|]+)'.format(re.escape(keyword)))

    matches = re.findall(pattern, html_content)
    cleaned_matches = []

    # Iterate through each match and clean it
    for match in matches:
        # Use regular expressions to extract specific patterns from the match
        # First, try to find patterns like "13_0_8abc-123"
        cleaned_match = re.search(r'\b\d+_\d+_\d+[a-zA-Z0-9_-]+\b', match)
        if cleaned_match:
            if cleaned_match.group() not in cleaned_matches and cleaned_match.group() != "": cleaned_matches.append(cleaned_match.group())
        else:
            # If the above pattern is not found, try to find patterns like "13_0_8" with boundaries
            # boundaries of words are marked as \b
            cleaned_match = re.search(r'\b\d+_\d+_\d+\b', match)
            if cleaned_match:
                if cleaned_match.group() not in cleaned_matches and cleaned_match.group() != "": cleaned_matches.append(cleaned_match.group())
            else:
                # If still not found, try to find patterns like "13_0_8" without boundaries
                cleaned_match = re.search(r'\d+_\d+_\d', match)
                if cleaned_match:
                    if cleaned_match.group() not in cleaned_matches and cleaned_match.group() != "": cleaned_matches.append(cleaned_match.group())

    # Store the cleaned matches in the results dictionary with the keyword as the key
    if cleaned_matches == []:
        new_pattern = re.compile(r'(?i)(?<!data-){}:\s*(.*?)(?=\n)'.format(re.escape(keyword)))
        if new_pattern != pattern:
            print("TRYING MY BEST....")
            ## hardcoded search with another pattern
            search_keywords_in_html(results,html_content,keyword,new_pattern)
        else:
            print(("No clean matches found for keyword: {}".format(keyword)))

    if keyword not in results.keys():
        results[keyword] = cleaned_matches


    return results

def findGTs(html_content, doTarget = False, doReference = False):
    """
    way more difficult to find the GT names in the html page, wrt to the release!!
    So i do this step by step. Looking for Description, then for GT, then for data, then for the pattern of target and reference!
    Find target and reference elements in the given HTML content.

    Args:
        html_content (str): HTML content to search.

    Returns:
        dict or None: A dictionary containing the target and reference elements, or None if not found.
    """
    target = []
    reference = []

    ## i'm excluding everything that is not a word, a space or - or _
    excluded_chars = r'(<.*?>)|([^\w\s-])'

    # Narrow down the search to the "description" section
    div_start = "</div><p><strong>"
    div_end = "</p>"
    div_pattern = re.escape(div_start) + "(.*?)" + re.escape(div_end)
    div_match = re.search(div_pattern, html_content, re.IGNORECASE | re.DOTALL)

    if div_match:
        div_text = div_match.group(1)
    else:
        print("</div><p><strong> not found, looking for description....")
        div_start = 'description'
        div_end = '</html>'
        div_pattern = re.escape(div_start) + "(.*?)" + re.escape(div_end)
        div_match = re.search(div_pattern, html_content, re.IGNORECASE | re.DOTALL)

        if div_match:
            print("Description found!!")
            div_text = div_match.group(1)
        else:
            print("Description not found")

    if div_match:
        # Find the line that contains "GT" within the lines starting with "</div><p><strong>" or "Description" and ending with "</p>" or "</html>"
        gt_pattern = r"(?i)^.*GT.*$"
        gt_match = re.search(gt_pattern, div_text, re.MULTILINE)

        if gt_match:
            # print("GT found!!")
            gt_line = gt_match.group(0)
            gt_line_index = div_text.index(gt_line)

            # Find the lines that contain "data" or "Data" after the "GT" line
            data_pattern = r"(?i)^.*data\S*$"
            lines = div_text.split("\n")
            data_lines = []

            for line in lines:
                if re.search(data_pattern, line):
                    data_lines.append(line.strip())

            if len(data_lines) > 0:
                # Search for patterns like 123X_abc within the lines after "data"
                target_reference_pattern = r"(\d{3}X_[a-zA-Z]+\S*)"
                for line in data_lines:
                    if doTarget:
                        if re.search(r"\btarget\b", line, re.IGNORECASE):
                            target_match = re.search(target_reference_pattern, line)
                            if target_match:
                                target_value = re.sub(excluded_chars, '', target_match.group(1))
                                target.append(target_value)
                    if doReference:
                        if re.search(r"\breference\b", line, re.IGNORECASE):
                            reference_match = re.search(target_reference_pattern, line)
                            if reference_match:
                                reference_value = re.sub(excluded_chars, '', reference_match.group(1))
                                reference.append(reference_value)
            ## still need to work on this part due to special char (see excluded_chars), spaces or whatever
            ## eventually i'm not really sure i'm appending the corret values to the lists
            ## target match here is not defined
            else:
                print("Data line not found, trying without it...")
                # If "data" is not found, directly search for the pattern
                target_pattern = r"(?:target)[\s:-]*\d{3}X_[a-zA-Z]+\S*"
                reference_pattern = r"(?:reference)[\s:-]*\d{3}X_[a-zA-Z]+\S*"
                for line in data_lines:
                    if doTarget:
                        if re.findall(target_pattern, line):
                            target.append(list(target_match))
                    if doReference:
                        if re.search(reference_pattern, line):
                            reference.append(list(reference_match))
        else:
            print("GT line not found, trying without it...")
            # If "GT" is not found, directly search for the pattern
            target_pattern = r"(?i)(?:target)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
            reference_pattern = r"(?i)(?:reference)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
            if doTarget:
                target_matches = re.findall(target_pattern, div_text)
                if target_matches:
                    for match in target_matches:
                        separated_targets = re.split(" ", match)
                        target.extend(separated_targets)
            if doReference:
                reference_matches = re.findall(reference_pattern, div_text)
                if reference_matches:
                    for match in reference_matches:
                        separated_reference = re.split(" ", match)
                        reference.extend(separated_reference)
    else:
        print("Description not found, trying my best without it...")
        target_pattern = r"(?i)(?:target)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
        reference_pattern = r"(?i)(?:reference)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
        if doTarget:
            target_matches = re.findall(target_pattern, html_content)
            if target_matches:
                for match in target_matches:
                    separated_targets = re.split(" ", match)
                    target.extend(separated_targets)

        reference_matches = re.findall(reference_pattern, html_content)
        if doReference:
            if reference_matches:
                for match in reference_matches:
                    separated_reference = re.split(" ", match)
                    reference.extend(separated_reference)

    # Filter out elements with "/" and with no "data" in them (dataRun3 for example)
    if doTarget:
        target_filtered = [elem for elem in target if "/" not in elem and "data" in elem]
    if doReference:
        reference_filtered = [elem for elem in reference if "/" not in elem and "data" in elem]

    # Remove HTML tags from the elements
    if doTarget:
        cleaned_target = [re.sub(r"<.*?>", "", elem) for elem in target_filtered]
    if doReference:
        cleaned_reference = [re.sub(r"<.*?>", "", elem) for elem in reference_filtered]

    ##easy case, everything was good
    if doTarget and doReference:
        if len(cleaned_reference) == 1 and len(cleaned_target) == 1:
            return {"target": cleaned_target[0], "reference": cleaned_reference[0]}

    ##1st bad case, multiple GTs
    if doReference:
        if len(cleaned_reference) > 1 or len(cleaned_reference) > 1:
            print ("Never tested. Multiple GTs found!")
            if len(cleaned_reference) > 1:
                print("Please, choose one GT for reference: ")
                for i in cleaned_reference:
                    print(("GT {}-th: ".format(i,cleaned_reference[i])))
                answer = int(input().lower())
            cleaned_reference_prov = [cleaned_reference[answer]]
            cleaned_reference = cleaned_reference_prov

        if doTarget:
            if len(cleaned_target) > 1:
                print("Please, choose one GT for target: ")
                for i in cleaned_target:
                    print(("GT {}-th: ".format(i,cleaned_target[i])))
                answer = int(input().lower())
                cleaned_target_prov = [cleaned_target[answer]]
                cleaned_target = cleaned_target_prov
            return {"target": cleaned_target[0], "reference": cleaned_reference[0]}

        return {"reference": cleaned_reference[0]}

    ##2st bad case, not ref GT
    if doReference:
        if len(cleaned_reference) == 0:
            print("Do you want to manually insert reference GT? [y/n]")
            answer = input().lower()
            if answer == "n" or answer == "no":
                cleaned_reference = [""]
                print("Continuing without reference GT...")
            elif answer == "y" or answer == "yes":
                print("Please, insert reference GTs...")
                cleaned_reference = [input()]

    ##2nd bad case, no target GT:
    if doTarget:
        if len(cleaned_target) == 0:
            print("Do you want to manually insert target GT? [y/n]")
            answer = input().lower()
            if answer == "n" or answer == "no":
                print("Continuing without target GT...")
                cleaned_target = [""]
            elif answer == "y" or answer == "yes":
                print("Please, insert target GTs...")
                cleaned_target = [input()]

    if doTarget and doReference:
        return {"target": cleaned_target[0], "reference": cleaned_reference[0]}
    elif doTarget and not doReference:
        return {"target": cleaned_target[0]}
    elif not doTarget and doReference:
        return {"reference": cleaned_reference[0]}


## scarico html con i risultati della pagina e li salvo in output_files.html
## seleziono le righe che mi interessano e salvo il nome del file in una lista, selezionando tra DQM e .root
## tra questi faccio una classifica, cercando quelli che sono più simili alle mie parole chiave
## favoreggio quelli che hanno v2 dentro e penalizzo quelli che hanno v1 dentro
## favoreggio quelli che hanno i soliti run number (355769, 356381,357735) + quelli del 2023
## se ci sono tre elementi con lo stesso identico punteggio e un nome file molto simile
## tipo DQM_V0001_R000356635__ZeroBias__CMSSW_13_1_0_pre4-130X_dataRun3_v1_RelVal_2022C-v1__DQMIO.root e DQM_V0001_R000357735__ZeroBias__CMSSW_13_1_0_pre4-130X_dataRun3_v1_RelVal_2022D-v1__DQMIO.root (cambia la era e il runnumber)
## favorisco la tripletta --> non sempre le campagne hanno tre file, ma ultimamente si.. 
## ritorno la lista totale con i punteggi! 

def similarity_score(file_name, keys):
    score = sum(-200 for keyword in keys if keyword in file_name)
    score = score + sum(Levenshtein.distance(key, file_name) for key in keys)
    hs_keys = ["v2", "v3", "355769", "356381", "357735", "367131", "369978", "2022C", "2022D", "2022B", "2023C", "2023D", "STD"]
    ls_keys = ["v1","HLT","CNAFARM"]
    for item in hs_keys:
        if item in file_name:
            score = score - 50
    for item in ls_keys:
        if item in file_name:
            score = score + 25
    return score

def checkProxy():
    cmd = 'voms-proxy-info'
    proc = subprocess.Popen(cmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
    out, err = proc.communicate()

    # Decodifica gli output byte in stringhe
    out_str = out.decode('utf-8')
    err_str = err.decode('utf-8')

    # No Proxy at all ?
    if 'Proxy not found' in err_str:
        print('WARNING: No GRID proxy -> Get one first with:')
        print('voms-proxy-init -voms cms -rfc --valid 168:0')
        exit()

    # More than 24h ?
    timeLeft = 0
    for line in out_str.split("\n"):
        if 'timeleft' in line:
            timeLeft = int(line.split(':')[1])

    if timeLeft < 24:
        print('WARNING: Your proxy is only valid for ', str(timeLeft), ' hours -> Renew it with:')
        print('voms-proxy-init -voms cms -rfc --valid 168:0')
        exit()


def getFileNames(Rel, GTs, sample): 
    ## questo il comando per prendere l'html della webpage con i files
    print(bcolors.OKBLUE + "Downloading the list of all the DQM files..." + bcolors.ENDC)
    checkProxy()
    x509_user_proxy_path = os.popen("voms-proxy-info -path").read().strip()
    os.environ["X509_USER_PROXY"] = x509_user_proxy_path
    os.system("wget -q --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY -O output_files.html \"https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/\"".format(Rel.split("_")[0], Rel.split("_")[1]))

    # che è simile a quello per scaricare i files, ma scarica l'html in un file output_files.html 
    
    with open("/afs/cern.ch/user/a/abulla/CMSSW_14_0_0/src/TkRelVal/output_files.html", "r") as file:
        DQMfiles_html = file.read()

    # print(DQMfiles_html)

    if GTs != "":
        Rel = Rel+"_"+GTs+"-"
    else:
        Rel = Rel+"-"

    keywords = [Rel, "ZeroBias", "dataRun3"]
    pattern = r".*{}.*".format(r".*".join(map(re.escape, keywords)))

    files = []

    for line in DQMfiles_html.splitlines():
        # print line
        if re.search(pattern, line):
            # print("La riga contiene tutte le parole chiave:", line)
            match = re.search(r'DQM.*?\.root', line)
            if match:
                file_name = match.group(0)
                files.append(file_name)
        else:
            gts_parts = GTs.split('_')
            if Rel in line and "ZeroBias" in line:
                if any(gts_part in line for gts_part in gts_parts):
                    match = re.search(r'DQM.*?\.root', line)
                    if match:
                        file_name = match.group(0)
                        files.append(file_name)

    os.system("rm output_files.html")

    # Calcola il punteggio di similarità per ogni file
    scores = {name: similarity_score(name, keywords) for name in files}
    print(scores)

    # Se ci sono tre (o due, per il 2023) files con un nome molto simile e lo stesso punteggio, abbassa il loro punteggio:
    # è molto verosimile che siano i file che cerco!
    # if len(scores) >1 :
    #     for name1, name2 in itertools.combinations(scores, 2):
    #         if scores[name1] == scores[name2]:
    #             if difflib.SequenceMatcher(None, name1, name2).ratio() > 0.9:
    #                 scores[name1] -= 100
    #                 scores[name2] -= 100
    if len(scores) > 2 :
        for name1, name2, name3 in itertools.combinations(scores, 3):
            if "2022" in name1 and "2022" in name2 and "2022" in name3:
                if scores[name1] == scores[name2] == scores[name3]:
                    if difflib.SequenceMatcher(None, name1, name2, name3).ratio() > 0.9:
                        scores[name1] -= 100
                        scores[name2] -= 100
                        scores[name3] -= 100
        for name1, name2 in itertools.combinations(scores, 2):
            if "2023" in name1 and "2023" in name2:
                if scores[name1] == scores[name2]:
                        if difflib.SequenceMatcher(None, name1, name2 ).ratio() > 0.9:
                                scores[name1] -= 100
                                scores[name2] -= 100
            
    # Ordina i file in base al punteggio di similarità (dal più simile al meno simile), e prendo i primi tre
    sorted_files = sorted(list(scores.items()), key=lambda x: x[1])[:5]
    # print( "DEBUGGGG: ", sorted_files)

    dic = {}
    for item in sorted_files:
        filename = item[0]
        value = item[1]
        run = findRun(filename)
        era = findEra(filename)
        release = findRelease(filename)
        sample = findSample(filename)

        dic[filename] = {
            'rootname': filename,
            'run': run,
            'era': era,
            'release': release,
            'sample': sample,
            'value': value
        }

    sorted_dic = sorted(list(dic.items()), key=lambda x: int(x[1]['run']))

    return OrderedDict(sorted_dic)

def doRazor(dic1, dic2):
    _runs1 = [dic1[entry]["run"] for entry in dic1.keys()]
    _runs2 = [dic2[entry]["run"] for entry in dic2.keys()]

    common_runs = [i for i in _runs2 if i in _runs1]

    for key1 in list(dic1.keys()):
        if dic1[key1]["run"] not in common_runs:
            del dic1[key1]
            
    for key2 in list(dic2.keys()):
        if dic2[key2]["run"] not in common_runs:
            del dic2[key2]

            

def compare(args):
    ref, tar, directory = args

    dire_tar = os.path.join(directory, findImportantRelease(tar["rootname"])[:-1]+"x", tar["label"], tar["run"], tar["sample"])
    dire_ref = os.path.join(directory, findImportantRelease(ref["rootname"])[:-1]+"x", ref["label"], ref["run"], ref["sample"])

    # if is_file_in_directory(tar["rootname"], directory): 
    #     print("Files di target già presenti nella directory")
    # else:
    #     print("Il file target non è presente nella directory, scarico?")
    #     ask_to_continue()
    #     command = 'wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" -A "{}" --no-check-certificate --certificate ~/.globus/html_cert/myCert.pem --private-key ~/.globus/html_cert/myCert.key'.format(Rel["target"].split("_")[0], Rel["target"].split("_")[1], tar["rootname"])
    #     os.system(command)
    #     command = 'mkdir -p {}'.format(dire_tar)
    #     os.system(command)
    #     command = 'mv {} {}'.format(tar["rootname"], dire_tar)
    #     os.system(command)

    # if is_file_in_directory(ref["rootname"], directory): 
    #     print("Files di reference già presenti nella directory")
    # else:
    #     print("Il file reference non è presente nella directory, scarico?")
    #     ask_to_continue()
    #     command = 'wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" -A "{}" --no-check-certificate --certificate ~/.globus/html_cert/myCert.pem --private-key ~/.globus/html_cert/myCert.key'.format(Rel["reference"].split("_")[0], Rel["reference"].split("_")[1], ref["rootname"])
    #     os.system(command)
    #     command = 'mkdir -p {}'.format(dire_ref)
    #     os.system(command)
    #     command = 'mv {} {}'.format(ref["rootname"], dire_ref)
    #     os.system(command)

    print(bcolors.OKGREEN + "Finally doing the comparison" + bcolors.ENDC)
    print(("python3 start.py --refFile {} --targetFile {} --refLabel {} --targetLabel {} --FullPlots".format(os.path.join(dire_ref,ref["rootname"]), os.path.join(dire_tar,tar["rootname"]), ref["label"], tar["label"])))
    # ask_to_continue()
    os.system("python3 start.py --refFile {} --targetFile {} --refLabel {} --targetLabel {} --FullPlots".format(os.path.join(dire_ref,ref["rootname"]), os.path.join(dire_tar,tar["rootname"]), ref["label"], tar["label"]))



#######################################################################
###                                                                 ###
###                          +++ MAIN +++                           ###
###                                                                 ###
#######################################################################

if __name__ == "__main__":
        
    # # URL to be passed as an argument to the program
    url = sys.argv[1]
    output_file = "output.html"

    try:
        # Verify the Kerberos ticket
        if not verify_kerberos_ticket():
            raise ValueError("Invalid Kerberos ticket. Perform authentication.")

        # Create the Kerberos ticket (kinit) if necessary
            os.system('kinit')

        # Delete the output file if it already exists
        if os.path.isfile(output_file):
            os.remove(output_file)

        # Delete the ssocookie_temp.txt file if it already exists
        if os.path.isfile("ssocookie_temp.txt"):
            os.remove("ssocookie_temp.txt")

        # Get the SSO cookie if not already present
        if not os.path.isfile("ssocookie_temp.txt"):
            get_sso_cookie(url)
        if get_sso_cookie(url):
            print("SSO cookie obtained successfully.")

        # Read the HTML using the SSO cookie and save it to a file
        if read_html_with_cookie(url, output_file):
            print(("HTML read successfully using the SSO cookie and saved to", output_file))
        else:
            raise IOError("Failed to read HTML using the SSO cookie.")

        # Delete the ssocookie_temp.txt file
        # if os.path.isfile("ssocookie_temp.txt"):
        #     os.remove("ssocookie_temp.txt")
        
    except ValueError as e:
        print(("Error:", str(e)))
        exit()
    except Exception as e:
        print(("An unexpected error occurred:", str(e)))
        exit()


    with open(output_file, "r") as file:
        html_content = file.read()

    ## remove html file, i saved it in a variable
    # os.remove(output_file)

    keywords_to_search = ["target", "reference", "target release", "reference release"]

    results = {}
    for keyword in keywords_to_search:
       search_keywords_in_html(results, html_content, keyword)

    target_values = results["target"] + results["target release"]
    reference_values = results["reference"] + results["reference release"]

    if len(set(target_values)) > 1:
        target_values = filter_substring_list(target_values)

    if len(set(target_values)) == 1:
        target_value = target_values[0]
    else:
        print("Le voci 'target' e 'target release' non sono tutte uguali.")
        print(target_values)
        exit()

    if len(reference_values) > 1:
        reference_values = filter_substring_list(reference_values)
    if len(set(reference_values)) == 1:
        reference_value = reference_values[0]
    else:
        print("Le voci 'reference' e 'reference release' non sono tutte uguali.")
        print(reference_values)
        exit()


    Rel = {"target": target_value, "reference": reference_value}
    ## fin qui ho preso le relase, ora cerchiamo i GT!!!
    ## se ho trovato anche il GT nella relase, lo inserisco nel GT
    if len(Rel["target"].split("_")) > 3:
        GTs = {}
        GTs["target"] = Rel["target"].replace(Rel["target"].split("_")[0] + "_" + Rel["target"].split("_")[1] + "_" + Rel["target"].split("_")[2]+"_","")
        Rel["target"] = Rel["target"].split("_")[0] + "_" + Rel["target"].split("_")[1] + "_" + Rel["target"].split("_")[2]
    else:
        GTs = findGTs(html_content, doTarget=True)
    
    if len(Rel["reference"].split("_")) > 3:
        GTs["reference"] = Rel["reference"].replace(Rel["reference"].split("_")[0] + "_" + Rel["reference"].split("_")[1] + "_" + Rel["reference"].split("_")[2]+"_","")
        Rel["reference"] = Rel["reference"].split("_")[0] + "_" + Rel["reference"].split("_")[1] + "_" + Rel["reference"].split("_")[2]
    else:
        if "reference" not in GTs:
            GTs = findGTs(html_content, doReference = True)

    # GTs = findGTs(html_content)
    print("Releases: ", Rel)
    print("Global Tags: ", GTs)


    ## CHECK POINT
    ask_to_continue()
    import pprint


    ## A questo punto, devo cercare i samples online ed eventualmente scaricarli, poi ho quasi finito!
    ## prima magari verifichiamo se li ho già...
    ## ma prima ancora, cerchiamo **veramente** quelli che voglio!
    target_files = getFileNames(Rel["target"], GTs["target"], "ZeroBias")
    reference_files = getFileNames(Rel["reference"], GTs["reference"], "ZeroBias")

    ## cut out the files with not matching runs!
    ## if i have to compare different eras this obv will be a problem
    ## but the framework does not support that for the time being :)
    doRazor(target_files, reference_files)

    # print "Target files: ", target_files.keys()
    # print "Target files runs: "
    # print "Reference files: ", reference_files.keys()
    # print "Reference files runs: ", reference_files.values()

    print(bcolors.HEADER + "Target files: " + bcolors.ENDC)
    for entry_name, entry_data in list(target_files.items()):
        print(("{}:".format(entry_name)))
        print(("  rootfile: {}".format(entry_data['rootname'])))
        print(("  run: {}".format(entry_data['run'])))
        print(("  era: {}".format(entry_data['era'])))
        print(("  release: {}".format(entry_data['release'])))
        print(("  sample: {}".format(entry_data['sample'])))
        print(("  value: {}\n".format(entry_data['value'])))
        

    print(bcolors.HEADER + "Reference files: " + bcolors.ENDC)
    for entry_name, entry_data in list(reference_files.items()):
        print(("{}:".format(entry_name)))
        print(("  rootfile: {}".format(entry_data['rootname'])))
        print(("  run: {}".format(entry_data['run'])))
        print(("  era: {}".format(entry_data['era'])))
        print(("  release: {}".format(entry_data['release'])))
        print(("  sample: {}".format(entry_data['sample'])))
        print(("  value: {}\n".format(entry_data['value'])))

    ## CHECK POINT
    ask_to_continue()

    ## here i want to have the exactly same dimension of the dictionaries, so i have to cut, eventually :)


    # a questo punto ho le informazioni che mi servono, verifico di avere la coppia reference-target, se non li ho li scarico e poi li confronto
    # se li ho già, li confronto direttamente
    # # Directory principale da controllare
    directory = "/eos/project/c/cmsweb/www/tracking/validation/DATA/DQM/"

    # Funzione per controllare se un file è presente nella directory e/o nelle sottodirectory
    def is_file_in_directory(file, directory):
        for root, dirs, files in os.walk(directory):
            if file in files:
                return root
        return False


    ## take the key for the first entry in each dictionary
    key1 = next(iter(target_files))
    key2 = next(iter(reference_files))
    dic_ref = reference_files[key2] 
    dic_tar = target_files[key1]

    ## prima di controllare se ci sono o non ci sono i file, aggiungo il label (visto che mi servono entrambi i file per calcolarli)
    ## sta cosa non è **totalmente** vera ma per ora lasciamo così..
    if dic_ref["run"] == dic_tar["run"] and dic_ref["era"] == dic_tar["era"]:
        dic_ref["label"], dic_tar["label"] = findLabel(dic_ref["release"], dic_tar["release"], dic_ref["run"])
        # print "DEBUGGG::  Labels: ", ref["label"], tar["label"]
    else:
        print("Run e/o era diversi tra i due file. Orindamento Fallito!")
        print(("ref_run: ", ref["run"], "tar_run: ", tar["run"]))
        exit()

    print("Labels: ", dic_ref["label"], dic_tar["label"])

    # mettere a tutti lo stesso label, chiesto una sola volta, per ref[0] e tar[0]
    for ref_key, ref in list(reference_files.items()):
        ref["label"] = dic_ref["label"]

    for tar_key, tar in list(target_files.items()):
        tar["label"] = dic_tar["label"]

    ask_to_continue()

    ## A questo punto aggiorno il path di destinazione dei file, seguento la sintassi:
    ## DQM/release/label/run/sample/file.root
    ## Controlla se i file sono presenti nella directory e nelle sottodirectory
    ## se non ci sono, li scarica e li sposta nella directory giusta
    ## se ci sono, li confronta e basta

    for ref,tar in zip(list(reference_files.values()), list(target_files.values())):
        dire_tar = os.path.join(directory, findImportantRelease(tar["rootname"])[:-1]+"x", tar["label"], tar["run"], tar["sample"])
        dire_ref = os.path.join(directory, findImportantRelease(ref["rootname"])[:-1]+"x", ref["label"], ref["run"], ref["sample"])

        if is_file_in_directory(tar["rootname"], directory) != False: 
            ##FIXME the case in which the file is *not* in a directory made with the label (i.e file is in ../pre5/.. but i want label 13_3_0_pre5 for comparison)
            ## it was in that directory because for older comparison that was enought. Let's re-download, easiest and silliest thing to do but works :)
            if dire_tar != os.path.join(is_file_in_directory(tar["rootname"], directory),tar["rootname"]):
                print ("File was alredy here, but under different folder. Lets re-downald that.. i will fix in future...")
                command = 'wget -q -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" -A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'.format(Rel["target"].split("_")[0], Rel["target"].split("_")[1], tar["rootname"])
                os.system(command)
                command = 'mkdir -p {}'.format(dire_tar)
                os.system(command)
                command = 'mv {} {}'.format(tar["rootname"], dire_tar)
                os.system(command)
            else:
                print("Files di target già presenti nella directory")
        else:
            print("Il file target non è presente nella directory, scarico")
            command = 'wget -q -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" -A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'.format(Rel["target"].split("_")[0], Rel["target"].split("_")[1], tar["rootname"])
            os.system(command)
            command = 'mkdir -p {}'.format(dire_tar)
            os.system(command)
            command = 'mv {} {}'.format(tar["rootname"], dire_tar)
            os.system(command)

        if is_file_in_directory(ref["rootname"], directory) != False: 
            ## FIXME the case in which the file is *not* in a directory made with the label (i.e file is in ../pre5/.. but i want label 13_3_0_pre5 for comparison)
            ## it was in that directory because for older comparison that was enought. Let's re-download, easiest and silliest thing to do but works :)
            if dire_ref != os.path.join(is_file_in_directory(ref["rootname"], directory),ref["rootname"]):
                print("File was already here but in a different folder. Let's re-download that.. TO BE FIXED")
                command = 'wget -q -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" -A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'.format(Rel["reference"].split("_")[0], Rel["reference"].split("_")[1], ref["rootname"])
                os.system(command)
                command = 'mkdir -p {}'.format(dire_ref)
                os.system(command)
                command = 'mv {} {}'.format(ref["rootname"], dire_ref)
                os.system(command)
            else:
                print("Files di reference già presenti nella directory")
        else:
            print("Il file reference non è presente nella directory, scarico")
            command = 'wget -q -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" -A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'.format(Rel["reference"].split("_")[0], Rel["reference"].split("_")[1], ref["rootname"])
            os.system(command)
            command = 'mkdir -p {}'.format(dire_ref)
            os.system(command)
            command = 'mv {} {}'.format(ref["rootname"], dire_ref)
            os.system(command)

    arguments = [(ref, tar, directory) for ref, tar in zip(list(reference_files.values()), list(target_files.values()))]

    print("Arguments: ", arguments)
    num_cores = min(len(arguments),cpu_count())
    pool = Pool(processes=num_cores)  # Numero di core da utilizzare
    print(("Running the processes in multiprocessing mode: {} cores used".format(num_cores)))
    ask_to_continue()
    pool.map(compare, arguments)
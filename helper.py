# -*- coding: utf-8 -*-
"""
RelVal DQM comparator helper.

What this script does (high level):
- Given a CMSWeb URL (RelVal report / page), it authenticates via Kerberos/SSO and downloads the HTML.
- Parses target/reference CMSSW releases (and GlobalTags if present).
- Queries the DQM RelVal browser to find candidate DQM ROOT files (e.g. ZeroBias) for target/reference.
- Matches target/reference by common runs, ensures labels are consistent, downloads missing ROOT files to EOS.
- Launches comparisons via start.py (optionally in multiprocessing).
"""

import os
import subprocess
import sys
import re
import Levenshtein
import difflib
import itertools
import getpass
from collections import OrderedDict
from multiprocessing import Pool, cpu_count
import requests
import tsgauth
from common.utils import *

user = getpass.getuser()
# NOTE: user home on AFS is /afs/cern.ch/user/<first_letter>/<username>/
sys.path.insert(0, f'/afs/cern.ch/user/{user[0]}/{user}/CMSSW_14_0_0/src/TkRelVal/collisions')


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
    if answer in ("n", "no"):
        print("Exiting...")
        exit()
    elif answer in ("y", "yes"):
        print("Continuing...")


# 1. Verify a valid Kerberos ticket (klist)
def verify_kerberos_ticket():
    try:
        subprocess.check_output(['klist'])
        return True
    except subprocess.CalledProcessError:
        return False


# 2. (Legacy) obtain SSO cookie using auth-get-sso-cookie (not used below)
def get_sso_cookie(url):
    try:
        subprocess.check_output(['auth-get-sso-cookie', '-o', 'ssocookie_temp.txt', '-u', url])
        return True
    except subprocess.CalledProcessError:
        return False


# 3. (Legacy) read HTML using curl + cookie (not used below)
def read_html_with_cookie(url, output_file):
    try:
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
    return filtered_list


def search_keywords_in_html(results, html_content, keyword, pattern=None, new_pattern_used=False):
    """
    Try to extract values like CMSSW releases from lines that look like:
      keyword: 13_0_8abc-123 ...
    """
    if pattern is None:
        pattern = re.compile(r'(?i)(?<!data-){}:\s*([^<\s.|]+)'.format(re.escape(keyword)))

    matches = re.findall(pattern, html_content)
    matches = set(matches)

    cleaned_matches = []
    for match in matches:
        cleaned_match = re.search(r'\d+_\d+_\d+(?:_[a-zA-Z0-9]+)?', match)
        if cleaned_match:
            if cleaned_match.group() not in cleaned_matches and cleaned_match.group() != "":
                cleaned_matches.append(cleaned_match.group())
        else:
            cleaned_match = re.search(r'\b\d+_\d+_\d+\b', match)
            if cleaned_match:
                if cleaned_match.group() not in cleaned_matches and cleaned_match.group() != "":
                    cleaned_matches.append(cleaned_match.group())
            else:
                cleaned_match = re.search(r'\d+_\d+_\d', match)
                if cleaned_match:
                    if cleaned_match.group() not in cleaned_matches and cleaned_match.group() != "":
                        cleaned_matches.append(cleaned_match.group())

    if cleaned_matches == []:
        new_pattern = re.compile(r'(?i)(?<!data-){}:\s*(.*?)(?=\n)'.format(re.escape(keyword)))
        if new_pattern != pattern:
            print("Trying alternative pattern...")
            search_keywords_in_html(results, html_content, keyword, new_pattern)
        else:
            print(f"No clean matches found for keyword: {keyword}")

    if keyword not in results.keys():
        results[keyword] = cleaned_matches

    return results


def findGTs(html_content, doTarget=False, doReference=False):
    """
    Attempt to find GlobalTag names (target/reference) in the HTML content.
    """
    target = []
    reference = []

    excluded_chars = r'(<.*?>)|([^\w\s-])'

    div_start = "</div><p><strong>"
    div_end = "</p>"
    div_pattern = re.escape(div_start) + "(.*?)" + re.escape(div_end)
    div_match = re.search(div_pattern, html_content, re.IGNORECASE | re.DOTALL)

    if div_match:
        div_text = div_match.group(1)
    else:
        print("Could not find '</div><p><strong>'. Trying to locate 'description' section...")
        div_start = 'description'
        div_end = '</html>'
        div_pattern = re.escape(div_start) + "(.*?)" + re.escape(div_end)
        div_match = re.search(div_pattern, html_content, re.IGNORECASE | re.DOTALL)
        if div_match:
            print("Description found.")
            div_text = div_match.group(1)
        else:
            print("Description not found.")

    if div_match:
        gt_pattern = r"(?i)^.*GT.*$"
        gt_match = re.search(gt_pattern, div_text, re.MULTILINE)

        if gt_match:
            gt_line = gt_match.group(0)

            data_pattern = r"(?i)^.*data\S*$"
            lines = div_text.split("\n")
            data_lines = [line.strip() for line in lines if re.search(data_pattern, line)]

            if len(data_lines) > 0:
                target_reference_pattern = r"(\d{3}X_[a-zA-Z]+\S*)"
                for line in data_lines:
                    if doTarget and re.search(r"\btarget\b", line, re.IGNORECASE):
                        target_match = re.search(target_reference_pattern, line)
                        if target_match:
                            target_value = re.sub(excluded_chars, '', target_match.group(1))
                            target.append(target_value)
                    if doReference and re.search(r"\breference\b", line, re.IGNORECASE):
                        reference_match = re.search(target_reference_pattern, line)
                        if reference_match:
                            reference_value = re.sub(excluded_chars, '', reference_match.group(1))
                            reference.append(reference_value)
            else:
                print("No explicit 'data' line found. Trying a broader match...")
                target_pattern = r"(?:target)[\s:-]*\d{3}X_[a-zA-Z]+\S*"
                reference_pattern = r"(?:reference)[\s:-]*\d{3}X_[a-zA-Z]+\S*"

                if doTarget:
                    target_matches = re.findall(target_pattern, div_text, flags=re.IGNORECASE)
                    for match in target_matches:
                        target.extend(re.split(r"\s+", match))

                if doReference:
                    reference_matches = re.findall(reference_pattern, div_text, flags=re.IGNORECASE)
                    for match in reference_matches:
                        reference.extend(re.split(r"\s+", match))
        else:
            print("No line containing 'GT' found. Trying a broad target/reference pattern...")
            target_pattern = r"(?i)(?:target)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
            reference_pattern = r"(?i)(?:reference)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
            if doTarget:
                target_matches = re.findall(target_pattern, div_text)
                for match in target_matches:
                    target.extend(re.split(" ", match))
            if doReference:
                reference_matches = re.findall(reference_pattern, div_text)
                for match in reference_matches:
                    reference.extend(re.split(" ", match))
    else:
        print("Description not found. Trying a broad match on the full HTML...")
        target_pattern = r"(?i)(?:target)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
        reference_pattern = r"(?i)(?:reference)[\s:-]*\d{3}X_[a-zA-Z]+[\S]*"
        if doTarget:
            target_matches = re.findall(target_pattern, html_content)
            for match in target_matches:
                target.extend(re.split(" ", match))
        if doReference:
            reference_matches = re.findall(reference_pattern, html_content)
            for match in reference_matches:
                reference.extend(re.split(" ", match))

    if doTarget:
        target_filtered = [elem for elem in target if "/" not in elem and "data" in elem]
        cleaned_target = [re.sub(r"<.*?>", "", elem) for elem in target_filtered]
    if doReference:
        reference_filtered = [elem for elem in reference if "/" not in elem and "data" in elem]
        cleaned_reference = [re.sub(r"<.*?>", "", elem) for elem in reference_filtered]

    if doTarget and doReference:
        if len(cleaned_reference) == 1 and len(cleaned_target) == 1:
            return {"target": cleaned_target[0], "reference": cleaned_reference[0]}

    if doReference:
        if len(cleaned_reference) > 1 or (doTarget and len(cleaned_target) > 1):
            print("Multiple GTs found (this path was never fully tested).")
            if len(cleaned_reference) > 1:
                print("Please choose one reference GT:")
                for idx, gt in enumerate(cleaned_reference):
                    print(f"  [{idx}] {gt}")
                answer = int(input().strip())
                cleaned_reference = [cleaned_reference[answer]]

            if doTarget and len(cleaned_target) > 1:
                print("Please choose one target GT:")
                for idx, gt in enumerate(cleaned_target):
                    print(f"  [{idx}] {gt}")
                answer = int(input().strip())
                cleaned_target = [cleaned_target[answer]]

            if doTarget:
                return {"target": cleaned_target[0], "reference": cleaned_reference[0]}
            return {"reference": cleaned_reference[0]}

        if len(cleaned_reference) == 0:
            print("No reference GT found. Do you want to insert it manually? [y/n]")
            answer = input().lower()
            if answer in ("n", "no"):
                cleaned_reference = [""]
                print("Continuing without reference GT...")
            else:
                print("Please insert reference GT:")
                cleaned_reference = [input().strip()]

    if doTarget:
        if len(cleaned_target) == 0:
            print("No target GT found. Do you want to insert it manually? [y/n]")
            answer = input().lower()
            if answer in ("n", "no"):
                print("Continuing without target GT...")
                cleaned_target = [""]
            else:
                print("Please insert target GT:")
                cleaned_target = [input().strip()]

    if doTarget and doReference:
        return {"target": cleaned_target[0], "reference": cleaned_reference[0]}
    elif doTarget and not doReference:
        return {"target": cleaned_target[0]}
    elif not doTarget and doReference:
        return {"reference": cleaned_reference[0]}


def similarity_score(file_name, keys):
    score = sum(-200 for keyword in keys if keyword in file_name)
    score = score + sum(Levenshtein.distance(key, file_name) for key in keys)
    hhs_keys = ["v3"]
    hs_keys = ["v2", "355769", "356381", "357735", "367131", "369978", "2022C", "2022D", "2022B", "2023C", "2023D", "STD", "RelVal"]
    ls_keys = ["v1", "HLT", "CNAFARM", "Lumi", "ARM", "KIT"]
    for item in hhs_keys:
        if item in file_name:
            score = score - 75
    for item in hs_keys:
        if item in file_name:
            score = score - 50
    for item in ls_keys:
        if item in file_name:
            score = score + 30
    return score


def _parse_timeleft_to_hours(timeleft_str):
    # Expected formats: "168:00:00", "23:59:59", etc.
    parts = timeleft_str.strip().split(":")
    try:
        if len(parts) == 3:
            h = int(parts[0])
            return h
        if len(parts) == 2:
            h = int(parts[0])
            return h
    except ValueError:
        pass
    return 0


def checkProxy():
    cmd = 'voms-proxy-info'
    proc = subprocess.Popen(cmd, stderr=subprocess.PIPE, stdout=subprocess.PIPE, shell=True)
    out, err = proc.communicate()

    out_str = out.decode('utf-8', errors='ignore')
    err_str = err.decode('utf-8', errors='ignore')

    if 'Proxy not found' in err_str:
        print('WARNING: No GRID proxy found. Get one first with:')
        print('  voms-proxy-init -voms cms -rfc --valid 168:0')
        exit()

    timeLeftHours = 0
    for line in out_str.split("\n"):
        if 'timeleft' in line:
            # line example: "timeleft  : 167:59:59"
            tl = line.split()[-1]
            timeLeftHours = _parse_timeleft_to_hours(tl)

    if timeLeftHours < 24:
        print(f'WARNING: Your proxy is only valid for ~{timeLeftHours} hours. Renew it with:')
        print('  voms-proxy-init -voms cms -rfc --valid 168:0')
        exit()


def drop_different_versions(files):
    filtered_data = {}
    for file in files:
        match = re.match(r"(.*)(-v)(\d+)(__DQMIO\.root)", file)
        if match:
            base_name = match.group(1)
            version = int(match.group(3))
            if base_name not in filtered_data or version > filtered_data[base_name][1]:
                filtered_data[base_name] = (file, version)
    return [file for file, version in filtered_data.values()]


def getFileNames(Rel, GTs, sample):
    print(bcolors.OKBLUE + "Downloading the list of all DQM files..." + bcolors.ENDC)
    checkProxy()
    x509_user_proxy_path = os.popen("voms-proxy-info -path").read().strip()
    os.environ["X509_USER_PROXY"] = x509_user_proxy_path

    os.system(
        "wget -q --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY "
        "-O output_files.html "
        "\"https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/\"".format(
            Rel.split("_")[0], Rel.split("_")[1]
        )
    )

    html_path = f"/afs/cern.ch/user/{user[0]}/{user}/CMSSW_14_0_0/src/TkRelVal/output_files.html"
    with open(html_path, "r") as file:
        DQMfiles_html = file.read()

    if GTs != "":
        Rel = Rel + "_" + GTs + "-"
    else:
        Rel = Rel + "-"

    keywords = ["ZeroBias", Rel, "dataRun3"]
    pattern = r".*{}.*".format(r".*".join(map(re.escape, keywords)))

    files = []
    for line in DQMfiles_html.splitlines():
        if re.search(pattern, line):
            match = re.search(r'DQM.*?\.root', line)
            if match:
                print(f"Match found: {match.group(0)}")
                files.append(match.group(0))
        else:
            gts_parts = GTs.split('_')
            if Rel in line and "ZeroBias" in line:
                if any(gts_part in line for gts_part in gts_parts):
                    match = re.search(r'DQM.*?\.root', line)
                    if match:
                        files.append(match.group(0))

    files = drop_different_versions(files)

    scores = {name: similarity_score(name, keywords) for name in files}
    print(scores)

    if len(scores) > 2:
        # Prefer triples with similar names and same score
        for name1, name2, name3 in itertools.combinations(scores, 3):
            if "2022B" in name1 and "2022C" in name2 and "2022D" in name3:
                if scores[name1] == scores[name2] == scores[name3]:
                    r12 = difflib.SequenceMatcher(None, name1, name2).ratio()
                    r23 = difflib.SequenceMatcher(None, name2, name3).ratio()
                    r13 = difflib.SequenceMatcher(None, name1, name3).ratio()
                    if min(r12, r23, r13) > 0.9:
                        scores[name1] -= 100
                        scores[name2] -= 100
                        scores[name3] -= 100

        for name1, name2 in itertools.combinations(scores, 2):
            if "2023C" in name1 and "2023D" in name2:
                if scores[name1] == scores[name2]:
                    if difflib.SequenceMatcher(None, name1, name2).ratio() > 0.9:
                        scores[name1] -= 100
                        scores[name2] -= 100

    sorted_files = sorted(list(scores.items()), key=lambda x: x[1])[:5]

    # Keep only desired run numbers
    runnumberlist = ["355769", "356381", "357735", "367131", "369978"]
    sorted_files = [it for it in sorted_files if findRun(it[0]) in runnumberlist]

    dic = {}
    for filename, value in sorted_files:
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

    dire_tar = os.path.join(directory, findImportantRelease(tar["rootname"])[:-1] + "x", tar["label"], tar["run"], tar["sample"])
    dire_ref = os.path.join(directory, findImportantRelease(ref["rootname"])[:-1] + "x", ref["label"], ref["run"], ref["sample"])

    print(bcolors.OKGREEN + "Running the comparison..." + bcolors.ENDC)
    cmd = f"python3 start.py --refFile {os.path.join(dire_ref, ref['rootname'])} --targetFile {os.path.join(dire_tar, tar['rootname'])} --refLabel {ref['label']} --targetLabel {tar['label']} --FullPlots"
    print(cmd)
    os.system(cmd)


if __name__ == "__main__":
    url = sys.argv[1]
    output_file = "output.html"

    try:
        if not verify_kerberos_ticket():
            raise ValueError("Invalid Kerberos ticket. Please authenticate (kinit).")

        if os.path.isfile(output_file):
            os.remove(output_file)

        auth = tsgauth.oidcauth.KerbSessionAuth()
        response = requests.get(url, **auth.authparams())
        print(response)
        print(response.status_code)

        if response.status_code == 200:
            print("Successfully loaded credentials, reading the URL content...")
            html_lines = response.text.splitlines()
            with open(output_file, "w", encoding="utf-8") as file:
                for line in html_lines:
                    if "Report’s status has been changed" in line:
                        print("Encountered termination string, stopping HTML write.")
                        break
                    file.write(line + "\n")
        else:
            raise ValueError(f"Error during GET request: {response.status_code}")

    except ValueError as e:
        print(f"Error: {str(e)}")
        exit()
    except Exception as e:
        print(f"An unexpected error occurred: {str(e)}")
        exit()

    with open(output_file, "r") as file:
        html_content = file.read()

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
        print("The entries 'target' and 'target release' are not consistent:")
        print(target_values)
        exit()

    if len(reference_values) > 1:
        reference_values = filter_substring_list(reference_values)

    if len(set(reference_values)) == 1:
        reference_value = reference_values[0]
    else:
        print("The entries 'reference' and 'reference release' are not consistent:")
        print(reference_values)
        exit()

    Rel = {"target": target_value, "reference": reference_value}
    print("Releases:", Rel)

    # Extract GT if already embedded in release string; otherwise parse from HTML
    if len(Rel["target"].split("_")) > 3:
        GTs = {}
        GTs["target"] = Rel["target"].replace(
            Rel["target"].split("_")[0] + "_" + Rel["target"].split("_")[1] + "_" + Rel["target"].split("_")[2] + "_", ""
        )
        Rel["target"] = "_".join(Rel["target"].split("_")[:3])
    else:
        GTs = findGTs(html_content, doTarget=True)

    if len(Rel["reference"].split("_")) > 3:
        GTs["reference"] = Rel["reference"].replace(
            Rel["reference"].split("_")[0] + "_" + Rel["reference"].split("_")[1] + "_" + Rel["reference"].split("_")[2] + "_", ""
        )
        Rel["reference"] = "_".join(Rel["reference"].split("_")[:3])
    else:
        if "reference" not in GTs:
            GTs = findGTs(html_content, doReference=True)

    print("Releases:", Rel)
    print("Global Tags:", GTs)

    ask_to_continue()

    target_files = getFileNames(Rel["target"], GTs["target"], "ZeroBias")
    reference_files = getFileNames(Rel["reference"], GTs["reference"], "ZeroBias")

    # Keep only matching runs between reference and target
    doRazor(target_files, reference_files)

    print(bcolors.HEADER + "Target files:" + bcolors.ENDC)
    for entry_name, entry_data in target_files.items():
        print(f"{entry_name}:")
        print(f"  rootfile: {entry_data['rootname']}")
        print(f"  run: {entry_data['run']}")
        print(f"  era: {entry_data['era']}")
        print(f"  release: {entry_data['release']}")
        print(f"  sample: {entry_data['sample']}")
        print(f"  value: {entry_data['value']}\n")

    print(bcolors.HEADER + "Reference files:" + bcolors.ENDC)
    for entry_name, entry_data in reference_files.items():
        print(f"{entry_name}:")
        print(f"  rootfile: {entry_data['rootname']}")
        print(f"  run: {entry_data['run']}")
        print(f"  era: {entry_data['era']}")
        print(f"  release: {entry_data['release']}")
        print(f"  sample: {entry_data['sample']}")
        print(f"  value: {entry_data['value']}\n")

    ask_to_continue()

    directory = "/eos/project/c/cmsweb/www/tracking/validation/DATA/DQM/"

    def is_file_in_directory(file, directory):
        for root, dirs, files in os.walk(directory):
            if file in files:
                return root
        return False

    key1 = next(iter(target_files))
    key2 = next(iter(reference_files))
    dic_ref = reference_files[key2]
    dic_tar = target_files[key1]

    if dic_ref["run"] == dic_tar["run"] and dic_ref["era"] == dic_tar["era"]:
        dic_ref["label"], dic_tar["label"] = findLabel(dic_ref["release"], dic_tar["release"], dic_ref["run"])
    else:
        print("Run and/or era differ between the two files. Label assignment failed!")
        print(f"ref_run: {dic_ref['run']}  tar_run: {dic_tar['run']}")
        exit()

    print("Labels:", dic_ref["label"], dic_tar["label"])

    for ref in reference_files.values():
        ref["label"] = dic_ref["label"]
    for tar in target_files.values():
        tar["label"] = dic_tar["label"]

    ask_to_continue()

    for ref, tar in zip(reference_files.values(), target_files.values()):
        dire_tar = os.path.join(directory, findImportantRelease(tar["rootname"])[:-1] + "x", tar["label"], tar["run"], tar["sample"])
        dire_ref = os.path.join(directory, findImportantRelease(ref["rootname"])[:-1] + "x", ref["label"], ref["run"], ref["sample"])

        tar_found_root = is_file_in_directory(tar["rootname"], directory)
        if tar_found_root:
            current_tar_path = os.path.join(tar_found_root, tar["rootname"])
            desired_tar_path = os.path.join(dire_tar, tar["rootname"])
            if desired_tar_path != current_tar_path:
                print("Target file exists but under a different folder. Re-downloading (TODO: improve).")
                command = (
                    'wget -q -e robots=off --wait 1 -r -l1 -nd -np '
                    '"https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" '
                    '-A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'
                ).format(Rel["target"].split("_")[0], Rel["target"].split("_")[1], tar["rootname"])
                os.system(command)
                os.system(f'mkdir -p {dire_tar}')
                os.system(f'mv {tar["rootname"]} {dire_tar}')
            else:
                print("Target file already present.")
        else:
            print("Target file not found in EOS, downloading...")
            command = (
                'wget -q -e robots=off --wait 1 -r -l1 -nd -np '
                '"https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" '
                '-A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'
            ).format(Rel["target"].split("_")[0], Rel["target"].split("_")[1], tar["rootname"])
            os.system(command)
            os.system(f'mkdir -p {dire_tar}')
            os.system(f'mv {tar["rootname"]} {dire_tar}')

        ref_found_root = is_file_in_directory(ref["rootname"], directory)
        if ref_found_root:
            current_ref_path = os.path.join(ref_found_root, ref["rootname"])
            desired_ref_path = os.path.join(dire_ref, ref["rootname"])
            if desired_ref_path != current_ref_path:
                print("Reference file exists but under a different folder. Re-downloading (TODO: improve).")
                command = (
                    'wget -q -e robots=off --wait 1 -r -l1 -nd -np '
                    '"https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" '
                    '-A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'
                ).format(Rel["reference"].split("_")[0], Rel["reference"].split("_")[1], ref["rootname"])
                os.system(command)
                os.system(f'mkdir -p {dire_ref}')
                os.system(f'mv {ref["rootname"]} {dire_ref}')
            else:
                print("Reference file already present.")
        else:
            print("Reference file not found in EOS, downloading...")
            command = (
                'wget -q -e robots=off --wait 1 -r -l1 -nd -np '
                '"https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/CMSSW_{}_{}_x/" '
                '-A "{}" --no-check-certificate --certificate $X509_USER_PROXY --private-key $X509_USER_PROXY'
            ).format(Rel["reference"].split("_")[0], Rel["reference"].split("_")[1], ref["rootname"])
            os.system(command)
            os.system(f'mkdir -p {dire_ref}')
            os.system(f'mv {ref["rootname"]} {dire_ref}')

    arguments = [(ref, tar, directory) for ref, tar in zip(reference_files.values(), target_files.values())]
    print("Arguments:", arguments)

    num_cores = min(len(arguments), cpu_count())
    pool = Pool(processes=num_cores)
    print(f"Running comparisons in multiprocessing mode: using {num_cores} cores")
    ask_to_continue()
    pool.map(compare, arguments)
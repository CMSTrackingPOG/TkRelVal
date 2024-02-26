import json
import ROOT
import os
import subprocess
import tempfile

## this fuction trasforms list1=[1,2,3,6,8,9,10] grouping the numbers
## and making intervals --> list2=[[1,3],[6,6],[8,10]]
## this is needed to write a ~json file which is the input (-i) to brilcalc!
def group_into_intervals(numbers):
    intervals = []
    start = numbers[0]
    end = numbers[0]
    for i in range(1, len(numbers)):
        if numbers[i] == numbers[i - 1] + 1:
            end = numbers[i]
        else:
            intervals.append([start, end])
            start = numbers[i]
            end = numbers[i]
    intervals.append([start, end])
    return intervals


def findRun(filename):
    rawrun = filename.split("_")[2]
    return rawrun[-6:]


def mkJson(filename, temp_file):
    file = ROOT.TFile(filename, "read")
    print("AO")
    # print("debuggg: ", filename)
    runNum = int(findRun(filename.split("/")[-1]))
    path1 = "DQMData/Run "+str(runNum)+"/Tracking/Run summary/V0Monitoring/Lambda/n_vs_LS"
    path2 = "DQMData/Run "+str(runNum)+"/Tracking/Run summary/V0Monitoring/HIP_OOTpu_INpu/Lambda/n_vs_LS"

    # create a list of non null entries
    non_null_entries = []
    hist = file.Get(path1)
    if hist and not hist.IsZombie():
        print(("debuggg: lumi isto found @ ", path1))
        for i in range(0, hist.GetNbinsX() + 1):
            if hist.GetBinContent(i) != 0:
                non_null_entries.append(i)
        lista = group_into_intervals(non_null_entries)
    
    else:
        ## provo con un altro path, perche' gli ultimi file hanno un path diverso per questo histo!!
        hist = file.Get(path2)
        if hist and not hist.IsZombie():
            print(("debuggg: lumi isto found @ ", path2))
            for i in range(0, hist.GetNbinsX() + 1):
                if hist.GetBinContent(i) != 0:
                    non_null_entries.append(i)
            lista = group_into_intervals(non_null_entries)
        else:
            lista = None

    file.Close()

    # create a dictionary to make a string "runNumber: intervals of non null entries"
    if lista:
        result = {runNum: lista}
        result_json = json.dumps(result)
        with open(temp_file, "w") as f:
            json.dump(result_json, f)
    else:   
        print("ERROR:: no non null entries found in the histogram!")
        print("Or histogram not found!")

## brillcalc output is ~grafic, its not just the output!
## need this fuction to read the 4th line (where the number is stored)
## and i read it from a txt file, since the output of brilcalc will be store in it
def read_recorded_value(file_name):
    with open(file_name, 'r') as file:
        lines = file.readlines()
        counter = 0
        for line in lines:
            data_line = line.strip().split('|')
            if counter == 4 :
                try:
                    return float(data_line[6].strip())
                except ValueError or IndexError:
                    print("ERROR:: the luminosity value is not a number, something went wrong with lumicalc! Setting it to 0.")
                    return float(0.)
            counter = counter+1
    
 # now lets launch the command with our brand new json
def LumiCalc(filename):
    temp_file = tempfile.NamedTemporaryFile(delete=False)
    temp_json_path = temp_file.name+".json"
    temp_txt_path = temp_file.name+".txt"
    check = mkJson(filename,temp_json_path)

    with open(temp_json_path, "r") as f:
        jsondata = str(json.load(f))
        if len(jsondata) == 0:
            ## in thi case, lumi is not computed for some reason...    
            print("ERROR:: json file is empty, something went wrong with mkJson!")
            return float(0.)

    os.system("rm {}".format(temp_json_path))
    print("computing the luminosity with lumicalc, this could take a while...")
    command = "brilcalc lumi -i "+"\""+jsondata+"\""+" -u /pb >> " + temp_txt_path
    # print command
    os.system(command)
    lumiValue = read_recorded_value(temp_txt_path)
    print(("Luminosity [/pb] is: ", lumiValue))
    os.system("rm {}".format(temp_txt_path))
    return lumiValue
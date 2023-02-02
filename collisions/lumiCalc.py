import json
import ROOT
import os
import subprocess

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


def mkJson(filename):
    file = ROOT.TFile(filename, "read")
    runNum = int(findRun(filename.split("/")[-1]))
    path = "DQMData/Run "+str(runNum)+"/Tracking/Run summary/V0Monitoring/Lambda/n_vs_LS"

    # access histo
    hist = file.Get(path)

    # create a list of non null entries
    non_null_entries = []

    # loop on each bin of the hist and save non null entries
    for i in range(0, hist.GetNbinsX() + 1):
        if hist.GetBinContent(i) != 0:
            non_null_entries.append(i)

    lista = group_into_intervals(non_null_entries)

    file.Close()

    # create a dictionary to make a string "runNumber: intervals of non null entries"
    result = {runNum: lista}

    result_json = json.dumps(result)
    with open("temp.json", "w") as f:
        json.dump(result_json, f)

## brillcalc output is ~grafic, its not just the output!
## need this fuction to read the 4th line (where the number is stored)
## and i read it from a txt file, since the output of brilcalc will be store in it
def read_recorded_value(file_name):
    with open(file_name, 'r') as file:
        lines = file.readlines()
        counter = 0;
        for line in lines:
            data_line = line.strip().split('|')
            if counter == 4 :
                try:
                    recorded = float(data_line[6].strip())
                    return recorded
                except ValueError:
                    continue
            counter = counter+1
    return 0
    
 # now lets launch the command with our brand new json
def LumiCalc(filename):
    mkJson(filename)
    with open("temp.json", "r") as f:
        jsondata = str(json.load(f))

    print("computing the luminosity with lumicalc, this could take a while...")
    command = "brilcalc lumi -i "+"\""+jsondata+"\""+" -u /pb >> temp.txt"
    os.system(command)
    lumiValue = read_recorded_value("temp.txt")
    print("Luminosity [/pb] is: ", lumiValue)
    os.system("rm temp.json")
    os.system("rm temp.txt")
    return lumiValue
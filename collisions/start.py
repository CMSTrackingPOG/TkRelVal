# coding=utf-8

import ROOT
import sys
import os
from configparser import ConfigParser
import argparse
import numpy as np
import lumiCalc

def findRun(filename):
    rawrun = filename.split("_")[2]
    return rawrun[-6:]

def findSample(filename):
    rawsample = filename.split("__")
    return rawsample[1]

def findRelease(filename):
    rawrelease = filename.split("__")
    return rawrelease[2]

def findEra(filename):
    return filename.split("202")[1][1]

def difference(string1, string2):
# Split both strings into list items
    string1 = string1.split("_")
    string2 = string2.split("_")

    A = set(string1) # Store all string1 list items in set A
    B = set(string2) # Store all string2 list items in set B
 
    str_diff = B.symmetric_difference(A)
    isEmpty = (len(str_diff) == 0)
 
    if isEmpty:
    # print("No Difference. Both Strings Are Same")
        return 1
    else:
    # print("The Difference Between Two Strings: ")
        return list(str_diff)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Command line parser for starting the tracking validation repo')
    parser.add_argument('--refFile',     dest='referenceFile',     help='old release version', required = True)
    parser.add_argument('--targetFile',     dest='targetFile',     help='new release version', required = True)
    parser.add_argument('--refLabel',     dest='referenceLabel',     help='label name for the reference file. It will appear on graphs and in the folder name', required = False)
    parser.add_argument('--targetLabel',     dest='targetLabel',     help='label name for the target file. It will appear on graphs and in the folder name', required = False)
    parser.add_argument('--lumi',     dest='lumi',     help='lumi in ', required = False)
    parser.add_argument('--FullPlots',     dest='FullPlots',     help='command to produce ALL the plots', default = False, action = 'store_true', required = False)
    # parser.add_argument('--v',     dest='verbose',     help='Optional prints with retrieved infos', default = True, action = 'store_false', required = False)

    args = parser.parse_args()

    oldFileName = args.referenceFile
    newFileName = args.targetFile
    oldFile = oldFileName.split("/")[-1]
    newFile = newFileName.split("/")[-1]
    # print(oldFile)

    ## trovo il run number
    oldRun = findRun(oldFile)
    newRun = findRun(newFile)
    if newRun != oldRun :
        print("FOUND ERROR IN RUN NUMBER. THERY ARE NOT EQUAL!")
        # exit()

    ## trovo la era
    oldEra = findEra(oldFile)
    newEra = findEra(newFile)
    if newEra != oldEra :
        print("FOUND ERROR IN ERA. THERY ARE NOT EQUAL!")
        # exit()

    ## trovo il sample name
    oldSample = findSample(oldFile)
    newSample = findSample(newFile)
    if newSample != oldSample :
        print("FOUND ERROR IN SAMPLE NAME. THERY ARE NOT THE SAME!")
        # exit()
    
    ## trovo la "release" e creo in automatico il nome della cartella
    oldRelease = findRelease(oldFile)
    newRelease = findRelease(newFile)

    output = difference(oldRelease,newRelease)
    old_important_parameters = [oldRelease.split("_")[0], oldRelease.split("_")[1], oldRelease.split("_")[2], oldRelease.split("_")[3]]
    new_important_parameters = [newRelease.split("_")[0], newRelease.split("_")[1], newRelease.split("_")[2], newRelease.split("_")[3]]
    if output == 1: 
        print("ERROR, NO DIFFERENCES FOUND IN RELEASES VERSION")
    
    for param in old_important_parameters:
        if param not in output:
            ## in questo caso non cambiano parametri importanti (CMSSW, 12,3,X), quindi il cambiamento è un rereco vs prompt o pre4 vs pre5
            check = False
        else:
            ## in questo caso c'è cambiamento di release
            check = True

    ## here i want to store all the label "accepted". Dont know if it will be a feature i will use.. 
    ## i just put it there for the moment.. 
    accepted_names = ["Prompt"]
    oldLabelName = output[0]
    newLabelName = output[1]

    if args.referenceLabel is not None:
        oldLabelName = args.referenceLabel
    if args.targetLabel is not None:
        newLabelName = args.targetLabel

    if check == False:
        if args.referenceLabel is None:
            if oldLabelName not in accepted_names:
                print "Needed a label name for: ", oldFile
                oldLabelName = raw_input("Please insert a label name: ")

        if args.targetLabel is None:
            if newLabelName not in accepted_names:
                print "Needed a label name for: ", newFile
                newLabelName = raw_input("Please insert a label name: ")

        folderName = oldRun+"_"+oldSample+"_"+oldRelease.split("_")[0]+"_"+oldRelease.split("_")[1]+"_"+oldRelease.split("_")[2]+"_"+oldRelease.split("_")[3]+"_"+oldLabelName+"_vs_"+newRelease.split("_")[1]+"_"+newRelease.split("_")[2]+"_"+newRelease.split("_")[3]+"_"+newLabelName
        print(folderName)
    else :
        folderName = oldRun+"_"+oldSample+"_"+oldRelease.split("_")[0]+"_"+oldRelease.split("_")[1]+"_"+oldRelease.split("_")[2]+"_"+oldRelease.split("_")[3]+"_vs_"+newRelease.split("_")[1]+"_"+newRelease.split("_")[2]+"_"+newRelease.split("_")[3]
        print(folderName)

# Before executing the macro, which takes quite much time, I update the index.html so that i can view the plots!
# Now I search for the first "</UL>" word and insert an HREF to see the new folder in the webpage! search by line number and then insert a line
# Not the smartest way, need to work on this one day

    import subprocess

    htmlFile=("/eos/project/c/cmsweb/www/tracking/validation/DATA/index.html")
    word="</UL>"
    linenum=0
    with open(htmlFile) as myFile:
        for num, line in enumerate(myFile,1):
            if folderName in line:
                break
            else:
                if word in line:
                    linenum = num
                    break

    if linenum != 0:
        newstring = "<LI><A HREF=\""+folderName+"/index.html\">"+folderName+","+oldEra+"</A></LI>"
        rc = subprocess.call(["sed -i \'{}i \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ {}\' /eos/project/c/cmsweb/www/tracking/validation/DATA/index.html".format(linenum,newstring)], shell=True)

    lumi = str(round(float(lumiCalc.LumiCalc(oldFileName)),2))


# FROM THIS POINT I SHOLD TRANSLATE THE .SH FILE.. 
# I do not have time at this moment, but i will one day.
# for now, i just use the sh

    if args.FullPlots == True:
        rc = subprocess.call(["./makeValidationPlots.sh", oldRun,oldFileName,oldLabelName,newFileName,newLabelName,folderName,oldEra,lumi,"true"])
    else:
        rc = subprocess.call(["./makeValidationPlots.sh", oldRun,oldFileName,oldLabelName,newFileName,newLabelName,folderName,oldEra,lumi])

 






# coding=utf-8

import ROOT
import sys
import os
from configparser import ConfigParser
import argparse
import numpy as np
from collisions.lumiCalc import *
from common.utils import *


def new_html_line(html_file,release,newline,val):
    # with file_lock:
    with open(html_file, "r") as file:
        lines = file.readlines()
    
    ## look for the range of line i can watch, depending on the val value
    ## in fact, alca validation are in the first part of the html file, while release validations are the second part
    ## i want the two columns to be almast independent, so i can add the new line in the right place
    
    start = len(lines)
    end = len(lines)
    if val == "AlCa":
        for i, line in enumerate(lines):
            if line.strip().startswith("<div class=\"right-column\">"):
                start = i
            if line.strip().startswith("</div>"):
                end = i
                ## qui mi devo fermare al primo </div> che trovo, perche' e' quello che chiude la prima colonna
                break
    elif val == "Release":
        for i, line in enumerate(lines):
            if line.strip().startswith("<div class=\"left-column\">"):
                start = i
            if line.strip().startswith("</div>"):
                end = i
                ## qui invece se mi fermo al primo, non trovo lo start.. vado avanti, niente break!!

    if start == len(lines):
        print "ERROR:: start not found in the hmlt file! Something went wrong"
        sys.exit(1)
    
    ## i dont want to add new lines if they are already there
    selected_lines = [line.strip() for i, line in enumerate(lines) if i >= start and i < end]
    if newline not in selected_lines:
        found_chapter = False
        last_index = 0

        for i, line in enumerate(lines):
            if start < i < end:
                if line.strip().startswith("<OL>{}".format(release)):
                    found_chapter = True
                if line.strip() == "</UL>":
                    if found_chapter == True:
                        lines.insert(i, "                    {}\n".format(newline))
                        break
                    else:
                        last_index = i

        if last_index != 0 and found_chapter == False:
            lines.insert(last_index, "                </UL>\n")
            lines.insert(last_index, "                    {}\n".format(newline))
            lines.insert(last_index, "                <UL>\n")
            lines.insert(last_index, "            <OL>{}\n".format(release))
            lines.insert(last_index, "            <BR>\n")
            lines.insert(last_index, "            <BR>\n")
            lines.insert(last_index, "            <BR>\n")
            lines.insert(last_index, "            </OL>\n")
            lines.insert(last_index, "                </UL>\n")

        if last_index == 0:
            print "ERROR:: last </UL> not found in the hmlt file! Something went wrong"
            sys.exit(1)

        with open(html_file, "w") as file:
            file.write("".join(lines))


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
    print(oldFile)

    ## find the run number
    oldRun = findRun(oldFile)
    newRun = findRun(newFile)
    if newRun != oldRun or newRun is None or oldRun is None:
        print("ERROR:: FOUND ERROR IN RUN NUMBER. THERY ARE NOT EQUAL!")
        # exit()


    ## find the era
    oldEra = findEra(oldFile, "2022")
    newEra = findEra(newFile, "2022")
    if oldEra not in ["A", "B", "C", "D", "E", "F"] or newEra not in ["A", "B", "C", "D", "E", "F"]:
        print("WARNING:: ERA NOT FOUNDED!")
        newEra = "X"
        oldEra = "X"
    if newEra != oldEra :
        print("WARNING:: FOUND ERROR IN ERA. THERY ARE NOT EQUAL!")


    ## find the sample name
    oldSample = findSample(oldFile)
    newSample = findSample(newFile)
    if newSample != oldSample or newSample is None or oldSample is None:
        print("ERROR:: FOUND ERROR IN SAMPLE NAME. THERY ARE NOT THE SAME!")
        # exit()
    

    ## find the "release" name
    oldRelease = findRelease(oldFile)
    newRelease = findRelease(newFile)

    ## find the label name, only if it is not given as input. If it is given, it will be used
    ## if args.referenceLabel is None and/or args.targetLabel is None they are hendled as input, so everything is fine
    print("OLD RELEASE: {}".format(oldRelease))
    print("NEW RELEASE: {}".format(newRelease))

    oldLabelName, newLabelName = findLabel(oldRelease, newRelease, oldRun, args.referenceLabel, args.targetLabel)
    folderName = make_folder_name(oldRun, oldSample, oldRelease, oldLabelName, newRelease, newLabelName)
    

    # ## need to make this as a function, so that i can use it somewhere else
    # output = difference(oldRelease,newRelease)
    # old_important_parameters = [oldRelease.split("_")[0], oldRelease.split("_")[1], oldRelease.split("_")[2], oldRelease.split("_")[3].split("-")[0]]
    # new_important_parameters = [newRelease.split("_")[0], newRelease.split("_")[1], newRelease.split("_")[2], newRelease.split("_")[3].split("-")[0]]
    # if output == None: 
    #     print("WARNING:: NO DIFFERENCES FOUND IN RELEASES VERSION")
    
    # for param in old_important_parameters:
    #     if param not in output:
    #         ## in questo caso non cambiano parametri importanti (CMSSW, 12,3,X), quindi il cambiamento è un rereco vs prompt o pre4 vs pre5
    #         check = False
    #     else:
    #         ## in questo caso c'è cambiamento di release
    #         check = True

    # ## here i want to store all the label "accepted". Dont know if it will be a feature i will use.. 
    # ## i just put it there for the moment.. 

    # filtered_output = filter_list(output)
    # del output

    # try:
    #     oldLabelName = filtered_output[0]
    #     newLabelName = filtered_output[1]
    # except IndexError:
    #     oldLabelName = "old"
    #     newLabelName = "new"

    # if args.referenceLabel is not None:
    #     oldLabelName = args.referenceLabel
    # if args.targetLabel is not None:
    #     newLabelName = args.targetLabel

    # if check == False:
    #     if args.referenceLabel is None:
    #         print "ref Label is: ", oldLabelName
    #         change_name = raw_input("Do you want to change it? (yes/no): ")
    #         if change_name.lower() == "yes" or change_name.lower() == "y":
    #             oldLabelName = raw_input("Please insert a label name: ")
    #     if args.targetLabel is None:
    #         print "target Label is: ", newLabelName
    #         change_name = raw_input("Do you want to change it? (yes/no): ")
    #         if change_name.lower() == "yes" or change_name.lower() == "y":
    #             newLabelName = raw_input("Please insert a label name: ")

    #     folderName = oldRun+"_"+oldSample+"_"+oldRelease.split("_")[0]+"_"+oldRelease.split("_")[1]+"_"+oldRelease.split("_")[2]+"_"+oldRelease.split("_")[3]+"_"+oldLabelName+"_vs_"+newRelease.split("_")[1]+"_"+newRelease.split("_")[2]+"_"+newRelease.split("_")[3]+"_"+newLabelName
    #     print(folderName)
    # else :
    #     folderName = oldRun+"_"+oldSample+"_"+oldRelease.split("_")[0]+"_"+oldRelease.split("_")[1]+"_"+oldRelease.split("_")[2]+"_"+oldRelease.split("_")[3]+"_vs_"+newRelease.split("_")[1]+"_"+newRelease.split("_")[2]+"_"+newRelease.split("_")[3]
    #     print(folderName)

# Before executing the macro, which takes quite much time, I update the index.html so that i can view the plots!
# Now I search for the first "</UL>" word and insert an HREF to see the new folder in the webpage! search by line number and then insert a line
# Not the smartest way, need to work on this one day

    htmlFile="/eos/project/c/cmsweb/www/tracking/validation/DATA/index.html"
    chap = oldRelease.split("_")[0] + " " + oldRelease.split("_")[1]+"_"+oldRelease.split("_")[2]+"_X"
    newstring = "<LI><A HREF=\""+folderName+"/index.html\">"+folderName+","+oldEra+"</A></LI>"

    ## check if afs is abulla or magdy
    ## in the first case, pass "Release" as a parameter, in the second case, pass "AlCa"
    current_path = os.getcwd()
    if "abulla" not in current_path:
        new_html_line(htmlFile, chap, newstring, "AlCa")
    else:
        new_html_line(htmlFile, chap, newstring, "Release")

    ## now i need to check if the lumi is the same. If it is not, i need to print a warning and use the old one
    oldLumi = str(round(float(LumiCalc(oldFileName)),2))
    newLumi = str(round(float(LumiCalc(newFileName)),2))

    if oldLumi != newLumi:
        print("WARNING:: FOUND DIFFERENT LUMINOSITY VALUES: "+oldLumi+" vs "+newLumi)
        print("WARNING:: USING THE OLD LUMINOSITY VALUE: "+oldLumi)
    lumi = oldLumi

# FROM THIS POINT I SHOULD TRANSLATE THE .SH FILE.. 
# I do not have time at this moment, but i will one day.
# for now, i just use the sh
    import subprocess
    os.chdir('/afs/cern.ch/user/a/abulla/CMSSW_9_4_8/src/TkRelVal/collisions')
    if args.FullPlots == True:
        rc = subprocess.call(["./makeValidationPlots.sh", oldRun,oldFileName,oldLabelName,newFileName,newLabelName,folderName,oldEra,lumi,"true"])
    else:
        rc = subprocess.call(["./makeValidationPlots.sh", oldRun,oldFileName,oldLabelName,newFileName,newLabelName,folderName,oldEra,lumi])
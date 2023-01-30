# coding=utf-8

import ROOT
import sys
import os
from configparser import ConfigParser
import argparse
import numpy as np

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
  
#   print('The programs runs successfully.')


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Command line parser for starting the tracking validation repo')
    parser.add_argument('--refFile',     dest='referenceFile',     help='old release version', required = True)
    parser.add_argument('--targetFile',     dest='targetFile',     help='new release version', required = True)
    parser.add_argument('--refLabel',     dest='referenceLabel',     help='label name for the reference file. It will appear on graphs and in the folder name', required = False)
    parser.add_argument('--targetLabel',     dest='targetLabel',     help='label name for the target file. It will appear on graphs and in the folder name', required = False)
    parser.add_argument('--FullPlots',     dest='FullPlots',     help='command to produce ALL the plots', default = False, action = 'store_true', required = False)
    # parser.add_argument('--v',     dest='verbose',     help='Optional prints with retrieved infos', default = True, action = 'store_false', required = False)
    # parser.add_argument('--BName',     dest='BName',     help='Branch name of TNtuple where weights are stored. Default is "w".', default = 'w', required = False)


    args = parser.parse_args()

    oldFile = args.referenceFile
    newFile = args.targetFile
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

# STILL TO DO. "PROMPT" VA BENE INSERIRLO NELLE DIFFERENZA, MA AL POSTO DI V11 VORREI INSERIRE PER ESEMPIO "RERECO". 
# HO BISOGNO DI UNA LISTA DI "CAMBIAMENTI" IMPORTANTI CHE POSSONO ESSERE MESSI, TIPO PROMPT, E NEGLI ALTR CASI METTERE DA TERMINALE

# DA QUI DI FATTO POTREI TRADURRE makeValidationPlot.sh MA FACCIO PRIMA AD ESEGUIRLO.
# Eventualmente, lo posso usare anche solo per la creazione delle cartelle e di alcuni index.html.. Per poi eseguire il root qui
# In questo modo posso aggiungere ulteriori opzioni direttamente da qui.. Probabilmente è più comodo(?) per luminosità e altre cazzate

    import subprocess

    # Before executing the macro, which takes quite much time, I update the index.html so that i can view the plots!
    # Now I search for the first "</UL>" word and insert an HREF to see the new folder in the webpage! search by line number and then insert a line
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
        newstring = "<LI><A HREF=\""+folderName+"/index.html\">"+folderName+","+oldEra
        rc = subprocess.call(["sed -i \'{}i \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ {}\' /eos/project/c/cmsweb/www/tracking/validation/DATA/index.html".format(linenum,newstring)], shell=True)

    lumi = "0"

    if args.FullPlots == True:
        rc = subprocess.call(["./makeValidationPlotsPROV.sh", oldRun,oldFile,oldLabelName,newFile,newLabelName,folderName,oldEra,lumi,"true"])
    else:
        rc = subprocess.call(["./makeValidationPlotsPROV.sh", oldRun,oldFile,oldLabelName,newFile,newLabelName,folderName,oldEra])

 
# STILL TO DO:
# - Toccare ReleaseComparison.cpp per le robe grafiche che ci sono nel todo, quelle che rimangono
# - Luminosità. C'è da capire ancora se utilizzare il grafico di V0 o se affidarsi a lumicalc col json di mia.. In ogni caso lo 
# calcolerei qui e glielo passerei come parametro probabilmente.. magari non direttamente qui ma passandolo a make bla bla 

# Script più intelligente per l'html file esterno, in modo da fare "capitoli" e orindarli in boh ordine alfabetico o qualcosa di simile?





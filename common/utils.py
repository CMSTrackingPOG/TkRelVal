def findRun(filename):
    rawrun = filename.split("_")[2]
    try: 
        return rawrun[-6:]
    except IndexError:
        return None

def findSample(filename):
    rawsample = filename.split("__")
    try:
        return rawsample[1]
    except IndexError:
        return None

def findRelease(filename):
    rawrelease = filename.split("__")
    try:
        return rawrelease[2]
    except IndexError:
        return None

def findEra(filename, year="2022"):
    try:
        split = filename.split(year)[1][0]
        splits = filename.split(year)
        if len(splits) > 2:
            for i in range(1,len(splits)):
                chance = splits[i][0]
                if chance.isupper():
                    return chance
        else:
            return split
    except IndexError:
        try:
            return findEra(filename, "2023")
        except IndexError:
            return None

def findImportantRelease(filename):
    rawrelease = filename.split("__")
    try:
        return rawrelease[2].split("_")[0] + "_" + rawrelease[2].split("_")[1] + "_" + rawrelease[2].split("_")[2] + "_" + rawrelease[2].split("_")[3].split("-")[0]
    except IndexError:
        return None


def findLabel(oldRelease, newRelease, oldRun, referenceLabel=None, targetLabel=None):
    output = difference(oldRelease, newRelease)
    old_important_parameters = [oldRelease.split("_")[0], oldRelease.split("_")[1], oldRelease.split("_")[2], oldRelease.split("_")[3].split("-")[0]]
    new_important_parameters = [newRelease.split("_")[0], newRelease.split("_")[1], newRelease.split("_")[2], newRelease.split("_")[3].split("-")[0]]
    
    if output is None:
        print("WARNING:: NO DIFFERENCES *AT ALL* FOUND IN RELEASES VERSION")

    ##also removing duplicates
    filtered_output = list(set(filter_list(output)))
    del output

    try:
        if filtered_output[0] in oldRelease:
            oldLabelName = filtered_output[0] 
            newLabelName = filtered_output[1]
        else:
            oldLabelName = filtered_output[1] 
            newLabelName = filtered_output[0]
    except IndexError:
        oldLabelName = "old"
        newLabelName = "new"

    if referenceLabel is not None:
        oldLabelName = referenceLabel
    if targetLabel is not None:
        newLabelName = targetLabel

    if referenceLabel is None:
        print("ref Label for {} is: {}".format(oldRelease,oldLabelName))
        change_name = raw_input("Do you want to change it? if yes type it, otherwise no: ").lower()
        # if change_name.lower() != "no" or change_name.lower() != "n" or change_name.lower() != "":
        if len(change_name)>3:
            oldLabelName = change_name
    if targetLabel is None:
        print("target Label for {} is: {}".format(newRelease,newLabelName))
        change_name = raw_input("Do you want to change it? if yes type it, otherwise type no: ").lower()
        # if change_name.lower() != "no" or change_name.lower() != "n" or change_name.lower() != "":
        if len(change_name)>3:
            newLabelName = change_name

    return oldLabelName, newLabelName


def make_folder_name(oldRun, oldSample, oldRelease, oldLabelName, newRelease, newLabelName):
    ## if the label is just one word (eg pre4), then just add it to the folder name
    ## if it is something more complex (eg 13_0_4_pre4) then i have to split it!
    if len(oldLabelName.split("_")) > 1:
        ## in this case, i have a complex label, so the folder is just run + sample + label
        if len(newLabelName.split("_")) > 1:
            folderName = oldRun+"_"+oldSample+"_"+oldLabelName+"_vs_"+newLabelName
        else:
            folderName = oldRun+"_"+oldSample+"_"+oldLabelName+"_vs_"+newRelease.split("_")[1]+"_"+newRelease.split("_")[2]+"_"+newRelease.split("_")[3]+"_"+newLabelName
    else:
        folderName = oldRun+"_"+oldSample+"_"+oldRelease.split("_")[0]+"_"+oldRelease.split("_")[1]+"_"+oldRelease.split("_")[2]+"_"+oldRelease.split("_")[3]+"_"+oldLabelName+"_vs_"+newRelease.split("_")[1]+"_"+newRelease.split("_")[2]+"_"+newRelease.split("_")[3]+"_"+newLabelName

    return folderName


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
        return None
    else:
    # print("The Difference Between Two Strings: ")
        return list(str_diff)


def filter_list(output):
    accepted = ["prompt", "Prompt", "rereco", "Rereco", "ReReco", "pre", "Pre"]
    ## split all the element in output in a single word and check if it is in accepted. If not, remove it from output
    new_list = []
    for it in output:
        if len(it.split("-")) > 0:
            new_list.extend(it.split("-"))
        elif len(it.split("_")) > 0:
            new_list.extend(it.split("_"))

    filtered = [item for item in new_list if any(term in item for term in accepted)]
    del new_list
    return filtered
import json
import ROOT
import os
import subprocess
import tempfile


# --------------------------------------------------
# Group consecutive lumi sections into intervals
# Example:
# [1,2,3,6,8,9,10] -> [[1,3],[6,6],[8,10]]
# --------------------------------------------------
def group_into_intervals(numbers):
    if not numbers:
        return []

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


# --------------------------------------------------
# Extract run number from filename
# --------------------------------------------------
def findRun(filename):
    rawrun = filename.split("_")[2]
    return rawrun[-6:]


# --------------------------------------------------
# Build temporary JSON for brilcalc
# --------------------------------------------------
def mkJson(filename, temp_file):

    print("[INFO] Opening ROOT file:", filename)

    file = ROOT.TFile(filename, "READ")
    runNum = int(findRun(filename.split("/")[-1]))

    path1 = f"DQMData/Run {runNum}/Tracking/Run summary/V0Monitoring/Lambda/n_vs_LS"
    path2 = f"DQMData/Run {runNum}/Tracking/Run summary/V0Monitoring/HIP_OOTpu_INpu/Lambda/n_vs_LS"

    non_null_entries = []
    hist = file.Get(path1)

    if hist and not hist.IsZombie():
        print("[DEBUG] Lumi histogram found at:", path1)
    else:
        hist = file.Get(path2)
        if hist and not hist.IsZombie():
            print("[DEBUG] Lumi histogram found at:", path2)

    if hist and not hist.IsZombie():
        for i in range(0, hist.GetNbinsX() + 1):
            if hist.GetBinContent(i) != 0:
                non_null_entries.append(i)

        lista = group_into_intervals(non_null_entries)
    else:
        lista = None

    file.Close()

    if lista:
        result = {runNum: lista}
        with open(temp_file, "w") as f:
            json.dump(result, f)
        return True
    else:
        print("[ERROR] No non-zero entries found or histogram missing.")
        return False


# --------------------------------------------------
# Read luminosity value from brilcalc output
# --------------------------------------------------
def read_recorded_value(file_name):

    with open(file_name, 'r') as file:
        lines = file.readlines()

        for counter, line in enumerate(lines):
            data_line = line.strip().split('|')

            if counter == 4:
                try:
                    return float(data_line[6].strip())
                except (ValueError, IndexError):
                    print("[ERROR] Luminosity value is not numeric. brilcalc output malformed.")
                    return 0.0

    print("[ERROR] Could not find luminosity line in brilcalc output.")
    return 0.0


# --------------------------------------------------
# Run brilcalc
# --------------------------------------------------
def LumiCalc(filename):

    temp_file = tempfile.NamedTemporaryFile(delete=False)
    temp_json_path = temp_file.name + ".json"
    temp_txt_path = temp_file.name + ".txt"

    success = mkJson(filename, temp_json_path)

    if not success:
        return 0.0

    with open(temp_json_path, "r") as f:
        jsondata = json.dumps(json.load(f))

    if len(jsondata) == 0:
        print("[ERROR] JSON file is empty. mkJson failed.")
        return 0.0

    os.remove(temp_json_path)

    print("[INFO] Computing luminosity with brilcalc (this may take a while)...")

    command = (
        f'brilcalc lumi -i "{jsondata}" -u /pb -c web >> {temp_txt_path}'
    )

    print("[DEBUG] Executing command:", command)

    try:
        subprocess.run(command, shell=True, check=True)
        lumiValue = read_recorded_value(temp_txt_path)

    except subprocess.CalledProcessError as e:
        print("[ERROR] brilcalc execution failed:", e)
        lumiValue = 0.0

    except Exception as e:
        print("[ERROR] Unexpected error:", e)
        lumiValue = 0.0

    print("[INFO] Luminosity [/pb]:", lumiValue)

    os.remove(temp_txt_path)

    return lumiValue
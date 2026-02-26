#!/bin/bash
######################################
# Script to download ROOT files from CMS DQM RelValData repository based on specified criteria.
# Usage: ./getFiles.sh <web_dir> <run> <rel> <sample> [add_key] [optional_arg]
# Example: ./getFiles.sh CMSSW_16_0_x 392294 pre1 ZeroBias 
# notes:
# - This script is designed to download ROOT files from the CMS DQM RelValData repository based
#     on specified criteria such as run number, sample type, and release version.
# - Uses `curl` to fetch the directory listing and filter files using `grep` and `sed`. Wget is not used directly due to the need for authentication and handling of the file list.
# - Future alternatives: files do live in /eos/cms/store/relval/ but it's a bit more complicated to get them.
######################################
# -----------------------------
# Arguments
# -----------------------------
web_dir=${1}        # es: CMSSW_16_0_x
run=${2}            # es: 392294
rel=${3}            # es: pre1
sample=${4}         # es: ZeroBias
add_key=${5:-.*}
optional_arg=${6:-.*}

## check certificate and proxy
if ! voms-proxy-info -exists; then
    echo "No valid proxy found. Please create a proxy using 'voms-proxy-init command before running this script."
    exit 1
fi
export X509_USER_PROXY=$(voms-proxy-info -path)

BASE="https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/${web_dir}/"

echo "Getting sample: $sample"
echo "From: $BASE"

PATTERN="${run}.*${sample}.*${rel}.*${add_key}.*${optional_arg}.*root"

# -----------------------------
# Download files
# -----------------------------
curl -s --insecure \
     --cert "$X509_USER_PROXY" \
     --key  "$X509_USER_PROXY" \
     "$BASE" \
| grep -oE "href=['\"][^'\"]+\.root['\"]" \
| sed -E "s/href=['\"]//;s/['\"]$//" \
| grep -E "$PATTERN" \
| xargs -r -I{} -P 6 bash -c '
    echo "Downloading https://cmsweb.cern.ch{}"
    curl -L --insecure \
         --cert "'"$X509_USER_PROXY"'" \
         --key  "'"$X509_USER_PROXY"'" \
         -O "https://cmsweb.cern.ch{}"
    sleep 1
'

# -----------------------------
# File organization
# -----------------------------
if [ "$sample" == "Cosmics" ] ; then

    if ls *${sample}*.root >/dev/null 2>&1; then
        mkdir -p cosmics
        mv *${sample}*.root cosmics/
    else
        echo "File not found for sample: $sample"
    fi

else

    if ls *${run}*${sample}*.root >/dev/null 2>&1; then

        TARGET="DQM/${web_dir}/${rel}/${run}/${sample}"
        mkdir -p "$TARGET"

        mv -f *${run}*${sample}*.root "$TARGET"/ 2>/dev/null

    else
        echo "File not found for sample: $sample"
    fi

fi
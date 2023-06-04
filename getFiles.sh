#!/bin/bash

# Parameters passed from command line
web_dir=${1}  # ref dir of DQM
run=${2}  # specify what run you want to download
rel=${3}  # old release to check against (e.g. pre1)
sample=${4}
add_key=${5:-*}
optional_arg=${6:-*}

echo "Getting sample: $sample"

wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/$web_dir/" -A "*$run*$sample*$rel*$add_key*$optional_arg*root" --no-check-certificate --certificate ~/.globus/myCert.pem --private-key ~/.globus/myCert.key


if [ ${sample} == "Cosmics" ] ; then
    if ls *${sample}*.root 1> /dev/null 2>&1; then
        mv *${sample}*.root cosmics/
    else
        echo "File not found for sample: $sample"
    fi
else
    if ls *${run}*${sample}*.root 1> /dev/null 2>&1; then
        cd collisions/DQM
        if [ ! -d ${web_dir} ] ; then    
            mkdir ${web_dir}
        fi 
        cd ${web_dir}
        relval=${rel}
        if [ ! -d ${rel} ] ; then    
            mkdir ${rel}
        fi
        cd ${rel}
        if [ ! -d ${run} ] ; then    
            mkdir ${run}
        fi
        cd ${run}
        if [ ! -d ${sample} ] ; then 
            mkdir ${sample}
        fi
        cd ../../../../../

        mv *${run}*${sample}*.root collisions/DQM/${web_dir}/${rel}/${run}/${sample}/
    else
        echo "File not found for sample: $sample"
    fi
fi
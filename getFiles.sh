#! /bin/bash

#Parameters passed from command line
web_dir=$1 #ref dir of DQM
#web_dir2=$2 #new directory of DQM files on web
run=$2 #specify what run you want to download 
rel_old=$3 #old release to check against (e.g. pre1)
rel_new=$4 #new release (e.q. pre2)
sample=$5

echo "Getting sample: " ${sample}

wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/${web_dir}/" -A "*${run}*${sample}*${rel_old}*root, *${run}*${sample}*${rel_new}*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem

if [ ${sample} == "Cosmics" ] ; then
    mv *${sample}*.root cosmics/
else
    cd collisions/DQM
    if [ ! -d ${web_dir} ] ; then    
        mkdir ${web_dir}
    fi 
    cd ${web_dir}
    relval=${rel_old}"_vs_"${rel_new}
    if [ ! -d ${relval} ] ; then    
        mkdir ${relval}
    fi
    cd ${relval}
    if [ ! -d ${run} ] ; then    
        mkdir ${run}
    fi
    cd ${run}
    if [ ! -d ${sample} ] ; then 
        mkdir ${sample}
    fi
    cd ../../../../../

    mv *${run}*${sample}*.root collisions/DQM/${web_dir}/${relval}/${run}/${sample}/
fi
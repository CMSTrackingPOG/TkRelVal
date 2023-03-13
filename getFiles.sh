#! /bin/bash

#Parameters passed from command line
web_dir=$1 #ref dir of DQM
#web_dir2=$2 #new directory of DQM files on web
run=$2 #specify what run you want to download 
rel=$3 #old release to check against (e.g. pre1)
# rel_new=$4 #new release (e.q. pre2)
sample=$4
add_key=$5

echo "Getting sample: " ${sample}

if [ -z "$add_key" ]; then
# argomento 5 non passato! 
  wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/${web_dir}/" -A "*${run}*${sample}*${rel}*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem
else
# argomento 5 passato
  wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/${web_dir}/" -A "*${run}*${sample}*${rel}*${add_key}*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem
fi

if [ ${sample} == "Cosmics" ] ; then
    mv *${sample}*.root cosmics/
else
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
fi
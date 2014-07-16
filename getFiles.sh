#! /bin/bash

#Parameters passed from command line
web_dir1=$1 #ref dir of DQM
web_dir2=$2 #new directory of DQM files on web
run=$3 #specify what run you want to download 
rel_old=$4 #old release to check against (e.g. pre1)
rel_new=$5 #new release (e.q. pre2)


for sample in Jet MinimumBias
do
#Get all the necessary files
  wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/$web_dir1/" -A "*$run*$sample*$rel_old*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem

#wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/$web_dir2/" -A "*$run*$sample*$rel_new*frozenHLT*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem

  wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/$web_dir2/" -A "*$run*$sample*$rel_new*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem

done




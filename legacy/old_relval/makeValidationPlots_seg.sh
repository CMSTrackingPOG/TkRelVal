#! /bin/bash

#Parameters passed from command line
#get_files=$1 #if true, get all files from web
#web_dir=$2 #directory of DQM files on web
run=$1 #specify what run you want to download 
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)
#rmroot=$6 #remove root files if true
set_scale=$4 #set scale for compilation

#if [ "$get_files" = true ] ; then

#Get all the necessary files
#wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/$web_dir/" -A "*$run*$rel_old*root, *$run*$rel_new*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem

#fi 

#Make a local copy of the plots here
if [ -d RunComparison ] ; then
    rm -r RunComparison
    mkdir RunComparison
elif [ ! -d RunComparison ] ; then
    mkdir RunComparison
fi

#Do this for all matching data sets
for sample in MET #SingleMu #SingleElectron JetHT MinimumBias MET Tau SinglePhoton DoubleElectron
  do

  #Set the files to be used for this sample
  if [ -f *"$sample"*"$rel_old"* ] && [ -f *"$sample"*"$rel_new"* ] ; then
      refFile=$(ls *"$sample"*"$rel_old"*)
      newFile=$(ls *"$sample"*"$rel_new"*)
      release=CMSSW_"$rel_new"_"$sample"_Run_"$run"
                                             
      #Creat directory for webpage
     # if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/test_kmcdermo/$release ] ; then    
#	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/test_kmcdermo/$release 
 #     fi                            
      if [ -d $release ] ; then
	  rm -r $release
	  mkdir $release
      elif [ ! -d $release ] ; then
	  mkdir $release
      fi

    
      #test locally
      #if [ ! -d $release ] ; then
      #	  mkdir $release
      #fi

      echo "Analyzing $refFile and $newFile in $release"                                                                                   

      #Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
      root -b -q -l "RunValidationComparison.C("\"$refFile\",\"$newFile\",\"$set_scale\"")"   
#     root -b -q -l "RunValidationComparison.C("\"$refFile\",\"$newFile\"")"   

      #Copy all the plots to the directory to be published
#      cp RunComparison/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/test_kmcdermo/$release
      cp RunComparison/*.png $release #test locally

      #Run the perl script to generate html to publish plots nicely to web
      #cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/test_kmcdermo/$release
      cd $release #test locally
      ../diow.pl -t "$release validation" -c 3 -icon 200                 
      cd -                                                    
      
      #remove plots for next iteration
      rm RunComparison/*.png
  fi

done

#Delete the cumbersome root files if not needed
if [ "$rmroot" = true ] ; then
    rm -rf *.root
fi

#! /bin/bash

#Parameters passed from command line
#get_files=$1 #if true, get all files from web
#web_dir=$2 #directory of DQM files on web
run=$1 #specify what run you want to download 
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)
#rmroot=$4 #remove root files if true

#if [ "${get_files}" = true ] ; then

#Get all the necessary files
#wget -e robots=off --wait 1 -r -l1 -nd -np "https://cmsweb.cern.ch/dqm/relval/data/browse/ROOT/RelValData/${web_dir}/" -A "*${run}*${rel_old}*root, *${run}*${rel_new}*root" --no-check-certificate --certificate ~/.globus/usercert.pem --private-key ~/.globus/userkey.pem

#fi 

#Make a local copy of the plots here
if [ -d RunComparison ] ; then
    rm -r RunComparison
    mkdir RunComparison
    mkdir RunComparison/generalTracks
    mkdir RunComparison/highPurityTracks
elif [ ! -d RunComparison ] ; then
    mkdir RunComparison
    mkdir RunComparison/generalTracks
    mkdir RunComparison/highPurityTracks
fi

#scaled and unscaled

#Do this for all matching data sets
#for scale in 0 1 3
for scale in 3 # it should be noted that the preferred scaled from RelVal from 720 onward is 3 --> scale all histos to nTracks ratio  
do 
  
  for sample in MinimumBias Jet #SingleMu #SingleElectron JetHT MinimumBias MET Tau SinglePhoton DoubleElectron
    do

      refFile=$(ls *"${run}"*"${sample}"*"${rel_old}"*)
      newFile=$(ls *"${run}"*"${sample}"*"${rel_new}"*)
      release=CMSSW_"${rel_new}"_vs_"${rel_old}"_Run_"${run}"_"${sample}"
	#release=CMSSW_"${rel_new}"_"${sample}"_Run_"${run}"
      
      if [ "${scale}" == "0" ] ; then
	  release+="_unscaled"
      elif [ "${scale}" == "1" ] ; then
	  release+="_scaledPerHisto"
      fi
      
      #Creat directory for webpage
      if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} ] ; then    
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
      fi                            

      #subdirectory for generalTracks
      if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks ] ; then    
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks 
      else 
	  rm -r /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks 
      fi                            

      #subdirectory for highPurityTracks
      if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks ] ; then    
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks 
      else
	  rm -r /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks 
      fi                                  

      #test locally
      #if [ ! -d $release ] ; then
      #	  mkdir $release
      #fi
      
      echo "Analyzing ${refFile} and ${newFile} in ${release}"                                                                                   
      
      #Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
      root -b -q -l "RunValidationComparison.C("\"${refFile}\",\"${newFile}\",\"${scale}\"")"   
      
      #Copy all the plots to the directory to be published
      cp RunComparison/generalTracks/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks
      cp RunComparison/highPurityTracks/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks
      #cp RunComparison/*.png $release #test locally

      #remove plots for next iteration
      rm RunComparison/generalTracks/*.png
      rm RunComparison/highPurityTracks/*.png
      
      #generate index.html files on the fly for release directory
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
      ../genSubDir.sh "${release}"
      cd -

      #Run the perl script to generate html to publish plots nicely to web --> run for both genTracks and highPurity
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks
      #cd $release #test locally
      ../../diow.pl -t "${release} generalTracks validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks
      ../../diow.pl -t "${release} highPurityTracks validation" -c 3 -icon 200                 
      cd -                                                    

  done
done

#Delete the cumbersome root files if not needed
#if [ "${rmroot}" = true ] ; then
#    rm -rf *.root
#fi

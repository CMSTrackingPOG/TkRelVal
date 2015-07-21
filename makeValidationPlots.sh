#! /bin/bash

#Parameters passed from command line
run=$1 #specify what run you want to download 
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)
#rmroot=$4 #remove root files if true

#Make a local copy of the plots here
if [ -d RunComparison ] ; then
    rm -r RunComparison
    mkdir RunComparison
    mkdir RunComparison/SiStrip
    mkdir RunComparison/generalTracks
    mkdir RunComparison/generalTracks/GeneralProperties
    mkdir RunComparison/generalTracks/HitProperties
    mkdir RunComparison/highPurityTracks
    mkdir RunComparison/highPurityTracks/GeneralProperties
    mkdir RunComparison/highPurityTracks/HitProperties
elif [ ! -d RunComparison ] ; then
    mkdir RunComparison
    mkdir RunComparison/SiStrip
    mkdir RunComparison/generalTracks
    mkdir RunComparison/generalTracks/GeneralProperties
    mkdir RunComparison/generalTracks/HitProperties
    mkdir RunComparison/highPurityTracks
    mkdir RunComparison/highPurityTracks/GeneralProperties
    mkdir RunComparison/highPurityTracks/HitProperties
fi

#scaled and unscaled --> see ReleaseComparison.cpp for explaination of scales

#Do this for all matching data sets
#for scale in 0 1 3
for scale in 3 # it should be noted that the preferred scaled from RelVal from 720 onward is 3 --> scale all histos to nTracks ratio  
do 
  
  for sample in MinimumBias Jet #SingleMu #SingleElectron MET Tau SinglePhoton DoubleElectron
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
      
      #Creat directories for webpage
      if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} ] ; then    
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/GeneralProperties 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/HitProperties
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/GeneralProperties 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/HitProperties
      else
	  rm -r /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/GeneralProperties 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/HitProperties
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/GeneralProperties 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/HitProperties
      fi                            
      
      echo "Analyzing ${refFile} and ${newFile} in ${release}"                                                                                   
      
      #Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
      root -b -q -l "runValidationComparison.C("\"${refFile}\",\"${newFile}\",\"${scale}\"")"   
      
      #Copy all the plots to the directory to be published
      cp RunComparison/SiStrip/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
      cp RunComparison/generalTracks/GeneralProperties/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/GeneralProperties
      cp RunComparison/generalTracks/HitProperties/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/HitProperties
      cp RunComparison/highPurityTracks/GeneralProperties/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/GeneralProperties
      cp RunComparison/highPurityTracks/HitProperties/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/HitProperties

      #remove plots for next iteration
      rm RunComparison/SiStrip/*.png
      rm RunComparison/generalTracks/GeneralProperties/*.png
      rm RunComparison/generalTracks/HitProperties/*.png
      rm RunComparison/highPurityTracks/GeneralProperties/*.png
      rm RunComparison/highPurityTracks/HitProperties/*.png
      
      #generate index.html files on the fly for release directory
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
      ../genSubDir.sh "${release}" 
      cd -
      
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks
      ../../genSubSubDir.sh "${release}" "generalTracks"
      cd -
      
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks
      ../../genSubSubDir.sh "${release}" "highPurityTracks"
      cd -

      #Run the perl script to generate html to publish plots nicely to web --> run for both genTracks and highPurity, and SiStrip
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
      ../../diow.pl -t "${release} SiStrip Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/GeneralProperties
      ../../../diow.pl -t "${release} generalTracks General Properties Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/generalTracks/HitProperties
      ../../../diow.pl -t "${release} generalTracks Hit Properties Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/GeneralProperties
      ../../../diow.pl -t "${release} highPurityTracks General Properties Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/highPurityTracks/HitProperties
      ../../../diow.pl -t "${release} highPurityTracks Hit Properties Validation" -c 3 -icon 200                 
      cd -                                                    

  done
done

#Delete the cumbersome root files if not needed
#if [ "${rmroot}" = true ] ; then
#    rm -rf *.root
#fi

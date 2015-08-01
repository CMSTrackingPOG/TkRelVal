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
    mkdir RunComparison/genTks
    mkdir RunComparison/genTks/GenProps
    mkdir RunComparison/genTks/HitProps
    mkdir RunComparison/HPTks
    mkdir RunComparison/HPTks/GenProps
    mkdir RunComparison/HPTks/HitProps
elif [ ! -d RunComparison ] ; then
    mkdir RunComparison
    mkdir RunComparison/SiStrip
    mkdir RunComparison/genTks
    mkdir RunComparison/genTks/GenProps
    mkdir RunComparison/genTks/HitProps
    mkdir RunComparison/HPTks
    mkdir RunComparison/HPTks/GenProps
    mkdir RunComparison/HPTks/HitProps
fi

# to keep the same format, need to change all root files with "MinimumBias" to "MinBias"
rename MinimumBias MinBias *MinimumBias*.root

#scaled and unscaled --> see ReleaseComparison.cpp for explaination of scales

#Do this for all matching data sets
#for scale in 0 1 3
for scale in 3 # it should be noted that the preferred scaled from RelVal from 720 onward is 3 --> scale all histos to nTracks ratio  
do 
  
  for sample in MinBias Jet #SingleMu #SingleElectron MET Tau SinglePhoton DoubleElectron
    do

      refFile=$(ls *"${run}"*"${sample}"*"${rel_old}"*)
      newFile=$(ls *"${run}"*"${sample}"*"${rel_new}"*)
      release=CMSSW_750_vs_750pre6_"${run}"_"${sample}"
	#release=CMSSW_"${rel_new}"_"${sample}"_Run_"${run}"
      
      if [ "${scale}" == "0" ] ; then
	  release+="_unscaled"
      elif [ "${scale}" == "1" ] ; then
	  release+="_scaledPerHisto"
      fi
      
      #Create directories for webpage
      if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} ] ; then    
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/GenProps 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/HitProps
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/GenProps 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/HitProps
      else
	  rm -r /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/GenProps 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/HitProps
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/GenProps 
	  mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/HitProps
      fi                            
      
      echo "Analyzing ${refFile} and ${newFile} in ${release}"                                                                                   
      
      #Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
      root -b -q -l "runValidationComparison.C("\"${refFile}\",\"${newFile}\",\"${scale}\"")"   
      
      #Copy all the plots to the directory to be published
      cp RunComparison/SiStrip/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
      cp RunComparison/genTks/GenProps/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/GenProps
      cp RunComparison/genTks/HitProps/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/HitProps
      cp RunComparison/HPTks/GenProps/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/GenProps
      cp RunComparison/HPTks/HitProps/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/HitProps

      #remove plots for next iteration
      rm RunComparison/SiStrip/*.png
      rm RunComparison/genTks/GenProps/*.png
      rm RunComparison/genTks/HitProps/*.png
      rm RunComparison/HPTks/GenProps/*.png
      rm RunComparison/HPTks/HitProps/*.png
      
      #generate index.html files on the fly for release directory
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
      ../genSubDir.sh "${release}" 
      cd -
      
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks
      ../../genSubSubDir.sh "${release}" "genTks"
      cd -
      
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks
      ../../genSubSubDir.sh "${release}" "HPTks"
      cd -

      #Run the perl script to generate html to publish plots nicely to web --> run for both genTracks and highPurity, and SiStrip
      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/SiStrip
      ../../diow.pl -t "${release} SiStrip Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/GenProps
      ../../../diow.pl -t "${release} genTks General Properties Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/genTks/HitProps
      ../../../diow.pl -t "${release} genTks Hit Properties Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/GenProps
      ../../../diow.pl -t "${release} HPTks General Properties Validation" -c 3 -icon 200                 
      cd -                                                    

      cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}/HPTks/HitProps
      ../../../diow.pl -t "${release} HPTks Hit Properties Validation" -c 3 -icon 200                 
      cd -                                                    

  done
done

#Delete the cumbersome root files if not needed
#if [ "${rmroot}" = true ] ; then
#    rm -rf *.root
#fi

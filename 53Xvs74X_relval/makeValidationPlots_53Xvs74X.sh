#! /bin/bash

#Parameters passed from command line
run=$1 #specify what run you want to download 
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)

if [ -d RunComparison ] ; then
    rm -r RunComparison
    mkdir RunComparison
elif [ ! -d RunComparison ] ; then
    mkdir RunComparison
fi

#scaled and unscaled

#Do this for all matching data sets
#for scale in 0 1 3
for scale in 3 # it should be noted that the preferred scaled from RelVal from 720 onward is 3 --> scale all histos to nTracks ratio  
do 
  
  for sample in JetHT #MinimumBias
    do

    #Set the files to be used for this sample
    if [ -f *"${sample}"*"${rel_old}"* ] && [ -f *"${sample}"*"${rel_new}"* ] ; then
	
	refFile=$(ls *"${sample}"*"${rel_old}"*)
	newFile=$(ls *"${sample}"*"${rel_new}"*)

	if [ "${sample}" == "DoubleMu" ] ; then
	    release=CMSSW_"${rel_new}"_vs_"${rel_old}"_"Zmumu"_Run_"${run}"_correctalgo
	else
	    release=CMSSW_"${rel_new}"_vs_"${rel_old}"_"${sample}"_Run_"${run}"_etaonly_zero
	fi

      #Creat directory for webpage
	if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} ] ; then    
	    mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
	fi                            
	    
      #test locally
      #if [ ! -d $release ] ; then
      #	  mkdir $release
      #fi
	    
	echo "Analyzing ${refFile} and ${newFile} in ${release}"                                                                                   
	    
      #Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
	root -b -q -l "RunValidationComparison_53Xvs74X.C("\"${refFile}\",\"${newFile}\",\"${scale}\"")"   
	    
      #Copy all the plots to the directory to be published
	cp RunComparison/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
      #cp RunComparison/*.png $release #test locally
	    
      #Run the perl script to generate html to publish plots nicely to web
	cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
      #cd $release #test locally
	../diow.pl -t "${release} validation" -c 3 -icon 200                 
	cd -                                                    
	
      #remove plots for next iteration
	rm RunComparison/*.png
    fi
  done
done

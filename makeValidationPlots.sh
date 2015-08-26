#! /bin/bash

#Parameters passed from command line
run=$1 #specify what run you want to download 
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)
#rmroot=$4 #remove root files if true

#scaled and unscaled --> see ReleaseComparison.cpp for explaination of scales

#Do this for all matching data sets
for sample in MinBias #Jet #SingleMu SingleEl #MET Tau SinglePhoton DoubleElectron
do
    
    refFile=$(ls *"${run}"*"${sample}"*"${rel_old}"*)
    newFile=$(ls *"${run}"*"${sample}"*"${rel_new}"*)
    release=CMSSW_"${rel_new}"_vs_"${rel_old}"_"${run}"_"${sample}"

    directory=/afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
    
    #Create directories for webpage
    if [ ! -d ${directory} ] ; then    
	mkdir ${directory} 

	mkdir ${directory}/SiStrip
	for subdir in TEC TIB TID TOB 
	do
	    mkdir ${directory}/SiStrip/${subdir}
	done

	mkdir ${directory}/genTks 
	for subdir in GenProps HitProps TkBuilding
	do
	    mkdir ${directory}/genTks/${subdir}
	done
	
	mkdir ${directory}/HPTks 
	for subdir in GenProps HitProps
	do
	    mkdir ${directory}/HPTks/${subdir}
	done
	
	mkdir ${directory}/dEdx
	for subdir in PO SO SP HitInfo
	do
	    mkdir ${directory}/dEdx/${subdir}
	done

	mkdir ${directory}/PV
	for subdir in Alignment offlinePVs
	do
	    mkdir ${directory}/PV/${subdir}
	done

	mkdir ${directory}/PackCand
	for subdir in MatchedTks lostTks
	do
	    mkdir ${directory}/PackCand/${subdir}
	done
    else
	rm -r ${directory} 
	mkdir ${directory} 

	mkdir ${directory}/SiStrip
	for subdir in TEC TIB TID TOB 
	do
	    mkdir ${directory}/SiStrip/${subdir}
	done

	mkdir ${directory}/genTks 
	for subdir in GenProps HitProps TkBuilding
	do
	    mkdir ${directory}/genTks/${subdir}
	done
	
	mkdir ${directory}/HPTks 
	for subdir in GenProps HitProps
	do
	    mkdir ${directory}/HPTks/${subdir}
	done
	
	mkdir ${directory}/dEdx
	for subdir in PO SO SP HitInfo
	do
	    mkdir ${directory}/dEdx/${subdir}
	done

	mkdir ${directory}/PV
	for subdir in Alignment offlinePVs
	do
	    mkdir ${directory}/PV/${subdir}
	done

	mkdir ${directory}/PackCand
	for subdir in MatchedTks lostTks
	do
	    mkdir ${directory}/PackCand/${subdir}
	done
    fi                            
    
    echo "Analyzing ${refFile} and ${newFile} in ${release}"                                                                                   
    #Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
    root -b -q -l "runValidationComparison.C("\"${refFile}\",\"${newFile}\",\"${directory}\"")"   
    
    #generate index.html files on the fly for release directory
    cd ${directory}
    ../genSubDir.sh "${release}" 
    cd -
    
    cd ${directory}/SiStrip
    ../../genSubSubDirSiStrip.sh "${release}" 
    cd -                                                    

    cd ${directory}/genTks
    ../../genSubSubDirTk.sh "${release}" "genTks"
    cd -
    
    cd ${directory}/HPTks
    ../../genSubSubDirTk.sh "${release}" "HPTks"
    cd -

    cd ${directory}/dEdx
    ../../genSubSubDirdEdx.sh "${release}" 
    cd -

    cd ${directory}/PV
    ../../genSubSubDirPV.sh "${release}" 
    cd -

    cd ${directory}/PackCand
    ../../genSubSubDirPackCand.sh "${release}" 
    cd -

    # now make pretty plots on webpage with perl script
    cd ${directory}/SiStrip/TEC
    ../../../diow.pl -t "${release} SiStrip TEC Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/SiStrip/TIB
    ../../../diow.pl -t "${release} SiStrip TIB Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/SiStrip/TID
    ../../../diow.pl -t "${release} SiStrip TID Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/SiStrip/TOB
    ../../../diow.pl -t "${release} SiStrip TOB Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/genTks/GenProps
    ../../../diow.pl -t "${release} genTks General Properties Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/genTks/HitProps
    ../../../diow.pl -t "${release} genTks Hit Properties Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/genTks/TkBuilding
    ../../../diow.pl -t "${release} genTks Track Building Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/HPTks/GenProps
    ../../../diow.pl -t "${release} HPTks General Properties Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/HPTks/HitProps
    ../../../diow.pl -t "${release} HPTks Hit Properties Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/dEdx/PO
    ../../../diow.pl -t "${release} dEdx DQMHarm2PO Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/dEdx/SO
    ../../../diow.pl -t "${release} dEdx DQMHarm2SO Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/dEdx/SP
    ../../../diow.pl -t "${release} dEdx DQMHarm2SP Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/dEdx/HitInfo
    ../../../diow.pl -t "${release} dEdx HitInfo Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/PV/Alignment
    ../../../diow.pl -t "${release} OfflinePV Alignment Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/PV/offlinePVs
    ../../../diow.pl -t "${release} OfflinePV Primary Vertices Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/PackCand/MatchedTks
    ../../../diow.pl -t "${release} Packed Candidate Matched Tracks Validation" -c 3 -icon 200                 
    cd -                                                    

    cd ${directory}/PackCand/lostTks
    ../../../diow.pl -t "${release} Packed Candidate Lost Tracks Validation" -c 3 -icon 200                 
    cd -                                                    

done

#Delete the cumbersome root files if not needed
#if [ "${rmroot}" = true ] ; then
#    rm -rf *.root
#fi

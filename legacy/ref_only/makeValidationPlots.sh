#! /bin/sh

#Parameters passed from command line

run=256869
sample=JetHT

file=DQM_V0001_R000256869__HLTPhysics__CMSSW_7_4_12_patch4-2015_10_06_HLTnewconditions0_74X_dataRun2_HLTValidation_Candidate_2015_10_05_11_13_00-v1__HLT_DQMIO.root
release=CMSSW_7412p4_HLTnewcond_vs_HLTref_${sample}

directory=/afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}

#Create directories for webpage
if [ ! -d ${directory} ] ; then    
    mkdir ${directory} 

    for subdir in TEC TIB TID TOB 
    do
	mkdir -p ${directory}/SiStrip/${subdir}_lin
	mkdir -p ${directory}/SiStrip/${subdir}_log
    done

    for subdir in GenProps HitProps TkBuilding
    do
	mkdir -p ${directory}/genTks/${subdir}_lin
	mkdir -p ${directory}/genTks/${subdir}_log
    done
    
    for subdir in GenProps HitProps
    do
	mkdir -p ${directory}/HPTks/${subdir}_lin
	mkdir -p ${directory}/HPTks/${subdir}_log
    done
    
    for subdir in PO SO SP HitInfo
    do
	mkdir -p ${directory}/dEdx/${subdir}_lin
	mkdir -p ${directory}/dEdx/${subdir}_log
    done

    for subdir in Alignment offlineBS offlinePVs
    do
	mkdir -p ${directory}/PV/${subdir}_lin
	mkdir -p ${directory}/PV/${subdir}_log
    done

    for subdir in MatchedTks LostTks
    do
	mkdir -p ${directory}/PackCand/${subdir}_lin
	mkdir -p ${directory}/PackCand/${subdir}_log
    done
else
    rm -r ${directory} 
    mkdir ${directory} 

    for subdir in TEC TIB TID TOB 
    do
	mkdir -p ${directory}/SiStrip/${subdir}_lin
	mkdir -p ${directory}/SiStrip/${subdir}_log
    done

    for subdir in GenProps HitProps TkBuilding
    do
	mkdir -p ${directory}/genTks/${subdir}_lin
	mkdir -p ${directory}/genTks/${subdir}_log
    done
    
    for subdir in GenProps HitProps
    do
	mkdir -p ${directory}/HPTks/${subdir}_lin
	mkdir -p ${directory}/HPTks/${subdir}_log
    done
    
    for subdir in PO SO SP HitInfo
    do
	mkdir -p ${directory}/dEdx/${subdir}_lin
	mkdir -p ${directory}/dEdx/${subdir}_log
    done

    for subdir in Alignment offlineBS offlinePVs
    do
	mkdir -p ${directory}/PV/${subdir}_lin
	mkdir -p ${directory}/PV/${subdir}_log
    done

    for subdir in MatchedTks LostTks
    do
	mkdir -p ${directory}/PackCand/${subdir}_lin
	mkdir -p ${directory}/PackCand/${subdir}_log
    done
fi                            

echo "Analyzing ${file} in ${release}"   

#Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
root -b -q -l "runValidationComparison.C("\"${file}\",\"${run}\",\"${directory}\"")"   

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
for subdir in TEC TIB TID TOB 
do
    for scale in lin log
    do 
	cd ${directory}/SiStrip/${subdir}_${scale}
	../../../diow.pl -t "${release} SiStrip ${subdir} Validation (${scale})" -c 3 -icon 200    
	cd --
    done
done

for subdir in GenProps HitProps TkBuilding
do
    for scale in lin log
    do 
	cd ${directory}/genTks/${subdir}_${scale}
	../../../diow.pl -t "${release} genTks ${subdir} Validation (${scale})" -c 3 -icon 200  
	cd --
    done
done

for subdir in GenProps HitProps
do
    for scale in lin log
    do 
	cd ${directory}/HPTks/${subdir}_${scale}
	../../../diow.pl -t "${release} HPTks ${subdir} Validation (${scale})" -c 3 -icon 200 
	cd --
    done
done

for subdir in PO SO SP HitInfo
do
    for scale in lin log
    do 
	cd ${directory}/dEdx/${subdir}_${scale}
	../../../diow.pl -t "${release} dEdx ${subdir} Validation (${scale})" -c 3 -icon 200                 
	cd --
    done
done

for subdir in offlinePVs offlineBS Alignment
do
    for scale in lin log
    do 
	cd ${directory}/PV/${subdir}_${scale}
	../../../diow.pl -t "${release} OfflinePV ${subdir} Validation (${scale})" -c 3 -icon 200  
	cd --
    done
done

for subdir in MatchedTks LostTks
do
    for scale in lin log
    do 
	cd ${directory}/PackCand/${subdir}_${scale}
	../../../diow.pl -t "${release} Packed Candidate ${subdir} Validation (${scale})" -c 3 -icon 200
	cd --
    done
done


#! /bin/sh

#Parameters passed from command line
run=$1 #specify run number
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)
sample=$4 #Jet, JetHT, MinBias, SingleMu, SingleEl, ZeroBias
full=${5:false} # if true, do all plots, otherwise, just essential plots

refFile=$(ls *"${run}"*"${sample}"*"${rel_old}"*)
newFile=$(ls *"${run}"*"${sample}"*"${rel_new}"*)
release=CMSSW_8024_PRnewco_vs_8025_PRref_"${run}"_"${sample}"
#release=CMSSW_"${rel_new}"_vs_"${rel_old}"_"${run}"_"${sample}"

directory=/afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}

#Create directories for webpage
if [ ! -d ${directory} ] ; then    
    mkdir ${directory} 
else
    rm -r ${directory} 
    mkdir ${directory} 
fi                            

for subdir in offline #pixel
do
    mkdir -p ${directory}/PV_HPTks/${subdir}_lin
    mkdir -p ${directory}/PV_HPTks/${subdir}_log
done

for subdir in TEC TIB TID TOB 
do
    mkdir -p ${directory}/SiStrip/${subdir}_lin
    mkdir -p ${directory}/SiStrip/${subdir}_log
done

for subdir in GenProps HitProps HitEff PU TkBuilding LSan
do
    mkdir -p ${directory}/genTks/${subdir}_lin
    mkdir -p ${directory}/genTks/${subdir}_log
done

for subdir in GenProps HitProps PU LSan
do
    mkdir -p ${directory}/HPTks_dzPV0p1/${subdir}_lin
    mkdir -p ${directory}/HPTks_dzPV0p1/${subdir}_log
done

for subdir in GenProps HitProps PU LSan
do
    mkdir -p ${directory}/HPTks_0to1/${subdir}_lin
    mkdir -p ${directory}/HPTks_0to1/${subdir}_log
done

for subdir in GenProps HitProps HitEff PU LSan
do
    mkdir -p ${directory}/HPTks_gt1/${subdir}_lin
    mkdir -p ${directory}/HPTks_gt1/${subdir}_log
done

for subdir in PO SO SP HitInfo
do
    mkdir -p ${directory}/dEdx/${subdir}_lin
    mkdir -p ${directory}/dEdx/${subdir}_log
done

for subdir in Alignment offlineBS offlinePVs
do
    mkdir -p ${directory}/OfflinePV/${subdir}_lin
    mkdir -p ${directory}/OfflinePV/${subdir}_log
done

for subdir in Ks Ks_Lxy16 Lambda Lambda_Lxy16
do
    mkdir -p ${directory}/V0/${subdir}_lin
    mkdir -p ${directory}/V0/${subdir}_log
done

for subdir in MatchedTks LostTks
do
    mkdir -p ${directory}/PackCand/${subdir}_lin
    mkdir -p ${directory}/PackCand/${subdir}_log
done

echo "Analyzing ${refFile} and ${newFile} in ${release}"   

#Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
root -b -q -l "runValidationComparison.C("\"${refFile}\",\"${newFile}\",\"${directory}\",\"${full}\"")"   

#generate index.html files on the fly for release directory
cd ${directory}
../genSubDir.sh "${release}" 
cd -

cd ${directory}/PV_HPTks
../../genSubSubDirPV_HPTks.sh "${release}" 
cd -                                                    

cd ${directory}/SiStrip
../../genSubSubDirSiStrip.sh "${release}" 
cd -                                                    

cd ${directory}/genTks
../../genSubSubDirTk.sh "${release}" "genTks"
cd -

cd ${directory}/HPTks_dzPV0p1
../../genSubSubDirTk.sh "${release}" "HPTks_dzPV0p1"
cd -

cd ${directory}/HPTks_0to1
../../genSubSubDirTk.sh "${release}" "HPTks_0to1"
cd -

cd ${directory}/HPTks_gt1
../../genSubSubDirTk.sh "${release}" "HPTks_gt1"
cd -

cd ${directory}/dEdx
../../genSubSubDirdEdx.sh "${release}" 
cd -

cd ${directory}/OfflinePV
../../genSubSubDirOfflinePV.sh "${release}" 
cd -

cd ${directory}/V0
../../genSubSubDirV0.sh "${release}" 
cd -

cd ${directory}/PackCand
../../genSubSubDirPackCand.sh "${release}" 
cd -

# now make pretty plots on webpage with perl script

for subdir in offline #pixel
do
    for scale in lin log
    do 
	cd ${directory}/PV_HPTks/${subdir}_${scale}
	../../../diow.pl -t "${release} Tracking PV HP Tracks, 0 < pT < 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 -icon 200    
	cd --
    done
done

for subdir in TEC TIB TID TOB 
do
    for scale in lin log
    do 
	cd ${directory}/SiStrip/${subdir}_${scale}
	../../../diow.pl -t "${release} SiStrip ${subdir} Collisions Validation (${scale})" -c 3 -icon 200    
	cd --
    done
done

for subdir in GenProps HitProps HitEff PU TkBuilding LSan
do
    for scale in lin log
    do 
	cd ${directory}/genTks/${subdir}_${scale}
	../../../diow.pl -t "${release} genTks ${subdir} Collisions Validation (${scale})" -c 3 -icon 200  
	cd --
    done
done

for subdir in GenProps HitProps PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_dzPV0p1/${subdir}_${scale}
	../../../diow.pl -t "${release} HPTks, dz PV 0 < p < 1 ${subdir} Collisions Validation (${scale})" -c 3 -icon 200 
	cd --
    done
done

for subdir in GenProps HitProps PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_0to1/${subdir}_${scale}
	../../../diow.pl -t "${release} HPTks, 0 < pT < 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 -icon 200 
	cd --
    done
done

for subdir in GenProps HitProps HitEff PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_gt1/${subdir}_${scale}
	../../../diow.pl -t "${release} HPTks, pT > 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 -icon 200 
	cd --
    done
done

for subdir in PO SO SP HitInfo
do
    for scale in lin log
    do 
	cd ${directory}/dEdx/${subdir}_${scale}
	../../../diow.pl -t "${release} dEdx ${subdir} Collisions Validation (${scale})" -c 3 -icon 200                 
	cd --
    done
done

for subdir in offlinePVs offlineBS Alignment
do
    for scale in lin log
    do 
	cd ${directory}/OfflinePV/${subdir}_${scale}
	../../../diow.pl -t "${release} OfflinePV ${subdir} Collisions Validation (${scale})" -c 3 -icon 200  
	cd --
    done
done

for subdir in Ks Ks_Lxy16 Lambda Lambda_Lxy16
do
    for scale in lin log
    do 
	cd ${directory}/V0/${subdir}_${scale}
	../../../diow.pl -t "${release} V0 Monitoring ${subdir} Collisions Validation (${scale})" -c 3 -icon 200
	cd --
    done
done

for subdir in MatchedTks LostTks
do
    for scale in lin log
    do 
	cd ${directory}/PackCand/${subdir}_${scale}
	../../../diow.pl -t "${release} Packed Candidate ${subdir} Collisions Validation (${scale})" -c 3 -icon 200
	cd --
    done
done

#!/bin/bash

#Parameters passed from command line
run=$1 #specify run number
refFile=$2
refLabel=$3
newFile=$4
newLabel=$5
folderName=$6
era=$7
lumi=${8:-0}
full=${9:false} # if true, do all plots, otherwise, just essential plots

# directory=/eos/user/a/abulla/www/public/Physics/tracking/validation/DATA/${release}
directory=/eos/project/c/cmsweb/www/tracking/validation/DATA/${folderName}

## Se lumi = 0, ovvero non l'ho presa dal py, --> prendiamola da brillcalc direi

#Create directories for webpage
if [ ! -d ${directory} ] ; then    
    mkdir ${directory} 
else
    rm -i -rf ${directory} 
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

for subdir in GenProps HitProps HitEff HitEffAll PU TkBuilding LSan
do
    mkdir -p ${directory}/genTks/${subdir}_lin
    mkdir -p ${directory}/genTks/${subdir}_log
done

for subdir in GenProps HitProps HitEff HitEffAll HitEffSL HitEffAllSL PU LSan
do
    mkdir -p ${directory}/HPTks_dzPV0p1/${subdir}_lin
    mkdir -p ${directory}/HPTks_dzPV0p1/${subdir}_log
done

for subdir in GenProps HitProps PU LSan
do
    mkdir -p ${directory}/HPTks_0to1/${subdir}_lin
    mkdir -p ${directory}/HPTks_0to1/${subdir}_log
done

for subdir in GenProps HitProps HitEff HitEffAll HitEffBX HitEffSL HitEffAllSL PU LSan
do
    mkdir -p ${directory}/HPTks_gt1/${subdir}_lin
    mkdir -p ${directory}/HPTks_gt1/${subdir}_log
done

for subdir in PO SO SP HitInfo
do
    mkdir -p ${directory}/dEdx/${subdir}_lin
    mkdir -p ${directory}/dEdx/${subdir}_log
done

for subdir in Alignment ResPV ResOtherV offlineBS offlinePVs
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

echo "Analyzing ${refFile} and ${newFile} in ${folderName}"   

#Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
root -b -q -l "runValidationComparisonPROV.C("\"${refFile}\",\"${refLabel}\",\"${newFile}\",\"${newLabel}\",\"${directory}\",\"${era}\",${lumi},\"${full}\"")"   

#generate index.html files on the fly for release directory
cd ${directory}
../afscode/genSubDir.sh 
cd -

cd ${directory}/PV_HPTks
../../afscode/genSubSubDirPV_HPTks.sh
cd -                                                    

cd ${directory}/SiStrip
../../afscode/genSubSubDirSiStrip.sh
cd -                                                    

cd ${directory}/genTks
../../afscode/genSubSubDirTk.sh "${release}" "genTks"
cd -

cd ${directory}/HPTks_dzPV0p1
../../afscode/genSubSubDirTk.sh "${release}" "HPTks_dzPV0p1"
cd -

cd ${directory}/HPTks_0to1
../../afscode/genSubSubDirTk.sh "${release}" "HPTks_0to1"
cd -

cd ${directory}/HPTks_gt1
../../afscode/genSubSubDirTk.sh "${release}" "HPTks_gt1"
cd -

cd ${directory}/dEdx
../../afscode/genSubSubDirdEdx.sh 
cd -

cd ${directory}/OfflinePV
../../afscode/genSubSubDirOfflinePV.sh
cd -

cd ${directory}/V0
../../afscode/genSubSubDirV0.sh
cd -

cd ${directory}/PackCand
../../afscode/genSubSubDirPackCand.sh
cd -

# now make pretty plots on webpage with perl script

for subdir in offline #pixel
do
    for scale in lin log
    do 
	cd ${directory}/PV_HPTks/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} Tracking PV HP Tracks, 0 < pT < 1 GeV ${subdir} Collisions Validation (${scale})" -c 3    
	cd --
    done
done

for subdir in TEC TIB TID TOB 
do
    for scale in lin log
    do 
	cd ${directory}/SiStrip/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} SiStrip ${subdir} Collisions Validation (${scale})" -c 3    
	cd --
    done
done

for subdir in GenProps HitProps HitEff HitEffAll PU TkBuilding LSan
do
    for scale in lin log
    do 
	cd ${directory}/genTks/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} genTks ${subdir} Collisions Validation (${scale})" -c 3  
	cd --
    done
done

for subdir in GenProps HitProps HitEff HitEffAll HitEffSL HitEffAllSL PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_dzPV0p1/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} HPTks, dz PV 0 < p < 1 ${subdir} Collisions Validation (${scale})" -c 3 
	cd --
    done
done

for subdir in GenProps HitProps PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_0to1/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} HPTks, 0 < pT < 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 
	cd --
    done
done

for subdir in GenProps HitProps HitEff HitEffAll HitEffBX HitEffSL HitEffAllSL PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_gt1/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} HPTks, pT > 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 
	cd --
    done
done

for subdir in PO SO SP HitInfo
do
    for scale in lin log
    do 
	cd ${directory}/dEdx/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} dEdx ${subdir} Collisions Validation (${scale})" -c 3                 
	cd --
    done
done

for subdir in Alignment ResPV ResOtherV offlinePVs offlineBS
do
    for scale in lin log
    do 
	cd ${directory}/OfflinePV/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} OfflinePV ${subdir} Collisions Validation (${scale})" -c 3  
	cd --
    done
done

for subdir in Ks Ks_Lxy16 Lambda Lambda_Lxy16
do
    for scale in lin log
    do 
	cd ${directory}/V0/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} V0 Monitoring ${subdir} Collisions Validation (${scale})" -c 3 
	cd --
    done
done

for subdir in MatchedTks LostTks
do
    for scale in lin log
    do 
	cd ${directory}/PackCand/${subdir}_${scale}
	../../../afscode/diow.pl -t "${release} Packed Candidate ${subdir} Collisions Validation (${scale})" -c 3 
	cd --
    done
done
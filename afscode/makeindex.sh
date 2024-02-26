folderName=$(basename "$PWD")
directory=/eos/project/c/cmsweb/www/tracking/validation/DATA/${folderName}

#generate index.html files on the fly for release directory
cd ${directory}
../afscode/genSubDir.sh
cp ../afscode/style.css .
cd -

cd ${directory}/PV_HPTks
../../afscode/genSubSubDirPV_HPTks.sh
cp ../../afscode/style.css .
cd -                                                    

cd ${directory}/SiStrip
../../afscode/genSubSubDirSiStrip.sh
cp ../../afscode/style.css .
cd -                                                    

cd ${directory}/genTks
../../afscode/genSubSubDirTk.sh "${release}" "genTks"
cp ../../afscode/style.css .
cd -

cd ${directory}/HPTks_dzPV0p1
../../afscode/genSubSubDirTk.sh "${release}" "HPTks_dzPV0p1"
cp ../../afscode/style.css .
cd -

cd ${directory}/HPTks_0to1
../../afscode/genSubSubDirTk.sh "${release}" "HPTks_0to1"
cp ../../afscode/style.css .
cd -

cd ${directory}/HPTks_gt1
../../afscode/genSubSubDirTk.sh "${release}" "HPTks_gt1"
cp ../../afscode/style.css .
cd -

cd ${directory}/dEdx
../../afscode/genSubSubDirdEdx.sh 
cp ../../afscode/style.css .
cd -

cd ${directory}/OfflinePV
../../afscode/genSubSubDirOfflinePV.sh
cp ../../afscode/style.css .
cd -

for subdir in HIP_OOTpu_INpu HIP_OOTpu_noINpu HIP_noOOTpu_INpu
do
    cd ${directory}/V0/${subdir}
    ../../../afscode/genSubSubDirV0.sh
    cp ../../../afscode/style.css .
    cd -
done

cd ${directory}/PackCand
../../afscode/genSubSubDirPackCand.sh
cp ../../afscode/style.css .
cd -

# now make pretty plots on webpage with perl script
# i dont use perl because i prefer the filter and my personal .php!
# if you prefer perl just comment the cp command and de comment the diow.pl !

for subdir in offline #pixel
do
    for scale in lin log
    do 
	cd ${directory}/PV_HPTks/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} Tracking PV HP Tracks, 0 < pT < 1 GeV ${subdir} Collisions Validation (${scale})" -c 3    
    cp ../../../afscode/index.php .
	cd --
    done
done

for subdir in TEC TIB TID TOB 
do
    for scale in lin log
    do 
	cd ${directory}/SiStrip/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} SiStrip ${subdir} Collisions Validation (${scale})" -c 3   
    cp ../../../afscode/index.php . 
	cd --
    done
done

for subdir in GenProps HitProps HitEff HitEffAll PU TkBuilding LSan
do
    for scale in lin log
    do 
	cd ${directory}/genTks/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} genTks ${subdir} Collisions Validation (${scale})" -c 3  
    cp ../../../afscode/index.php . 
	cd --
    done
done

for subdir in GenProps HitProps HitEff HitEffAll HitEffSL HitEffAllSL PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_dzPV0p1/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} HPTks, dz PV 0 < p < 1 ${subdir} Collisions Validation (${scale})" -c 3 
    cp ../../../afscode/index.php . 
	cd --
    done
done

for subdir in GenProps HitProps PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_0to1/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} HPTks, 0 < pT < 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 
    cp ../../../afscode/index.php . 
	cd --
    done
done

for subdir in GenProps HitProps HitEff HitEffAll HitEffBX HitEffSL HitEffAllSL PU LSan
do
    for scale in lin log
    do 
	cd ${directory}/HPTks_gt1/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} HPTks, pT > 1 GeV ${subdir} Collisions Validation (${scale})" -c 3 
    cp ../../../afscode/index.php . 
	cd --
    done
done

for subdir in PO SO SP HitInfo
do
    for scale in lin log
    do 
	cd ${directory}/dEdx/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} dEdx ${subdir} Collisions Validation (${scale})" -c 3     
    cp ../../../afscode/index.php .             
	cd --
    done
done

for subdir in Alignment ResPV ResOtherV offlinePVs offlineBS
do
    for scale in lin log
    do 
	cd ${directory}/OfflinePV/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} OfflinePV ${subdir} Collisions Validation (${scale})" -c 3  
    cp ../../../afscode/index.php . 
	cd --
    done
done


cd ${directory}/V0/
cp ../../afscode/index.php .
cd --
for subdir in HIP_OOTpu_INpu HIP_OOTpu_noINpu HIP_noOOTpu_INpu
do
    for ssubdir in Ks Ks_Lxy16 Lambda Lambda_Lxy16
    do
        for scale in lin log
        do 
        cd ${directory}/V0/${subdir}/${ssubdir}_${scale}
        # ../../../afscode/diow.pl -t "${release} V0 Monitoring ${subdir} Collisions Validation (${scale})" -c 3
        cp ../../../../afscode/index.php .  
        cd --
        done
    done
done

for subdir in MatchedTks LostTks
do
    for scale in lin log
    do 
	cd ${directory}/PackCand/${subdir}_${scale}
	# ../../../afscode/diow.pl -t "${release} Packed Candidate ${subdir} Collisions Validation (${scale})" -c 3 
    cp ../../../afscode/index.php . 
	cd --
    done
done
#! /bin/sh

#Parameters passed from command line
run=$1 #specify run number
rel_old=$2 #old release to check against (e.g. pre1)
rel_new=$3 #new release (e.q. pre2)
sample=$4 #Jet, JetHT, MinBias, SingleMu, SingleEl, ZeroBias
full=${5:false} # if true, do all plots, otherwise, just essential plots

refFile=$(ls *"${run}"*"${sample}"*"${rel_old}"*)
newFile=$(ls *"${run}"*"${sample}"*"${rel_new}"*)
#release=CMSSW_9_0_0_pre2-ROOT6_vs_9_0_0_pre2_"${run}"_"${sample}"
release=CMSSW_"${rel_new}"_vs_"${rel_old}"_"${run}"_"${sample}"

directory=/afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}

#Create directories for webpage
if [ ! -d ${directory} ] ; then    
    mkdir ${directory} 
else
    rm -r ${directory} 
    mkdir ${directory} 
fi                            

for subdir in GenProps HitProps PU SplitTk TkBuilding TkEff
do
    mkdir -p ${directory}/${subdir}_lin
    mkdir -p ${directory}/${subdir}_log
done

echo "Analyzing ${refFile} and ${newFile} in ${release}"   

#Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
root -b -q -l "runValidationComparison_cos.C("\"${refFile}\",\"${newFile}\",\"${directory}\",\"${full}\"")"   

#generate index.html files on the fly for release directory
cd ${directory}
../genSubDir_cos.sh "${release}" 
cd -

# now make pretty plots on webpage with perl script

for subdir in GenProps HitProps PU SplitTk TkBuilding TkEff
do
    for scale in lin log
    do 
	cd ${directory}/${subdir}_${scale}
	../../diow.pl -t "${release} ${subdir} Cosmics Validation (${scale})" -c 3 -icon 200  
	cd --
    done
done
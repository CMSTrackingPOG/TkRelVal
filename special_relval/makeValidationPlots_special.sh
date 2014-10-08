#! /bin/bash

#Parameters passed from command line
refFile=$1 #old release to check against (e.g. pre1)
newFile=$2 #new release (e.q. pre2)

if [ -d RunComparison ] ; then
    rm -r RunComparison
    mkdir RunComparison
elif [ ! -d RunComparison ] ; then
    mkdir RunComparison
fi

#Do this for all matching data sets
for scale in 1
do 
  
  release="EscaleZS_noZeroBin"

  if [ "${scale}" == "0" ] ; then
      release+="_unscaled"
  elif [ "${scale}" == "3" ] ; then
      release+="_scalednEvents"
  fi
  
  if [ ! -d /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} ] ; then    
      mkdir /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release} 
  fi                            
    
  echo "Analyzing ${refFile} and ${newFile} in ${release}"                                                                                   
  
  root -b -q -l "RunValidationComparison_special.C("\"${refFile}\",\"${newFile}\",\"${scale}\"")"   
  
  cp RunComparison/*.png /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
  
  cd /afs/cern.ch/cms/Physics/tracking/validation/DATA/${release}
    ../diow.pl -t "${release} validation" -c 3 -icon 200                 
  cd -                                                    
  
  rm RunComparison/*.png
done



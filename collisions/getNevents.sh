#! /bin/sh

#Parameters passed from command line
file1=$1 #ref file
file2=$2 #new file
run=$3 #run number

#Run the ROOT Macro. This is trivial, compiles a .cpp file that makes all the plots.  
root -b -q -l "GetNEventsFromFiles.C("\"${file1}\",\"${file2}\",\"${run}\"")"   

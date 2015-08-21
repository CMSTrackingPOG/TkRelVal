void runValidationComparison(char* refFile, char* newFile, char * c_scale, char * doMiniAODval) {
  gROOT->LoadMacro("ReleaseComparison.cpp++g");
  int setscale = atoi(c_scale);
  V1_V2_trkComparison(refFile,newFile,setscale,doMiniAODval);
}


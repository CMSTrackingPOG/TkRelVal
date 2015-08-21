void runValidationComparison(char* refFile, char* newFile, char * c_scale, char * miniaod) {
  gROOT->LoadMacro("ReleaseComparison.cpp++g");
  int  setscale     = atoi(c_scale);
  bool doMiniAODval = bool(atoi(miniaod)); // super ugly!
  V1_V2_trkComparison(refFile,newFile,setscale,doMiniAODval);
}


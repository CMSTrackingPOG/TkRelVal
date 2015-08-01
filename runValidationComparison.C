void runValidationComparison_comp(char* refFile, char* newFile, char * c_scale) {
  gROOT->LoadMacro("ReleaseComparison_compressed.cpp++g");
  int setscale = atoi(c_scale);
  V1_V2_trkComparison(refFile,newFile,setscale);
}


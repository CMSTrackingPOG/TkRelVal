void runValidationComparison(const char * refFile, const char * newFile, const TString directory) {
  gROOT->LoadMacro("ReleaseComparison.cpp++g");
  V1_V2_trkComparison(refFile,newFile,directory);
}


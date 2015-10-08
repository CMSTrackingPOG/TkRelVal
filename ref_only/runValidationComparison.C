void runValidationComparison(const char * file, const char * run, const TString directory) {
  gROOT->LoadMacro("ReleaseComparison.cpp++g");
  V1_V2_trkComparison(file,run,directory);
}


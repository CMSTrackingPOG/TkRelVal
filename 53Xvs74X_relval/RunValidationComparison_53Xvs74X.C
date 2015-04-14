RunValidationComparison_53Xvs74X(char* refFile, char* newFile, char * c_scale)
{
  gROOT->ProcessLine(".L ReleaseComparison_53Xvs74X.cpp++");
  gSystem->Load("ReleaseComparison_53Xvs74X_cpp.so");
  int setscale = atoi(c_scale);
  V1_V2_trkComparison(refFile,newFile,setscale);
}


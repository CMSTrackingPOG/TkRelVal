RunValidationComparison(char* refFile, char* newFile, char * c_scale)
//RunValidationComparison(char* refFile, char* newFile)
{
  gROOT->ProcessLine(".L ReleaseComparison.cpp++");
  gSystem->Load("ReleaseComparison_cpp.so");
  int setscale = atoi(c_scale);
  V1_V2_trkComparison(refFile,newFile,setscale);
}


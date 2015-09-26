RunValidationComparison_special(char* refFile, char* newFile, char * c_scale)
{
  gROOT->ProcessLine(".L ReleaseComparison_special.cpp++");
  gSystem->Load("ReleaseComparison_special_cpp.so");
  int setscale = atoi(c_scale);
  V1_V2_trkComparison(refFile,newFile,setscale);
}


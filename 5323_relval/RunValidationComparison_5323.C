RunValidationComparison_5323(char* refFile, char* newFile, char * c_scale)
//RunValidationComparison(char* refFile, char* newFile)
{
  gROOT->ProcessLine(".L ReleaseComparison_5323.cpp++");
  gSystem->Load("ReleaseComparison_5323_cpp.so");
  int setscale = atoi(c_scale);
  V1_V2_trkComparison(refFile,newFile,setscale);
}


#include "ReleaseComparison.cpp+"

void runValidationComparison(const char * refFile, const char * newFile, 
			     const TString directory, const TString full) 
{
  bool fullbool = full.Contains("true",TString::kExact);
  V1_V2_trkComparison(refFile,newFile,directory,fullbool);
}


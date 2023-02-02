#include "ReleaseComparison.cpp+"

void runValidationComparison(const char * refFile, const char * refLabel, const char * newFile, const char * newLabel,
			     const TString directory, const TString era, const Double_t lumi, const TString full) 
{
  bool fullbool = full.Contains("true",TString::kExact);
  V1_V2_trkComparison(refFile,refLabel,newFile,newLabel,directory,era,lumi,fullbool);
}


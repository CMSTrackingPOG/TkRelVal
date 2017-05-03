void runValidationComparison_cos(const char * refFile, const char * newFile, 
				 const TString directory, const TString full) 
{
  bool fullbool = full.Contains("true",TString::kExact);
  gROOT->LoadMacro("ReleaseComparison_cos.cpp+g");
  V1_V2_trkComparison(refFile,newFile,directory,fullbool);
}


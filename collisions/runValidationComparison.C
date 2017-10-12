#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "ReleaseComparison.cpp+"

void setupcpp11() // customize ACLiC's behavior ...
{
  TString o;
  // customize MakeSharedLib
  o = TString(gSystem->GetMakeSharedLib());
  o = o.ReplaceAll(" -c ", " -std=c++0x -c ");
  gSystem->SetMakeSharedLib(o.Data());
  // customize MakeExe
  o = TString(gSystem->GetMakeExe());
  o = o.ReplaceAll(" -c ", " -std=c++0x -c ");
  gSystem->SetMakeExe(o.Data());
} 

void runValidationComparison(const char * refFile, const char * newFile, 
			     const TString directory, const TString full) 
{
  setupcpp11(); 

  bool fullbool = full.Contains("true",TString::kExact);
  V1_V2_trkComparison(refFile,newFile,directory,fullbool);
}


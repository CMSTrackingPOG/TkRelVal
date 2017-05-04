#include "TString.h"

void GetNEventsFromFiles(TString filename1, TString filename2, TString run)
{
  TFile * file1 = TFile::Open(filename1.Data());
  TFile * file2 = TFile::Open(filename2.Data());

  TString histname = Form("DQMData/Run %s/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties/NumberOfTracks_GenTk",run.Data());

  TH1F * hist1 = (TH1F*)file1->Get(histname.Data());
  TH1F * hist2 = (TH1F*)file2->Get(histname.Data());

  std::cout << "nEvents for file1: " << hist1->GetEntries() << std::endl;
  std::cout << "nEvents for file2: " << hist2->GetEntries() << std::endl;
}


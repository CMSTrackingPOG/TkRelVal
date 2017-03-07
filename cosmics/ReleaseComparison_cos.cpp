#include "ReleaseComparison_cos.hh"

void V1_V2_trkComparison(const TString fileName1, const TString fileName2, 
			 const TString directory, const bool full) {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  setTDRStyle(tdrStyle);

  gROOT->SetBatch(kTRUE);
  gStyle->SetPalette(1);
  gStyle->SetOptStat(110111);
  gStyle->SetOptFit(1);
  gROOT->ForceStyle();

  // fileName1 --> REFERENCE
  Int_t pos = fileName1.Index("_R0");
  TString runString1(fileName1(pos+5,6));
  Int_t pos1 = fileName1.Index("CMSSW")+6;
  Int_t pos2 = fileName1.Index("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-76X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-80X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-81X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-90X");
  TString relString1(fileName1(pos1,pos2-pos1)); 
  TFile *file1 = TFile::Open(fileName1.Data());
  std::cout << "Getting histos for run number... " << runString1.Data()
	    <<" for release " << relString1.Data() << std::endl;  
  if ( file1->IsZombie() )
    std::cout << "File: " << fileName1.Data() << " cannot be opened!" << std::endl;
  //  relString1 = "9_0_0_pre2";

  // fileName2 --> NEW
  pos = fileName2.Index("_R0");
  TString runString2(fileName2(pos+5,6));
  pos1 = fileName2.Index("CMSSW")+6;
  pos2 = fileName2.Index("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-76X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-80X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-81X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-90X");  
  TString relString2(fileName2(pos1,pos2-pos1));
  TFile *file2 = TFile::Open(fileName2.Data());
  std::cout << "Getting histos for run number... " << runString2.Data()
    	    <<" for release " << relString2.Data() << std::endl;  
  if ( file2->IsZombie() )
    std::cout << "File: " << fileName2.Data() << " cannot be opened!" << std::endl;
  //  relString2 = "900p2-ROOT6";
  
  //================= Print CMS Lumi on these guys =================//

  Double_t magB = 0;
  Int_t    year = 0;

  // hack in cosmics
  if      (atoi(runString1.Data()) == 256259){magB = 0.0; year = 2015;} // 2015C cosmics
  else if (atoi(runString1.Data()) == 272133){magB = 3.8; year = 2016;} // 2016B cosmics

  //====================== Make master canvas  ======================// 
  TCanvas *canvas = new TCanvas("master canv","");

  //====================== Get histo integrals ======================// 
  // ---> Scale all histos (besides PV/Aignment) by nEvents

  TString tempname1 = "DQMData/Run ";
  tempname1.Append(runString1);
  tempname1.Append("/Tracking/Run summary/TrackParameters/GeneralProperties/NumberOfTracks_CosmicTk");

  TH1F * hNormTempV1   = (TH1F*)file1->Get(tempname1.Data());
  Double_t V1_integral = hNormTempV1->GetEntries();
  delete hNormTempV1;

  TString tempname2 = "DQMData/Run ";
  tempname2.Append(runString2);
  tempname2.Append("/Tracking/Run summary/TrackParameters/GeneralProperties/NumberOfTracks_CosmicTk");

  TH1F * hNormTempV2 = (TH1F*)file2->Get(tempname2.Data());
  Double_t V2_integral = hNormTempV2->GetEntries();
  delete hNormTempV2;

  //====================== done with scaling ======================// 

  TString dirname = ""; // input root file directory
  TString outdir  = ""; // output file directory
  TString extra   = ""; // extra string at end of hist title

  ///////////////////////////////////////////////
  // Histograms in GeneralProperties directory //
  ///////////////////////////////////////////////
  dirname = "/Tracking/Run summary/TrackParameters/GeneralProperties";
  outdir  = directory+"/GenProps";

  // TH1F plots
  for (int i = 0; i < 2; i++) { // such a hack!
    if      (i == 0) extra = "_CKFTk";
    else if (i == 1) extra = "_CosmicTk";

    createTH1FPlot("Chi2Prob", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("Chi2", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("Chi2oNDF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("FractionOfGoodTracks", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfMeanLayersPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfMeanRecHitsPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfTracks", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackEtaErr", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPErrOverP", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackP", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPhiErr", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPtErrOverPt", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPt", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPzErrOverPz", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackPz", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("TrackQ", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("algorithm", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("originalAlgorithm", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);  
    createTH1FPlot("stoppingSource", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);

    // TProfile Plots
    if (full) {
      createTProfPlot("NumberOfLayersPerTrackVsEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("NumberOfLayersPerTrackVsPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("NumberOfRecHitsPerTrackVsEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("NumberOfRecHitsPerTrackVsPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("NumberOfValidRecHitsPerTrackVsEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("TrackPtErrOverPtVsEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
    }
  }

  ///////////////////////////////////////////
  // Histograms in HitProperties directory //
  ///////////////////////////////////////////
  dirname = "/Tracking/Run summary/TrackParameters/HitProperties";
  outdir  = directory+"/HitProps";

  for (int i = 0; i < 2; i++) { // such a hack!
    if      (i == 0) extra = "_CKFTk";
    else if (i == 1) extra = "_CosmicTk";

    createTH1FPlot("NumberOf3DLayersPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfOffLayersPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfLostRecHitsPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfMissingLayersPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfOffLayersPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfRecHitsPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfValidRecHitsPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("ValidFractionPerTrack", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  }

  //////////////////////////////////////////
  // Histograms in PUmonitoring directory //
  //////////////////////////////////////////
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/PUmonitoring";
    outdir  = directory+"/PU";
    extra   = "";

    createTProfPlot("NumberOfTracksVsGoodPVtx", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
    createTProfPlot("NumberOfTracksVsPUPVtx", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
  }

  /////////////////////////////////////////
  // Histograms in SplitTracks directory //
  /////////////////////////////////////////
  dirname = "/Tracking/Run summary/TrackParameters/SplitTracks";
  outdir  = directory+"/SplitTk";

  for (int i = 0; i < 2; i++) { // such a hack!
    if      (i == 0) extra = "_global";
    else if (i == 1) extra = "_tracker";

    createTH1FPlot("dcurvAbsoluteResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dcurvNormalizedResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("ddxyAbsoluteResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("ddxyNormalizedResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("ddzAbsoluteResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("ddzNormalizedResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dphiAbsoluteResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dphiNormalizedResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dptAbsoluteResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dptNormalizedResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dthetaAbsoluteResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("dthetaNormalizedResiduals", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  }

  ///////////////////////////////////////////
  // Histograms in TrackBuilding directory //
  ///////////////////////////////////////////
  dirname = "/Tracking/Run summary/TrackParameters/TrackBuilding";
  outdir  = directory+"/TkBuilding";

  for (int i = 0; i < 2; i++) { // such a hack!
    if      (i == 0) extra = "_CKFTk";
    else if (i == 1) extra = "_CosmicTk";

    createTH1FPlot("NumberOfRecHitsPerSeed_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("NumberOfSeeds_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedDxy_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedDz_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedEta_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedPhi_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedPt_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedQ_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    createTH1FPlot("SeedTheta_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
    
    if (full) {
      createTProfPlot("NumberOfRecHitsPerSeedVsEtaProfile_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
      createTProfPlot("NumberOfRecHitsPerSeedVsPhiProfile_combinedP5SeedsForCTF", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, magB, year);
    }
  }

  /////////////////////////////////////////////
  // Histograms in TrackEfficiency directory //
  /////////////////////////////////////////////
  dirname = "/Tracking/Run summary/TrackParameters/TrackEfficiency";
  outdir  = directory+"/TkEff";
  extra   = "_CKFTk";

  createTH1FPlot("deltaX", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("deltaY", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effCompatibleLayers", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effD0", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effX", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effY", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("effZ", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonCompatibleLayers", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonD0", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonX", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonY", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("muonZ", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("signDeltaX", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("signDeltaY", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackCompatibleLayers", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackD0", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackEta", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackPhi", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackX", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackY", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);
  createTH1FPlot("trackZ", extra, dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, magB, year);

  delete file1;
  delete file2;
  delete canvas;
  delete tdrStyle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                                                                                //
//                             START OF Create Plots for TH1Fs                                    //
//                                                                                                //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool createTH1FPlot(const TString hname, const TString extra, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, TString outdir, const Double_t magB, const Int_t year) {

  // ++++++++++++ Get name of histos and get histos +++++++++++++ //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);

  TString hnameV1 = basename1; // reference
  hnameV1.Append(dirname+"/");
  hnameV1.Append(hname);
  hnameV1.Append(extra);

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);

  TString hnameV2 = basename2;
  hnameV2.Append(dirname+"/");
  hnameV2.Append(hname);
  hnameV2.Append(extra);

  // use booleans to plot hists even if some are missing
  Bool_t isHist1 = false;
  Bool_t isHist2 = false;

  TH1F * hBinTempV1 = (TH1F*)V1file->Get(hnameV1.Data());
  if ( hBinTempV1 == (TH1F*) NULL ) {
    std::cout << "Could not grab hist: " << hnameV1  << std::endl << " for REF file " << V1file->GetName() << std::endl;
  }
  else {
    isHist1 = true;
  }
  
  TH1F * hBinTempV2 = (TH1F*)V2file->Get(hnameV2.Data());
  if ( hBinTempV2 == (TH1F*) NULL ) {
    std::cout << "Could not grab hist: " << hnameV2  << std::endl << " for NEW file " << V2file->GetName() << std::endl;
  }
  else {
    isHist2 = true;
  }

  if (!isHist1 && !isHist2){ // skip plot if neither there
    std::cout << "Well, couldn't grab this hist from either file, just go to the next one." << std::endl << std::endl;
    return false;
  }
  else if (!isHist1 && isHist2) { // just draw one hist 
    hBinTempV1 = (TH1F*)hBinTempV2->Clone();
  }
  else if (!isHist2 && isHist1) { // just draw one hist
    hBinTempV2 = (TH1F*)hBinTempV1->Clone();
  }

  // Check that bins match for ratio plot

  TH1F * histV1 = 0; // reference
  TH1F * histV2 = 0; // target

  const Double_t h1_xlow = hBinTempV1->GetXaxis()->GetBinLowEdge(hBinTempV1->GetXaxis()->GetFirst());
  const Double_t h2_xlow = hBinTempV2->GetXaxis()->GetBinLowEdge(hBinTempV2->GetXaxis()->GetFirst());

  const Double_t h1_xup = hBinTempV1->GetXaxis()->GetBinUpEdge(hBinTempV1->GetXaxis()->GetLast());
  const Double_t h2_xup = hBinTempV2->GetXaxis()->GetBinUpEdge(hBinTempV2->GetXaxis()->GetLast());

  const Int_t h1_nbins = hBinTempV1->GetNbinsX();
  const Int_t h2_nbins = hBinTempV2->GetNbinsX();

  const Double_t h1_binWidth = (h1_xup - h1_xlow) / (Double_t)h1_nbins;
  const Double_t h2_binWidth = (h2_xup - h2_xlow) / (Double_t)h2_nbins;

  const Double_t h1_nEntries = hBinTempV1->GetEntries();
  const Double_t h2_nEntries = hBinTempV2->GetEntries();

  if ((h1_xlow == h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){
    histV1 = (TH1F*)hBinTempV1->Clone();//V1file->Get(hnameV1);
    histV2 = (TH1F*)hBinTempV2->Clone();//V2file->Get(hnameV2);
  }
  else if((h1_xlow == h2_xlow) && (h1_xup < h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV2 = (TH1F*)hBinTempV2->Clone();//V2file->Get(hnameV2); // copy histV2 

    histV1 = new TH1F(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h2_nbins,h2_xlow,h2_xup); // want to have the same number of bins as larger histo
    histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
    histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){ // fill bins with first original content (up to hist1 bins), then zeros after
      if (ibin <= h1_nbins){
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin));
      }
      else { //if (ibin > h1_nbins){
	histV1->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if((h1_xlow == h2_xlow) && (h1_xup > h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV1 = (TH1F*)hBinTempV1->Clone();//V1file->Get(hnameV1); // copy histV1 

    histV2 = new TH1F(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h1_nbins,h1_xlow,h1_xup);
    histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
    histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
      if (ibin <= h2_nbins){
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin));
      }
      else { //if (ibin > h2_nbins){
	histV2->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if((h1_xlow < h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV1 = (TH1F*)hBinTempV1->Clone();//V1file->Get(hnameV1); // copy histV1 

    histV2 = new TH1F(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h1_nbins,h1_xlow,h1_xup);
    histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
    histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());

    const Int_t bindiff = h1_nbins - h2_nbins;
    for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
      if (ibin <= bindiff){ // fill zeros for bins not originally in hist2
	histV2->SetBinContent(ibin,0.0); 
      }
      else { 
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin-bindiff));	
      }
    }
  }
  else if((h1_xlow > h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV2 = (TH1F*)hBinTempV1->Clone();//V1file->Get(hnameV1); // copy histV1 

    histV1 = new TH1F(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h2_nbins,h2_xlow,h2_xup);
    histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
    histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());

    const Int_t bindiff = h2_nbins - h1_nbins;
    for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){
      if (ibin <= bindiff){ // fill zeros for bins not originally in hist1
	histV1->SetBinContent(ibin,0.0); 
      }
      else { 
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin-bindiff));	
      }
    }
  }
  else{
    std::cout << "Bin Check Failed...skipping this histogram... here's what happened: " << std::endl;
    std::cout << "histV1 failed on " << hnameV1  << std::endl << " for file " << V1file->GetName() << std::endl;
    std::cout << "       bin info: " << h1_xlow << " " << h1_xup << " " << h1_nbins << std::endl;
    std::cout << "histV2 failed on " << hnameV2  << std::endl << " for file " << V2file->GetName() << std::endl;
    std::cout << "       bin info: " << h2_xlow << " " << h2_xup << " " << h2_nbins << std::endl;

    delete hBinTempV1;
    delete hBinTempV2;
    return false;
  }

  histV1->SetEntries(h1_nEntries);
  histV2->SetEntries(h2_nEntries);

  // Don't look at zero bin -- > Also could use this for truncation and bin setting -->Range is binlower to upper
  //  Int_t range_upper = histV1->GetXaxis()->GetLast();
  //  histV1->GetXaxis()->SetRangeUser(1,range_upper);
  //  histV2->GetXaxis()->SetRangeUser(1,range_upper);

  //+++++NORMALIZING V1-V2++++++++++++++++++++++++++++++++++++++++

  if (isHist1 && isHist2) {
    if (V1_integral>V2_integral) {
      histV1->Scale(V2_integral / V1_integral); // scale down h1
      histV2->Scale(1);
    } 
    else if (V2_integral>V1_integral) {
      histV1->Scale(1);
      histV2->Scale(V1_integral / V2_integral); // scale down h2
    }
  }
  //+++++NORMALIZING V1-V2+end+++++++++++++++++++++++++++++++++++++++

  //++++++++++++++++++++ Settings for Histos +++++++++++++++++++//

  //+++Name the files under comparison+++
  TString V1_V1run = relstring1;
  TString V2_V2run = relstring2;

  if (isHist1 && isHist2) {
    histV1->SetName(V1_V1run);
    histV2->SetName(V2_V2run);
  }
  else if (!isHist1 && isHist2) { // only plot histV1 in the case of missing hists
    histV1->SetName(V2_V2run);
  }
  else if (isHist1 && !isHist2) { // only plot histV1 in the case of missing hists
    histV1->SetName(V1_V1run);
  }

  // options for drawing
  double max = 0;
  const double V1max = histV1->GetBinContent(histV1->GetMaximumBin());
  const double V2max = histV2->GetBinContent(histV2->GetMaximumBin());
  max = (V1max>V2max) ? V1max : V2max;

  double min = 0;
  const double V1min = histV1->GetBinContent(histV1->GetMinimumBin());
  const double V2min = histV2->GetBinContent(histV2->GetMinimumBin());
  min = (V1min<V2min) ? V1min : V2min;

  histV1->SetLineStyle(1);
  histV1->GetYaxis()->SetLabelSize(0.038);
  histV1->GetXaxis()->SetTitleSize(0.0);
  histV1->SetLineWidth(2);
  histV1->SetLineColor(kBlue); // h1 is ref ...originally was red... switched to match MC comparisons
  histV1->SetMarkerColor(kBlue); // h1 is ref ...originally was red... switched to match MC comparisons
  histV1->SetMaximum(max); // just to get all points to show up
  //  if (histV1->GetSumw2() == (TArrayD*) NULL) histV1->Sumw2();
  histV1->Sumw2();

  histV2->GetXaxis()->SetTitleSize(0.0);
  histV2->SetLineWidth(2);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  histV2->SetMarkerColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  //  if (histV2->GetSumw2() == (TArrayD*) NULL) histV2->Sumw2();
  histV2->Sumw2();

  if (!isHist1) { // only plot hist1 in case of missing hists
    histV1->SetLineColor(kRed);
    histV1->SetMarkerColor(kRed);
    histV1->SetLineWidth(2);
  }

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    histV1->GetXaxis()->SetRangeUser(0,2);
    histV2->GetXaxis()->SetRangeUser(0,2);
  }

  //++++++++++++++++++++ Change axis title names +++++++++++++++++++//

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    histV1->GetXaxis()->SetTitle("");
    histV2->GetXaxis()->SetTitle("");
  }
  else if (dirname.Contains("TrackEfficiency",TString::kExact)) {
    histV1->GetXaxis()->SetTitle(hname.Data());
    histV2->GetXaxis()->SetTitle(hname.Data());

    if (hname.Contains("track",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Number of Tracks");
    }
    else if (hname.Contains("muon",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Number of Muon");
    }
    else if (hname.Contains("eff",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Efficiency (nTracks/nMuons)");
    }
  }
  
  //++++++++++++++++++++ Draw Histograms +++++++++++++++++++//

  canvas->cd();

  TPad* mainpad = new TPad("mainpad","mainpad", 0.0, 0.3, 0.93, 0.99);
  mainpad->SetBottomMargin(0);
  mainpad->Draw();
  mainpad->cd();

  histV1->Draw("EP"); // Draw old histo first, ratio is new/old
  if (isHist1 && isHist2) {
    histV2->Draw("EP sames");
  }

  mainpad->Update();

  //++++++++++++++++++++ Draw Legends +++++++++++++++++++//

  TLegend *leg = new TLegend(0.29,0.85,0.485,0.94);
  leg->SetTextSize(0.042);
  leg->SetTextFont(42);
  leg->SetFillColor(10); 
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histV1, histV1->GetName(), "L" );
  if (isHist1 && isHist2) {
    leg->AddEntry(histV2, histV2->GetName(), "L" );
  }
  leg->Draw("SAME");

  //++++++++++++++++++++ Draw both stats boxes +++++++++++++++++++//

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  TPaveStats *st2;
  if (isHist1 && isHist2){
    st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
  }
  st1->SetX1NDC(0.77);
  st1->SetX2NDC(0.98);
  if (isHist1 && isHist2){
    st2->SetX1NDC(0.77);  
    st2->SetX2NDC(0.98);    
  }

  st1->SetY1NDC(0.77);
  st1->SetY2NDC(0.94);
  const Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  const Double_t gaph = 0.02;
  if (isHist1 && isHist2){
    st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
    st2->SetY2NDC(st1->GetY1NDC() - gaph);
  }

  //++++++++++++++++++++ Make ratio histograms +++++++++++++++++++//

  canvas->cd();
  TPad* respad = new TPad("respad","respad", 0.0, 0.05, 0.93, 0.3);
  respad->SetTopMargin(0.0);
  respad->SetBottomMargin(0.2);
  respad->Draw();
  respad->cd();

  TH1F* hratio = (TH1F*) histV2->Clone("hratio");
  hratio->Divide(histV1);

  hratio->SetMaximum(1.25);
  hratio->SetMinimum(0.75);
  hratio->GetXaxis()->SetTitle(histV1->GetXaxis()->GetTitle());

  hratio->GetXaxis()->SetTitleSize(0.13);
  hratio->GetXaxis()->SetTitleOffset(0.9);
  hratio->GetXaxis()->SetLabelSize(0.13);
  hratio->GetXaxis()->SetTickSize(0.1);
  hratio->GetXaxis()->SetNdivisions(510);

  hratio->GetYaxis()->SetTitleSize(0.13);
  hratio->GetYaxis()->SetTitleOffset(0.36);
  hratio->GetYaxis()->SetLabelSize(0.13);
  hratio->GetYaxis()->SetNdivisions(505);
  if (isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle("NEW/REF");
  }
  else if (!isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle("NEW/NEW");
  }
  else if (isHist1 && !isHist2){
    hratio->GetYaxis()->SetTitle("REF/REF");
  }
  hratio->SetStats(0);
  hratio->SetTitle("");
  hratio->SetLineColor(1);
  hratio->SetMarkerColor(1);
  hratio->Draw("EP");

  //++++++++++++++++++++ Draw ratio line +++++++++++++++++++//
  
  TLine * ratioline = new TLine();

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    ratioline->SetX1(0);
    ratioline->SetX2(2);
  }
  else {
    ratioline->SetX1(hratio->GetXaxis()->GetXmin());
    ratioline->SetX2(hratio->GetXaxis()->GetXmax());
  }
  ratioline->SetY1(1.0);
  ratioline->SetY2(1.0);

  // customize appearance
  ratioline->SetLineColor(kRed);
  ratioline->SetLineWidth(2);

  // draw line then redraw hratio on top
  ratioline->Draw("SAME");
  hratio->Draw("EP SAME");

  //++++++++++++++++++++ Define filename, change filename output if necessary +++++++++++++++++++//

  TString filename = hname+extra;
  if (dirname.Contains("TrackBuilding",TString::kExact) ){
    TString replacestr  = "_combinedP5SeedsForCTF";
    Ssiz_t  length      = replacestr.Length();
    Ssiz_t  filenamepos = filename.Index(replacestr.Data());
    
    TString toreplace = "";
    filename.Replace(filenamepos,length,toreplace);
  }

  filename.Append(".png");
  TString filenamecopy = filename; // copy filename for log .. stupid but whatever

  //++++++++++++++++++++ Save output canvas +++++++++++++++++++//
  CMSLumi(canvas, 0, year, magB);

  // log first
  mainpad->cd();
  mainpad->SetLogy(1);
  histV1->SetMaximum(max*(1.5));
  filename.Prepend(outdir+"_log/");
  canvas->cd();
  canvas->Print(filename.Data());

  // linear second
  mainpad->cd();
  mainpad->SetLogy(0);
  histV1->SetMaximum( (max>0 ? max*1.05 : max/1.05) );
  histV1->SetMinimum( (min>0 ? min/1.05 : min*1.05) );
  filenamecopy.Prepend(outdir+"_lin/");
  canvas->cd();
  canvas->Print(filenamecopy.Data());

  //++++++++++++++++++++ delete objects +++++++++++++++++++//

  if ( st1 ) {delete st1;}
  if ( isHist1 && isHist2 ) {
    if ( st2 ) {delete st2;}
  }

  if ( leg ) {delete leg;}

  if ( ratioline ) {delete ratioline;}
  if ( hratio ) {delete hratio;}

  if ( histV1 ) {delete histV1;}
  if ( histV2 ) {delete histV2;}

  if ( hBinTempV1 ) {delete hBinTempV1;} 
  if ( hBinTempV2 ) {delete hBinTempV2;}

  if ( mainpad ) {delete mainpad;}
  if ( respad )  {delete respad;}

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                                                                                //
//                              END OF Create Plots for TH1Fs                                     //
//                                                                                                //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                                                                                //
//                          START OF Create Plots for TProfiles                                   //
//                                                                                                //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool createTProfPlot(const TString hname, const TString extra, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, TString outdir, const Double_t magB, const Int_t year) {

  // ++++++++++++ Get name of histos and get histos +++++++++++++ //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);

  TString hnameV1 = basename1; // reference
  hnameV1.Append(dirname+"/");
  hnameV1.Append(hname);
  hnameV1.Append(extra);

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);

  TString hnameV2 = basename2;
  hnameV2.Append(dirname+"/");
  hnameV2.Append(hname);
  hnameV2.Append(extra);

  // use booleans to plot hists even if some are missing
  Bool_t isHist1 = false;
  Bool_t isHist2 = false;

  TProfile * hBinTempV1 = (TProfile*)V1file->Get(hnameV1.Data());
  if ( hBinTempV1 == (TProfile*) NULL ) {
    std::cout << "Could not grab hist: " << hnameV1  << std::endl << " for REF file " << V1file->GetName() << std::endl;
  }
  else {
    isHist1 = true;
  }
  
  TProfile * hBinTempV2 = (TProfile*)V2file->Get(hnameV2.Data());
  if ( hBinTempV2 == (TProfile*) NULL ) {
    std::cout << "Could not grab hist: " << hnameV2  << std::endl << " for NEW file " << V2file->GetName() << std::endl;
  }
  else {
    isHist2 = true;
  }

  if (!isHist1 && !isHist2){ // skip plot if neither there
    std::cout << "Well, couldn't grab this hist from either file, just go to the next one." << std::endl << std::endl;
    return false;
  }
  else if (!isHist1 && isHist2) { // just draw one hist 
    hBinTempV1 = (TProfile*)hBinTempV2->Clone();
  }
  else if (!isHist2 && isHist1) { // just draw one hist
    hBinTempV2 = (TProfile*)hBinTempV1->Clone();
  }

  // Check that bins match for ratio plot

  TProfile * histV1 = 0; // reference
  TProfile * histV2 = 0; // target

  const Double_t h1_xlow = hBinTempV1->GetXaxis()->GetBinLowEdge(hBinTempV1->GetXaxis()->GetFirst());
  const Double_t h2_xlow = hBinTempV2->GetXaxis()->GetBinLowEdge(hBinTempV2->GetXaxis()->GetFirst());

  const Double_t h1_xup = hBinTempV1->GetXaxis()->GetBinUpEdge(hBinTempV1->GetXaxis()->GetLast());
  const Double_t h2_xup = hBinTempV2->GetXaxis()->GetBinUpEdge(hBinTempV2->GetXaxis()->GetLast());

  const Int_t h1_nbins = hBinTempV1->GetNbinsX();
  const Int_t h2_nbins = hBinTempV2->GetNbinsX();

  const Double_t h1_binWidth = (h1_xup - h1_xlow) / (Double_t)h1_nbins;
  const Double_t h2_binWidth = (h2_xup - h2_xlow) / (Double_t)h2_nbins;

  const Double_t h1_nEntries = hBinTempV1->GetEntries();
  const Double_t h2_nEntries = hBinTempV2->GetEntries();

  if ((h1_xlow == h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){
    histV1 = (TProfile*)hBinTempV1->Clone();//V1file->Get(hnameV1);
    histV2 = (TProfile*)hBinTempV2->Clone();//V2file->Get(hnameV2);
  }
  else if((h1_xlow == h2_xlow) && (h1_xup < h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV2 = (TProfile*)hBinTempV2->Clone();//V2file->Get(hnameV2); // copy histV2 

    histV1 = new TProfile(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h2_nbins,h2_xlow,h2_xup); // want to have the same number of bins as larger histo
    histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
    histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){ // fill bins with first original content (up to hist1 bins), then zeros after
      if (ibin <= h1_nbins){
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin));
      }
      else { //if (ibin > h1_nbins){
	histV1->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if((h1_xlow == h2_xlow) && (h1_xup > h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV1 = (TProfile*)hBinTempV1->Clone();//V1file->Get(hnameV1); // copy histV1 

    histV2 = new TProfile(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h1_nbins,h1_xlow,h1_xup);
    histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
    histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
      if (ibin <= h2_nbins){
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin));
      }
      else { //if (ibin > h2_nbins){
	histV2->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if((h1_xlow < h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV1 = (TProfile*)hBinTempV1->Clone();//V1file->Get(hnameV1); // copy histV1 

    histV2 = new TProfile(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h1_nbins,h1_xlow,h1_xup);
    histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
    histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());

    const Int_t bindiff = h1_nbins - h2_nbins;
    for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
      if (ibin <= bindiff){ // fill zeros for bins not originally in hist2
	histV2->SetBinContent(ibin,0.0); 
      }
      else { 
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin-bindiff));	
      }
    }
  }
  else if((h1_xlow > h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV2 = (TProfile*)hBinTempV1->Clone();//V1file->Get(hnameV1); // copy histV1 

    histV1 = new TProfile(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h2_nbins,h2_xlow,h2_xup);
    histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
    histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());

    const Int_t bindiff = h2_nbins - h1_nbins;
    for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){
      if (ibin <= bindiff){ // fill zeros for bins not originally in hist1
	histV1->SetBinContent(ibin,0.0); 
      }
      else { 
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin-bindiff));	
      }
    }
  }
  else{
    std::cout << "Bin Check Failed...skipping this histogram... here's what happened: " << std::endl;
    std::cout << "histV1 failed on " << hnameV1  << std::endl << " for file " << V1file->GetName() << std::endl;
    std::cout << "       bin info: " << h1_xlow << " " << h1_xup << " " << h1_nbins << std::endl;
    std::cout << "histV2 failed on " << hnameV2  << std::endl << " for file " << V2file->GetName() << std::endl;
    std::cout << "       bin info: " << h2_xlow << " " << h2_xup << " " << h2_nbins << std::endl;

    delete hBinTempV1;
    delete hBinTempV2;
    return false;
  }

  histV1->SetEntries(h1_nEntries);
  histV2->SetEntries(h2_nEntries);

  // Don't look at zero bin -- > Also could use this for truncation and bin setting -->Range is binlower to upper
  //  Int_t range_upper = histV1->GetXaxis()->GetLast();
  //  histV1->GetXaxis()->SetRangeUser(1,range_upper);
  //  histV2->GetXaxis()->SetRangeUser(1,range_upper);

  //++++++++++++++++++++ Settings for Histos +++++++++++++++++++//

  //+++Name the files under comparison+++
  TString V1_V1run = relstring1;
  TString V2_V2run = relstring2;

  if (isHist1 && isHist2) {
    histV1->SetName(V1_V1run);
    histV2->SetName(V2_V2run);
  }
  else if (!isHist1 && isHist2) { // only plot histV1 in the case of missing hists
    histV1->SetName(V2_V2run);
  }
  else if (isHist1 && !isHist2) { // only plot histV1 in the case of missing hists
    histV1->SetName(V1_V1run);
  }

  // options for drawing
  double max = 0;
  const double V1max = histV1->GetBinContent(histV1->GetMaximumBin());
  const double V2max = histV2->GetBinContent(histV2->GetMaximumBin());
  max = (V1max>V2max) ? V1max : V2max;

  double min = 0;
  const double V1min = histV1->GetBinContent(histV1->GetMinimumBin());
  const double V2min = histV2->GetBinContent(histV2->GetMinimumBin());
  min = (V1min<V2min) ? V1min : V2min;

  histV1->SetLineStyle(1);
  histV1->GetYaxis()->SetLabelSize(0.038);
  histV1->GetXaxis()->SetTitleSize(0.0);
  histV1->SetLineWidth(2);
  histV1->SetLineColor(kBlue); // h1 is ref ...originally was red... switched to match MC comparisons
  histV1->SetMarkerColor(kBlue); // h1 is ref ...originally was red... switched to match MC comparisons
  histV1->SetMaximum(max); // just to get all points to show up
  if (histV1->GetSumw2() == (TArrayD*) NULL) histV1->Sumw2();

  histV2->GetXaxis()->SetTitleSize(0.0);
  histV2->SetLineWidth(2);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  histV2->SetMarkerColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  if (histV2->GetSumw2() == (TArrayD*) NULL) histV2->Sumw2();

  if (!isHist1) { // only plot hist1 in case of missing hists
    histV1->SetLineColor(kRed);
    histV1->SetMarkerColor(kRed);
    histV1->SetLineWidth(2);
  }

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    histV1->GetXaxis()->SetRangeUser(0,2);
    histV2->GetXaxis()->SetRangeUser(0,2);
  }

  //++++++++++++++++++++ Change axis title names +++++++++++++++++++//

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    histV1->GetXaxis()->SetTitle("");
    histV2->GetXaxis()->SetTitle("");
  }
  else if (dirname.Contains("TrackEfficiency",TString::kExact)) {
    histV1->GetXaxis()->SetTitle(hname.Data());
    histV2->GetXaxis()->SetTitle(hname.Data());

    if (hname.Contains("track",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Number of Tracks");
    }
    else if (hname.Contains("muon",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Number of Muon");
    }
    else if (hname.Contains("eff",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Efficiency (nTracks/nMuons)");
    }
  }
  
  //++++++++++++++++++++ Draw Histograms +++++++++++++++++++//

  canvas->cd();

  TPad* mainpad = new TPad("mainpad","mainpad", 0.0, 0.3, 0.93, 0.99);
  mainpad->SetBottomMargin(0);
  mainpad->Draw();
  mainpad->cd();

  histV1->Draw("EP"); // Draw old histo first, ratio is new/old
  if (isHist1 && isHist2) {
    histV2->Draw("EP sames");
  }

  mainpad->Update();

  //++++++++++++++++++++ Draw Legends +++++++++++++++++++//

  TLegend *leg = new TLegend(0.29,0.85,0.485,0.94);
  leg->SetTextSize(0.042);
  leg->SetTextFont(42);
  leg->SetFillColor(10); 
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histV1, histV1->GetName(), "L" );
  if (isHist1 && isHist2) {
    leg->AddEntry(histV2, histV2->GetName(), "L" );
  }
  leg->Draw("SAME");

  //++++++++++++++++++++ Draw both stats boxes +++++++++++++++++++//

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  TPaveStats *st2;
  if (isHist1 && isHist2){
    st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
  }
  st1->SetX1NDC(0.77);
  st1->SetX2NDC(0.98);
  if (isHist1 && isHist2){
    st2->SetX1NDC(0.77);  
    st2->SetX2NDC(0.98);    
  }

  st1->SetY1NDC(0.77);
  st1->SetY2NDC(0.94);
  const Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  const Double_t gaph = 0.02;
  if (isHist1 && isHist2){
    st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
    st2->SetY2NDC(st1->GetY1NDC() - gaph);
  }

  //++++++++++++++++++++ Make ratio histograms +++++++++++++++++++//

  canvas->cd();
  TPad* respad = new TPad("respad","respad", 0.0, 0.05, 0.93, 0.3);
  respad->SetTopMargin(0.0);
  respad->SetBottomMargin(0.2);
  respad->Draw();
  respad->cd();

  TProfile* hratio = (TProfile*) histV2->Clone("hratio");
  hratio->Divide(histV1);

  hratio->SetMaximum(1.25);
  hratio->SetMinimum(0.75);
  hratio->GetXaxis()->SetTitle(histV1->GetXaxis()->GetTitle());

  hratio->GetXaxis()->SetTitleSize(0.13);
  hratio->GetXaxis()->SetTitleOffset(0.9);
  hratio->GetXaxis()->SetLabelSize(0.13);
  hratio->GetXaxis()->SetTickSize(0.1);
  hratio->GetXaxis()->SetNdivisions(510);

  hratio->GetYaxis()->SetTitleSize(0.13);
  hratio->GetYaxis()->SetTitleOffset(0.36);
  hratio->GetYaxis()->SetLabelSize(0.13);
  hratio->GetYaxis()->SetNdivisions(505);
  if (isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle("NEW/REF");
  }
  else if (!isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle("NEW/NEW");
  }
  else if (isHist1 && !isHist2){
    hratio->GetYaxis()->SetTitle("REF/REF");
  }
  hratio->SetStats(0);
  hratio->SetTitle("");
  hratio->SetLineColor(1);
  hratio->SetMarkerColor(1);
  hratio->Draw("EP");

  //++++++++++++++++++++ Draw ratio line +++++++++++++++++++//
  
  TLine * ratioline = new TLine();

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    ratioline->SetX1(0);
    ratioline->SetX2(2);
  }
  else {
    ratioline->SetX1(hratio->GetXaxis()->GetXmin());
    ratioline->SetX2(hratio->GetXaxis()->GetXmax());
  }
  ratioline->SetY1(1.0);
  ratioline->SetY2(1.0);

  // customize appearance
  ratioline->SetLineColor(kRed);
  ratioline->SetLineWidth(2);

  // draw line then redraw hratio on top
  ratioline->Draw("SAME");
  hratio->Draw("EP SAME");

  //++++++++++++++++++++ Define filename, change filename output if necessary +++++++++++++++++++//

  TString filename = hname+extra;
  if (dirname.Contains("TrackBuilding",TString::kExact) ){
    TString replacestr  = "_combinedP5SeedsForCTF";
    Ssiz_t  length      = replacestr.Length();
    Ssiz_t  filenamepos = filename.Index(replacestr.Data());
    
    TString toreplace = "";
    filename.Replace(filenamepos,length,toreplace);
  }

  filename.Append(".png");
  TString filenamecopy = filename; // copy filename for log .. stupid but whatever

  //++++++++++++++++++++ Save output canvas +++++++++++++++++++//
  CMSLumi(canvas, 0, year, magB);

  // log first
  mainpad->cd();
  mainpad->SetLogy(1);
  histV1->SetMaximum(max*(1.5));
  filename.Prepend(outdir+"_log/");
  canvas->cd();
  canvas->Print(filename.Data());

  // linear second
  mainpad->cd();
  mainpad->SetLogy(0);
  histV1->SetMaximum( (max>0 ? max*1.05 : max/1.05) );
  histV1->SetMinimum( (min>0 ? min/1.05 : min*1.05) );
  filenamecopy.Prepend(outdir+"_lin/");
  canvas->cd();
  canvas->Print(filenamecopy.Data());

  //++++++++++++++++++++ delete objects +++++++++++++++++++//

  if ( st1 ) {delete st1;}
  if ( isHist1 && isHist2 ) {
    if ( st2 ) {delete st2;}
  }

  if ( leg ) {delete leg;}

  if ( ratioline ) {delete ratioline;}
  if ( hratio ) {delete hratio;}

  if ( histV1 ) {delete histV1;}
  if ( histV2 ) {delete histV2;}

  if ( hBinTempV1 ) {delete hBinTempV1;} 
  if ( hBinTempV2 ) {delete hBinTempV2;}

  if ( mainpad ) {delete mainpad;}
  if ( respad )  {delete respad;}

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                //
//                                                                                                //
//                           END OF Create Plots for TProfiles                                    //
//                                                                                                //
//                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

void setTDRStyle(TStyle *& tdrStyle) {
  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  
  tdrStyle->SetMarkerStyle(20);
  tdrStyle->SetMarkerSize(0.6);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

  // For the Global title:
  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.052, "XYZ");
  tdrStyle->SetTitleXOffset(0.875);
  tdrStyle->SetTitleYOffset(1.05);

  // For the axis labels:
  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:
  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:
  tdrStyle->SetPaperSize(20.,20.);

  tdrStyle->cd();
}

 void CMSLumi(TCanvas *& canv, const Int_t iPosX, const Int_t year, const Double_t magB) { // hacked from collisions
  canv->cd();

  TString cmsText      = "CMS";
  Double_t cmsTextFont = 61;  // default is helvetic-bold
  
  Bool_t writeExtraText  = true;
  TString extraText      = "Preliminary";
  Double_t extraTextFont = 52;  // default is helvetica-italics

  TString magBText = Form("Cosmics: %4i (%3.1f T)",year,magB) ; 
  
  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  Double_t magBTextSize     = 0.6;
  Double_t magBTextOffset   = 0.2;
  Double_t cmsTextSize      = 0.75;
  Double_t cmsTextOffset    = 0.1;  // only used in outOfFrame version
  Double_t extraTextOffset  = 0.05;  // only used in outOfFrame version

  Double_t relPosX    = 0.045;
  Double_t relPosY    = 0.035;
  Double_t relExtraDY = 1.2;
 
  // ratio of "CMS" and extra text size
  Double_t extraOverCmsTextSize  = 0.76;
 
  Bool_t outOfFrame    = false;
  if ( iPosX/10 == 0 ) {
    outOfFrame = true;
  }

  Int_t alignY_=3;
  Int_t alignX_=2;
  if (iPosX/10 == 0) {alignX_ = 1;}
  if (iPosX == 0)    {alignY_ = 1;}
  if (iPosX/10 == 1) {alignX_ = 1;}
  if (iPosX/10 == 2) {alignX_ = 2;}
  if (iPosX/10 == 3) {alignX_ = 3;}
  Int_t align_ = 10*alignX_ + alignY_;

  Double_t H = canv->GetWh();
  Double_t W = canv->GetWw();
  Double_t l = canv->GetLeftMargin();
  Double_t t = canv->GetTopMargin();
  Double_t r = canv->GetRightMargin();
  Double_t b = canv->GetBottomMargin();
  Double_t e = 0.025;

  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack);    

  Double_t extraTextSize = extraOverCmsTextSize*cmsTextSize;

  latex.SetTextFont(42);
  latex.SetTextAlign(31); 
  latex.SetTextSize(magBTextSize*t);    
  latex.DrawLatex(0.93-r,1-t+magBTextOffset*t,magBText); //  1-r, 0.93-r

  if (outOfFrame) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l+extraTextOffset,1-t+magBTextOffset*t,cmsText);
  }
  
  Double_t posX_;
  if (iPosX%10 <= 1) {
    posX_ =   l + relPosX*(1-l-r);
  }
  else if (iPosX%10 == 2) {
    posX_ =  l + 0.5*(1-l-r);
  }
  else if (iPosX%10 == 3) {
    posX_ =  1-r - relPosX*(1-l-r);
  }

  Double_t posY_ = 1-t - relPosY*(1-t-b);

  if (!outOfFrame) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextSize(cmsTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, cmsText);
    
    if (writeExtraText) {
      latex.SetTextFont(extraTextFont);
      latex.SetTextAlign(align_);
      latex.SetTextSize(extraTextSize*t);
      latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
    }
  }
  
  else if (outOfFrame && writeExtraText){
    if (iPosX == 0) {
      posX_ = l +  relPosX*(1-l-r)+0.05 + extraTextOffset;
      posY_ = 1-t+magBTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, extraText);      
  }
}

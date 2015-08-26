#include "ReleaseComparison.hh"

void V1_V2_trkComparison(const string fileName1, const string fileName2, const TString directory) {

  gROOT->SetBatch(kTRUE);

  gROOT->SetStyle("Default");
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(111101);

  gStyle->SetOptFit(1);

  TCanvas *canvas = new TCanvas;

  // fileName1 --> REFERENCE
  int pos = fileName1.find("_R0");
  std::string runString1 = fileName1.substr (pos+5,6);
  int pos1 = fileName1.find("CMSSW")+6;
  int pos2 = fileName1.find("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-PRE");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-FT");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-74X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-75X");
  std::string relString1 = fileName1.substr (pos1,pos2-pos1); 
  TFile *file1 = TFile::Open(fileName1.c_str());
  std::cout << "Getting histos for run number... " << runString1 
	    <<" for release " << relString1 << std::endl;  
  if ( file1->IsZombie() )
    std::cout << "File: " << fileName1 << " cannot be opened!" << std::endl;
  //  relString1 += " - REF";

  // fileName2 --> NEW
  pos = fileName2.find("_R0");
  std::string runString2 = fileName2.substr (pos+5,6);
  pos1 = fileName2.find("CMSSW")+6;
  pos2 = fileName2.find("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-PRE");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-FT");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-74X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-75X");
  std::string relString2 = fileName2.substr (pos1,pos2-pos1);
  TFile *file2 = TFile::Open(fileName2.c_str());
  std::cout << "Getting histos for run number... " << runString2 
    	    <<" for release " << relString2 << std::endl;  
  if ( file2->IsZombie() )
    std::cout << "File: " << fileName2 << " cannot be opened!" << std::endl;
  //  relString2 += " - NEW";

  //******************* Get histo integrals ***********************//
  TString tempname1 = "DQMData/Run ";
  tempname1.Append(runString1);
  tempname1.Append("/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties/NumberOfTracks_GenTk");

  TH1F * hNormTempV1   = (TH1F*)file1->Get(tempname1.Data());
  Double_t V1_integral = hNormTempV1->GetEntries();
  delete hNormTempV1;

  TString tempname2 = "DQMData/Run ";
  tempname2.Append(runString2);
  tempname2.Append("/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties/NumberOfTracks_GenTk");

  TH1F * hNormTempV2 = (TH1F*)file2->Get(tempname2.Data());
  Double_t V2_integral = hNormTempV2->GetEntries();

  delete hNormTempV2;
  
  //******************* done with scaling ***********************//

  // Histograms in BeamSpotParameters directory
  TString dirname = "";

  // Histograms in dEdx directory 
  // 2PO
  dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2PO";
  createPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // 2SO
  dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2SO";
  createPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // 2SP
  dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2SP";
  createPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Hists in dEdx Hits Info
  dirname = "/Tracking/Run summary/dEdxHits/dedxHitInfo";
  createPlot("Harm2_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Pixel_dEdxPerCluster_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Strip_dEdxPerCluster_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Histograms in SiStrip --> Used for validation of noCCC
  dirname = "/SiStrip/Run summary/MechanicalView";
  TString histname = "Summary_ClusterChargePerCMfromOrigin";
  createPlot(histname+"_OffTrack__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  histname = "Summary_ClusterChargePerCMfromTrack";  
  createPlot(histname+"__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  histname = "Summary_ClusterCharge";  
  createPlot(histname+"_OffTrack__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OffTrack__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot(histname+"_OnTrack__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Histograms in GeneralProperties directory
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties";
  createPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // High purity histos
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties";
  createPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);  // first set is copy of genTrack distributions
  createPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Additional Plots for HP --> SIP, DOCA
  createPlot("DistanceOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);  // additional distributions for goodTracks
  createPlot("DistanceOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SIP2DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SIP3DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SIPDxyToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SIPDxyToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SIPDzToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SIPDzToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("xPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("yPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("zPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Histograms in HitProperties directory --> generalTracks
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties";
  createPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TIB";
  createPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TOB";
  createPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TID";
  createPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TEC";
  createPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixBarrel";
  createPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixEndcap";
  createPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Histograms in HitProperies directory --> HighPurity
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties";
  createPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TIB";
  createPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TOB";
  createPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TID";
  createPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TEC";
  createPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/PixBarrel";
  createPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/PixEndcap";
  createPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Track building info --> count seeds in gen tracks
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/TrackBuilding";

  // detached triplets
  createPlot("NumberOfSeeds_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // initialStep
  createPlot("NumberOfSeeds_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // low pt triplet
  createPlot("NumberOfSeeds_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // mixed triplet
  createPlot("NumberOfSeeds_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // muon in out
  createPlot("NumberOfSeeds_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // muon out in
  createPlot("NumberOfSeeds_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // pixelLess
  createPlot("NumberOfSeeds_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // pixel pair
  createPlot("NumberOfSeeds_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // tobtec
  createPlot("NumberOfSeeds_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedEta_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPhi_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("SeedPt_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Offline Primary vertices
  dirname = "/OfflinePV/Run summary/Alignment";
  createPlot("chi2ndf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("chi2prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("dxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("dz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("ntracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("sumpt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/OfflinePV/Run summary/offlinePrimaryVertices";
  createPlot("otherDiffX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherDiffY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherPosX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherPosY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherPosZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherVtxChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherVtxNdf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherVtxProb", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("otherVtxTrksNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  createPlot("tagDiffX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagDiffY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagPosX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagPosY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagPosZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagVtxChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagVtxNdf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagVtxProb", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("tagVtxTrksNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  createPlot("vtxNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  // Packed Candidate - miniAOD validation
  dirname = "/Tracking/Run summary/PackedCandidate";
  createPlot("diffCharge", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffEtaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffTheta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffThetaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPhiError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPtError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffQoverp", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffQoverpError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffVx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffVy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffVz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternHasValidHitInFirstPixelBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternNumberOfLostPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternNumberOfValidHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternNumberOfValidPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffIsHighPurity", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffLostInnerHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNdof", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNormalizedChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNumberOfHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNumberOfPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);

  dirname = "/Tracking/Run summary/PackedCandidate/lostTracks";
  createPlot("diffCharge", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffEtaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffTheta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffThetaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPhiError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPtError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffQoverp", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffQoverpError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffPz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffVx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffVy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffVz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternHasValidHitInFirstPixelBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternNumberOfLostPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternNumberOfValidHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffHitPatternNumberOfValidPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffIsHighPurity", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffLostInnerHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNdof", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNormalizedChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNumberOfHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  createPlot("diffNumberOfPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, directory);
  
  delete file1;
  delete file2;
  delete canvas;
}

bool createPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, const TString directory) {
  setTDRStyle();

  canvas->cd();
  TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.0,1.0,0.8);
  mainpad->Draw();
  mainpad->cd();

  // ************ Get name of histos and get histos ************* //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);

  TString hnameV1 = basename1; // reference
  hnameV1.Append(dirname+"/");
  hnameV1.Append(hname);

  if ( (!dirname.Contains("SiStrip",TString::kExact)) && (!dirname.Contains("TrackBuilding",TString::kExact)) && (!dirname.Contains("dEdx",TString::kExact)) && (!dirname.Contains("OfflinePV",TString::kExact)) && (!dirname.Contains("PackedCandidate",TString::kExact)) ) {
    hnameV1.Append("_GenTk");
  }

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);

  TString hnameV2 = basename2;
  hnameV2.Append(dirname+"/");
  hnameV2.Append(hname);

  if ( (!dirname.Contains("SiStrip",TString::kExact)) && (!dirname.Contains("TrackBuilding",TString::kExact)) && (!dirname.Contains("dEdx",TString::kExact)) && (!dirname.Contains("OfflinePV",TString::kExact)) && (!dirname.Contains("PackedCandidate",TString::kExact)) ) {
    hnameV2.Append("_GenTk");
  }

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
    std::cout << "Well, couldn't grab this hist from either file, just go to the next one." << std::endl;
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

  Double_t h1_xlow = hBinTempV1->GetXaxis()->GetBinLowEdge(hBinTempV1->GetXaxis()->GetFirst());
  Double_t h2_xlow = hBinTempV2->GetXaxis()->GetBinLowEdge(hBinTempV2->GetXaxis()->GetFirst());

  Double_t h1_xup = hBinTempV1->GetXaxis()->GetBinUpEdge(hBinTempV1->GetXaxis()->GetLast());
  Double_t h2_xup = hBinTempV2->GetXaxis()->GetBinUpEdge(hBinTempV2->GetXaxis()->GetLast());

  Int_t h1_nbins = hBinTempV1->GetNbinsX();
  Int_t h2_nbins = hBinTempV2->GetNbinsX();

  Double_t h1_binWidth = (h1_xup - h1_xlow) / (Double_t)h1_nbins;
  Double_t h2_binWidth = (h2_xup - h2_xlow) / (Double_t)h2_nbins;

  Double_t h1_nEntries = hBinTempV1->GetEntries();
  Double_t h2_nEntries = hBinTempV2->GetEntries();

  if ((h1_xlow == h2_xlow) && (h1_xup == h2_xup) && (h1_binWidth == h2_binWidth)){
    histV1 = (TH1F*)hBinTempV1->Clone();//V1file->Get(hnameV1);
    histV2 = (TH1F*)hBinTempV2->Clone();//V2file->Get(hnameV2);
  }
  else if((h1_xlow == h2_xlow) && (h1_xup < h2_xup) && (h1_binWidth == h2_binWidth)){ // Fill h1 from h1xlow to h1high with h1 info, and up to h2high, fill zero 
    histV2 = (TH1F*)hBinTempV2->Clone();//V2file->Get(hnameV2); // copy histV2 

    histV1 = new TH1F(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h2_nbins,h2_xlow,h2_xup);
    histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
    histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());
    for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){
      if (ibin <= h1_nbins){
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin));
      }
      else if (ibin > h1_nbins){
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
      else if (ibin > h2_nbins){
	histV2->SetBinContent(ibin,0.0); 
      }
    }
  }
  else if(h1_binWidth != h2_binWidth){
    if ((h1_xlow < h2_xlow) && (h1_xup == h2_xup)){
      histV1 = (TH1F*)hBinTempV1->Clone();//V1file->Get(hnameV1);

      histV2 = new TH1F(hBinTempV2->GetName(),hBinTempV2->GetTitle(),h2_nbins,h1_xlow,h2_xup);
      histV2->SetXTitle(hBinTempV2->GetXaxis()->GetTitle());
      histV2->SetYTitle(hBinTempV2->GetYaxis()->GetTitle());
      for (Int_t ibin = 1; ibin <= h1_nbins; ibin++){
	histV2->SetBinContent(ibin,hBinTempV2->GetBinContent(ibin));
      }
    }
    else if ((h2_xlow < h1_xlow) && (h1_xup == h2_xup)){
      histV2 = (TH1F*)hBinTempV2->Clone();//V2file->Get(hnameV2);

      histV1 = new TH1F(hBinTempV1->GetName(),hBinTempV1->GetTitle(),h1_nbins,h2_xlow,h1_xup);
      histV1->SetXTitle(hBinTempV1->GetXaxis()->GetTitle());
      histV1->SetYTitle(hBinTempV1->GetYaxis()->GetTitle());
      for (Int_t ibin = 1; ibin <= h2_nbins; ibin++){
	histV1->SetBinContent(ibin,hBinTempV1->GetBinContent(ibin));
      }
    }
  }
  else{
    std::cout << "Bin Check Failed... here's what happened: " << std::endl;
    std::cout << "histV1 failed on " << hnameV1  << std::endl << " for file " << V1file->GetName() << std::endl;
    std::cout << "       bin info: " << h1_xlow << " " << h1_xup << " " << h1_nbins << std::endl;
    std::cout << "histV2 failed on " << hnameV2  << std::endl << " for file " << V2file->GetName() << std::endl;
    std::cout << "       bin info: " << h2_xlow << " " << h2_xup << " " << h2_nbins << std::endl;
    exit(1);
  }

  histV1->SetEntries(h1_nEntries);
  histV2->SetEntries(h2_nEntries);

  // Don't look at zero bin -- > Also could use this for truncation and bin setting -->Range is binlower to upper
  //  Int_t range_upper = histV1->GetXaxis()->GetLast();
  //  histV1->GetXaxis()->SetRangeUser(1,range_upper);
  //  histV2->GetXaxis()->SetRangeUser(1,range_upper);

  //*****NORMALIZING V1-V2****************************************

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
  //*****NORMALIZING V1-V2*end***************************************

  //***Name the files under comparison***
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

  if (hname.Contains("algorithm",TString::kExact)){
    histV1->GetXaxis()->SetRangeUser(4,17);
    histV2->GetXaxis()->SetRangeUser(4,17);
  }

  // options for drawing
  double max = 0;
  double V1max = histV1->GetBinContent(histV1->GetMaximumBin());
  double V2max = histV2->GetBinContent(histV2->GetMaximumBin());

  max = (V1max>V2max) ? V1max : V2max;
  histV1->SetLineStyle(1);
  histV1->GetYaxis()->SetLabelSize(0.038);
  histV1->SetLineWidth(5);
  histV1->SetLineColor(kBlue); // h1 is ref ...originally was red... switched to match MC comparisons
  histV1->SetMaximum(max*(1.1));
  histV2->SetLineWidth(3);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 

  if (!isHist1) { // only plot hist1 in case of missing hists
    histV1->SetLineColor(kRed);
    histV1->SetLineWidth(3);
  }

  if ( hname.Contains("NumberOfTracks",TString::kExact) || hname.Contains("TrackPt",TString::kExact) || hname.Contains("Chi2",TString::kExact) || hname.Contains("DistanceOfClosestApproach",TString::kExact) || hname.Contains("algorithm",TString::kExact) || hname.Contains("TrackPz",TString::kExact) || hname.Contains("TrackP_ImpactPoint",TString::kExact) || hname.Contains("TrackPErrOverP",TString::kExact) || hname.Contains("TrackPzErrOverPz",TString::kExact) || hname.Contains("SIP",TString::kExact) || hname.Contains("NumberOfMeanLayersPerTrack",TString::kExact) || hname.Contains("NumberOfMeanRecHitsPerTrack",TString::kExact) ) {
    mainpad->SetLogy(1);
  }
  else if ( hname.Contains("NumberOfLayersPerTrack",TString::kExact) && !hname.Contains("NumberOfLayersPerTrack_",TString::kExact) ){
    mainpad->SetLogy(1);
  }
  else if ( hname.Contains("NumberOfRecHitsPerTrack",TString::kExact) && !hname.Contains("NumberOfRecHitsPerTrack_",TString::kExact) ){
    mainpad->SetLogy(1);
  }
  else if ( hname.Contains("NumberOfLostRecHitsPerTrack",TString::kExact) ){
    mainpad->SetLogy(1);
  }
  else if ( dirname.Contains("SiStrip",TString::kExact) || dirname.Contains("dEdx",TString::kExact) || dirname.Contains("TrackBuilding",TString::kExact) ){
    mainpad->SetLogy(1);
  }
  else if ( dirname.Contains("OfflinePV",TString::kExact) ){
    mainpad->SetLogy(1);
  }
  else{
    mainpad->SetLogy(0);
  }

  if ( (hname.Contains("NumberOfTracks",TString::kExact)) && (dirname.Contains("highPurityTracks/pt_1/GeneralProperties",TString::kExact)) ){
    histV1->GetXaxis()->SetRangeUser(0,1000);
    histV2->GetXaxis()->SetRangeUser(0,1000);
  }
  else if (hname.Contains("Chi2oNDF",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,10);
    histV2->GetXaxis()->SetRangeUser(0,10);
  }

  if (dirname.Contains("PackedCandidate",TString::kExact)) {
    histV1->GetXaxis()->SetTitle(histV1->GetTitle());
    histV1->GetYaxis()->SetTitle("Number of Tracks");
  }

  if (dirname.Contains("OfflinePV",TString::kExact)) {
    if (dirname.Contains("Alignment",TString::kExact)) {
      if ( (hname.Contains("ntracks",TString::kExact)) || (hname.Contains("sumpt",TString::kExact)) ) {
	if (hname.Contains("ntracks",TString::kExact)) {
	  histV1->GetXaxis()->SetTitle("Number of PV Tracks (p_{T} > 1 GeV)");
	}
	else {
	  histV1->GetXaxis()->SetTitle("Sum p_{T} of PV Tracks (p_{T} > 1 GeV)");
	}
	histV1->GetYaxis()->SetTitle("Number of Events");
      }
      else {
	histV1->GetYaxis()->SetTitle("Number of PV Tracks");
	if (hname.Contains("chi2ndf",TString::kExact)) {
	  histV1->GetXaxis()->SetTitle("PV Tracks (p_{T} > 1 GeV) #chi^{2}/ndof");
	}
	else if (hname.Contains("chi2prob",TString::kExact)) {
	  histV1->GetXaxis()->SetTitle("PV Tracks (p_{T} > 1 GeV) #chi^{2} probability");
	}
	else if (hname.Contains("chi2prob",TString::kExact)) {
	  histV1->GetXaxis()->SetTitle("PV Tracks (p_{T} > 1 GeV) #chi^{2} probability");
	}
	else if (hname.Contains("dxy",TString::kExact)) {
	  histV1->GetXaxis()->SetTitle("PV Tracks (p_{T} > 1 GeV) d_{xy} (cm)");
	}
	else if (hname.Contains("dz",TString::kExact)) {
	  histV1->GetXaxis()->SetTitle("PV Tracks (p_{T} > 1 GeV) d_{z} (cm)");
	}
      }
    }  // end check over alignment names
    
    else { // now in offline whatever
      TString nametag = "";
      if (hname.Contains("other",TString::kExact)){
	nametag = "other";
	histV1->GetYaxis()->SetTitle("Number of Vertices");
      }
      else if (hname.Contains("tag",TString::kExact)){
	nametag = "tag";
	histV1->GetYaxis()->SetTitle("Number of Vertices");
      }
      else {
	histV1->GetXaxis()->SetTitle("Number of Primary Vertices");
	histV1->GetYaxis()->SetTitle("Number of Events");
      }

      if (hname.Contains("DiffX",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("X distance from BeamSpot (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("DiffY",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("Y distance from BeamSpot (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("PosX",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("Position X Coordinate (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("PosY",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("Position Y Coordinate (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("PosZ",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("Position Z Coordinate (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("Chi2",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("#chi^{2} (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("Ndf",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("#chi^{2} / ndf (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("Prob",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("#chi^{2} probability (%s Vtx)",nametag.Data()));
      }
      else if (hname.Contains("TrksNbr",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(Form("Reconstructed Tracks in Vertex (%s Vtx)",nametag.Data()));
      }
    }
  } // end check over OfflinePV to set titles
  
  if (hname.Contains("Summary_ClusterCharge",TString::kExact) ){
    histV1->GetYaxis()->SetTitle("Numer of Charge Clusters");
    if (hname.Contains("PerCMfromOrigin",TString::kExact) ){
      TString detname  = hname;
      
      TString identstr = "Track__";
      Ssiz_t  trackpos = detname.Index(identstr.Data());
      Ssiz_t  tklength = identstr.Length();
      Ssiz_t  detpos   = trackpos+tklength;
      
      detname.Remove(0,detpos);
      
      TString dblws = "__";
      Ssiz_t  wspos = detname.Index(dblws.Data());   
      Ssiz_t  wslen = dblws.Length();
      detname.Replace(wspos,wslen," ");
      
      if (hname.Contains("On",TString::kExact) ){
	histV1->GetXaxis()->SetTitle(Form("%s dQ / dx from Origin ON Track [C/cm]",detname.Data()));
      }
      else if (hname.Contains("Off",TString::kExact) ){
	histV1->GetXaxis()->SetTitle(Form("%s dQ / dx from Origin OFF Track [C/cm]",detname.Data()));
      }
    } //fromOrigin x axis title
    else if (hname.Contains("PerCMfromTrack",TString::kExact) ){
      TString detname  = hname;
      
      TString identstr = "Track__";
      Ssiz_t  trackpos = detname.Index(identstr.Data());
      Ssiz_t  tklength = identstr.Length();
      Ssiz_t  detpos   = trackpos+tklength;
      
      detname.Remove(0,detpos);
      
      TString dblws = "__";
      Ssiz_t  wspos = detname.Index(dblws.Data());   
      Ssiz_t  wslen = dblws.Length();
      detname.Replace(wspos,wslen," ");
      
      histV1->GetXaxis()->SetTitle(Form("%s dQ / dx from Track [C/cm]",detname.Data()));
    } //fromTrack x axis title
  }

  histV1->Draw(); // Draw old histo first, ratio is new/old
  if (isHist1 && isHist2) {
    histV2->Draw("sames");
  }

  mainpad->Update();

  TLegend *leg;
  if ( (hname.Contains("NumberOfTracks",TString::kExact)) || (hname.Contains("vtxNbr",TString::kExact)) || (hname.Contains("algorithm",TString::kExact)) || (hname.Contains("NumberOfMeanRecHitsPerTrack",TString::kExact)) || (hname.Contains("NumberOfMeanLayersPerTrack",TString::kExact)) ){
    leg = new TLegend(0.60,0.88,0.76,0.97);
  }
  else if ( hname.Contains("Summary_ClusterChargePerCMfromOrigin",TString::kExact) || hname.Contains("Summary_ClusterChargePerCMfromTrack",TString::kExact) ){
    leg = new TLegend(0.18,0.88,0.34,0.97);
  }
  else{
    leg = new TLegend(0.32,0.88,0.48,0.97);
  }
  leg->SetTextSize(0.042);
  leg->SetTextFont(42);
  leg->SetFillColor(10); 
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histV1, histV1->GetName(), "L" );
  if (isHist1 && isHist2) {
    leg->AddEntry(histV2, histV2->GetName(), "L" );
  }
  leg->Draw("SAME");

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  TPaveStats *st2;
  if (isHist1 && isHist2){
    st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
  }
  if ( (hname.Contains("Chi2Prob",TString::kExact)) || hname.Contains("FractionOfGoodTracks",TString::kExact) ) {
    st1->SetX1NDC(0.50);
    st1->SetX2NDC(0.71);
    if (isHist1 && isHist2){
      st2->SetX1NDC(0.50);  
      st2->SetX2NDC(0.71);    
    }
  }
  else{
    st1->SetX1NDC(0.77);
    st1->SetX2NDC(0.98);
    if (isHist1 && isHist2){
      st2->SetX1NDC(0.77);  
      st2->SetX2NDC(0.98);    
    }
  }

  st1->SetY1NDC(0.80);
  st1->SetY2NDC(0.97);
  Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  Double_t gaph = 0.02;
  if (isHist1 && isHist2){
    st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
    st2->SetY2NDC(st1->GetY1NDC() - gaph);
  }

  // Draw ratio histogram

  canvas->cd();
  TPad* respad = new TPad("respad","respad",0.0,0.81,1.0,0.98);
  respad->SetTopMargin(1.05);
  respad->Draw();
  respad->cd();
  TH1F* hratio = (TH1F*) histV2->Clone("hratio");
  if (hname.Contains("algorithm",TString::kExact)){
    hratio->GetXaxis()->SetRangeUser(4,17); // algo
  }
  hratio->Divide(histV1);
  hratio->SetMaximum(hratio->GetMaximum()*1.1);
  hratio->SetMinimum(hratio->GetMinimum()/1.1);
  //if (hratio->GetMinimum()==0.0) hratio->SetMinimum(1.0/hratio->GetMaximum());
  //    hratio->SetMinimum(1.0/hratio->GetMaximum());
  hratio->GetYaxis()->SetLabelSize(0.1);
  //    hratio->GetYaxis()->SetRangeUser(0,2);
  hratio->GetXaxis()->SetLabelSize(0);
  hratio->GetXaxis()->SetTitleSize(0);
  hratio->GetYaxis()->SetTitleSize(0.22);
  hratio->GetYaxis()->SetTitleOffset(0.26);
  hratio->GetYaxis()->SetLabelSize(0.2);
  hratio->GetYaxis()->SetNdivisions(5);
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
  hratio->Draw();

  // Compare parameters of histograms
  /*  double Entries1 = histV1->GetEntries();
  double Entries2 = histV2->GetEntries();
    if (Entries1 != Entries2) {
    std::cout<<" Difference in # of ENTRIES for " <<hname<< std::endl;
    std::cout<<"\t Entries1 = " << Entries1 << "\t Entries2 = " << Entries2 << std::endl;
  }

  double Mean1 = histV1->GetMean();
  double Mean2 = histV2->GetMean();
  if (Mean1 != Mean2) {
    std::cout<<" Difference in MEANS for " <<hname<< std::endl;
    std::cout<<"\t Mean1 = " << Mean1 << "\t Mean2 = " << Mean2 << std::endl;
  }

  double RMS1 = histV1->GetRMS();
  double RMS2 = histV2->GetRMS();
  if (RMS1 != RMS2) {
    std::cout<<" Difference in RMS for " <<hname<< std::endl;
    std::cout<<"\t RMS1 = " << RMS1 << "\t RMS2 = " << RMS2 << std::endl;
  }
  */

  TString filename = hname;
 
  // shorten name of SiStrip plots for output .png
  if (dirname.Contains("SiStrip",TString::kExact) ){
    if (filename.Contains("PerCMfromOrigin",TString::kExact) ){
      TString replacestr  = "Summary_ClusterChargePerCMfromOrigin";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "Sum_CCPerCMOrigin";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("PerCMfromTrack",TString::kExact) ){
      TString replacestr  = "Summary_ClusterChargePerCMfromTrack";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "Sum_CCPerCMTrack";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("Summary_ClusterCharge_",TString::kExact) ){
      TString replacestr  = "Summary_ClusterCharge_";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "Sum_CC_";
      filename.Replace(filenamepos,length,toreplace);
    }
  }

  // drop _ at end of dEdx plots
  if (dirname.Contains("dEdx",TString::kExact) ){
    if (filename.Contains("PerTrack_",TString::kExact)) {  
      TString replacestr  = "PerTrack_";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "PerTrack";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("PerCluster_",TString::kExact)) {  
      TString replacestr  = "PerCluster_";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "PerCluster";
      filename.Replace(filenamepos,length,toreplace);
    }
  }

  // drop extra duplicate modifier from track building plots
  if (dirname.Contains("TrackBuilding",TString::kExact) ){
    if (filename.Contains("detachedTripletStepSeeds",TString::kExact)) {  
      TString replacestr  = "detachedTripletStepSeeds_detachedTripletStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "detachedTripletStep";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("initialStepSeeds",TString::kExact)) {  
      TString replacestr  = "initialStepSeeds_initialStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "initialStep";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("lowPtTripletStepSeeds",TString::kExact)) {  
      TString replacestr  = "lowPtTripletStepSeeds_lowPtTripletStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "lowPtTripletStep";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("mixedTripletStepSeeds",TString::kExact)) {  
      TString replacestr  = "mixedTripletStepSeeds_mixedTripletStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "mixedTripletStep";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("muonSeededSeedsInOut",TString::kExact)) {  
      TString replacestr  = "muonSeededSeedsInOut_muonSeededStepInOut";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "muonSeededStepInOut";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("muonSeededSeedsOutIn",TString::kExact)) {  
      TString replacestr  = "muonSeededSeedsOutIn_muonSeededStepOutIn";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "muonSeededStepOutIn";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("pixelLessStepSeeds",TString::kExact)) {  
      TString replacestr  = "pixelLessStepSeeds_pixelLessStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "pixelLessStep";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("pixelPairStepSeeds",TString::kExact)) {  
      TString replacestr  = "pixelPairStepSeeds_pixelPairStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "pixelPairStep";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("tobTecStepSeeds",TString::kExact)) {  
      TString replacestr  = "tobTecStepSeeds_tobTecStep";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "tobTecStep";
      filename.Replace(filenamepos,length,toreplace);
    }
  } // end concatinating track building strings

  // place output plots in right place
  if (dirname.Contains("SiStrip",TString::kExact)){
    if (filename.Contains("TEC",TString::kExact)){
      filename.Prepend("SiStrip/TEC/");
    } 
    else if (filename.Contains("TIB",TString::kExact)){
      filename.Prepend("SiStrip/TIB/");
    } 
    else if (filename.Contains("TID",TString::kExact)){
      filename.Prepend("SiStrip/TID/");
    } 
    else if (filename.Contains("TOB",TString::kExact)){
      filename.Prepend("SiStrip/TOB/");
    } 
  }
  else if (dirname.Contains("highPurityTracks/pt_1",TString::kExact)){
    if (dirname.Contains("GeneralProperties",TString::kExact)){
      filename.Prepend("HPTks/GenProps/");
    }
    else if (dirname.Contains("HitProperties",TString::kExact)){
      filename.Prepend("HPTks/HitProps/");
    }
  }
  else if (dirname.Contains("generalTracks",TString::kExact)){ 
    if (dirname.Contains("GeneralProperties",TString::kExact)){
      filename.Prepend("genTks/GenProps/");
    }
    else if (dirname.Contains("HitProperties",TString::kExact)){
      filename.Prepend("genTks/HitProps/");
    }
    else if (dirname.Contains("TrackBuilding",TString::kExact)){
      filename.Prepend("genTks/TkBuilding/");
    }
  }
  else if (dirname.Contains("dEdx",TString::kExact)){ 
    if (dirname.Contains("dedxDQMHarm2PO",TString::kExact)){
      filename.Prepend("dEdx/PO/");
    }
    else if (dirname.Contains("dedxDQMHarm2SO",TString::kExact)){
      filename.Prepend("dEdx/SO/");
    }
    else if (dirname.Contains("dedxDQMHarm2SP",TString::kExact)){
      filename.Prepend("dEdx/SP/");
    }
    else if (dirname.Contains("dEdxHits/dedxHitInfo",TString::kExact)){
      filename.Prepend("dEdx/HitInfo/");
    }
  }
  else if (dirname.Contains("OfflinePV",TString::kExact)) {
    if (dirname.Contains("Alignment",TString::kExact)) {
      filename.Prepend("PV/Alignment/");
    }
    else if (dirname.Contains("offlinePrimaryVertices",TString::kExact)) {
      filename.Prepend("PV/offlinePVs/");
    }
  }
  else if (dirname.Contains("PackedCandidate",TString::kExact)) {
    if (dirname.Contains("lostTracks",TString::kExact)) {
      filename.Prepend("PackCand/lostTks/");
    }
    else {
      filename.Prepend("PackCand/MatchedTks/");
    }
  }

  filename.Prepend(directory.Data());
  filename.Append(".png");

  canvas->Print(filename);

  if ( st1 ) {delete st1;}
  if ( isHist1 && isHist2 ) {
    if ( st2 ) {delete st2;}
  }

  if ( leg ) {delete leg;}

  if ( hratio ) {delete hratio;}

  if ( histV1 ) {delete histV1;}
  if ( histV2 ) {delete histV2;}

  if ( hBinTempV1 ) {delete hBinTempV1;} 
  if ( hBinTempV2 ) {delete hBinTempV2;}

  if ( mainpad ) {delete mainpad;}
  if ( respad )  {delete respad;}

  return true;
}

void setTDRStyle() {

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

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

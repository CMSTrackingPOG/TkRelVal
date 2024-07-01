#include "ReleaseComparison.hh"
#include "PlotFunctions.hh"

void V1_V2_trkComparison(const TString fileName1, const TString labelName1, const TString fileName2, const TString labelName2,  
			 const TString directory, const TString era, const Double_t lumi, const bool full) 
{
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
  setTDRStyle(tdrStyle);

  gROOT->SetBatch(kTRUE);
  gStyle->SetPalette(1);
  gStyle->SetOptStat("emroun");
  gStyle->SetOptFit(1);
  gROOT->ForceStyle();
  
  Int_t pos = fileName1.Index("_R0");
  TString runString1(fileName1(pos+5,6));
  TString relString1 = labelName1;

  TFile *file1 = TFile::Open(fileName1.Data());
  std::cout << "Getting histos for run number... " << runString1.Data() 
	    <<" for release " << relString1.Data() << std::endl;  
  if ( file1->IsZombie() )
    std::cout << "File: " << fileName1.Data() << " cannot be opened!" << std::endl;
  pos = fileName2.Index("_R0");
  TString runString2(fileName2(pos+5,6));
  TString relString2 = labelName2;
  TFile *file2 = TFile::Open(fileName2.Data());
  std::cout << "Getting histos for run number... " << runString2.Data() 
    	    <<" for release " << relString2.Data() << std::endl;  
  if ( file2->IsZombie() )
    std::cout << "File: " << fileName2.Data() << " cannot be opened!" << std::endl;
  //  relString2 = "PRnewco";
  
  //================= Print CMS Lumi on these guys =================//

  // Double_t lumi = 0;
  Double_t tev = 13.6;

  //====================== Make master canvas  ======================// 
  TCanvas *canvas = new TCanvas("master canv","");

  //====================== Get histo integrals ======================// 
  // ---> Scale all histos (besides PV/Aignment) by nEvents

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

  //==================== PV/Alignment Integrals ====================// 

  TString tempname1_al = "DQMData/Run ";
  tempname1_al.Append(runString1);
  tempname1_al.Append("/OfflinePV/Run summary/Alignment/ntracks");

  TH1F * hNormTempV1_al   = (TH1F*)file1->Get(tempname1_al.Data());
  Double_t V1_integral_al = hNormTempV1_al->GetEntries();
  delete hNormTempV1_al;

  TString tempname2_al = "DQMData/Run ";
  tempname2_al.Append(runString2);
  tempname2_al.Append("/OfflinePV/Run summary/Alignment/ntracks");

  TH1F * hNormTempV2_al   = (TH1F*)file2->Get(tempname2_al.Data());
  Double_t V2_integral_al = hNormTempV2_al->GetEntries();
  delete hNormTempV2_al;

  //====================== done with scaling ======================// 

  // Histograms in BeamSpotParameters directory
  TString dirname = ""; // input root file directory
  TString outdir  = ""; // output file directory

  // PV plots inside Tracking (not offlinePV folder)
  dirname = "/Tracking/Run summary/PrimaryVertices/highPurityTracks/pt_0to1/offline";
  outdir  = directory+"/PV_HPTks/offline";
  createTH1FPlot("FractionOfGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("GoodPVtxNumberOfTracks_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("GoodPVtxSumPt_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfBADndofPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  if (full) { // profile plots
    dirname = "/Tracking/Run summary/PrimaryVertices/highPurityTracks/pt_0to1/offline/PUmonitoring/VsGoodPVtx";
    createTProfPlot("FractionOfGoodPVtxVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("FractionOfGoodPVtxVsPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodPVtxChi2ProbVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodPVtxChi2oNDFVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodPVtxNumberOfTracksVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodPVtxSumPtVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfBADndofPVtxVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfPVtxVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  if (full)
  {
    // Histograms in dEdx directory 
    // 2PO
    dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2PO";
    outdir  = directory+"/dEdx/PO";
    createTH1FPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    
    // 2SO
    dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2SO";
    outdir  = directory+"/dEdx/SO";
    createTH1FPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

    // 2SP
    dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2SP";
    outdir  = directory+"/dEdx/SP";
    createTH1FPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
    // Hists in dEdx Hits Info
    dirname = "/Tracking/Run summary/dEdxHits/dedxHitInfo";
    outdir  = directory+"/dEdx/HitInfo";
    createTH1FPlot("Harm2_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("Pixel_dEdxPerCluster_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("Strip_dEdxPerCluster_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }  

  // Histograms in SiStrip --> Used for validation of noCCC
  dirname = "/SiStrip/Run summary/MechanicalView"; // could do  IsolatedBunches/MechanicalView as well
  TString histname = "Summary_ClusterChargePerCMfromTrack";  
  outdir  = directory+"/SiStrip/";
  createTH1FPlot(histname+"__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TEC", lumi, era, tev);
  createTH1FPlot(histname+"__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TEC", lumi, era, tev);
  createTH1FPlot(histname+"__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TIB", lumi, era, tev);
  createTH1FPlot(histname+"__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TID", lumi, era, tev);
  createTH1FPlot(histname+"__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TID", lumi, era, tev);
  createTH1FPlot(histname+"__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TOB", lumi, era, tev);

  // Histograms in GeneralProperties directory
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties";
  outdir  = directory+"/genTks/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxWO0VsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F plots
  createTH1FPlot("AbsDistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsNHits_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/generalTracks/PUmonitoring";
    outdir  = directory+"/genTks/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // High purity histos - dz PV0 p1? 
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/GeneralProperties";
  outdir  = directory+"/HPTks_dzPV0p1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("DistanceOfClosestApproachToPVVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("DistanceOfClosestApproachVsEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("DistanceOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxWO0VsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("xPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("xPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("yPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("yPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("zPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("zPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("AbsDistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsNHits_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DeltaZToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIP2DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIP3DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDxyToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDxyToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDzToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDzToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/PUmonitoring";
    outdir  = directory+"/HPTks_dzPV0p1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // High purity histos - 0 < pt < 1 GeV
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/GeneralProperties";
  outdir  = directory+"/HPTks_0to1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxWO0VsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("AbsDistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsNHits_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/PUmonitoring";
    outdir  = directory+"/HPTks_0to1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // High purity histos - pt > 1 GeV
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties";
  outdir  = directory+"/HPTks_gt1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("DistanceOfClosestApproachToPVVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("DistanceOfClosestApproachVsEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("DistanceOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfGoodPVtxWO0VsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("AbsDistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsNHits_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("Chi2oNDFVsPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DeltaZToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("DistanceOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // Additional Plots for HP --> SIP, DOCA
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIP2DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIP3DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDxyToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDxyToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDzToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("SIPDzToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("xPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("yPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("zPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("xPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("yPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("zPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/PUmonitoring";
    outdir  = directory+"/HPTks_gt1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // Histograms in HitProperties directory --> generalTracks
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties";
  outdir  = directory+"/genTks/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TIB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TOB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TID";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TEC";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixBarrel";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixEndcap";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // Histograms in HitProperies outdir --> HighPurity dz PV0 p1?
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties";
  outdir  = directory+"/HPTks_dzPV0p1/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TIB";
  // TProfile Plots
  if (full) {
    createTProfPlot("NumberOfLayersPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
	     
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TOB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TID";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TEC";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/PixBarrel";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/PixEndcap";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // Histograms in HitProperies outdir --> HighPurity 0 < pt < 1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/HitProperties";
  outdir  = directory+"/HPTks_0to1/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // Histograms in HitProperies outdir --> HighPurity pt > 1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties";
  outdir  = directory+"/HPTks_gt1/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TIB";
  // TProfile Plots
  if (full) {
    createTProfPlot("NumberOfLayersPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
	     
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TOB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TID";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TEC";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/PixBarrel";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/PixEndcap";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  //LS Analysis
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  //LS Analysis - HP dz PV0 p1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/LSanalysis";
  outdir  = directory+"/HPTks_dzPV0p1/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  //LS Analysis - HP 0pt1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/LSanalysis";
  outdir  = directory+"/HPTks_0to1/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  //LS Analysis - HP pt>1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/LSanalysis";
  outdir  = directory+"/HPTks_gt1/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // HitEffFromHitPattern
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitEffFromHitPattern";
  outdir  = directory+"/genTks/HitEff";
  
  // efficiencies
  if (full)
  {
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // HitEffFromHitPattern
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitEffFromHitPattern";
  outdir  = directory+"/HPTks_dzPV0p1/HitEff";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // HitEffFromHitPattern
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPattern";
  outdir  = directory+"/HPTks_gt1/HitEff";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // vs BX
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPatternVsBX";
  outdir  = directory+"/HPTks_gt1/HitEffBX";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_BX_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_BX_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // vs OnlineLUMI
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitEffFromHitPatternVsOnlineLUMI";
  outdir  = directory+"/HPTks_dzPV0p1/HitEffSL";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_LUMI_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // vs OnlineLUMI
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPatternVsOnlineLUMI";
  outdir  = directory+"/HPTks_gt1/HitEffSL";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_LUMI_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // HitEff: All
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitEffFromHitPatternAll";
  outdir  = directory+"/genTks/HitEffAll";
  
  // efficiencies
  if (full)
  {
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // HitEff: All
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitEffFromHitPatternAll";
  outdir  = directory+"/HPTks_dzPV0p1/HitEffAll";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // HitEff: All
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPatternAll";
  outdir  = directory+"/HPTks_gt1/HitEffAll";
  
  // efficiencies
  if (full)
  {
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // All vs OnlineLUMI
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitEffFromHitPatternAllVsOnlineLUMI";
  outdir  = directory+"/HPTks_dzPV0p1/HitEffAllSL";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_LUMI_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // All vs OnlineLUMI
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPatternAllVsOnlineLUMI";
  outdir  = directory+"/HPTks_gt1/HitEffAllSL";
  
  // efficiencies
  if (full)
  {
    createTH1FPlot("effic_vs_LUMI_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_PXF3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("effic_vs_LUMI_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);


  // Track building info --> count seeds in gen tracks + MVA Plots
  // detachedQuadStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/detachedQuadStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if (full) 
  {
    createTH1FPlot("FractionOfCandOverSeeds_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsEta_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsPhi_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_detachedQuadStepSeeds_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_detachedQuadStepTrackCandidates_detachedQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // detachedTripletStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/detachedTripletStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackMVA2_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackMVA2HP_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  { 
    createTH1FPlot("FractionOfCandOverSeeds_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsEta_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsPhi_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA2VsEtaProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA2VsPtProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA2HPVsEtaProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA2HPVsPtProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/detachedTripletStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  
  // highPtTripletStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/highPtTripletStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if (full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_highPtTripletStepSeeds_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_highPtTripletStepTrackCandidates_highPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  // initialStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/initialStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2HP_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA3_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA3HP_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  { 
    createTH1FPlot("FractionOfCandOverSeeds_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA3VsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA3VsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA3HPVsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA3HPVsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/initialStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  
  
  // jetCoreRegionalStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/jetCoreRegionalStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    // createTH1FPlot("NumberOfTrackingRegions_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackingRegionCandidateEta_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackingRegionCandidatePhi_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackingRegionCandidatePt_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/jetCoreRegionalStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  // lowPtQuadStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/lowPtQuadStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_lowPtQuadStepSeeds_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_lowPtQuadStepTrackCandidates_lowPtQuadStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }
  
  
  // lowPtTripletStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/lowPtTripletStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/lowPtTripletStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  

  // mixedTripletStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/mixedTripletStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2HP_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsEtaProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsPtProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsEtaProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsPtProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/mixedTripletStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  //MuonSeededStepInOut
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/muonSeededStepInOut/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsEta_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsPhi_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/muonSeededStepInOut/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  //MuonSeededStepOutIn
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/muonSeededStepOutIn/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";

  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsEta_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVsPhi_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/muonSeededStepOutIn/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  

  // pixelLessStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/pixelLessStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2HP_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsEtaProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsPtProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsEtaProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsPtProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/pixelLessStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  

  // pixelPairStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/pixelPairStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  
  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/pixelPairStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }
  
  // tobTecStep
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/tobTecStep/TrackBuilding";
  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("TrackMVA2_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  // createTH1FPlot("TrackMVA2HP_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  if(full)
  {
    createTH1FPlot("FractionOfCandOverSeeds_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsEta_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("NumberOfTrajCandsPerSeedVsPhi_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrajCandsPerSeed_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedStoppingSource_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSeta_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("StoppingSourceVSphi_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsEta_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("StoppingSourceVsPhi_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfSeeds_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedEta_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPhi_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("SeedPt_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("NumberOfTrackCandidates_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("StoppingSource_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandEta_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPhi_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("TrackCandPt_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    createTProfPlot("TrackMVA1VsPtProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsEtaProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2VsPtProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsEtaProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    // createTProfPlot("TrackMVA2HPVsPtProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  }

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/SeedMon/tobTecStep/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  if (full)
  { 
    createTH1FPlot("NumberOfSeeds_lumiFlag_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  // Pixel Primary vertices
  dirname = "/OfflinePV/Run summary/Alignment";
  outdir  = directory+"/OfflinePV/Alignment";	     
  // TProfile Plots
  createTProfPlot("dxyVsEta_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dxyVsEta_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dxyVsPhi_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dxyVsPhi_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzVsEta_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzVsEta_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzVsPhi_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzVsPhi_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  // IP errors
  createTProfPlot("dxyErrVsEta_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dxyErrVsEta_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dxyErrVsPhi_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dxyErrVsPhi_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzErrVsEta_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzErrVsEta_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzErrVsPhi_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTProfPlot("dzErrVsPhi_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);

  // TH1F Plots
  createTH1FPlot("chi2ndf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("chi2prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dxy_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dxy_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dxyErr_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dxyErr_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dz_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dz_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dzErr_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("dzErr_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("ntracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("sumpt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);

  // Resolution PV
  dirname = "/OfflinePV/Run summary/Resolution/PV";
  outdir  = directory+"/OfflinePV/ResPV";
  createTH1FPlot("pull_x", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);

  if (full)
  {
    createTH1FPlot("pull_x_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_x_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_y_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_y_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_z_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_z_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_x_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_x_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_y_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_y_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_z_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_z_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  }

  // Resolution OtherV
  dirname = "/OfflinePV/Run summary/Resolution/OtherV";
  outdir  = directory+"/OfflinePV/ResOtherV";
  createTH1FPlot("pull_x", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_x_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_y_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("pull_z_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_x_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_y_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_ntracks_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_ntracks_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_nvertices_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_nvertices_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_sumpt_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  createTH1FPlot("res_z_vs_sumpt_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);

  if (full)
  {
    createTH1FPlot("pull_x_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_x_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_y_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_y_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_z_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("pull_z_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_x_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_x_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_y_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_y_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_z_vs_instLumiScal_Mean", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
    createTH1FPlot("res_z_vs_instLumiScal_Sigma", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, era, tev);
  }

  // Offline Beamspot
  if (full)
  {
    dirname = "/OfflinePV/Run summary/offlineBeamSpot";
    outdir  = directory+"/OfflinePV/offlineBS";	     
    createTH1FPlot("bsBeamWidthX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsBeamWidthY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsDxdz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsDydz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsSigmaZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
    createTH1FPlot("bsZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  }

  // Offline PVs
  dirname = "/OfflinePV/Run summary/offlinePrimaryVertices";
  outdir  = directory+"/OfflinePV/offlinePVs";	     
  createTH1FPlot("otherDiffX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherDiffY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherErrX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherErrY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherErrZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherPosX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherPosY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherPosZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherType", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherVtxChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherVtxNdf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherVtxProb", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherVtxScore", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("otherVtxTrksNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTProfPlot("otherVtxTrksVsZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTH1FPlot("otherVtxTrksWeight", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  createTH1FPlot("tagDiffX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagDiffY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagErrX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagErrY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagErrZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagPosX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagPosY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagPosZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagType", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagVtxChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagVtxNdf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagVtxProb", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagVtxScore", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("tagVtxTrksNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTProfPlot("tagVtxTrksVsZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
  createTH1FPlot("tagVtxTrksWeight", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  createTH1FPlot("vtxNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("goodvtxNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  // V0 Monitoring
  // Ks
  if (full)
  {
    // for (const std::string& var : {"HIP_OOTpu_INpu", "HIP_OOTpu_noINpu", "HIP_noOOTpu_INpu", "noHIP_OOTpu_INpu"}) {
    for (const std::string& var : {"HIP_OOTpu_INpu", "HIP_OOTpu_noINpu", "HIP_noOOTpu_INpu"}) {
      dirname = "/Tracking/Run summary/V0Monitoring/" + TString(var.c_str()) + "/Ks";
      outdir  = directory+"/V0/" + TString(var.c_str()) + "/Ks";
      createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      // createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

      createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);

      // Ks/Lxy16
      dirname = "/Tracking/Run summary/V0Monitoring/" + TString(var.c_str()) + "/Ks/Lxy16";
      outdir  = directory+"/V0/" + TString(var.c_str()) + "/Ks_Lxy16";
      createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      
      createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);

      // Lambda
      dirname = "/Tracking/Run summary/V0Monitoring/" + TString(var.c_str()) + "/Lambda";
      outdir  = directory+"/V0/" + TString(var.c_str()) + "/Lambda";
      createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

      createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);

      // Lambda/Lxy16
      dirname = "/Tracking/Run summary/V0Monitoring/" + TString(var.c_str()) + "/Lambda/Lxy16";
      outdir  = directory+"/V0/" + TString(var.c_str()) + "/Lambda_Lxy16";
      createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
      createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

      createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
      createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, era, tev);
    }
  }

  // Packed Candidate - miniAOD validation
  dirname = "/Tracking/Run summary/PackedCandidate";
  outdir  = directory+"/PackCand/MatchedTks";	     
  createTH1FPlot("diffCharge", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDszDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDszDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDszDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaLambda", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaLambdaStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaLambdaUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiPhiStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiPhiUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovQoverpQoverp", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovQoverpQoverpStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovQoverpQoverpUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDszError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffEtaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternHasValidHitInFirstPixelBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternNumberOfLostPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternNumberOfValidHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternNumberOfValidPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffIsHighPurity", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffLostInnerHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNdof", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNormalizedChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffPt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffPtError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffVx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffVy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffVz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberPixelHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberStripHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("selectionFlow", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfPixelLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfStripLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternTrackerLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternPixelLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternStripLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberPixelLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberStripLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  dirname = "/Tracking/Run summary/PackedCandidate/lostTracks";
  outdir  = directory+"/PackCand/LostTks";
  createTH1FPlot("diffCharge", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDszDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDszDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDszDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovDxyDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaLambda", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaLambdaStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovLambdaLambdaUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiPhiStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovPhiPhiUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovQoverpQoverp", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovQoverpQoverpStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffCovQoverpQoverpUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDszError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDxyPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffDzPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffEtaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternHasValidHitInFirstPixelBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternNumberOfLostPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternNumberOfValidHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternNumberOfValidPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffIsHighPurity", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffLostInnerHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNdof", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNormalizedChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffPt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffPtError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffTrackDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffVx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffVy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffVz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberPixelHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberStripHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("selectionFlow", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfPixelLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffNumberOfStripLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternTrackerLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternPixelLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("diffHitPatternStripLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberPixelLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);
  createTH1FPlot("numberStripLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, era, tev);

  delete file1;
  delete file2;
  delete canvas;
  delete tdrStyle;
}
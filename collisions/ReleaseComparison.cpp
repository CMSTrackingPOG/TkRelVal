#include "ReleaseComparison.hh"

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
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-80X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-81X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-90X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-91X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-92X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-93X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-2016");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.Index("-2017");
  TString relString1(fileName1(pos1,pos2-pos1)); 
  TFile *file1 = TFile::Open(fileName1.Data());
  std::cout << "Getting histos for run number... " << runString1.Data() 
	    <<" for release " << relString1.Data() << std::endl;  
  if ( file1->IsZombie() )
    std::cout << "File: " << fileName1.Data() << " cannot be opened!" << std::endl;
  //  relString1 = "PRref";

  // fileName2 --> NEW
  pos = fileName2.Index("_R0");
  TString runString2(fileName2(pos+5,6));
  pos1 = fileName2.Index("CMSSW")+6;
  pos2 = fileName2.Index("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-80X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-81X");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-90X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-91X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-92X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-93X");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-2016");  
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.Index("-2017");  
  TString relString2(fileName2(pos1,pos2-pos1));
  TFile *file2 = TFile::Open(fileName2.Data());
  std::cout << "Getting histos for run number... " << runString2.Data() 
    	    <<" for release " << relString2.Data() << std::endl;  
  if ( file2->IsZombie() )
    std::cout << "File: " << fileName2.Data() << " cannot be opened!" << std::endl;
  //  relString2 = "HLTrefer";
  
  //================= Print CMS Lumi on these guys =================//

  Double_t lumi = 0;
  Int_t    tev = 0;

  if      (atoi(runString1.Data()) == 269598){lumi = 0.00;  tev = 13;} // 2016  data, 25ns, 0T 
  else if (atoi(runString1.Data()) == 272930){lumi = 3.48;  tev = 13;} // 2016A data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 273503){lumi = 24.55; tev = 13;} // 2016B data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 274160){lumi = 17.27; tev = 13;} // 2016B data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 274199){lumi = 63.25; tev = 13;} // 2016B data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 275657){lumi = 16.67; tev = 13;} // 2016C data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 276092){lumi = 14.00; tev = 13;} // 2016C data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 276458){lumi = 32.15; tev = 13;} // 2016D data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 276807){lumi = 31.38; tev = 13;} // 2016D data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 277069){lumi = 76.49; tev = 13;} // 2016E data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 278274){lumi = 18.15; tev = 13;} // 2016F data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 278963){lumi = 37.45; tev = 13;} // 2016G data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 280349){lumi = 104.78; tev = 13;} // 2016G data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 281797){lumi = 397.99; tev = 13;} // 2016H data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 281975){lumi = 54.01; tev = 13;} // 2016H data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 282731){lumi = 48.11; tev = 13;} // 2016H data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 283685){lumi = 21.08; tev = 13;} // 2016H data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 283877){lumi = 248.88; tev = 13;} // 2016H data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 283946){lumi = 306.16; tev = 13;} // 2016H data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 295613){lumi = 7.33;  tev = 13;} // 2017A data, 25ns, 3.8T
  else if (atoi(runString1.Data()) == 297227){lumi = 22.77; tev = 13;} // 2017B data, 25ns, 3.8T
  else {lumi = 0.0; tev = 0.0;}

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

  // could also include Tracking/Run summary/V0monitoring
  // also include Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1

  // PV plots inside Tracking (not offlinePV folder)
  dirname = "/Tracking/Run summary/PrimaryVertices/highPurityTracks/pt_0to1/offline";
  outdir  = directory+"/PV_HPTks/offline";
  createTH1FPlot("FractionOfGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("GoodPVtxNumberOfTracks_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("GoodPVtxSumPt_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfBADndofPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  if (full) { // profile plots
    dirname = "/Tracking/Run summary/PrimaryVertices/highPurityTracks/pt_0to1/offline/PUmonitoring/VsGoodPVtx";
    createTProfPlot("FractionOfGoodPVtxVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("FractionOfGoodPVtxVsPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("GoodPVtxChi2ProbVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("GoodPVtxChi2oNDFVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("GoodPVtxNumberOfTracksVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("GoodPVtxSumPtVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfBADndofPVtxVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfPVtxVsGoodPVtx_offline", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // Histograms in dEdx directory 
  // 2PO
  dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2PO";
  outdir  = directory+"/dEdx/PO";
  createTH1FPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // 2SO
  dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2SO";
  outdir  = directory+"/dEdx/SO";
  createTH1FPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // 2SP
  dirname = "/Tracking/Run summary/dEdx/dedxDQMHarm2SP";
  outdir  = directory+"/dEdx/SP";
  createTH1FPlot("HIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIPOfHighPt_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIPOfHighPt_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_FractionOfSaturateddEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_MassPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("MIP_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    
  // Hists in dEdx Hits Info
  dirname = "/Tracking/Run summary/dEdxHits/dedxHitInfo";
  outdir  = directory+"/dEdx/HitInfo";
  createTH1FPlot("Harm2_dEdxPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfdEdxHitsPerTrack_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Pixel_dEdxPerCluster_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Strip_dEdxPerCluster_", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  
  // Histograms in SiStrip --> Used for validation of noCCC
  dirname = "/SiStrip/Run summary/MechanicalView"; // could do  IsolatedBunches/MechanicalView as well
  TString histname = "Summary_ClusterChargePerCMfromTrack";  
  outdir  = directory+"/SiStrip/";
  createTH1FPlot(histname+"__TEC__MINUS", dirname+"/TEC/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TEC", lumi, tev);
  createTH1FPlot(histname+"__TEC__PLUS", dirname+"/TEC/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TEC", lumi, tev);
  createTH1FPlot(histname+"__TIB", dirname+"/TIB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TIB", lumi, tev);
  createTH1FPlot(histname+"__TID__MINUS", dirname+"/TID/MINUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TID", lumi, tev);
  createTH1FPlot(histname+"__TID__PLUS", dirname+"/TID/PLUS", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TID", lumi, tev);
  createTH1FPlot(histname+"__TOB", dirname+"/TOB", file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir+"TOB", lumi, tev);

  // Histograms in GeneralProperties directory
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties";
  outdir  = directory+"/genTks/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F plots
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/generalTracks/PUmonitoring";
    outdir  = directory+"/genTks/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // High purity histos - dz PV0 p1? 
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/GeneralProperties";
  outdir  = directory+"/HPTks_dzPV0p1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/PUmonitoring";
    outdir  = directory+"/HPTks_dzPV0p1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // High purity histos - 0 < pt < 1 GeV
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/GeneralProperties";
  outdir  = directory+"/HPTks_0to1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/PUmonitoring";
    outdir  = directory+"/HPTks_0to1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // High purity histos - pt > 1 GeV
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties";
  outdir  = directory+"/HPTks_gt1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("DistanceOfClosestApproachToPVVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("DistanceOfClosestApproachVsEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("DistanceOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("stoppingSource", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/PUmonitoring";
    outdir  = directory+"/HPTks_0to1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // High purity histos - pt > 1 GeV
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties";
  outdir  = directory+"/HPTks_gt1/GenProps";

  // TProfile Plots
  if (full) {
    createTProfPlot("DistanceOfClosestApproachToBSVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("DistanceOfClosestApproachToPVVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("DistanceOfClosestApproachVsEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("DistanceOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("GoodTracksFractionVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfRecHitsPerTrackVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    //  createTProfPlot("NumberOfTracksVsLS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfValidRecHitsPerTrackVsPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("TrackPtErrOverPtVsEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("xPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrt000", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("yPointOfClosestApproachVsZ0wrtPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("zPointOfClosestApproachVsPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("originalAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  
  createTH1FPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMeanRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackEtaErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPhiErr_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPErrOverP_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPtErrOverPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackPzErrOverPz_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackQ_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // Additional Plots for HP --> SIP, DOCA
  createTH1FPlot("DistanceOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);  // additional distributions for goodTracks
  createTH1FPlot("DistanceOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("SIP2DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("SIP3DToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("SIPDxyToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("SIPDxyToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("SIPDzToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("SIPDzToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("xPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("yPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("zPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("xPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("yPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("zPointOfClosestApproachToPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // PU Monitoring
  if (full) {
    dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/PUmonitoring";
    outdir  = directory+"/HPTks_gt1/PU";
    createTProfPlot("NumberOfTracksVsGoodPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfTracksVsPUPVtx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // Histograms in HitProperties directory --> generalTracks
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties";
  outdir  = directory+"/genTks/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TIB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TOB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TID";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TEC";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixBarrel";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixEndcap";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // Histograms in HitProperies outdir --> HighPurity dz PV0 p1?
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties";
  outdir  = directory+"/HPTks_dzPV0p1/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TIB";
  // TProfile Plots
  if (full) {
    createTProfPlot("NumberOfLayersPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
	     
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TOB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TID";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/TEC";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/PixBarrel";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/HitProperties/PixEndcap";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // Histograms in HitProperies outdir --> HighPurity 0 < pt < 1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/HitProperties";
  outdir  = directory+"/HPTks_0to1/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // Histograms in HitProperies outdir --> HighPurity pt > 1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties";
  outdir  = directory+"/HPTks_gt1/HitProps";
  createTH1FPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfOffLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOf3DLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingInnerRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfMissingOuterRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("ValidFractionPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TIB";
  // TProfile Plots
  if (full) {
    createTProfPlot("NumberOfLayersPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
	     
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TOB";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TID";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/TEC";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/PixBarrel";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitProperties/PixEndcap";
  if (full) {
    // TProfile Plots
    createTProfPlot("NumberOfLayersPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfLayersPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsEta_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("NumberOfRecHitsPerTrackVsPhi_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // TH1F Plots
  createTH1FPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  //LS Analysis
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/LSanalysis";
  outdir  = directory+"/genTks/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  if  (full) {
    createTH1FPlot("NumberOfSeeds_lumiFlag_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfSeeds_lumiFlag_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  }

  //LS Analysis - HP dz PV0 p1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/dzPV0p1/LSanalysis";
  outdir  = directory+"/HPTks_dzPV0p1/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  //LS Analysis - HP 0pt1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_0to1/LSanalysis";
  outdir  = directory+"/HPTks_0to1/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  //LS Analysis - HP pt>1
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/LSanalysis";
  outdir  = directory+"/HPTks_gt1/LSan";
  createTH1FPlot("Chi2oNDF_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfRecHitsPerTrack_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("NumberOfTracks_lumiFlag_GenTk", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // HitEffFromHitPattern
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitEffFromHitPattern";
  outdir  = directory+"/genTks/HitEff";
  
  // efficiencies
  if (full)
  {
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // HitEffFromHitPattern
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPattern"; // could also add HitEffFromHitPatternVsBx
  outdir  = directory+"/HPTks_gt1/HitEff";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_PU_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_PU_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // vs BX
  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/HitEffFromHitPatternVsBX"; // could also add HitEffFromHitPatternVsBx
  outdir  = directory+"/HPTks_gt1/HitEffBX";

  if (full)
  {
    // efficiencies
    createTH1FPlot("effic_vs_BX_PXB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_PXB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_PXB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_PXF1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_PXF2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC7", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC8", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TEC9", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TIB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TIB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TIB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TIB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TID1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TID2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TID3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TOB1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TOB2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TOB3", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TOB4", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TOB5", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("effic_vs_BX_TOB6", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  }
  createTH1FPlot("globalEfficiencies", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // Track building info --> count seeds in gen tracks + MVA Plots
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/TrackBuilding";

  outdir  = directory+"/genTks/TkBuilding";
  createTH1FPlot("TrackMVA1_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2HP_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA1_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2HP_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA3_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA3HP_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA1_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA1_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2HP_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA1_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2HP_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA1_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA1_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("TrackMVA2HP_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  if (full) 
  {
    // detached triplets
    createTH1FPlot("NumberOfSeeds_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_detachedTripletStepSeeds_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsEtaProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsPtProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsEtaProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsPtProfile_detachedTripletStepTrackCandidates_detachedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // initialStep
    createTH1FPlot("NumberOfSeeds_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_initialStepSeeds_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA3VsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA3VsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA3HPVsEtaProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA3HPVsPtProfile_initialStepTrackCandidates_initialStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // jetCoreRegional
    createTH1FPlot("NumberOfSeeds_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_jetCoreRegionalStepSeeds_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // low pt triplet
    createTH1FPlot("NumberOfSeeds_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_lowPtTripletStepSeeds_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_lowPtTripletStepTrackCandidates_lowPtTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // mixed triplet
    createTH1FPlot("NumberOfSeeds_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_mixedTripletStepSeeds_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsEtaProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsPtProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsEtaProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsPtProfile_mixedTripletStepTrackCandidates_mixedTripletStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // muon in out
    createTH1FPlot("NumberOfSeeds_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_muonSeededSeedsInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_muonSeededTrackCandidatesInOut_muonSeededStepInOut", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // muon out in
    createTH1FPlot("NumberOfSeeds_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_muonSeededSeedsOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_muonSeededTrackCandidatesOutIn_muonSeededStepOutIn", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // pixelLess
    createTH1FPlot("NumberOfSeeds_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_pixelLessStepSeeds_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsEtaProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsPtProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsEtaProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsPtProfile_pixelLessStepTrackCandidates_pixelLessStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // pixel pair
    createTH1FPlot("NumberOfSeeds_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_pixelPairStepSeeds_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_pixelPairStepTrackCandidates_pixelPairStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

    // tobtec
    createTH1FPlot("NumberOfSeeds_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedEta_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPhi_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("SeedPt_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("NumberOfTrackCandidates_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("StoppingSource_tobTecStepSeeds_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandEta_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPhi_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTH1FPlot("TrackCandPt_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsEtaProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA1VsPtProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsEtaProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2VsPtProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsEtaProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
    createTProfPlot("TrackMVA2HPVsPtProfile_tobTecStepTrackCandidates_tobTecStep", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  }

  // Pixel Primary vertices
  dirname = "/OfflinePV/Run summary/Alignment";
  outdir  = directory+"/OfflinePV/Alignment";	     
  // TProfile Plots
  createTProfPlot("dxyVsEta_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dxyVsEta_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dxyVsPhi_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dxyVsPhi_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dzVsEta_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dzVsEta_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dzVsPhi_pt1", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTProfPlot("dzVsPhi_pt10", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  
  // TH1F Plots
  createTH1FPlot("chi2ndf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("chi2prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("dxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("dxyErr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("dz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("dzErr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("ntracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);
  createTH1FPlot("sumpt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral_al, V2_integral_al, outdir, lumi, tev);

  dirname = "/OfflinePV/Run summary/offlineBeamSpot";
  outdir  = directory+"/OfflinePV/offlineBS";	     
  createTH1FPlot("bsBeamWidthX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsBeamWidthY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsDxdz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsDydz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsSigmaZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("bsZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/OfflinePV/Run summary/offlinePrimaryVertices";
  outdir  = directory+"/OfflinePV/offlinePVs";	     
  createTH1FPlot("otherDiffX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherDiffY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherErrX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherErrY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherErrZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherPosX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherPosY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherPosZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherType", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherVtxChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherVtxNdf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherVtxProb", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherVtxScore", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("otherVtxTrksNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTProfPlot("otherVtxTrksVsZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTH1FPlot("otherVtxTrksWeight", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  createTH1FPlot("tagDiffX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagDiffY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagErrX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagErrY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagErrZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagPosX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagPosY", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagPosZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagType", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagVtxChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagVtxNdf", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagVtxProb", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagVtxScore", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("tagVtxTrksNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTProfPlot("tagVtxTrksVsZ", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  createTH1FPlot("tagVtxTrksWeight", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  createTH1FPlot("vtxNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("goodvtxNbr", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  // V0 Monitoring
  // Ks
  dirname = "/Tracking/Run summary/V0Monitoring/Ks";
  outdir  = directory+"/V0/Ks";
  createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  if (full)
  {
    createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // Ks/Lxy16
  dirname = "/Tracking/Run summary/V0Monitoring/Ks/Lxy16";
  outdir  = directory+"/V0/Ks_Lxy16";
  createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  if (full)
  {
    createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // Lambda
  dirname = "/Tracking/Run summary/V0Monitoring/Lambda";
  outdir  = directory+"/V0/Lambda";
  createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  if (full)
  {
    createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // Lambda/Lxy16
  dirname = "/Tracking/Run summary/V0Monitoring/Lambda/Lxy16";
  outdir  = directory+"/V0/Lambda_Lxy16";
  createTH1FPlot("n_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("n_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_normalized", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_Lxy_wrtBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_N", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_mass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_phi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("v0_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  if (full)
  {
    createTProfPlot("v0_Lxy_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_deltaMass", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_Lxy_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_LS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_N_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_deltaMass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_BX", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_PU", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_eta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_lumi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_pt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
    createTProfPlot("v0_mass_vs_p", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, outdir, lumi, tev);
  }

  // Packed Candidate - miniAOD validation
  dirname = "/Tracking/Run summary/PackedCandidate";
  outdir  = directory+"/PackCand/MatchedTks";	     
  createTH1FPlot("diffCharge", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDszDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDszDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDszDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaLambda", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaLambdaStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaLambdaUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiPhiStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiPhiUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovQoverpQoverp", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovQoverpQoverpStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovQoverpQoverpUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDszError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffEtaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternHasValidHitInFirstPixelBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternNumberOfLostPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternNumberOfValidHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternNumberOfValidPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffIsHighPurity", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffLostInnerHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNdof", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNormalizedChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffPt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffPtError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffVx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffVy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffVz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberPixelHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberStripHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("selectionFlow", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfPixelLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfStripLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternTrackerLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternPixelLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternStripLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberPixelLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberStripLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

  dirname = "/Tracking/Run summary/PackedCandidate/lostTracks";
  outdir  = directory+"/PackCand/LostTks";
  createTH1FPlot("diffCharge", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDszDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDszDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDszDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovDxyDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaDsz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaDszStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaDszUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaLambda", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaLambdaStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovLambdaLambdaUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiDxy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiDxyStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiDxyUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiPhiStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovPhiPhiUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovQoverpQoverp", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovQoverpQoverpStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffCovQoverpQoverpUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDszError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDxyPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzAssocPVStatus", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzAssocPVUnderOverFlowSign", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffDzPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffEta", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffEtaError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternHasValidHitInFirstPixelBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternNumberOfLostPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternNumberOfValidHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternNumberOfValidPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffIsHighPurity", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffLostInnerHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNdof", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNormalizedChi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfPixelHits", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffPhi", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffPt", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffPtError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDxyAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDxyError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDzAssocPV", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffTrackDzError", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffVx", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffVy", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffVz", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberPixelHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberStripHitsOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("selectionFlow", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfPixelLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffNumberOfStripLayers", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternTrackerLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternPixelLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("diffHitPatternStripLayersWithMeasurement", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberPixelLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);
  createTH1FPlot("numberStripLayersOverMax", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas, V1_integral, V2_integral, outdir, lumi, tev);

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

bool createTH1FPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, TString outdir, const Double_t lumi, const Int_t tev) {

  // ++++++++++++ Get name of histos and get histos +++++++++++++ //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);

  TString hnameV1 = basename1; // reference
  hnameV1.Append(dirname+"/");
  hnameV1.Append(hname);

  if ( dirname.Contains("GeneralProperties",TString::kExact) || dirname.Contains("HitProperties",TString::kExact) ) {
    hnameV1.Append("_GenTk");
  }

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);

  TString hnameV2 = basename2;
  hnameV2.Append(dirname+"/");
  hnameV2.Append(hname);

  if ( dirname.Contains("GeneralProperties",TString::kExact) || dirname.Contains("HitProperties",TString::kExact) ) {
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

  if (isHist1 && isHist2 && !(hname.Contains("globalEfficiencies",TString::kExact)) && !(hname.Contains("effic_vs_PU_",TString::kExact))) {
    // histV1->Sumw2();
    // histV2->Sumw2();
    // histV1->Scale(1.0/histV1->Integral()); // scale to unity
    // histV2->Scale(1.0/histV2->Integral());
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

  if ( (hname.Contains("NumberOfTracks",TString::kExact)) && (dirname.Contains("highPurityTracks",TString::kExact)) ){
    histV1->GetXaxis()->SetRangeUser(0,1000);
    histV2->GetXaxis()->SetRangeUser(0,1000);
  }
  else if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    histV1->GetXaxis()->SetRangeUser(4,17);
    histV2->GetXaxis()->SetRangeUser(4,17);
  }

  //++++++++++++++++++++ Change axis title names +++++++++++++++++++//

  if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    histV1->GetXaxis()->SetTitle("");
    histV2->GetXaxis()->SetTitle("");
  }
  else if (dirname.Contains("PackedCandidate",TString::kExact)) {
    if (!hname.Contains("selectionFlow",TString::kExact)) {
      histV1->GetXaxis()->SetTitle(histV1->GetTitle());
    }
    histV1->GetYaxis()->SetTitle("Number of Tracks");
  }
  else if (dirname.Contains("OfflinePV",TString::kExact)) {
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
    else if (dirname.Contains("offlineBeamSpot",TString::kExact)){ 
      if (hname.Contains("bsBeamWidthX",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot BeamWidthX");
      }
      else if (hname.Contains("bsBeamWidthY",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot BeamWidthY");
      }
      else if (hname.Contains("bsDxdz",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot dxdz");
      }
      else if (hname.Contains("bsDydz",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot dydz");
      }
      else if (hname.Contains("bsSigmaZ",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot #sigma_{z}");
      }
      else if (hname.Contains("bsX",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot x_{0}");
      }
      else if (hname.Contains("bsY",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot y_{0}");
      }
      else if (hname.Contains("bsZ",TString::kExact)) {
	histV1->GetXaxis()->SetTitle("BeamSpot z_{0}");
      }

      histV1->GetYaxis()->SetTitle("Number of Events");
    }
    else if (dirname.Contains("offlinePrimaryVertices",TString::kExact)){ 
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
  else if (dirname.Contains("HitEffFromHitPattern",TString::kExact)) {
    if (!hname.Contains("global",TString::kExact)) {
      histV1->GetXaxis()->SetTitle("Number of Good Vertices");

      TString detname = hname;

      TString drop   = "effic_vs_PU_";
      Ssiz_t  detpos = detname.Index(drop.Data());   
      Ssiz_t  detlen = drop.Length();
      detname.Replace(detpos,detlen,"");

      histV1->GetYaxis()->SetTitle(Form("%s Efficiency",detname.Data()));
    }
    else if (hname.Contains("global",TString::kExact)) {
      histV1->GetYaxis()->SetTitle("Global Efficiency");
    }
  }

  //++++++++++++++++++++ Change histogram names +++++++++++++++++++//

  if (hname.Contains("Summary_ClusterCharge",TString::kExact) ){
    histV1->GetYaxis()->SetTitle("Numer of Charge Clusters");
    if (hname.Contains("PerCMfromOrigin",TString::kExact) ){
      TString detname  = hname;
      
      TString identstr = "Track__";
      Ssiz_t  trackpos = detname.Index(identstr.Data());
      Ssiz_t  tklength = identstr.Length();
      Ssiz_t  detpos   = trackpos+tklength;
      
      detname.Remove(0,detpos);

      if (!(hname.Contains("TIB",TString::kExact) || hname.Contains("TOB",TString::kExact))) {
	TString dblws = "__";
	Ssiz_t  wspos = detname.Index(dblws.Data());   
	Ssiz_t  wslen = dblws.Length();
	detname.Replace(wspos,wslen," ");
      }
      
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
      
      if (!(hname.Contains("TIB",TString::kExact) || hname.Contains("TOB",TString::kExact))) {
	TString dblws = "__";
	Ssiz_t  wspos = detname.Index(dblws.Data());   
	Ssiz_t  wslen = dblws.Length();
	detname.Replace(wspos,wslen," ");
      }
	
      histV1->GetXaxis()->SetTitle(Form("%s dQ / dx from Track [C/cm]",detname.Data()));
    } //fromTrack x axis title
  }

  histV1->GetXaxis()->SetTitleSize(0);
  histV1->GetXaxis()->SetLabelSize(0);
  histV2->GetXaxis()->SetTitleSize(0);
  histV2->GetXaxis()->SetLabelSize(0);

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

  TLegend *leg;
  if ( (hname.Contains("NumberOfTracks",TString::kExact)) || (hname.Contains("vtxNbr",TString::kExact)) || (hname.Contains("algorithm",TString::kExact)) ||(hname.Contains("Algorithm",TString::kExact)) || (hname.Contains("NumberOfMeanRecHitsPerTrack",TString::kExact)) || (hname.Contains("NumberOfMeanLayersPerTrack",TString::kExact)) ){
    leg = new TLegend(0.57,0.85,0.765,0.94);
  }
  else if ( hname.Contains("Summary_ClusterChargePerCMfromOrigin",TString::kExact) || hname.Contains("Summary_ClusterChargePerCMfromTrack",TString::kExact) ){
    leg = new TLegend(0.175,0.85,0.37,0.94);
  }
  else{
    leg = new TLegend(0.29,0.85,0.485,0.94);
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

  //++++++++++++++++++++ Draw both stats boxes +++++++++++++++++++//

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

  if ( (hname.Contains("NumberOfTracks",TString::kExact)) && (dirname.Contains("highPurityTracks",TString::kExact)) ){
    ratioline->SetX1(0);
    ratioline->SetX2(1000);
  }
  else if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    ratioline->SetX1(4);
    ratioline->SetX2(17);
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

  TString filename = hname;
 
  if (dirname.Contains("PrimaryVertices/pt_0to1",TString::kExact) ){  // shorten name of offline PV plots in tracking dir, drop _offline
    if (dirname.Contains("offline",TString::kExact) ){
      TString replacestr  = "_offline";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (dirname.Contains("pixel",TString::kExact) ){
      TString replacestr  = "_pixel";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "";
      filename.Replace(filenamepos,length,toreplace);
    }
  }
  else if (dirname.Contains("SiStrip",TString::kExact) ){  // shorten name of SiStrip plots for output .png
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
  } // end sistrip plots name change
  else if (dirname.Contains("dEdx",TString::kExact) ){ // drop _ at end of dEdx plots
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
  } // drop _ at end of dEdx plots
  else if ((dirname.Contains("TrackBuilding",TString::kExact)) || (dirname.Contains("LSanalysis",TString::kExact)) ){ // drop extra duplicate modifier from track building and LS analysis plots
    if (dirname.Contains("LSanalysis",TString::kExact) ){  // drop lumiFlag and GenTk from LSanalysis plots
      if (filename.Contains("lumiFlag",TString::kExact) ){
	TString replacestr  = "_lumiFlag";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
	TString toreplace = "";
	filename.Replace(filenamepos,length,toreplace);
      }
      if (filename.Contains("GenTk",TString::kExact) ){
	TString replacestr  = "_GenTk";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
	TString toreplace = "";
	filename.Replace(filenamepos,length,toreplace);
      }
    } // end check over LSan plots

    // begin checks for duplicate step names
    if (filename.Contains("detachedTripletStep",TString::kExact)) {  
      if (filename.Contains("detachedTripletStepSeeds",TString::kExact)) {  
	TString replacestr  = "detachedTripletStepSeeds_detachedTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "detachedTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("detachedTripletStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "detachedTripletStepTrackCandidates_detachedTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "detachedTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("initialStep",TString::kExact)) {  
      if (filename.Contains("initialStepSeeds",TString::kExact)) {  
	TString replacestr  = "initialStepSeeds_initialStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "initialStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("initialStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "initialStepTrackCandidates_initialStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "initialStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("jetCoreRegionalStep",TString::kExact)) {  
      if (filename.Contains("jetCoreRegionalStepSeeds",TString::kExact)) {  
	TString replacestr  = "jetCoreRegionalStepSeeds_jetCoreRegionalStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "jetCoreRegionalStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("jetCoreRegionalStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "jetCoreRegionalStepTrackCandidates_jetCoreRegionalStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "jetCoreRegionalStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("lowPtTripletStep",TString::kExact)) {  
      if (filename.Contains("lowPtTripletStepSeeds",TString::kExact)) {  
	TString replacestr  = "lowPtTripletStepSeeds_lowPtTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "lowPtTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("lowPtTripletStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "lowPtTripletStepTrackCandidates_lowPtTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "lowPtTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("mixedTripletStep",TString::kExact)) {  
      if (filename.Contains("mixedTripletStepSeeds",TString::kExact)) {  
	TString replacestr  = "mixedTripletStepSeeds_mixedTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "mixedTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("mixedTripletStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "mixedTripletStepTrackCandidates_mixedTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "mixedTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("muonSeededStepInOut",TString::kExact)) {  
      if (filename.Contains("muonSeededSeedsInOut",TString::kExact)) {  
	TString replacestr  = "muonSeededSeedsInOut_muonSeededStepInOut";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
	TString toreplace = "muonSeededStepInOut";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("muonSeededTrackCandidatesInOut",TString::kExact)) {  
	TString replacestr  = "muonSeededTrackCandidatesInOut_muonSeededStepInOut";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
	TString toreplace = "muonSeededStepInOut";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("muonSeededStepOutIn",TString::kExact)) {  
      if (filename.Contains("muonSeededSeedsOutIn",TString::kExact)) {  
	TString replacestr  = "muonSeededSeedsOutIn_muonSeededStepOutIn";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "muonSeededStepOutIn";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("muonSeededTrackCandidatesOutIn",TString::kExact)) {  
	TString replacestr  = "muonSeededTrackCandidatesOutIn_muonSeededStepOutIn";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "muonSeededStepOutIn";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("pixelLessStep",TString::kExact)) {  
      if (filename.Contains("pixelLessStepSeeds",TString::kExact)) {  
	TString replacestr  = "pixelLessStepSeeds_pixelLessStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "pixelLessStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("pixelLessStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "pixelLessStepTrackCandidates_pixelLessStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "pixelLessStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("pixelPairStep",TString::kExact)) {  
      if (filename.Contains("pixelPairStepSeeds",TString::kExact)) {  
	TString replacestr  = "pixelPairStepSeeds_pixelPairStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "pixelPairStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("pixelPairStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "pixelPairStepTrackCandidates_pixelPairStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "pixelPairStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("tobTecStep",TString::kExact)) {  
      if (filename.Contains("tobTecStepSeeds",TString::kExact)) {  
	TString replacestr  = "tobTecStepSeeds_tobTecStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "tobTecStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("tobTecStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "tobTecStepTrackCandidates_tobTecStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "tobTecStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
  }// end concatinating track building + LSanalysis strings
  else if (dirname.Contains("GeneralProperties",TString::kExact) || dirname.Contains("HitProperties",TString::kExact) ){ // shorten "NumberOf" or "Distance of Closest "
    if (filename.Contains("NumberOf",TString::kExact)) {  
      TString replacestr  = "NumberOf";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "N";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("ImpactPoint",TString::kExact)) {  
      TString replacestr  = "ImpactPoint";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "IP";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("PointOfClosestApproach",TString::kExact)) {  
      TString replacestr  = "PointOfClosestApproach";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "PCA";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("DistanceOfClosestApproach",TString::kExact)) {  
      TString replacestr  = "DistanceOfClosestApproach";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "DistCA";
      filename.Replace(filenamepos,length,toreplace);
    }
  }

  filename.Append(".png");
  // copy filename for log .. stupid but whatever
  TString filenamecopy = filename;

  //++++++++++++++++++++ Save output canvas +++++++++++++++++++//
  CMSLumi(canvas, 0, tev, lumi);

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

bool createTProfPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, TString outdir, const Double_t lumi, const Int_t tev) {

  // ++++++++++++ Get name of histos and get histos +++++++++++++ //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);

  TString hnameV1 = basename1; // reference
  hnameV1.Append(dirname+"/");
  hnameV1.Append(hname);

  if (dirname.Contains("GeneralProperties",TString::kExact) || dirname.Contains("HitProperties",TString::kExact)) {
    hnameV1.Append("_GenTk");
  }

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);

  TString hnameV2 = basename2;
  hnameV2.Append(dirname+"/");
  hnameV2.Append(hname);

  if (dirname.Contains("GeneralProperties",TString::kExact) || dirname.Contains("HitProperties",TString::kExact)) {
    hnameV2.Append("_GenTk");
  }

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

  histV2->GetXaxis()->SetTitleSize(0.0);
  histV2->SetLineWidth(2);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  histV2->SetMarkerColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 

  if (!isHist1) { // only plot hist1 in case of missing hists
    histV1->SetLineColor(kRed);
    histV1->SetMarkerColor(kRed);
    histV1->SetLineWidth(2);
  }

  histV1->GetXaxis()->SetTitleSize(0);
  histV1->GetXaxis()->SetLabelSize(0);
  histV2->GetXaxis()->SetTitleSize(0);
  histV2->GetXaxis()->SetLabelSize(0);

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

  TLegend *leg;
  leg = new TLegend(0.29,0.85,0.485,0.94);
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

  TH1D * hratio = histV2->ProjectionX("numer","E"); // Ratio is TARGET divided by REF
  TH1D * hdenom = histV1->ProjectionX("denom","E");
  hratio->Divide(hdenom);

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
  hratio->Draw("P");

  //++++++++++++++++++++ Draw ratio line +++++++++++++++++++//
  
  TLine * ratioline = new TLine();

  ratioline->SetX1(hratio->GetXaxis()->GetXmin());
  ratioline->SetX2(hratio->GetXaxis()->GetXmax());
  ratioline->SetY1(1.0);
  ratioline->SetY2(1.0);

  // customize appearance
  ratioline->SetLineColor(kRed);
  ratioline->SetLineWidth(2);

  // draw line then redraw hratio on top
  ratioline->Draw("SAME");
  hratio->Draw("P SAME");

  //++++++++++++++++++++ Define filename, change filename output if necessary +++++++++++++++++++//

  TString filename = hname;
 
  if (dirname.Contains("PrimaryVertices/pt_0to1",TString::kExact) ){  // shorten name of offline PV plots in tracking dir, drop _offline
    if (dirname.Contains("offline",TString::kExact) ){
      TString replacestr  = "_offline";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (dirname.Contains("pixel",TString::kExact) ){
      TString replacestr  = "_pixel";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "";
      filename.Replace(filenamepos,length,toreplace);
    }
  }
  else if (dirname.Contains("GeneralProperties",TString::kExact) || dirname.Contains("HitProperties",TString::kExact) ){ // shorten "NumberOf" or "Distance of Closest "
    if (filename.Contains("NumberOf",TString::kExact)) {  
      TString replacestr  = "NumberOf";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "N";
      filename.Replace(filenamepos,length,toreplace);
    }
    
    if (filename.Contains("ImpactPoint",TString::kExact)) {  
      TString replacestr  = "ImpactPoint";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "IP";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("PointOfClosestApproach",TString::kExact)) {  
      TString replacestr  = "PointOfClosestApproach";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "PCA";
      filename.Replace(filenamepos,length,toreplace);
    }
    else if (filename.Contains("DistanceOfClosestApproach",TString::kExact)) {  
      TString replacestr  = "DistanceOfClosestApproach";
      Ssiz_t  length      = replacestr.Length();
      Ssiz_t  filenamepos = filename.Index(replacestr.Data());
      
      TString toreplace = "DistCA";
      filename.Replace(filenamepos,length,toreplace);
    }
  }

  filename.Append(".png");
  // copy filename for log .. stupid but whatever
  TString filenamecopy = filename;

  //++++++++++++++++++++ Save output canvas +++++++++++++++++++//
  CMSLumi(canvas, 0, tev, lumi);

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
  if ( hdenom ) {delete hdenom;}

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

void CMSLumi(TCanvas *& canv, const Int_t iPosX, const Int_t tev, const Double_t lumi) {
  canv->cd();

  TString cmsText      = "CMS";
  Double_t cmsTextFont = 61;  // default is helvetic-bold
  
  Bool_t writeExtraText  = true;
  TString extraText      = "Preliminary";
  Double_t extraTextFont = 52;  // default is helvetica-italics

  TString lumiText = Form("%4.2f pb^{-1} (%2i TeV)",lumi,tev);
  
  // text sizes and text offsets with respect to the top frame
  // in unit of the top margin size
  Double_t lumiTextSize     = 0.6;
  Double_t lumiTextOffset   = 0.2;
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
  latex.SetTextSize(lumiTextSize*t);    
  latex.DrawLatex(0.93-r,1-t+lumiTextOffset*t,lumiText); //  1-r, 0.93-r

  if (outOfFrame) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l+extraTextOffset,1-t+lumiTextOffset*t,cmsText);
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
      posY_ = 1-t+lumiTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_, posY_, extraText);      
  }
}

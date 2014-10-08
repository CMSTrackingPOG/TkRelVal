//INDIVIDUAL/MULTI-FILE COMPARISON

//***This macro produces overlaying histograms from either individual or sets of input files

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TROOT.h"
#include "TStyle.h"
#include "TFile.h"
#include "TPad.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TString.h"
#include "TF1.h"
#include "TPaveStats.h"

using namespace std;

void V1_V2_trkComparison(string fileName1, string fileName2, int scale);
bool createPlot(TString hname, TString dirname, TFile *V1file, TString relstring1, TFile *V2file, TString relstring2, TCanvas *canvas, int scale);
void setTDRStyle();

void V1_V2_trkComparison(string fileName1, string fileName2, int scale) {

  gROOT->SetBatch(kTRUE);

  gROOT->SetStyle("Default");
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(111101);

  gStyle->SetOptFit(1);

  TCanvas *canvas = new TCanvas;

  TString relString1 = "EscaleZS - SM";
  TString relString2 = "EscaleZS - PM";

  TFile *file1 = TFile::Open(fileName1.c_str());
  TFile *file2 = TFile::Open(fileName2.c_str());


  // Histograms in GeneralProperties directory
  TString  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties";
  
  createPlot("algorithm", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("DistanceOfClosestApproachToBS", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("TrackEta_ImpactPoint", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("TrackPhi_ImpactPoint", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfTracks", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("Chi2", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("Chi2oNDF", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("Chi2Prob", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("TrackPt_ImpactPoint", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/highPurityTracks/pt_1/GeneralProperties";
  createPlot("FractionOfGoodTracks", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfTracks", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("algorithm", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("Chi2oNDF", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("TrackEta_ImpactPoint", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("TrackPhi_ImpactPoint", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("TrackPt_ImpactPoint", dirname, file1,  relString1, file2, relString2, canvas, scale);

  // Histograms in HitProperties directory
  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties";
  createPlot("NumberOfRecHitsPerTrack", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfValidRecHitsPerTrack", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLostRecHitsPerTrack", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TIB";
  createPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack_TIB", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TOB";
  createPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack_TOB", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TID";
  createPlot("NumberOfRecHitsPerTrack_TID", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack_TID", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/TEC";
  createPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack_TEC", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixBarrel";
  createPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1,  relString1, file2, relString2, canvas, scale);

  dirname = "/Tracking/Run summary/TrackParameters/generalTracks/HitProperties/PixEndcap";
  createPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1,  relString1, file2, relString2, canvas, scale);
  createPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1,  relString1, file2, relString2, canvas, scale);

  //Primary vertices
  dirname = "/OfflinePV/Run summary/offlinePrimaryVertices";
  createPlot("vtxNbr", dirname, file1,  relString1, file2, relString2, canvas, scale);
}

bool createPlot(TString hname, TString dirname, TFile *V1file, TString relstring1, TFile *V2file, TString relstring2, TCanvas *canvas, int scale) {
  setTDRStyle();

  // don't look at non-zero bin
  Int_t range_upper = histV1->GetXaxis()->GetLast();
  histV1->GetXaxis()->SetRangeUser(1,range_upper);
  histV2->GetXaxis()->SetRangeUser(1,range_upper);

  int SetScale = scale;

  //IF =0 --> No scale applied ('direct' comparison)
  //IF =1 --> Scale INDIVIDUALLY (scale histograms individually) 
  //IF =2 --> Scale all GLOBALLY (scale all histograms to #tracks=1)
  //IF =3 --> Scale all GLOBALLY nEVENTS (scale all histos to nEntries in nTracks per Event)

  bool DrawRatio = true;
  canvas->cd();
  TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.0,1.0,0.8);
  mainpad->Draw();
  mainpad->cd();

  // ************ Get name of histos and get histos ************* //
  
  TString basename1 = "DQMData/Run ";
  basename1.Append("1");

  TString hnameV1 = basename1;
  hnameV1.Append(dirname+"/");
  hnameV1.Append(hname);

  if (hname != "vtxNbr"){
    hnameV1.Append("_GenTk");
  }

  TH1F * histV1 = (TH1F*)V1file->Get(hnameV1);
  if ( histV1 == (TH1F*) NULL ) {
    cout << "histV1 failed on " << hnameV1  << endl << " for file " << V1file->GetName() << endl;
    exit(1);
  }

  TString basename2 = "DQMData/Run ";
  basename2.Append("1");

  TString hnameV2 = basename2;
  hnameV2.Append(dirname+"/");
  hnameV2.Append(hname);
  
  if (hname != "vtxNbr"){
    hnameV2.Append("_GenTk");
  }

  TH1F * histV2 = (TH1F*)V2file->Get(hnameV2);
  if ( histV2 == (TH1F*) NULL ) {
    cout << "histV2 failed on " << hnameV2  << endl << " for file " << V2file->GetName() << endl;
    exit(1);
  }

  //******************* Get histo integrals ***********************//
  double V1_integral = 1.0;
  double V2_integral = 1.0;

  TH1F * hTempV1 = 0;
  TH1F * hTempV2 = 0;

  if (SetScale==1){    
    V1_integral = histV1->Integral();
    V2_integral = histV2->Integral();
  }
  else if ( (SetScale==2) || (SetScale==3) ){
    if (hname != "NumberOfTracks"){
      TString hTempNameV1 = basename1;
      hTempNameV1.Append("/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties/NumberOfTracks_GenTk");
      hTempV1 = (TH1F*)V1file->Get(hTempNameV1);
      
      TString hTempNameV2 = basename2;
      hTempNameV2.Append("/Tracking/Run summary/TrackParameters/generalTracks/GeneralProperties/NumberOfTracks_GenTk");
      hTempV2 = (TH1F*)V2file->Get(hTempNameV2);
    }
    else{
      hTempV1 = (TH1F*)histV1->Clone("hTempV1");
      hTempV2 = (TH1F*)histV2->Clone("hTempV2");
    }

    if (SetScale==2){
      V1_integral = hTempV1->GetBinContent(2);
      V2_integral = hTempV2->GetBinContent(2);

      std::cout << "The number of single tracks for V1 is " << V1_integral << std::endl;
      std::cout << "The number of single tracks for V2 is " << V2_integral << std::endl;
    }
    else if (SetScale==3){
      V1_integral = hTempV1->GetEntries();
      V2_integral = hTempV2->GetEntries();

      std::cout << "The number of events for V1 is " << V1_integral << std::endl;
      std::cout << "The number of events for V2 is " << V2_integral << std::endl;
    }
  }

  //*****NORMALIZING V1-V2****************************************

  if(V1_integral>V2_integral) {
    histV1->Scale(V2_integral / V1_integral);
    histV2->Scale(1);
  } 
  else if(V2_integral>V1_integral){
    histV1->Scale(1);
    histV2->Scale(V1_integral / V2_integral);
  }

  //*****NORMALIZING V1-V2*end***************************************

  //***Name the files under comparison***
  TString V1_V1run = "Run 1 ("+relstring1+")";
  TString V2_V2run = "Run 1 ("+relstring2+")";

  histV1->SetName(V1_V1run);
  histV2->SetName(V2_V2run);

  TString x_title = "";
  if( hname.Contains("vtxNbr"))                               x_title="Number of Primary Vertices per Event";

  histV1->SetLineWidth(5);
  histV1->SetLineStyle(1);
  histV1->SetLineColor(kRed);
  histV1->GetYaxis()->SetLabelSize(0.038);

  histV2->SetLineWidth(3);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kBlue);

  if ( hname.Contains("NumberOfTracks",TString::kExact)
      || hname.Contains("NumberOfGoodTracks",TString::kExact)
      || hname.Contains("TrackPt",TString::kExact)
      || hname.Contains("Chi2Prob",TString::kExact)
       ){
    mainpad->SetLogy(1);
  }
  else {
    mainpad->SetLogy(0);
  }

  if (hname.Contains("NumberOfGoodTracks",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,200);
    histV2->GetXaxis()->SetRangeUser(0,200);
  }

  if (hname.Contains("Chi2oNDF",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,10);
    histV2->GetXaxis()->SetRangeUser(0,10);
  }

  if (hname.Contains("vtxNbr")){
    histV1->GetXaxis()->SetTitle(x_title);
    histV1->GetYaxis()->SetTitle("Number of Events");
  }

  if ( hname.Contains("NumberOfTracks",TString::kExact)){
    histV1->GetXaxis()->SetRangeUser(125,range_upper);
    histV2->GetXaxis()->SetRangeUser(125,range_upper);
  }

  double max = 0;
  double V1max = histV1->GetBinContent(histV1->GetMaximumBin());
  double V2max = histV2->GetBinContent(histV2->GetMaximumBin());

  max = (V1max>V2max) ? V1max : V2max;
  histV1->SetMaximum(max*(1.1));

  histV1->Draw();
  histV2->Draw("sames");

  mainpad->Update();

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));

  st1->SetX1NDC(0.77);
  st1->SetY1NDC(0.80);

  st1->SetX2NDC(0.98);
  st1->SetY2NDC(0.97);
  Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  Double_t gaph = 0.02;
  TPaveStats *st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
  st2->SetX1NDC(0.77);  
  st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
  st2->SetX2NDC(0.98);    
  st2->SetY2NDC(st1->GetY1NDC() - gaph);

  TLegend *leg = new TLegend(0.32,0.86,0.76,0.97);
  leg->SetTextSize(0.042);
  leg->SetTextFont(42);
  leg->SetFillColor(10); 
  leg->SetBorderSize(1); // no frame, no shadow
  leg->AddEntry(histV1, V1_V1run, "L" );
  leg->AddEntry(histV2, V2_V2run, "L" );
  leg->Draw("SAME");

  // Draw ratio histogram
  if (DrawRatio){
    canvas->cd();
    TPad* respad = new TPad("respad","respad",0.0,0.78,1.0,0.95);
    respad->SetTopMargin(1.05);
    respad->Draw();
    respad->cd();
    TH1F* hratio = (TH1F*) histV2->Clone("hratio");
    hratio->Divide(histV1);
    hratio->SetMaximum(hratio->GetMaximum()*1.01);
    //if (hratio->GetMinimum()==0.0) hratio->SetMinimum(1.0/hratio->GetMaximum());
    hratio->SetMinimum(1.0/hratio->GetMaximum());
    hratio->GetYaxis()->SetLabelSize(0.1);
    hratio->GetYaxis()->SetRangeUser(0,2);
    hratio->GetXaxis()->SetLabelSize(0);
    hratio->GetXaxis()->SetTitleSize(0);
    hratio->GetYaxis()->SetTitleSize(0.22);
    hratio->GetYaxis()->SetTitleOffset(0.26);
    hratio->GetYaxis()->SetLabelSize(0.2);
    hratio->GetYaxis()->SetNdivisions(5);
    hratio->GetYaxis()->SetTitle("PM/SM");
 
    hratio->Draw();
  }

  // Compare parameters of histograms
  double Entries1 = histV1->GetEntries();
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

  TString filename = hname;

  if (hname.Contains("vtxNbr")){
    filename = "NumberOfPrimaryVertices";
  }

  if (dirname.Contains("highPurityTracks/pt_1/GeneralProperties",TString::kExact))
    filename.Prepend("RunComparison/GoodTracks_");
  else filename.Prepend("RunComparison/");

  filename.Append(".png");

  canvas->Print(filename);

  if ( histV1 ) {histV1->Delete();}
  if ( histV2 ) {histV2->Delete();}

  if ( hTempV1 ) {hTempV1->Delete();}
  if ( hTempV2 ) {hTempV2->Delete();}

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

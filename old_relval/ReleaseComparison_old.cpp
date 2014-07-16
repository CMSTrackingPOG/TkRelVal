
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

void setTDRStyle();
bool createPlot(TString hname, TString dirname, TFile *V1file, TString runstring1, TString relstring1, TFile *V2file, TString runstring2, TString relstring2, TCanvas *canvas);
void V1_V2_trkComparison(string fileName1, string fileName2);





bool createPlot(TString hname, TString dirname, TFile *V1file, TString runstring1, TString relstring1, TFile *V2file, TString runstring2, TString relstring2, TCanvas *canvas) {
  setTDRStyle();

  // Hacky solutions for handling changes in the histogram names
  bool doHack = false;

  TH1F* histoV1;
  TH1F* histoV2;
  TH1F* histV1;
  TH1F* histV2;

  int SetScale;
  //IF =2 --> No scale applied ('direct' comparison)
  //IF =1 --> Scale INDIVIDUALLY (scale histograms individually) 
  //IF =0 --> Scale all GLOBALLY (scale all histograms to #tracks=1)
  //IF =3 --> Scale all GLOBALLY nEVENTS (scale all histos to nEntries in nTracks per Event)

  SetScale = 1;

  bool DrawRatio = true;
  canvas->cd();
  TPad* mainpad = new TPad("mainpad","mainpad",0.0,0.0,1.0,0.8);
  mainpad->Draw();
  mainpad->cd();

  TString basename1 = "DQMData/Run ";
  basename1.Append(runstring1);
  basename1.Append("/Tracking/Run summary/TrackParameters/");
  basename1.Append(dirname+"/");
  /*
  if( hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
      hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) )
    basename1.Append("HitProperties/PixEndcap/");    
  else if ( hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
    basename1.Append("HitProperties/PixBarrel/");
v  //else if (hname.Contains("NumberOfGoodTracks",TString::kExact) )
    //basename1.Append("GeneralProperties/");
  else 

    basename1.Append(dirname+"/");
  */

  TString basename2 = "DQMData/Run ";
  basename2.Append(runstring2);



  if (!doHack){
    basename2.Append("/Tracking/Run summary/TrackParameters/");
    basename2.Append(dirname+"/");
  }
  else{
    if (dirname.Contains("GeneralProperties/GoodTracks",TString::kExact)) {
      basename2.Append("/Tracking/Run summary/TrackParameters/highPurityTracks/");
      dirname = "pt_1/GeneralProperties";
    }
    else
      basename2.Append("/Tracking/Run summary/TrackParameters/generalTracks/");
    basename2.Append(dirname+"/");
  }



  cout << basename1 << endl;
  cout << hname << endl;





  //*****SETTING GLOBAL SCALE*****************************************

  double V1_integral;
  double V2_integral;
  double scalefactor = -1;
	
      if (SetScale==0 && scalefactor<0) {

	TString scalename = "NumberOfTracks";

	//File #1 CTF
	TString hnameV1 = scalename;
	hnameV1.Prepend(basename1);
	hnameV1.Append("_GenTk");
	/*
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
	  hnameV1.Append("GenTk");
	*/
	histoV1 = (TH1F*)V1file->Get(hnameV1);
	
	//File #2 CTF
	TString hnameV2 = scalename;
	hnameV2.Prepend(basename2);
	hnameV2.Append("_GenTk");
	/*
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
	  hnameV2.Append("GenTk");
	*/
	histoV2 = (TH1F*)V2file->Get(hnameV2);
	
	V1_integral = histoV1->GetBinContent(2);
	V2_integral = histoV2->GetBinContent(2);
	std::cout << "The number of single tracks for V1 is " << V1_integral << std::endl;
	std::cout << "The number of single tracks for V2 is " << V2_integral << std::endl;
	if(V1_integral>V2_integral) {
	  scalefactor = V2_integral / V1_integral;
	  //std::cout << "The scalefactor is " << scalefactor << " for V1" << std::endl;
	} else {
	  scalefactor = V1_integral / V2_integral;
	  //std::cout << "The scalefactor is " << scalefactor << " for RS" << std::endl;
	}
	
	
      }
 
  if (SetScale==3 && scalefactor<0) {

	TString scalename = "NumberOfTracks";

	//File #1 CTF
	TString hnameV1 = scalename;
	hnameV1.Prepend(basename1);
	hnameV1.Append("_GenTk");
	/*
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
	  hnameV1.Append("GenTk");
	*/
	histoV1 = (TH1F*)V1file->Get(hnameV1);
	
	//File #2 CTF
	TString hnameV2 = scalename;
	hnameV2.Prepend(basename2);
	hnameV2.Append("_GenTk");
	/*
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
	  hnameV2.Append("GenTk");
	*/
	histoV2 = (TH1F*)V2file->Get(hnameV2);
	
	V1_integral = histoV1->Integral();
	V2_integral = histoV2->Integral();

	if(V1_integral>V2_integral) {
	  scalefactor = V2_integral / V1_integral;
	  //std::cout << "The scalefactor is " << scalefactor << " for V1" << std::endl;
	} else {
	  scalefactor = V1_integral / V2_integral;
	  //std::cout << "The scalefactor is " << scalefactor << " for RS" << std::endl;
	}
	
	
      }
 

 //*****SETTING GLOBAL SCALE*end****************************************

      //File #1
      TString hnameV1 = hname;
      hnameV1.Prepend(basename1);
      hnameV1.Append("_GenTk");
      /*
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
	  hnameV1.Append("GenTk");
      */
      histoV1 = (TH1F*)V1file->Get(hnameV1);
      
      //File #2
      TString hnameV2 = hname;
      
      // hack for change in histo names in 700pre11
      if (doHack) {
	if( hname.Contains("NumberOfRecHitsFoundPerTrack",TString::kExact)) hnameV2="NumberOfValidRecHitsPerTrack";
	if( hname.Contains("NumberOfRecHitsLostPerTrack",TString::kExact)) hnameV2="NumberOfLostRecHitsPerTrack";
	
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact)) hnameV2="NumberOfRecHitsPerTrack_TIB";
	if( hname.Contains("NumberOfTOBRecHitsPerTrack",TString::kExact)) hnameV2="NumberOfRecHitsPerTrack_TOB";
	if( hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact)) hnameV2="NumberOfRecHitsPerTrack_TID";
	if( hname.Contains("NumberOfTECRecHitsPerTrack",TString::kExact)) hnameV2="NumberOfRecHitsPerTrack_TEC";
	if( hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact)) hnameV2="NumberOfRecHitsPerTrack_PixBarrel";
	if( hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact)) hnameV2="NumberOfRecHitsPerTrack_PixEndcap";
	
	if( hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact)) hnameV2="NumberOfLayersPerTrack_TIB";
	if( hname.Contains("NumberOfTOBLayersPerTrack",TString::kExact)) hnameV2="NumberOfLayersPerTrack_TOB";
	if( hname.Contains("NumberOfTIDLayersPerTrack",TString::kExact)) hnameV2="NumberOfLayersPerTrack_TID";
	if( hname.Contains("NumberOfTECLayersPerTrack",TString::kExact)) hnameV2="NumberOfLayersPerTrack_TEC";
	if( hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact)) hnameV2="NumberOfLayersPerTrack_PixBarrel";
	if( hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact)) hnameV2="NumberOfLayersPerTrack_PixEndcap";
	
	if( hname.Contains("NumberOfGoodTracks",TString::kExact)) hnameV2="NumberOfTracks";
	if( hname.Contains("GoodTrackAlgorithm",TString::kExact)) hnameV2="algorithm";
	if( hname.Contains("GoodTrackChi2oNDF",TString::kExact)) hnameV2="Chi2oNDF";
	if( hname.Contains("GoodTrackEta_ImpactPoint",TString::kExact)) hnameV2="TrackEta_ImpactPoint";
	if( hname.Contains("GoodTrackPhi_ImpactPoint",TString::kExact)) hnameV2="TrackPhi_ImpactPoint";
	if( hname.Contains("GoodTrackPt_ImpactPoint",TString::kExact)) hnameV2="TrackPt_ImpactPoint";
	
      }

	//createPlot("NumberOfTIBLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

      hnameV2.Prepend(basename2);
      hnameV2.Append("_GenTk");
      /*
	if( hname.Contains("NumberOfTIBRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIDRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapRecHitsPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfTIBLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixBarrelLayersPerTrack",TString::kExact) ||
	    hname.Contains("NumberOfPixEndcapLayersPerTrack",TString::kExact) )
	  hnameV2.Append("GenTk");
      */
      histoV2 = (TH1F*)V2file->Get(hnameV2);

      std::cout<<hnameV1<<std::endl;
      
  //*****NORMALIZING V1-V2****************************************
      if (SetScale==2) {
	histV1 = (TH1F*)histoV1->Clone("histV1");
	histV2 = (TH1F*)histoV2->Clone("histV2");
      } 
      else if (SetScale==1) {
	
	//Note option: TH1::Integral("width")
	V1_integral = histoV1->Integral();
	V2_integral = histoV2->Integral();
	
	//std::cout << "The integral of V1 is " << V1_integral << std::endl;
	//std::cout << "The integral of V2 is " << V2_integral << std::endl;
	
	if(V1_integral>V2_integral) {
	  scalefactor = V2_integral / V1_integral;
	  //std::cout << "The scalefactor is " << scalefactor << " for V1" << std::endl;
	} else {
	  scalefactor = V1_integral / V2_integral;
	  //std::cout << "The scalefactor is " << scalefactor << " for V2" << std::endl;
	}
	
	histV1 = (TH1F*)histoV1->Clone("histV1");
	histV2 = (TH1F*)histoV2->Clone("histV2");
	
	if(V1_integral>V2_integral) {
	  histV1->Scale(scalefactor);
	  histV2->Scale(1);
	} else {
	  histV1->Scale(1);
	  histV2->Scale(scalefactor);
	}
	
      } 



      else if (SetScale==0) {
      histV1 = (TH1F*)histoV1->Clone("histV1");
      histV2 = (TH1F*)histoV2->Clone("histV2");
      
	if(V1_integral>V2_integral) {
	  histV1->Scale(scalefactor);
	  histV2->Scale(1);
	} else {
	  histV1->Scale(1);
	  histV2->Scale(scalefactor);
	}

      }

      else if (SetScale==3) {
      histV1 = (TH1F*)histoV1->Clone("histV1");
      histV2 = (TH1F*)histoV2->Clone("histV2");
      
	if(V1_integral>V2_integral) {
	  histV1->Scale(scalefactor);
	  histV2->Scale(1);
	} else {
	  histV1->Scale(1);
	  histV2->Scale(scalefactor);
	}

      }


  //*****NORMALIZING V1-V2*end***************************************

  //histV1->StatOverflows(kTRUE);
  //histV2->StatOverflows(kTRUE);

  //***Name the files under comparison***
  TString V1_V1run = "Run "+runstring1+" ("+relstring1+")";
  TString V2_V2run = "Run "+runstring2+" ("+relstring2+")";

  histV1->SetName(V1_V1run);
  histV2->SetName(V2_V2run);

  TString x_title = "";

  if( hname.Contains("DistanceOfClosestApproach",TString::kExact) )   x_title = "d0" ;
  if( hname.Contains("xPointOfClosestApproach",TString::kExact) )   x_title = "x PCA" ;
  if( hname.Contains("yPointOfClosestApproach",TString::kExact) )   x_title = "y PCA" ;
  if( hname.Contains("zPointOfClosestApproach",TString::kExact) )   x_title = "z PCA" ;
  if( hname.Contains("Pt",TString::kExact) )                  x_title = "p_{T} (GeV)" ;
  if( hname.Contains("Eta",TString::kExact) )                 x_title = "#eta" ;
  if( hname.Contains("Phi",TString::kExact) )                 x_title = "#phi" ;
  //if( hname.Contains("nTrkPerEvent",TString::kExact) )        x_title = "# of Tracks" ;
  if( hname.Contains("pdg",TString::kExact) )                 x_title = "Particle Data ID #" ;
  if( hname.Contains("NumberOfRecHitsPerTrack",TString::kExact) )        x_title = "#Hits/Track" ;
  if( hname.Contains("nTECHitPerTrack",TString::kExact) )     x_title = "TEC #Hits" ;
  if( hname.Contains("nTIBHitPerTrack",TString::kExact) )     x_title = "TIB #Hits" ;
  if( hname.Contains("nTIDHitPerTrack",TString::kExact) )     x_title = "TID #Hits" ;
  if( hname.Contains("nTOBHitPerTrack",TString::kExact) )     x_title = "TOB #Hits" ;
  if( hname.Contains("nPXBHitPerTrack",TString::kExact) )     x_title = "Barrel Pixel #Hits" ;
  if( hname.Contains("nPXFHitPerTrack",TString::kExact) )     x_title = "Foward Pixel #Hits" ;
  if( hname.Contains("Chi2"))                                 x_title="#chi^{2}";
  if( hname.Contains("Chi2ndof"))                             x_title="#chi^{2}/ndof";
  if( hname.Contains("NumberOfTracks"))                             x_title="#Tracks";


  TString hist_title;

  if( hname.Contains("xPointOfClosestApproach",TString::kExact) )               hist_title = x_title ;
  if( hname.Contains("zPointOfClosestApproach",TString::kExact) )               hist_title = x_title ;
  if( hname.Contains("Pt",TString::kExact) )               hist_title = "p_{T}" ;
  if( hname.Contains("Eta",TString::kExact) )              hist_title = x_title ;
  if( hname.Contains("Phi",TString::kExact) )              hist_title = x_title ;
  if( hname.Contains("NumberOfRecHitsPerTrack",TString::kExact) )     hist_title = x_title ;
  //if( hname.Contains("nTrkPerEvent",TString::kExact) )     hist_title = x_title ;
  if( hname.Contains("pdg",TString::kExact) )              hist_title = x_title ;
  if( hname.Contains("nTECHitPerTrack",TString::kExact) )  hist_title = x_title ;
  if( hname.Contains("nTIBHitPerTrack",TString::kExact) )  hist_title = x_title ;
  if( hname.Contains("nTIDHitPerTrack",TString::kExact) )  hist_title = x_title ;
  if( hname.Contains("nTOBHitPerTrack",TString::kExact) )  hist_title = x_title ;
  if( hname.Contains("NumberOfTracks") )                        hist_title = x_title;

  if (hname.Contains("FractionOfGoodTracks",TString::kExact)) {
    std::cout<<"Number of zeros = " << histV1->GetBinContent(1) << '\t' << histV2->GetBinContent(1) << std::endl;
    //histV1->GetXaxis()->SetRangeUser(0.5,1.0);
    //histV2->GetXaxis()->SetRangeUser(0.5,1.0);
  }

  double max = 0;
  double V1max = histV1->GetBinContent(histV1->GetMaximumBin());
  double V2max = histV2->GetBinContent(histV2->GetMaximumBin());

  (V1max>V2max) ? max=V1max : max=V2max;

  //if (hname.Contains("FractionOfGoodTracks",TString::kExact)) max *= 1.4;

  histV1->Draw();
  histV1->SetLineStyle(1);
  histV1->GetYaxis()->SetLabelSize(0.038);
  histV1->SetLineWidth(5);
  histV1->SetLineColor(kRed);
  /*
  if (RS_CosmicTF==1) histV1->SetLineColor(6); //light purple
  if (RS_CosmicTF==2) histV1->SetLineColor(3); //light green
  if (RS_CosmicTF==3) histV1->SetLineColor(50); //light red
  */
  //histV1->GetYaxis()->SetTitleYOffset(1.25);
  //histV1->GetYaxis()->SetTitleSize(0.06);
  //histV1->SetFillColor(50);
  //histV1->SetFillStyle(3002);
  histV1->SetMaximum(max*(1.1));
  //histV1->SetAxisRange(800,900,"X");
  //histV1->SetAxisRange(0,1000,"Y");
  //if(do_fit) histV1->Fit("gaus","0");
  //histV1->SetTitleSize( 0.040, "Y");
  //histV1->SetTitleOffset( 0.5,"Y");
  /* to modify titles...
  histV1->SetTitle("");
  histV1->GetYaxis()->SetTitle("Entries");
  histV1->GetXaxis()->SetTitle(x_title);
  */
  histV2->Draw();
  //histV2->SetLineStyle(2);
  histV2->SetLineWidth(3);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kBlue);
  //histV2->SetFillColor(9);
  //histV2->SetFillStyle(3002);

  if( hname.Contains("NumberOfTracks",TString::kExact)
      || hname.Contains("NumberOfGoodTracks",TString::kExact)
      || hname.Contains("TrackPt",TString::kExact)
      || hname.Contains("Chi2Prob",TString::kExact)
//      || hname.Contains("FractionOfGoodTracks",TString::kExact)
      )
    mainpad->SetLogy(1);
  else
    mainpad->SetLogy(0);

  //  if (hname.Contains("TrackPt",TString::kExact)) histV1->GetXaxis()->SetRangeUser(0,20);
  if (hname.Contains("NumberOfGoodTracks",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,200);
    histV2->GetXaxis()->SetRangeUser(0,200);
  }

  if (hname.Contains("Chi2oNDF",TString::kExact)) {
    histV1->GetXaxis()->SetRangeUser(0,10);
    histV2->GetXaxis()->SetRangeUser(0,10);
  }

  histV1->Draw();
  histV2->Draw("sames");

  //canvas->Update();
  mainpad->Update();

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  //st1->SetX1NDC(0.77);
  //st1->SetY1NDC(0.64);
  //st1->SetX2NDC(0.98);
  //st1->SetY2NDC(0.98);

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


  // places stats side-by-side belw legend
  /*    
  Double_t gapy = 0.02;
  Double_t gapx = 0.02;
  Double_t statw = 0.26;
  Double_t y2 = 0.84;
  Double_t y1 = 0.72;
  Double_t x1 = 0.22;
  st1->SetX1NDC(x1);
  st1->SetX2NDC(x1+statw);
  st1->SetY1NDC(y1);
  st1->SetY2NDC(y2);

  TPaveStats *st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
  st2->SetX1NDC(x1+statw+gapx); 
  st2->SetY1NDC(y1);
  st2->SetX2NDC(x1+statw+gapx+statw);
  st2->SetY2NDC(y2);
  */
  
  //V1_V1run
  //canvas->Update();
  TLegend *leg = new TLegend(0.32,0.86,0.76,0.97);
  //leg->SetTextSize(0.035);
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
    //for( int ibin = 1 ; ibin <= h_mc_tot->GetNbinsX() ; ibin++ ) h_mc_tot->SetBinError(ibin,0);
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
    hratio->GetYaxis()->SetTitle("NEW/REF");
 
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

  if (dirname.Contains("highPurityTracks/pt_1/GeneralProperties",TString::kExact))
    filename.Prepend("RunComparison/GoodTracks_");
  else filename.Prepend("RunComparison/");

  filename.Append(".png");

  canvas->Print(filename);
  /*
 filename.ReplaceAll(".png",".gif");
  canvas->Print(filename);
  */

  histV1->Delete();
  histV2->Delete();
  histoV1->Delete();
  histoV2->Delete();
  //delete histV1;
  //delete histV2;

  return true;
}

void V1_V2_trkComparison(string fileName1, string fileName2) {

  gROOT->SetBatch(kTRUE);

  gROOT->SetStyle("Default");
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  gStyle->SetPalette(1);
  gStyle->SetOptStat(111101);
  //gStyle->SetOptStat(0);

  gStyle->SetOptFit(1);

  TCanvas *canvas = new TCanvas;

  //std::string fileName1 = "/afs/cern.ch/cms/Physics/tracking/validation/DATA/DQM_V0002_R000134725__MinimumBias__CMSSW_3_7_1-GR_R_37X_V4_RelVal_valskim-v1__RECO.root";
  //std::string fileName1 = "/castor/cern.ch/cms/store/unmerged/dqm/DQMHarvesting-Run134725-MinimumBias-RECO/DQMHarvest-Run134725-MinimumBias-RECO-1022711/DQM_V0001_R000134725__MinimumBias__Commissioning10-PromptReco-v9__RECO";
  //std::string fileName1 = "/castor/cern.ch/cms/store/unmerged/dqm/CMSSW_3_9_0_pre2/MinimumBias/RECO/GR_R_38X_V9_RelVal_valskim-v1/134/DQM_V0001_R000134725__MinimumBias__CMSSW_3_9_0_pre2-GR_R_38X_V9_RelVal_valskim-v1__RECO.root";
  int pos = fileName1.find("_R0");
  std::string runString1 = fileName1.substr (pos+5,6);
  //istringstream stream(runString1);
  int pos1 = fileName1.find("CMSSW")+6;
  int pos2 = fileName1.find("/MinimumBias");
  if (pos2 == -1 ) pos2 = fileName1.find("/Jet");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-PRE");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName1.find("-FT");
  //pos1 = fileName1.find("GR");
  //pos2 = fileName1.find("_RelVal");
  std::string relString1 = fileName1.substr (pos1,pos2-pos1); 

  //relString1 += " 32bit";
  //TFile *file1 = new TFile(fileName1.c_str());
  TFile *file1 = TFile::Open(fileName1.c_str());
  //TRFIOFile *file1 = new TRFIOFile(fileName1.c_str());
  std::cout << "Getting histos for run number... " << runString1 
    //<< std::endl;
        <<" for release " << relString1 << std::endl;  
  if ( file1->IsZombie() )
    std::cout << "File: " << fileName1 << " cannot be opened!" << std::endl;

  //temp
  relString1 += " - REF";
  //relString1 += " - OldTrk";

  //std::string fileName2 = "/castor/cern.ch/cms/store/unmerged/dqm/CMSSW_3_9_0_pre3/MinimumBias/RECO/GR_R_38X_V9_RelVal_valskim-v1/134/DQM_V0001_R000134725__MinimumBias__CMSSW_3_9_0_pre3-GR_R_38X_V9_RelVal_valskim-v1__RECO.root";

  pos = fileName2.find("_R0");
  std::string runString2 = fileName2.substr (pos+5,6);
  //istringstream stream(runString2);
  // std::cout<<"pos1 = " <<pos1 << '\t' << "pos2 = " <<pos2<<std::endl;
  pos1 = fileName2.find("CMSSW")+6;
  pos2 = fileName2.find("/MinimumBias");
  if (pos2 == -1 ) pos2 = fileName2.find("/Jet");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-GR");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-PRE");
  if (pos2 == -1 || pos2<pos1) pos2 = fileName2.find("-FT");
  //pos1 = fileName2.find("GR");
  //pos2 = fileName2.find("_RelVal");
  std::string relString2 = fileName2.substr (pos1,pos2-pos1);
  //relString2 += " 64bit";

  //  std::cout<<"relString1 = " << relString1 << std::endl;
  //std::cout<<"relString2 = " << relString2 << std::endl;
  //std::cout<<"pos1 = " <<pos1 << '\t' << "pos2 = " <<pos2<<std::endl;

  //TFile *file2 = new TFile(fileName2.c_str());
  TFile *file2 = TFile::Open(fileName2.c_str());
  //TRFIOFile *file2 = new TRFIOFile(fileName2.c_str());
  std::cout << "Getting histos for run number... " << runString2 
    //<< std::endl;  
    	    <<" for release " << relString2 << std::endl;  
  if ( file2->IsZombie() )
    std::cout << "File: " << fileName2 << " cannot be opened!" << std::endl;
  //temp
  relString2 += " - NEW";


  // Histograms in BeamSpotParameters directory
  TString dirname = "BeamSpotParameters";

  // Histograms in GeneralProperties directory
  dirname = "generalTracks/GeneralProperties";
  createPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("xPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("yPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("zPointOfClosestApproach", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("DistanceOfClosestApproachToBS", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);


  createPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("Chi2", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("Chi2Prob", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  //dirname = "GeneralProperties/GoodTracks";
  dirname = "highPurityTracks/pt_1/GeneralProperties";

  createPlot("FractionOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfGoodTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfTracks", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("GoodTrackAlgorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("algorithm", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("GoodTrackChi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("Chi2oNDF", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("GoodTrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("TrackEta_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("GoodTrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("TrackPhi_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("GoodTrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("TrackPt_ImpactPoint", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  // Histograms in HitProperties directory
  dirname = "generalTracks/HitProperties";
  createPlot("NumberOfRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfRecHitsFoundPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfValidRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfRecHitsLostPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLostRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  dirname = "generalTracks/HitProperties/TIB";
  //createPlot("NumberOfTIBRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfTIBLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfRecHitsPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack_TIB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  dirname = "generalTracks/HitProperties/TOB";
  //createPlot("NumberOfTOBRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfTOBLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfRecHitsPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack_TOB", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  dirname = "generalTracks/HitProperties/TID";
  //createPlot("NumberOfTIDRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfTIDLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfRecHitsPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack_TID", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  dirname = "generalTracks/HitProperties/TEC";
  //createPlot("NumberOfTECRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfTECLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfRecHitsPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack_TEC", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  dirname = "generalTracks/HitProperties/PixBarrel";
  //createPlot("NumberOfPixBarrelRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfPixBarrelLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfRecHitsPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack_PixBarrel", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  dirname = "generalTracks/HitProperties/PixEndcap";
  //createPlot("NumberOfPixEndcapRecHitsPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  //createPlot("NumberOfPixEndcapLayersPerTrack", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfRecHitsPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);
  createPlot("NumberOfLayersPerTrack_PixEndcap", dirname, file1, runString1, relString1, file2, runString2, relString2, canvas);

  /* to add...
     highpurity?
   */

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
    // tdrStyle->SetPadBorderSize(Width_t size = 1);
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
    // tdrStyle->SetHistFillColor(1);
    // tdrStyle->SetHistFillStyle(0);
    tdrStyle->SetHistLineColor(1);
    tdrStyle->SetHistLineStyle(0);
    tdrStyle->SetHistLineWidth(1);
    // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
    // tdrStyle->SetNumberContours(Int_t number = 20);

    //   tdrStyle->SetEndErrorSize(2);
    //   tdrStyle->SetErrorMarker(20);
    //   tdrStyle->SetErrorX(0.);
  
    tdrStyle->SetMarkerStyle(20);

    //For the fit/function:
    tdrStyle->SetOptFit(1);
    tdrStyle->SetFitFormat("5.4g");
    tdrStyle->SetFuncColor(2);
    tdrStyle->SetFuncStyle(1);
    tdrStyle->SetFuncWidth(1);

    //For the date:
    tdrStyle->SetOptDate(0);
    // tdrStyle->SetDateX(Float_t x = 0.01);
    // tdrStyle->SetDateY(Float_t y = 0.01);

    // // For the statistics box:
    //   tdrStyle->SetOptFile(0);
    //   tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
    tdrStyle->SetStatColor(kWhite);
    tdrStyle->SetStatFont(42);
    tdrStyle->SetStatFontSize(0.025);
    tdrStyle->SetStatTextColor(1);
    tdrStyle->SetStatFormat("6.4g");
    tdrStyle->SetStatBorderSize(1);
    tdrStyle->SetStatH(0.1);
    tdrStyle->SetStatW(0.15);
    // tdrStyle->SetStatStyle(Style_t style = 1001);
    // tdrStyle->SetStatX(Float_t x = 0);
    // tdrStyle->SetStatY(Float_t y = 0);

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
    // tdrStyle->SetTitleH(0); // Set the height of the title box
    // tdrStyle->SetTitleW(0); // Set the width of the title box
    // tdrStyle->SetTitleX(0); // Set the position of the title box
    // tdrStyle->SetTitleY(0.985); // Set the position of the title box
    // tdrStyle->SetTitleStyle(Style_t style = 1001);
    // tdrStyle->SetTitleBorderSize(2);

    // For the axis titles:

    tdrStyle->SetTitleColor(1, "XYZ");
    tdrStyle->SetTitleFont(42, "XYZ");
    //tdrStyle->SetTitleSize(0.06, "XYZ");
    tdrStyle->SetTitleSize(0.052, "XYZ");
    // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
    // tdrStyle->SetTitleYSize(Float_t size = 0.02);
    //tdrStyle->SetTitleXOffset(0.9);
    tdrStyle->SetTitleXOffset(0.875);
    //tdrStyle->SetTitleYOffset(1.25);
    tdrStyle->SetTitleYOffset(1.05);
    // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

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
    // tdrStyle->SetLineScalePS(Float_t scale = 3);
    // tdrStyle->SetLineStyleString(Int_t i, const char* text);
    // tdrStyle->SetHeaderPS(const char* header);
    // tdrStyle->SetTitlePS(const char* pstitle);

    // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
    // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
    // tdrStyle->SetPaintTextFormat(const char* format = "g");
    // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
    // tdrStyle->SetTimeOffset(Double_t toffset);
    // tdrStyle->SetHistMinimumZero(kTRUE);

    tdrStyle->cd();

  }

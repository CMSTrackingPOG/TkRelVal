
#ifndef PLOT_FUNCTIONS_HH
#define PLOT_FUNCTIONS_HH


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

bool createTH1FPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, TString outdir, const Double_t lumi, const TString era, const Double_t tev) {

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

  if (isHist1 && isHist2 && 
      !(hname.Contains("globalEfficiencies",TString::kExact)) && 
      !(hname.Contains("effic_vs_PU_",TString::kExact)) &&
      !(dirname.Contains("Resolution",TString::kExact) && hname.Contains("_vs_",TString::kExact))) {
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
  if (histV1->GetSumw2N() == 0) histV1->Sumw2();

  histV2->GetXaxis()->SetTitleSize(0.0);
  histV2->SetLineWidth(2);
  histV2->SetLineStyle(1);
  histV2->SetLineColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  histV2->SetMarkerColor(kRed); // h2 is new ... ogirinally was blue --> switched to match MC 
  if (histV2->GetSumw2N() == 0) histV2->Sumw2();

  if (!isHist1) { // only plot hist1 in case of missing hists
    histV1->SetLineColor(kRed);
    histV1->SetMarkerColor(kRed);
    histV1->SetLineWidth(2);
  }

  //++++++++++++++++++++ Change axis ranges +++++++++++++++++++//

  if ((hname.Contains("NumberOfTracks",TString::kExact) && dirname.Contains("highPurityTracks",TString::kExact)) || 
      (hname.Contains("vs_nvertices",TString::kExact) && dirname.Contains("Resolution"))){
    const float max = GetMaxRange(histV1,histV2);
    histV1->GetXaxis()->SetRangeUser(0,max);
    histV2->GetXaxis()->SetRangeUser(0,max);
  }
  else if (hname.Contains("algorithm",TString::kExact) || hname.Contains("Algorithm",TString::kExact)){
    if (runstring1.Atoi() < 294927){
      histV1->GetXaxis()->SetRangeUser(4,17);
      histV2->GetXaxis()->SetRangeUser(4,17);
    }
    else {
      histV1->GetXaxis()->SetRangeUser(4,25);
      histV2->GetXaxis()->SetRangeUser(4,25);
    }
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
    else if (dirname.Contains("Resolution",TString::kExact)) {
      if (!hname.Contains("_vs_",TString::kExact)) {
	histV1->GetXaxis()->SetTitle(histV1->GetTitle());
	histV1->GetYaxis()->SetTitle("Number of Events");
      }
      else 
      {
	TString gaus = (hname.Contains("Mean",TString::kExact) ? "Mean" : "Sigma");
	TString vs   = "_vs_";
	Ssiz_t start = hname.Index(vs)+vs.Length();
	Ssiz_t end   = hname.Index(TString("_"+gaus));

	histV1->GetXaxis()->SetTitle(TString(hname(start,end-start)).Data());
	
	TString xyz;
	if      (hname.Contains("_x_",TString::kExact)) xyz = "x";
	else if (hname.Contains("_y_",TString::kExact)) xyz = "y";
	else if (hname.Contains("_z_",TString::kExact)) xyz = "z";
	
	TString var = (hname.Contains("pull",TString::kExact) ? (xyz+" pull") : Form("#sigma(%s)",xyz.Data()));
	histV1->GetYaxis()->SetTitle(TString(var+" "+gaus).Data());
      }  
    } // end check over resolution
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

  TPad* mainpad = new TPad("mainpad","mainpad", 0.0, 0.3, 0.813, 0.99);
  mainpad->SetBottomMargin(0.02);
  mainpad->Draw();
  mainpad->cd();

  histV1->Draw("EP"); // Draw old histo first, ratio is new/old
  if (isHist1 && isHist2) {
    histV2->Draw("EP sames");
  }

  mainpad->Update();

  //++++++++++++++++++++ Draw Legends +++++++++++++++++++//
  canvas->cd();
  TPad* sidepad = new TPad("sidepad","sidepad", 0.813, 0.05, 0.99, 0.99);
  sidepad->SetBottomMargin(0);
  sidepad->Draw();
  sidepad->cd();

  TLegend *leg = new TLegend(0.05,0.565,0.95,0.655);

  leg->SetTextSize(0.08);
  leg->SetTextFont(42);
  leg->SetFillColor(10); 
  leg->SetBorderSize(1); // no frame, no shadow

  string s1 = histV1->GetName();
  s1 = s1 + " (A)";

  string s2 = histV2->GetName();
  s2 = s2 + " (B)";

  leg->AddEntry(histV1, s1.c_str(), "lpf" );
  if (isHist1 && isHist2) {
    leg->AddEntry(histV2, s2.c_str(), "lpf" );
  }
  leg->Draw("SAME");
  sidepad->Update();
  //++++++++++++++++++++ Draw both stats boxes +++++++++++++++++++//

  // Here I will do a not very good thing.. I want statbox out of the histogram but it is not
  // easy, apparently, put them out of the histo box.. since they disappear. 
  // So declared a "sidepad" to put legend and statboxes. 
  // I think statbox, by default, is printed on the same pad of the histo.. So I need to clone it
  // and draw it in the right pad! But worst things are gonna come......

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  TPaveStats *stats1 = (TPaveStats*)(st1->Clone("stats1"));

  TPaveStats *st2 = NULL;
  TPaveStats *stats2  = NULL;

  if (isHist1 && isHist2){
    st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
    stats2 = (TPaveStats*)(st2->Clone("stats2"));
  }

  stats1->SetTextSize(0.08);
  if (isHist1 && isHist2){
    stats2->SetTextSize(0.08);
  }

  stats1->SetX1NDC(0.05);
  stats1->SetX2NDC(0.95);
  if (isHist1 && isHist2){
    stats2->SetX1NDC(0.05);
    stats2->SetX2NDC(0.95);
  }

  stats1->SetY1NDC(0.82);
  stats1->SetY2NDC(0.965);
  if (isHist1 && isHist2){
    stats2->SetY1NDC(0.665);
    stats2->SetY2NDC(0.81);
  }
  stats1->Draw();
  if (isHist1 && isHist2){
    stats2->Draw("SAME");
  }
// From this point I have to do a bad thing but that works.
// All I do is move 2 old stat box (st1 & st2) on the right, under the sidepad, so that 
// they are not visible. I have to do this becuase if I delete them, a statbox appear 
// on the right-top angle of the histo! And if I dont want it (Draw("same") without "sameS" S option)
// I get a segmentation violation :( So this is not a good thing to do, but works.. 
// note that to have printed st1 & st2 all i have to do is declare them and set their X&Y. Bot X and Y are necessary

  st1->SetX1NDC(1.2);
  st1->SetX2NDC(1.22);
  if (isHist1 && isHist2){
    st2->SetX1NDC(1.2);  
    st2->SetX2NDC(1.22);    
  }

  st1->SetY1NDC(0.75);
  st1->SetY2NDC(0.94);
  const Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  const Double_t gaph = 0.02;
  if (isHist1 && isHist2){
    st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
    st2->SetY2NDC(st1->GetY1NDC() - gaph);
  }
  //++++++++++++++++++++ Make ratio histograms +++++++++++++++++++//

  canvas->cd();
  TPad* respad = new TPad("respad","respad", 0.0, 0.05, 0.813, 0.3);
  respad->SetTopMargin(0.0);
  respad->SetBottomMargin(0.30);
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
    hratio->GetYaxis()->SetTitle(" B / A "); //  new/ref
  }
  else if (!isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle(" B / B "); //  new/new
  }
  else if (isHist1 && !isHist2){
    hratio->GetYaxis()->SetTitle(" A / A "); //  ref/ref
  }
  hratio->SetStats(0);
  hratio->SetTitle("");
  hratio->SetLineColor(1);
  hratio->SetMarkerColor(1);
  hratio->Draw("EP"); 
  //++++++++++++++++++++ Draw ratio line +++++++++++++++++++//
  // drowing a line at 1.0 on the ratio plot
  // and another at ratio intergal average value 
  TLine * ratioline = new TLine();
  TLine * ratioline2 = new TLine();

  float av_ratio = V2_integral / V1_integral;

  ratioline->SetX1(hratio->GetXaxis()->GetBinLowEdge(hratio->GetXaxis()->GetFirst()));
  ratioline->SetX2(hratio->GetXaxis()->GetBinUpEdge(hratio->GetXaxis()->GetLast()));
  ratioline2->SetX1(hratio->GetXaxis()->GetBinLowEdge(hratio->GetXaxis()->GetFirst()));
  ratioline2->SetX2(hratio->GetXaxis()->GetBinUpEdge(hratio->GetXaxis()->GetLast()));
  ratioline->SetY1(1.0);
  ratioline->SetY2(1.0);
  ratioline2->SetY1(av_ratio);
  ratioline2->SetY2(av_ratio);

  // customize appearance
  ratioline->SetLineColor(kRed);
  ratioline2->SetLineColor(kGreen);
  ratioline->SetLineWidth(2);
  ratioline2->SetLineWidth(2);
  ratioline->SetLineStyle(2);
  ratioline2->SetLineStyle(2);

  // draw line then redraw hratio on top
  ratioline->Draw("SAME");
  ratioline2->Draw("SAME");
  hratio->Draw("EP SAME");

  //++++++++++++++++++++ Define filename, change filename output if necessary +++++++++++++++++++//

  TString filename = hname;
  modifyFilename(filename,hname,dirname);    

  filename.Append(".png");
  // copy filename for log .. stupid but whatever
  TString filenamecopy = filename;

  //++++++++++++++++++++ Save output canvas +++++++++++++++++++//
  // CMSLumi(canvas, 0, tev, lumi, era);
  CMSLumi(canvas, 0, tev, lumi, era);

  if (hname.Contains("vs_sumpt",TString::kExact) && dirname.Contains("Resolution",TString::kExact)){
    mainpad->SetLogx(1);
    respad->SetLogx(1);
  }

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

  if (hname.Contains("vs_sumpt",TString::kExact) && dirname.Contains("Resolution",TString::kExact)){
    mainpad->SetLogx(0);
    respad->SetLogx(0);
  }
  //++++++++++++++++++++ delete objects +++++++++++++++++++//

  if ( st1 ) {delete st1;}
  if ( stats1 ) {delete stats1;}
  if ( isHist1 && isHist2 ) {
    if ( st2 != NULL ) {delete st2;}
    if ( stats2 != NULL ) {delete stats2;}
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
  if ( sidepad )  {delete sidepad;}

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

bool createTProfPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, TString outdir, const Double_t lumi, const TString era, const Double_t tev) 
{
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

  if (dirname.Contains("",TString::kExact) && (hname.Contains("dzVs",TString::kExact) || hname.Contains("dxyVs",TString::kExact)))
  {
    const double tmp = std::abs(std::abs(max)>std::abs(min) ? max : min);
    max = tmp * std::copysign(1.0,max);
    min = tmp * std::copysign(1.0,min);
  }

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

  TPad* mainpad = new TPad("mainpad","mainpad", 0.0, 0.3, 0.788, 0.99);
  mainpad->SetBottomMargin(0.02);
  mainpad->Draw();
  mainpad->cd();
  histV1->Draw("EP"); // Draw old histo first, ratio is new/old
  if (isHist1 && isHist2) {
    histV2->Draw("EP sames");
  }

  mainpad->Update();

  //++++++++++++++++++++ Draw Legends +++++++++++++++++++//
  canvas->cd();
  TPad* sidepad = new TPad("sidepad","sidepad", 0.788, 0.05, 0.99, 0.99);
  sidepad->SetBottomMargin(0);
  sidepad->Draw();
  sidepad->cd();

  TLegend *leg = new TLegend(0.05,0.45,0.95,0.54);

  leg->SetTextSize(0.08);
  leg->SetTextFont(42);
  leg->SetFillColor(10); 
  leg->SetBorderSize(1); // no frame, no shadow

  string s1 = histV1->GetName();
  s1 = s1 + " (A)";

  string s2 = histV2->GetName();
  s2 = s2 + " (B)";

  leg->AddEntry(histV1, s1.c_str(), "lpf" );
  if (isHist1 && isHist2) {
    leg->AddEntry(histV2, s2.c_str(), "lpf" );
  }
  leg->Draw("SAME");
  sidepad->Update();

  //++++++++++++++++++++ Draw both stats boxes +++++++++++++++++++//

  // Here I will do a not very good thing.. I want statbox out of the histogram but it is not
  // easy, apparently, put them out of the histo box.. since they disappear. 
  // So declared a "sidepad" to put legend and statboxes. 
  // I think statbox, by default, is printed on the same pad of the histo.. So I need to clone it
  // and draw it in the right pad! But worst things are gonna come......

  TPaveStats *st1 = (TPaveStats*)(histV1->GetListOfFunctions()->FindObject("stats"));
  TPaveStats *stats1 = (TPaveStats*)(st1->Clone("stats1"));

  TPaveStats *st2 = NULL;
  TPaveStats *stats2  = NULL;

   if (isHist1 && isHist2){
    st2 = (TPaveStats*)(histV2->GetListOfFunctions()->FindObject("stats"));
    stats2 = (TPaveStats*)(st2->Clone("stats2"));
  }

  stats1->SetTextSize(0.08);
  if (isHist1 && isHist2){
    stats2->SetTextSize(0.08);
  }

  stats1->SetX1NDC(0.05);
  stats1->SetX2NDC(0.95);
  if (isHist1 && isHist2){
    stats2->SetX1NDC(0.05);
    stats2->SetX2NDC(0.95);
  }

  stats1->SetY1NDC(0.762);
  stats1->SetY2NDC(0.965);
  if (isHist1 && isHist2){
    stats2->SetY1NDC(0.55);
    stats2->SetY2NDC(0.752);
  }
 
  stats1->Draw();
  if (isHist1 && isHist2){
    stats2->Draw("SAME");
  }

// From this point I have to do a bad thing but that works.
// All I do is move 2 old stat box (st1 & st2) on the right, under the sidepad, so that 
// they are not visible. I have to do this becuase if I delete them, a statbox appear 
// on the right-top angle of the histo! And if I dont want it (Draw("same") without "sameS" S option)
// I get a segmentation violation :( So this is not a good thing to do, but works.. 
// note that to have printed st1 & st2 all i have to do is declare them and set their X&Y. Bot X and Y are necessary

  st1->SetX1NDC(1.2);
  st1->SetX2NDC(1.22);
  if (isHist1 && isHist2){
    st2->SetX1NDC(1.2);  
    st2->SetX2NDC(1.22);    
  }

  st1->SetY1NDC(0.75);
  st1->SetY2NDC(0.94);
  const Double_t defaulth = st1->GetY2NDC() - st1->GetY1NDC();
  const Double_t gaph = 0.02;
  if (isHist1 && isHist2){
    st2->SetY1NDC(st1->GetY1NDC() - 1.0*defaulth - gaph);
    st2->SetY2NDC(st1->GetY1NDC() - gaph);
  }

  //++++++++++++++++++++ Make ratio histograms +++++++++++++++++++//

  canvas->cd();
  TPad* respad = new TPad("respad","respad", 0.0, 0.05, 0.788, 0.3);
  respad->SetTopMargin(0.0);
  respad->SetBottomMargin(0.30);
  respad->Draw();
  respad->cd();

  TH1D * hratio = histV2->ProjectionX("numer","E"); // Ratio is TARGET subtracted by REF divided by REF
  TH1D * hdenom = histV1->ProjectionX("denom","E");
  hratio->Add(hdenom,-1);
  hratio->Divide(hdenom);

  hratio->SetMaximum( 2.0);
  hratio->SetMinimum(-2.0);
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

  float av_ratio = 0.;
  float V2_integral = histV2->Integral();
  float V1_integral = histV1->Integral();

  if (isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle(" (B-A) / A "); // (NEW-REF)/REF
    av_ratio = (V2_integral -V1_integral) / V1_integral;
  }
  else if (!isHist1 && isHist2){
    hratio->GetYaxis()->SetTitle(" (B-B) / B "); // (NEW-NEW)/NEW
  }
  else if (isHist1 && !isHist2){
    hratio->GetYaxis()->SetTitle(" (A-A) / A "); // (REF-REF)/REF
  }
  hratio->SetStats(0);
  hratio->SetTitle("");
  hratio->SetLineColor(1);
  hratio->SetMarkerColor(1);
  hratio->Draw("P");

  //++++++++++++++++++++ Draw ratio line +++++++++++++++++++//
  
 //++++++++++++++++++++ Draw ratio line +++++++++++++++++++//
  // drowing a line at 1.0 on the ratio plot
  // and another at ratio intergal average value 
  TLine * ratioline = new TLine();
  TLine * ratioline2 = new TLine();

  ratioline->SetX1(hratio->GetXaxis()->GetBinLowEdge(hratio->GetXaxis()->GetFirst()));
  ratioline->SetX2(hratio->GetXaxis()->GetBinUpEdge(hratio->GetXaxis()->GetLast()));
  ratioline2->SetX1(hratio->GetXaxis()->GetBinLowEdge(hratio->GetXaxis()->GetFirst()));
  ratioline2->SetX2(hratio->GetXaxis()->GetBinUpEdge(hratio->GetXaxis()->GetLast()));
  ratioline->SetY1(1.0);
  ratioline->SetY2(1.0);
  ratioline2->SetY1(av_ratio);
  ratioline2->SetY2(av_ratio);

  // customize appearance
  ratioline->SetLineColor(kRed);
  ratioline2->SetLineColor(kGreen);
  ratioline->SetLineWidth(2);
  ratioline2->SetLineWidth(2);
  ratioline->SetLineStyle(2);
  ratioline2->SetLineStyle(2);

  // draw line then redraw hratio on top
  ratioline->Draw("SAME");
  ratioline2->Draw("SAME");
  hratio->Draw("EP SAME");

  //++++++++++++++++++++ Define filename, change filename output if necessary +++++++++++++++++++//

  TString filename = hname;
  modifyFilename(filename, hname, dirname);

  filename.Append(".png");
  // copy filename for log .. stupid but whatever
  TString filenamecopy = filename;

  //++++++++++++++++++++ Save output canvas +++++++++++++++++++//
  CMSLumi(canvas, 0, tev, lumi, era);

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
    if ( st2 != NULL ) {delete st2;}
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
  tdrStyle->SetCanvasDefH(900); //Height of canvas
  tdrStyle->SetCanvasDefW(1200); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(1);
  tdrStyle->SetPadBorderSize(0);
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
  tdrStyle->SetStatFontSize(0.04);
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

void CMSLumi(TCanvas *& canv, const Int_t iPosX, const Double_t tev, const Double_t lumi, const TString era) {
  canv->cd();

  TString cmsText      = "CMS";
  Double_t cmsTextFont = 61;  // default is helvetic-bold
  
  Bool_t writeExtraText  = true;
  TString extraText      = "Private";
  Double_t extraTextFont = 52;  // default is helvetica-italics

  TString lumiText; // Dichiarazione di lumiText all'esterno degli statement condizionali

  if (strcmp(era.Data(), "X") == 0) {
      if (lumi == 0.0) {
          lumiText = Form("Era NaN - NaN pb^{-1} - %2.1f TeV", tev);
      } else {
          lumiText = Form("Era NaN - %4.2f pb^{-1} - %2.1f TeV", lumi, tev);
      }
  } else if (lumi == 0.0) {
      lumiText = Form("Era %s - NaN pb^{-1} - %2.1f TeV", era.Data(), tev);
  } else {
      lumiText = Form("Era %s - %4.2f pb^{-1} - %2.1f TeV", era.Data(), lumi, tev);
  }
  
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
  latex.DrawLatex(0.8-r,1-t+lumiTextOffset*t,lumiText); //  1-r, 0.8-r

  if (outOfFrame) {
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l+extraTextOffset,1-t+lumiTextOffset*t,cmsText);
  }
  
  Double_t posX_ = 0;
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

void modifyFilename(TString& filename,const TString& hname, const TString& dirname)
{
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
    if (filename.Contains("detachedQuadStep",TString::kExact)) {  
      if (filename.Contains("detachedQuadStepSeeds",TString::kExact)) {  
	TString replacestr  = "detachedQuadStepSeeds_detachedQuadStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "detachedQuadStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("detachedQuadStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "detachedQuadStepTrackCandidates_detachedQuadStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "detachedQuadStep";
	filename.Replace(filenamepos,length,toreplace);
      }
    }
    else if (filename.Contains("detachedTripletStep",TString::kExact)) {  
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
    else if (filename.Contains("highPtTripletStep",TString::kExact)) {  
      if (filename.Contains("highPtTripletStepSeeds",TString::kExact)) {  
	TString replacestr  = "highPtTripletStepSeeds_highPtTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "highPtTripletStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("highPtTripletStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "highPtTripletStepTrackCandidates_highPtTripletStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "highPtTripletStep";
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
    else if (filename.Contains("lowPtQuadStep",TString::kExact)) {  
      if (filename.Contains("lowPtQuadStepSeeds",TString::kExact)) {  
	TString replacestr  = "lowPtQuadStepSeeds_lowPtQuadStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "lowPtQuadStep";
	filename.Replace(filenamepos,length,toreplace);
      }
      else if (filename.Contains("lowPtQuadStepTrackCandidates",TString::kExact)) {  
	TString replacestr  = "lowPtQuadStepTrackCandidates_lowPtQuadStep";
	Ssiz_t  length      = replacestr.Length();
	Ssiz_t  filenamepos = filename.Index(replacestr.Data());
	
	TString toreplace = "lowPtQuadStep";
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
}

float GetMaxRange(TH1F *& histV1, TH1F *& histV2)
{
  const float max1 = GetMaxRange(histV1);
  const float max2 = GetMaxRange(histV2);
  return (max1 >= max2 ? max1 : max2);
}

float GetMaxRange(TH1F *& hist)
{
  int bin = hist->GetNbinsX();
  for (Int_t ibin = 1; ibin <= hist->GetNbinsX(); ibin++)
  {
    if (hist->GetBinContent(ibin) != 0.f) bin = ibin;
  }
  return hist->GetXaxis()->GetBinUpEdge(bin);
}


#endif // PLOT_FUNCTIONS_HH
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TLine.h"

#include "TStyle.h"
#include "TString.h"
#include "TLatex.h"

void V1_V2_trkComparison(const string fileName1, const string fileName2, const TString directory);
void CMSLumi(TCanvas *& canv, const Int_t iPosX, const Int_t tev, const Double_t lumi);
bool createTH1FPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, TString outdir);
bool createTProfPlot(const TString hname, const TString dirname, TFile *& V1file, const TString runstring1, const TString relstring1, TFile *& V2file, const TString runstring2, const TString relstring2, TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, TString outdir);
void setTDRStyle(TStyle *& tdrStyle);

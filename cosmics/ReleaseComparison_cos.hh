#include <vector>
#include <iostream>

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

void V1_V2_trkComparison(const TString fileName1, const TString fileName2, 
			 const TString directory, const bool full);
void CMSLumi(TCanvas *& canv, const Int_t iPosX, const Int_t year, const Double_t magB);
bool createTH1FPlot (const TString hname, const TString extra, const TString dirname,
		     TFile *& V1file, const TString runstring1, const TString relstring1, 
		     TFile *& V2file, const TString runstring2, const TString relstring2, 
		     TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, 
		     TString outdir, const Double_t magB, const Int_t year);
bool createTProfPlot(const TString hname, const TString extra, const TString dirname,
		     TFile *& V1file, const TString runstring1, const TString relstring1, 
		     TFile *& V2file, const TString runstring2, const TString relstring2, 
		     TCanvas *& canvas, const Double_t V1_integral, const Double_t V2_integral, 
		     TString outdir, const Double_t magB, const Int_t year);
void setTDRStyle(TStyle *& tdrStyle);

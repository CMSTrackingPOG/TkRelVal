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

void V1_V2_trkComparison(string fileName1, string fileName2, int scale);
bool createPlot(TString hname, TString dirname, TFile *V1file, TString runstring1, TString relstring1, TFile *V2file, TString runstring2, TString relstring2, TCanvas *canvas, int scale);
void setTDRStyle();

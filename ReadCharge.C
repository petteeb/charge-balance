#include <algorithm>


void ReadCharge()
{
  TFile* f = new TFile("my_tree.root");

  TTree* t2 = (TTree*)f->Get("t2");
  TCanvas* c1 = new TCanvas("c1", "");
  
  t2->Draw("ETA");
  t2->Print();
  c1->Print("histogram5000.png");

}
//

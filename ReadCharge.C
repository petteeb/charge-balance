#include <algorithm>


void ReadCharge()
{
  //Our vars with sizes hopefully big enough I will set mult via the tree in a min
  
  Int_t mult = 1000;
  Double_t eta[500000];
  Int_t charge[500000];
  
  double min_x;
  double max_x;
  double line;
  ifstream text("bounds.txt");
  text >> min_x >> max_x;
  text.close();
  
  TProfile* h_q1q2_deta = new TProfile("h_q1q2_deta", "Charge1*Charge2_Delta_Eta", 150, min_x, max_x);
  TProfile* h_q1_deta = new TProfile("h_q1_deta", "Charge_1_Delta_Eta", 150, min_x, max_x);
  TProfile* h_q2_deta = new TProfile("h_q2_deta", "Charge_2_Delta_Eta", 150 , min_x, max_x);
  TCanvas* c1 = new TCanvas("c1", "");  
  //TFile* f = new  TFile("my_tree.root");
  TFile* f =  TFile::Open("my_tree.root","read");  
  TTree* t2 = (TTree*)f->Get("t2");

  
  TBranch* m1 = t2->GetBranch("mult");
  m1->SetAddress(&mult);
  
  TBranch* q1 = t2->GetBranch("charge");
  q1->SetAddress(charge);
  
  TBranch* e1 = t2->GetBranch("eta");
  e1->SetAddress(eta);

  //Gets the total number of events as each entry in the tree is one.
  int events = t2->GetEntries();

  
  for(int i = 0; i< events; i++)
    {//Gets the entries for the events.
      m1->GetEntry(i);
      e1->GetEntry(i);
      q1->GetEntry(i);
      
      for(int z =0; z<mult; z++)
	{//Now every particle's charge is multiplied with every other particles charge. For each delta eta must also be recorded.
	  Int_t charge_1 = charge[z];
	  Double_t eta_1 = eta[z];
	  
	    for(int x = 1; x < mult-(z+1); x++)
	    {
	      Double_t eta_2 = eta[z+x];
	      Int_t charge_2 = charge[z+x];
	      
	      h_q1q2_deta->Fill((eta_1-eta_2),(charge_1 * charge_2) );
	      h_q1_deta->Fill((eta_1-eta_2), charge_1);
	      h_q2_deta->Fill((eta_1-eta_2), charge_2);
	    }
	}
    }
    
  e1->Print();
  q1->Print();
  m1->Print();
  f->Close();
  
  h_q1q2_deta->Draw();
  c1->Print("hist.png");
  h_q1_deta->Draw();
  c1->Print("1chist.png");
  h_q2_deta->Draw();
  c1->Print("2chist.png");
  
  TFile* fout =  TFile::Open("histogram.root", "recreate");
  h_q1q2_deta->Write();
  h_q1_deta->Write();
  h_q2_deta->Write();
  fout->Write();
  fout->Close();

}
//

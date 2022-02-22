#include <algorithm>


void ReadCharge()
{
  //Our vars with sizes hopefully big enough I will set mult via the tree in a min
  
  Int_t mult = 1000;
  Double_t eta[500000];
  Int_t charge[500000];

  //A bunch of stuff to initialized TProfile2D Which I am cancelling me no understand.
  Int_t nx = 2;
  Double_t xlow= -1;
  Double_t xup = 1;
  Int_t ny = 100;
  Double_t ylow = -2.4;
  Double_t yup = 2.4 ;
  Option_t* option="";
  
  
  TFile* f = new  TFile("my_tree.root");
  //TFile* f =  TFile::Open("my_tree.root","read");
  TTree* t2 = (TTree*)f->Get("t2");
  TCanvas* c1 = new TCanvas("c1", "");
  TProfile* h1 = new TProfile("h1", "Delta Eta", 150, -5, 5);
  //TProfile2D* h1 = new TProfile2D("h1","Charge and Eta(Dscp.)", nx, xlow, xup, ny, ylow, yup, option);
  //Set all of the branches up and the assigns them a new address. This address can be used to examine a specific entry after
  //calling GetEntry(). 
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
	      //charge_1* charge[z+x]
	      h1->Fill((eta_1-eta_2),(charge_1 * charge_2) );
	    }
	}
    }
    
  e1->Print();
  q1->Print();
  m1->Print();
  //f->Close();
  h1->Draw();
  c1->Print("hist.png");
  ///t2->Draw("eta");
  //t2->Print();
  //c1->Print("histogram5000.png");

}
//

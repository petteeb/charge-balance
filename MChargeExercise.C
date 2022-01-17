
#include <algorithm>

void MChargeExercise()
{
  // The two generated charges.
  int num_of = 100000;//Number of sets of data
  int num_trk = 500;
  int q_1;
  int q_2;
  
  

  const int nbins = 100; //Bins for histogram
  
  double maximum_eta_1 = 2.4;
  double minimum_eta_1 = -maximum_eta_1;

  
  double width = 1.0;
  double x_min = minimum_eta_1 - 3* width;
  double x_max = maximum_eta_1 + 3*width;
    
  TCanvas* c1 = new TCanvas("c1", "");//starts new canvas to which everything is drawn
  TH1D* h1 = new TH1D("h1", "eta_2-eta_1", nbins, x_min, x_max);

  TProfile* h2 = new TProfile("h2", "Balance", nbins, x_min, x_max);
  TProfile* h3 = new TProfile("h3", "q_1", nbins, x_min, x_max);
  TProfile* h4 = new TProfile("h4", "q_2", nbins, x_min, x_max);

  //Setting seed to 0 randomizes the seed
  //Setting seed to 0 randomizes the seed
  //Setting see
  gRandom->SetSeed(0);

  
  double gen_value;
  //Generates sets for num_of times.
  for(int i = 0; i < num_of; i++)
    {
      
      for(int j = 0; j < num_trk; j++)
	{
	  gen_value = gRandom->Integer(2); 
      
	  if(gen_value == 0)
	    {
	      q_1 = -1;
	    }
	  else
	    {
	      q_1 = 1;
	    }
	  //Sets q_2 to the opposite charge
	  q_2 = -(q_1);
	  
	  
	  //No functions for random ranges that I could find in ROOT. I slapped together several temporarily. In the documentation it i      s noted that Rndm() should not be used for statistical studies.
	  double eta_1 = gRandom->Uniform(minimum_eta_1, maximum_eta_1);
	  double eta_2 = eta_1 +  gRandom->Gaus(0, width);
	  //Gaussian with mean 0 and standard deviation 10^^
	  
	  double d_eta = eta_2-eta_1;
	  
	  h1->Fill(d_eta); // adds the difference here as a datapoint for the histogram.
	  h2->Fill(d_eta, q_2*q_1);
	  h3->Fill(d_eta, q_1);
	  h4->Fill(d_eta, q_2);
	  //Below assigns the data to the previously stated matrix for storage.
	  
	  
	  //      cout << eta_2 << endl;
	}
    }
  
  h1->Draw();
  c1->Print("histogram.png");
  h2->Draw();
  c1->Print("q_1timesq_2.png");
  h3->Draw();
  c1->Print("q_1.png");
  h4->Draw();
  c1->Print("q_2.png");
  
  TH1D* hh2 = h2->ProjectionX("hh2");
  TH1D* hh4 = h4->ProjectionX("hh4");
  TH1D* hh3 = h3->ProjectionX("hh3");
  hh4->Multiply(hh3);
  hh4->Draw();
  
  c1->Print("averageq_1q_2.png");
  hh4->Add(hh2,-1);
  hh4->Draw();
  c1->Print("balance.png");
}


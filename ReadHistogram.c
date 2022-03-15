void ReadHistogram()
{
  TFile* f = TFile::Open("histogram.root","read");
  f->ls();
  TCanvas* c1 = new TCanvas("c1");
  TProfile* h_q1q2_deta = (TProfile*)f->Get("h_q1q2_deta");
  TProfile* h_q1_deta = (TProfile*)f->Get("h_q1_deta");
  TProfile* h_q2_deta = (TProfile*)f->Get("h_q2_deta");
  
  cout << h_q1q2_deta << endl;
  cout << h_q1_deta << endl;
  cout << h_q2_deta << endl;
  TH1D* h1_q1q2_deta = h_q1q2_deta->ProjectionX();
  TH1D* h1_q1_deta = h_q1_deta->ProjectionX();
  TH1D* h1_q2_deta = h_q2_deta->ProjectionX();
  cout << h1_q1q2_deta << endl;
  cout << h1_q1_deta << endl;
  cout << h1_q2_deta << endl;
  h1_q1q2_deta->Draw();
  c1->Print("1histnew.png");
  h1_q1_deta->Draw();
  c1->Print("2histnew.png");
  h1_q2_deta->Draw();
  c1->Print("3histnew.png");
 
}

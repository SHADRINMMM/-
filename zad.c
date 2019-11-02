
#include <iostream>
#include <cmath>
void zad()
{	
  
  TFile* f1= new TFile("1.root", "READ");
  auto tree1 = (TTree*)f1->Get("NOMINAL");
  TFile* f2= new TFile("2.root", "READ");
  auto tree2 = (TTree*)f2->Get("NOMINAL");
  TFile f("3.root", "recreate");
  TTree t1("t1", "Simple Tree") ;
  Float_t Pt1,Eta1,Phi1,E1,Pt2,Eta2,Phi2,E2;
  t1.Branch("Pt",&Pt1,"Pt");
  t1.Branch("Eta",&Eta1,"Eta");
  t1.Branch("Phi",&Phi1,"Phi");
  t1.Branch("E",&E1,"E");
  t1.Branch("Pt",&Pt2,"Pt");
  t1.Branch("Eta",&Eta2,"Eta");
  t1.Branch("Phi",&Phi2,"Phi");
  t1.Branch("E",&E2,"E");
  
  TH1F *h11 = new TH1F("M", "W ,mas [GeV];Entries", 50, 0, 100);
  TH1F *h22 = new TH1F("M", "W ,mas [GeV];Entries", 50, 0, 100);
  TH1F *h33 = new TH1F("M", "W ,mas [GeV];Entries", 3, 0, 5);
  
  TCanvas *c = new TCanvas("c","",1900,1900);
  c->Divide(2);
  h11->SetDirectory(gROOT);
  h22->SetDirectory(gROOT);
  h33->SetDirectory(gROOT);
  
  TLorentzVector* lep_0 = 0;
  TLorentzVector* met_reco = 0;
  tree1->SetBranchAddress("lep_0_p4", &lep_0);
  tree1->SetBranchAddress("met_reco_p4", &met_reco);
  
  
  Long64_t nEvents = tree1->GetEntries();
  std::cout<<"N events: "<< nEvents << std::endl;
  Long64_t pt1=0;
  Long64_t pt2=0;
  Long64_t phi1=0;
  Long64_t phi2=0;
  Long64_t m=0;
  Long64_t bin=0;
  
 for (Long64_t j = 0; j < nEvents; j++) {
     tree1->GetEntry(j);
	 bin=1;
	 h33->Fill(bin);
	 if ((pt1=lep_0->Pt())>25) {
	 phi1=lep_0->Phi();
	 bin=2;
	 h33->Fill(bin);
	 if ((pt2=met_reco->Pt())>25){
	 phi2=met_reco->Phi();
	 bin=3;
	 h33->Fill(bin);
	 m=pow(pt1*pt2*(1-cos((phi1-phi2))),0.5) ;
	 };
	 Pt1=lep_0->Pt();
	 Phi1=lep_0->Phi();
	 Eta1=lep_0->Eta();
	 E1=lep_0->E();
	 
	 Pt2=met_reco->Pt();
	 Phi2=met_reco->Phi();
	 Eta2=met_reco->Eta();
	 E2=met_reco->E();
	 
	 t1.Fill(); 
	 h11->Fill(m);
     };
	 }
 f1->Close();
 
 lep_0 = 0;
 met_reco = 0;
 tree2->SetBranchAddress("lep_0_p4", &lep_0);
 tree2->SetBranchAddress("met_reco_p4", &met_reco);
  nEvents = tree2->GetEntries();
 for ( Long64_t j = 0; j < nEvents; j++) {
     tree2->GetEntry(j);
	 if ((pt1=lep_0->Pt())>=25) {
	 phi1=lep_0->Phi();
	 
	 if ((pt2=met_reco->Pt())>=25){
	 phi2=met_reco->Phi();
	 m=pow(pt1*pt2*(1-cos((phi1-phi2))),0.5) ;
	 };
	 
	 h22->Fill(m);
     };
	 }
 f1->Close();
 Double_t scale1= 1/h11->Integral() ;
 Double_t scale2= 1/h22->Integral() ;
 Double_t scale3= 1/h33->Integral() ;
 h11->Scale(scale1) ;
 h22->Scale(scale2) ;
 h22->Scale(scale3) ;
 
 c->cd(1);
 h22->SetLineColor(6);
 h11->Draw("HIST");
 h22->Draw("HIST same");
 
  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(h11,"W->e+nu","l");
  legend->AddEntry(h22,"W->mu+nu","l");
  legend->Draw();
 
 c->cd(2);
 h33->Draw("HIST");
 auto legend1 = new TLegend(0.1,0.7,0.48,0.9);
  legend1->AddEntry(h11,"W->e+nu","l");
  
  legend->Draw();
  t1.Write();
}
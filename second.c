
#include <iostream>
#include <cmath>


void second()
{ const int nbins = 3;	
  
  TFile* f1= new TFile("1.root", "READ");
  auto tree1 = (TTree*)f1->Get("NOMINAL");
  TFile* f2= new TFile("2.root", "READ");
  auto tree2 = (TTree*)f2->Get("NOMINAL");
  //создаем дерево для записи 
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
  //создаем дерево для записи 
  TTree t2("t2", "Simple Tree") ;
  Float_t Pt3,Eta3,Phi3,E3,Pt4,Eta4,Phi4,E4;
  t2.Branch("Pt",&Pt3,"Pt");
  t2.Branch("Eta",&Eta3,"Eta");
  t2.Branch("Phi",&Phi3,"Phi");
  t2.Branch("E",&E3,"E");
  t2.Branch("Pt",&Pt4,"Pt");
  t2.Branch("Eta",&Eta4,"Eta");
  t2.Branch("Phi",&Phi4,"Phi");
  t2.Branch("E",&E4,"E");
  
  TH1F *h11 = new TH1F("M", "W ,mas [GeV];Entries", 50, 0, 100);
  TH1F *h22 = new TH1F("M", "W ,mas [GeV];Entries", 50, 0, 100);
  
  TH1D *cutflow = new TH1D("cutflow", "Number of accepted events", nbins, 1, nbins + 1);
  cutflow->GetXaxis()->SetBinLabel(1, "All");
  //cutflow->GetXaxis()->SetBinLabel(2, "Eta crack");
  cutflow->GetXaxis()->SetBinLabel(2, "lep_pT>25 GeV");
  cutflow->GetXaxis()->SetBinLabel(3, "met_et > 25 GeV");
  
  TH1D *cutflow1 = new TH1D("cutflow", "Number of accepted events", nbins, 1, nbins + 1);
  cutflow1->GetXaxis()->SetBinLabel(1, "All");
  //cutflow->GetXaxis()->SetBinLabel(2, "Eta crack");
  cutflow1->GetXaxis()->SetBinLabel(2, "lep_pT>25 GeV");
  cutflow1->GetXaxis()->SetBinLabel(3, "met_et > 25 GeV");
  
  
  TCanvas *c = new TCanvas("c","",1900,1900);
  c->Divide(2);
  h11->SetDirectory(gROOT);
  h22->SetDirectory(gROOT);
  cutflow->SetDirectory(gROOT);
  cutflow1->SetDirectory(gROOT);
  
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
	 cutflow->Fill(1);
	 pt1=lep_0->Pt();
	 if ( !(pt1 > 25) ) continue;
     cutflow->Fill(2);
	 phi1=lep_0->Phi();
	 
	 pt2=met_reco->Pt();
     if ( !(pt2 > 25) ) continue;
	 phi2=met_reco->Phi();
     cutflow->Fill(3);
	 m=pow(pt1*pt2*(1-cos((phi1-phi2))),0.5) ;
	 
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
	 
 f1->Close();
 
 lep_0 = 0;
 met_reco = 0;
 tree2->SetBranchAddress("lep_0_p4", &lep_0);
 tree2->SetBranchAddress("met_reco_p4", &met_reco);
 nEvents = tree2->GetEntries();
 for ( Long64_t j = 0; j < nEvents; j++) {
     tree2->GetEntry(j);
	 cutflow1->Fill(1);
	 pt1=lep_0->Pt();
	 if ( !(pt1 > 25) ) continue;
     cutflow1->Fill(2);
	 phi1=lep_0->Phi();
	 
	 pt2=met_reco->Pt();
     if ( !(pt2 > 25) ) continue;
	 phi2=met_reco->Phi();
     cutflow1->Fill(3);
	 
	 m=pow(pt1*pt2*(1-cos((phi1-phi2))),0.5) ;
	 
	 Pt3=lep_0->Pt();
	 Phi3=lep_0->Phi();
	 Eta3=lep_0->Eta();
	 E3=lep_0->E();
	
	 Pt4=met_reco->Pt();
	 Phi4=met_reco->Phi();
	 Eta4=met_reco->Eta();
	 E4=met_reco->E();
	 
	 t2.Fill(); 
	 h22->Fill(m);
     };
	 
 f2->Close();
 Double_t scale1= 1/h11->Integral() ;
 Double_t scale2= 1/h22->Integral() ;
 Double_t scale3= 1/cutflow->Integral() ;
 Double_t scale4= 1/cutflow1->Integral() ;
 h11->Scale(scale1) ;
 h22->Scale(scale2) ;
 cutflow->Scale(scale3) ;
 cutflow1->Scale(scale4) ;
 
 c->cd(1);
 h22->SetLineColor(6);
 h11->Draw("HIST");
 h22->Draw("HIST same");
 
  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(h11,"W->e+nu","l");
  legend->AddEntry(h22,"W->mu+nu","l");
  legend->Draw();
  c->cd(2);
  cutflow->Draw("HIST");
  cutflow1->SetLineColor(6);
   cutflow1->Draw("HIST same");
 

 

 //auto legend1 = new TLegend(0.1,0.7,0.48,0.9);
 //legend1->AddEntry(h11,"W->e+nu","l");
  
 //legend->Draw();
 t1.Write();
 t2.Write();

}
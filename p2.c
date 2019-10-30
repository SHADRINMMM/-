#include <cmath>
void p2()
{	
  
  TFile* f1= new TFile("1.root", "READ");
  auto tree1 = (TTree*)f1->Get("NOMINAL");
  TFile* f2= new TFile("2.root", "READ");
  auto tree2 = (TTree*)f2->Get("NOMINAL");
  
  
  TH1F *h11 = new TH1F("M", "W ,mas [GeV];Entries", 50, 0, 100);
  TCanvas *c = new TCanvas("c","",1900,1900);
  c->Divide();
  h11->SetDirectory(gROOT);
  
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
  Long64_t mas=0;
  std::cout<<pt1 << std::endl;
 for (Long64_t j = 0; j < nEvents; j++) {
     tree1->GetEntry(j);
	 pt1=lep_0->Pt();
	 phi1=lep_0->Phi();
	 pt2=met_reco->Pt();
	 phi2=met_reco->Phi();
	 m=pow(pt1*pt2*(1-cos((phi1-phi2))),0.5) ;
	 mas=mas+m ;
	 h11->Fill(m);
 }
 f1->Close();
  c->cd(1);
  h11->Draw();
    }
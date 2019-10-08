void work1()
{
  TFile* f= new TFile("user.dponomar.17679655._000003.SM_WLepton.root", "READ");
  auto tree = (TTree*)f->Get("NOMINAL");

  TH1F *h11 = new TH1F("Pt", "lep;P_{T} [GeV];Entries", 50, 0, 100);
  TH1F *h12 = new TH1F("Eta", "lep;Eta ;Entries", 50, -4,4);
  TH1F *h13 = new TH1F("Phi", "lep;Phi ;Entries", 50, -4, 4);
  TH1F *h14 = new TH1F("E", "lep;E [GeV];Entries", 50, 0, 400);
  TH1F *h21 = new TH1F("Pt", "met_reco;P_{T} [GeV];Entries", 50, -10, 120);
  TH1F *h22 = new TH1F("Eta", "met_reco;Eta ;Entries", 50, -4, 4);
  TH1F *h23 = new TH1F("Phi", "met_reco;Phi ;Entries", 50, -4, 4);
  TH1F *h24 = new TH1F("E", "met_reco;E [GeV];Entries", 50, -50, 150);
  
  TCanvas *c = new TCanvas("c","",1900,1900);
  c->Divide(2,4);
   TCanvas *c1 = new TCanvas("c1","",1900,1000);
  c1->Divide(2,4);

  h11->SetDirectory(gROOT);
  h12->SetDirectory(gROOT);
  h13->SetDirectory(gROOT);
  h14->SetDirectory(gROOT);
  h21->SetDirectory(gROOT);
  h22->SetDirectory(gROOT);
  h23->SetDirectory(gROOT);
  h24->SetDirectory(gROOT);


  TLorentzVector* lep_0 = 0;
  TLorentzVector* met_reco = 0;
  tree->SetBranchAddress("lep_0_p4", &lep_0);
  tree->SetBranchAddress("met_reco_p4", &met_reco);

  Long64_t nEvents = tree->GetEntries();
  std::cout<<"N events: "<< nEvents << std::endl;
    
    for (Long64_t j = 0; j < nEvents; j++) {
      tree->GetEntry(j);
      h11->Fill(lep_0->Pt());
      h12->Fill(lep_0->Eta());
      h13->Fill(lep_0->Phi());
      h14->Fill(lep_0->E());
      h21->Fill(met_reco->Pt());
      h22->Fill(met_reco->Eta());
      h23->Fill(met_reco->Phi());
      h24->Fill(met_reco->E());
    }
    
  f->Close();
    
    c->cd(1);
    h11->Draw();
    c->cd(2);
    h12->Draw();
    c->cd(3);
    h13->Draw();
    c->cd(4);
    h14->Draw();
    c1->cd(1);
    h21->Draw();
    c1->cd(2);
    h22->Draw();
    c1->cd(3);
    h23->Draw();
    c1->cd(4);
    h24->Draw();

}

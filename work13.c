void work13()
{	
  
  TFile* f1= new TFile("1.root", "READ");
  auto tree1 = (TTree*)f1->Get("NOMINAL");
  TFile* f2= new TFile("2.root", "READ");
  auto tree2 = (TTree*)f2->Get("NOMINAL");
  // TPad *pad1 = new TPad("pad1","",0,0,1,1);
  // TPad *pad2 = new TPad("pad2","",0,0,1,1);
  // pad2->SetFillStyle(4000); //will be transparent
  // pad1->Draw();
  // pad1->cd();
   

  TH1F *h11 = new TH1F("Pt", "lep;P_{T} [GeV];Entries", 50, 0, 100);
  TH1F *h12 = new TH1F("Eta", "lep;Eta ;Entries", 50, -4,4);
  TH1F *h13 = new TH1F("Phi", "lep;Phi ;Entries", 50, -4, 4);
  TH1F *h14 = new TH1F("E", "lep;E [GeV];Entries", 50, 0, 400);
  TH1F *h21 = new TH1F("Pt", "met_reco;P_{T} [GeV];Entries", 50, -10, 120);
  TH1F *h22 = new TH1F("Eta", "met_reco;Eta ;Entries", 50, -4, 4);
  TH1F *h23 = new TH1F("Phi", "met_reco;Phi ;Entries", 50, -4, 4);
  TH1F *h24 = new TH1F("E", "met_reco;E [GeV];Entries", 50, -50, 150);
  //аналогично для 2 дерева
  TH1F *h31 = new TH1F("Pt", "lep;P_{T} [GeV];Entries", 50, 0, 100);
  TH1F *h32 = new TH1F("Eta", "lep;Eta ;Entries", 50, -4,4);
  TH1F *h33 = new TH1F("Phi", "lep;Phi ;Entries", 50, -4, 4);
  TH1F *h34 = new TH1F("E", "lep;E [GeV];Entries", 50, 0, 400);
  TH1F *h41 = new TH1F("Pt", "met_reco;P_{T} [GeV];Entries", 50, -10, 120);
  TH1F *h42 = new TH1F("Eta", "met_reco;Eta ;Entries", 50, -4, 4);
  TH1F *h43 = new TH1F("Phi", "met_reco;Phi ;Entries", 50, -4, 4);
  TH1F *h44 = new TH1F("E", "met_reco;E [GeV];Entries", 50, -50, 150);
  
  TCanvas *c = new TCanvas("c","",1900,1900);
  c->Divide(2,2);
   TCanvas *c1 = new TCanvas("c1","",1900,1000);
  c1->Divide(2,2);

  h11->SetDirectory(gROOT);
  h12->SetDirectory(gROOT);
  h13->SetDirectory(gROOT);
  h14->SetDirectory(gROOT);
  h21->SetDirectory(gROOT);
  h22->SetDirectory(gROOT);
  h23->SetDirectory(gROOT);
  h24->SetDirectory(gROOT);
  
  h31->SetDirectory(gROOT);
  h32->SetDirectory(gROOT);
  h33->SetDirectory(gROOT);
  h34->SetDirectory(gROOT);
  h41->SetDirectory(gROOT);
  h42->SetDirectory(gROOT);
  h43->SetDirectory(gROOT);
  h44->SetDirectory(gROOT);


  TLorentzVector* lep_0 = 0;
  TLorentzVector* met_reco = 0;
  tree1->SetBranchAddress("lep_0_p4", &lep_0);
  tree1->SetBranchAddress("met_reco_p4", &met_reco);

  Long64_t nEvents = tree1->GetEntries();
  std::cout<<"N events: "<< nEvents << std::endl;
    
    for (Long64_t j = 0; j < nEvents; j++) {
      tree1->GetEntry(j);
      h11->Fill(lep_0->Pt());
      h12->Fill(lep_0->Eta());
      h13->Fill(lep_0->Phi());
      h14->Fill(lep_0->E());
      h21->Fill(met_reco->Pt());
      h22->Fill(met_reco->Eta());
      h23->Fill(met_reco->Phi());
      h24->Fill(met_reco->E());
    }
    
  f1->Close();
  
  lep_0 = 0;
  met_reco = 0;
  tree2->SetBranchAddress("lep_0_p4", &lep_0);
  tree2->SetBranchAddress("met_reco_p4", &met_reco);

  nEvents = tree2->GetEntries();
  std::cout<<"N events: "<< nEvents << std::endl;
    
    for (Long64_t j = 0; j < nEvents; j++) {
      tree2->GetEntry(j);
      h31->Fill(lep_0->Pt());
      h32->Fill(lep_0->Eta());
      h33->Fill(lep_0->Phi());
      h34->Fill(lep_0->E());
      h41->Fill(met_reco->Pt());
      h42->Fill(met_reco->Eta());
      h43->Fill(met_reco->Phi());
      h44->Fill(met_reco->E());
    }
    
  f2->Close();
	//вводдим значения для нормировки 
    Double_t scale1= 1/h11->Integral() ;
	Double_t scale2= 1/h12->Integral() ; 
	Double_t scale3= 1/h13->Integral() ; 
	Double_t scale4= 1/h14->Integral() ;
	Double_t scale5= 1/h21->Integral() ;
	Double_t scale6= 1/h22->Integral() ;
	Double_t scale7= 1/h23->Integral() ;
	Double_t scale8= 1/h24->Integral() ;
	Double_t scale9= 1/h31->Integral() ; 
	Double_t scale10= 1/h32->Integral();  
	Double_t scale11= 1/h33->Integral(); 
	Double_t scale12= 1/h34->Integral();
	Double_t scale13= 1/h41->Integral();
	Double_t scale14= 1/h42->Integral(); 
	Double_t scale15= 1/h43->Integral();
	Double_t scale16= 1/h44->Integral();
    //проводим нормировку 
	h12->Scale(scale2) ;
	h13->Scale(scale3) ;
	h14->Scale(scale4) ;
	h11->Scale(scale1) ;
	h22->Scale(scale6) ;
	h23->Scale(scale7) ;
	h24->Scale(scale8) ;
	h21->Scale(scale5) ;
	
    h32->Scale(scale10) ;
	h33->Scale(scale11) ;
	h34->Scale(scale12) ;
	h31->Scale(scale9) ;
	
	h42->Scale(scale14) ;
   h43->Scale(scale15) ;
	h44->Scale(scale16) ;
	h41->Scale(scale13) ;
	// постороение канвасов 
	
    c->cd(1);
	h11->SetLineColor(4);
    h11->Draw("HIST");
	h31->SetLineColor(6);
	h31->Draw("HIST same"); 
	
	TPaveText *pt = new TPaveText(0.7,0.85,0.98,0.98, "brNDC" );
pt-> SetFillColor (18);
pt-> SetTextAlign (12);
	
pt-> AddText( "pink- W->mu+nu " );
	pt-> AddText( "blue-  W->enu" );
	//pt-> AddText ( "\" <\ "для сортировки по возрастанию значений" );
   pt-> Draw ();
	
//	pad1->Update(); //this will force the generation of the "stats" box
 // TPaveStats *ps1 = (TPaveStats*)h31->GetListOfFunctions()->FindObject("stats");
 //  ps1->SetX1NDC(0.4); ps1->SetX2NDC(0.6);
  // pad1->Modified();
	
	//pad2->Update();
	//TPaveStats *ps2 = (TPaveStats*)h11->GetListOfFunctions()->FindObject("stats");
  // ps2->SetX1NDC(0.65); ps2->SetX2NDC(0.85);
  // ps2->SetTextColor(kRed);
	// TPad *pad1 = new TPad("pad1","",0,0,1,1);
      //pad2->SetFillStyle(4000); //will be transparent
	//pad1->Draw();
//pad1->cd(2);
 //c->cd(1);
	 
    c->cd(2);		
	h12->SetLineColor(4);
    h12->Draw("HIST");
	//pad1->Update();
	//TPaveStats *ps1 = (TPaveStats*)h12->GetListOfFunctions()->FindObject("stats");
   // ps1->SetX1NDC(0.4); ps1->SetX2NDC(0.6);
   // pad1->Modified();
	h32->SetLineColor(6);
	h32->Draw("HIST same");
	
    c->cd(3);
	h13->SetLineColor(4);
    h13->Draw("HIST");
	h33->SetLineColor(6);
	h33->Draw("HIST same");
	
    c->cd(4);
	h14->SetLineColor(4);
    h14->Draw("HIST");
	h34->SetLineColor(6);
	h34->Draw("HIST same");
	
    c1->cd(1);
	h21->SetLineColor(4);
    h21->Draw("HIST");
	h41->SetLineColor(6);
	h41->Draw("HIST same");
	
	TPaveText *pt1 = new TPaveText(0.7,0.85,0.98,0.98, "brNDC" );
pt1-> SetFillColor (18);
pt1-> SetTextAlign (12);
	
pt1-> AddText( "pink- W->mu+nu " );
	pt1-> AddText( "blue-  W->enu" );
	//pt-> AddText ( "\" <\ "для сортировки по возрастанию значений" );
   pt1-> Draw ();
	
    c1->cd(2);
	h22->SetLineColor(4);
    h22->Draw("HIST");
	h42->SetLineColor(6);
	h42->Draw("HIST same");
	
    c1->cd(3);
	h23->SetLineColor(4);
    h23->Draw("HIST");
	h43->SetLineColor(6);
    h43->Draw("HIST same");
	
	c1->cd(4);
	h24->SetLineColor(4);
    h24->Draw("HIST");
	h44->SetLineColor(6);
	h44->Draw("HIST same");
	
}

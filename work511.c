#include <iostream>
#include <cmath>
using namespace std;

void work511 ()
{ const int nbins = 5;	
  TFile* f1= new TFile("MCData16a.root", "READ"); //данные 
  auto tree1 = (TTree*)f1->Get("NOMINAL");
  TFile* f2= new TFile("MCData16.root", "READ");//фон
  auto tree2 = (TTree*)f2->Get("NOMINAL");
  
  TH1D *cutflow1 = new TH1D("cutflow", "Number of accepted events", nbins, 1, nbins + 1);
  cutflow1->GetXaxis()->SetBinLabel(1, "All");
  cutflow1->GetXaxis()->SetBinLabel(2, "pt_ph_S > 150");
  cutflow1->GetXaxis()->SetBinLabel(3, "pt_met_S> 130");
  cutflow1->GetXaxis()->SetBinLabel(3, "N_jets_S>=2");
  
  TH1D *cutflow2 = new TH1D("cutflow", "Number of accepted events", nbins, 1, nbins + 1);
  cutflow2->GetXaxis()->SetBinLabel(1, "All");
  cutflow2->GetXaxis()->SetBinLabel(2, "pt_ph_S > 150");
  cutflow2->GetXaxis()->SetBinLabel(3, "pt_met_S> 130");
  cutflow2->GetXaxis()->SetBinLabel(3, "N_jets_S>=2");
  
  TH1D *cutflow = new TH1D("cutflow", "Number of accepted events", nbins, 1, nbins + 1);
  cutflow->GetXaxis()->SetBinLabel(1, "All");
  TH1D *cutfloww = new TH1D("cutflow", "Number of accepted events", nbins, 1, nbins + 1);
  cutfloww->GetXaxis()->SetBinLabel(1, "All");

  
  TH1D *cutflow_S = new TH1D("cutflow", "Number events with kriteria for signal", nbins, 1, nbins + 1);
  cutflow_S->GetXaxis()->SetBinLabel(1, "All");
  cutflow_S->GetXaxis()->SetBinLabel(2, "mjj");
  cutflow_S->GetXaxis()->SetBinLabel(3, "Rapidity");
  cutflow_S->GetXaxis()->SetBinLabel(3, "centr");
  cutflow_S->GetXaxis()->SetBinLabel(3, "pt balance");
  
  TH1D *cutflow_B = new TH1D("cutflow", "Number events with kriteria for background", nbins, 1, nbins + 1);
  cutflow_B->GetXaxis()->SetBinLabel(1, "All");
  cutflow_B->GetXaxis()->SetBinLabel(2, "mjj");
  cutflow_B->GetXaxis()->SetBinLabel(3, "Rapidity");
  cutflow_B->GetXaxis()->SetBinLabel(3, "centr");
  cutflow_B->GetXaxis()->SetBinLabel(3, "pt balance");
  
  
  TCanvas *c = new TCanvas("c","",1900,1900);
  c->Divide(4);
  cutflow_S->SetDirectory(gROOT);
  cutflow_B->SetDirectory(gROOT);
  cutflow->SetDirectory(gROOT);
  cutflow1->SetDirectory(gROOT);
// 4 вектора в которые будут составляться из дерева 
// с индексом _S - собыите  
   TLorentzVector lead_S  ;
   TLorentzVector sub_lead_S ;
   TLorentzVector ph_S ;
   TLorentzVector met_S ;
   
   TLorentzVector lead_B  ;
   TLorentzVector sub_lead_B ;
   TLorentzVector ph_B ;
   TLorentzVector met_B ;
   //задание переменных 
   Double_t pt_lead_S;
   Double_t pt_lead_B;
   Double_t pt_sublead_B;
   Double_t pt_sublead_S;
   
   Double_t pt_met_B;
   Double_t pt_met_S;
   Double_t pt_ph_B;
   Double_t pt_ph_S ;
   
   Double_t eta_lead_S;
   Double_t eta_lead_B;
   Double_t eta_sublead_S;
   Double_t eta_sublead_B;
   
   Double_t eta_ph_S;
   Double_t eta_ph_B;
   
   Double_t phi_lead_S;
   Double_t phi_lead_B;
   Double_t phi_sublead_S;
   Double_t phi_sublead_B;
   
   Double_t phi_met_S;
   Double_t phi_met_B;
   
   Double_t phi_ph_S;
   Double_t phi_ph_B;
   
   Double_t E_lead_S;
   Double_t E_lead_B;
   
   Double_t E_sublead_S;
   Double_t E_sublead_B;
   Double_t N_jets_B;
   Double_t N_jets_S;
 // cчитывание данных из дерева 
   tree1-> SetBranchAddress ( "jet_lead_pt" , &pt_lead_S);
   tree1-> SetBranchAddress ( "jet_lead_eta" , &eta_lead_S);
   tree1-> SetBranchAddress ( "jet_lead_phi" , &phi_lead_S);
   tree1-> SetBranchAddress ( "jet_lead_E" , &E_lead_S);
   
   tree2-> SetBranchAddress ( "jet_lead_pt" , &pt_lead_B);
   tree2-> SetBranchAddress ( "jet_lead_eta" , &eta_lead_B);
   tree2-> SetBranchAddress ( "jet_lead_phi" , &phi_lead_B);
   tree2-> SetBranchAddress ( "jet_lead_E" , &E_lead_B);
   
   tree1-> SetBranchAddress ( "jet_sublead_pt" , &pt_sublead_S);
   tree1-> SetBranchAddress ( "jet_sublead_eta" , &eta_sublead_S);
   tree1-> SetBranchAddress ( "jet_sublead_phi" , &phi_sublead_S);
   tree1-> SetBranchAddress ( "jet_sublead_E" , &E_sublead_S);
   
   tree2-> SetBranchAddress ( "jet_sublead_pt" , &pt_sublead_B);
   tree2-> SetBranchAddress ( "jet_sublead_eta" , &eta_sublead_B);
   tree2-> SetBranchAddress ( "jet_sublead_phi" , &phi_sublead_B);
   tree2-> SetBranchAddress ( "jet_sublead_E" , &E_sublead_B);
   
   tree1-> SetBranchAddress ( "ph_pt" , &pt_ph_S);
   tree1-> SetBranchAddress ( "ph_eta" , &eta_ph_S);
   tree1-> SetBranchAddress ( "ph_phi" , &phi_ph_S);

   
   tree2-> SetBranchAddress ( "ph_pt" , &pt_ph_B);
   tree2-> SetBranchAddress ( "ph_eta" , &eta_ph_B);
   tree2-> SetBranchAddress ( "ph_phi" , &phi_ph_B);

   
   tree1-> SetBranchAddress ( "metTST_pt" , &pt_met_S);
   tree1-> SetBranchAddress ( "metTST_phi" , &phi_met_S);

   
   tree2-> SetBranchAddress ( "metTST_pt" , &pt_met_B);
   tree2-> SetBranchAddress ( "metTST_phi" , &phi_met_B);
   
   tree1-> SetBranchAddress ( "n_jet" , &N_jets_S);
   tree2-> SetBranchAddress ( "n_jet" , &N_jets_B);

 Long64_t Kr_S=0;
 Long64_t Kr_cetr_S=0;
 Long64_t Kr_mass_S=0;
 Long64_t Kr_rapidity_S=0;
Long64_t Kr_pt_S=0;

Long64_t Kr_B=0;
Long64_t Kr_cetr_B=0;
Long64_t Kr_mass_B=0;
Long64_t Kr_rapidity_B=0;
Long64_t Kr_pt_B =0;
 
  Double_t njj_S=0;
  Double_t njj_B=0;
  Double_t dnjj_S=0;
  Double_t dnjj_B=0;
  Double_t zet_S=0;
  Double_t zet_B=0;

  Long64_t nEvents_S = tree1->GetEntries();
  
  for ( Long64_t j = 0; j < nEvents_S; j++) {
	//проверка начальных критериев 
  	tree1->GetEntry(j);
	cutflow->Fill(1);
	cutflow1->Fill(1);
	if ( !(pt_ph_S > 150) ) continue;  
	cutflow1->Fill(2);
	if ( !(pt_met_S> 130) ) continue;  
	cutflow1->Fill(3);
	if ( !(N_jets_S>=2) ) continue;  
	cutflow1->Fill(4);
	// заполнение 4 векторов 
   lead_S.SetPtEtaPhiE(pt_lead_S,eta_lead_S,phi_lead_S,E_lead_S);
   sub_lead_S.SetPtEtaPhiE(pt_sublead_S,eta_sublead_S,phi_sublead_S,E_sublead_S);
	ph_S.SetPtEtaPhiM(pt_ph_S,eta_ph_S,phi_ph_S,0);
	met_S.SetPtEtaPhiM(pt_met_S,0,phi_met_S,0);
//критерий на инвариантную массу 
Kr_S=Kr_S+1;
cutflow_S->Fill(1);
if((lead_S.M()+sub_lead_S.M())>600) Kr_mass_S=Kr_mass_S+1;
cutflow_S->Fill(2);
//кртерий на разность быстрот
if((abs(lead_S.Rapidity()-sub_lead_S.Rapidity()))>2.5) Kr_rapidity_S=Kr_rapidity_S+1;
cutflow_S->Fill(3);
//критерий на центральность 
njj_S=(lead_S.PseudoRapidity()+sub_lead_S.PseudoRapidity())/2;	
dnjj_S=(lead_S.PseudoRapidity()-lead_S.PseudoRapidity());
zet_S=abs((ph_S.PseudoRapidity()-njj_S)/dnjj_S);
if (zet_S<0.3) Kr_cetr_S=Kr_cetr_S+1;
cutflow_S->Fill(4);
//критерий на pt 
if(pow(((lead_S+sub_lead_S+ph_S+met_S).Pt()),2)/(pow(lead_S.Pt(),2)+pow(sub_lead_S.Pt(),2)+pow(ph_S.Pt(),2)+pow(met_S.E(),2))<0.1) Kr_pt_S=Kr_pt_S+1;
  cutflow_S->Fill(5);
  }
  
  
  Long64_t nEvents_B = tree2->GetEntries();
  
  for ( Long64_t j = 0; j < nEvents_B; j++) {
	//проверка начальных критериев   
    tree2->GetEntry(j);
	cutfloww->Fill(1);
	cutflow2->Fill(1);
	if ( !(pt_ph_B > 150) ) continue;  
	cutflow2->Fill(2);
	if ( !(pt_met_B> 130) ) continue;  
	cutflow2->Fill(3);
	if ( !(N_jets_B>=2) ) continue;  
	cutflow2->Fill(4);	
	
	// заполнение 4 векторов  
	lead_B.SetPtEtaPhiE(pt_lead_B,eta_lead_B,phi_lead_B,E_lead_B);
	sub_lead_B.SetPtEtaPhiE(pt_sublead_B,eta_sublead_B,phi_sublead_B,E_sublead_B);
	ph_B.SetPtEtaPhiM(pt_ph_B,eta_ph_B,phi_ph_B,0);
	ph_B.SetPtEtaPhiM(pt_met_B,0,phi_met_B,0);
//критерий на инвариантную массу 
  cutflow_B->Fill(1);
	Kr_B=Kr_B+1;
if((lead_B.M()+sub_lead_B.M())>600) Kr_mass_B=Kr_mass_B+1;
cutflow_B->Fill(2);
//кртерий на разность быстрот
if((abs(lead_B.Rapidity()-sub_lead_B.Rapidity()))>2.5) Kr_rapidity_B=Kr_rapidity_B+1;
cutflow_B->Fill(3);
//критерий на центральность 
njj_B=(lead_B.PseudoRapidity()+sub_lead_B.PseudoRapidity())/2;	
dnjj_B=(lead_B.PseudoRapidity()-lead_B.PseudoRapidity());
zet_B=abs((ph_B.PseudoRapidity()-njj_B)/dnjj_B);
if (zet_B<0.3) Kr_cetr_B=Kr_cetr_B+1;
cutflow_B->Fill(4);
//критерий на pt 
if(pow(((lead_B+sub_lead_B+ph_B+met_B).Pt()),2)/(pow(lead_B.Pt(),2)+pow(sub_lead_B.Pt(),2)+pow(ph_B.Pt(),2)+pow(met_B.E(),2))<0.1) Kr_pt_B=Kr_pt_B+1;
  cutflow_B->Fill(5);
  }
Double_t Zn_Kr_mass =Kr_mass_S/sqrt(Kr_mass_S+Kr_mass_B);  
Double_t Zn_Kr_rapidity =Kr_rapidity_S/sqrt(Kr_rapidity_S+Kr_rapidity_B);  ;  
Double_t Zn_Kr_cetr =Kr_cetr_S/sqrt(Kr_cetr_S+Kr_cetr_B);  ;  
Double_t Zn_Kr_pt =Kr_pt_S/sqrt(Kr_pt_S+Kr_pt_B);  ;  
 
std::cout<<"значимость критерия для инвариантности масс "<< Zn_Kr_mass << std::endl;
std::cout<<"значимость критерия для быстроты "<< Zn_Kr_rapidity << std::endl;
std::cout<<"значимость критерия для центральности вылета "<<Zn_Kr_cetr << std::endl;
std::cout<<"значимость критерия для баланса импульсов "<< Zn_Kr_pt << std::endl; 


f1->Close();
f2->Close();

 Double_t scale1= 1/cutflow_S->Integral() ;
 Double_t scale2= 1/cutflow_B->Integral() ;
 Double_t scale3= 1/cutflow->Integral() ;
 Double_t scale4= 1/cutflow1->Integral() ;
 Double_t scale5= 1/cutfloww->Integral() ;
 Double_t scale6= 1/cutflow2->Integral() ;
 
 cutflow_S->Scale(scale1) ;
 cutflow_B->Scale(scale2) ;
 cutflow1->Scale(scale3) ;
 cutflow2->Scale(scale5) ;
 
 
 
 c->cd(1);
  cutflow1->Draw("HIST");
  cutflow2->SetLineColor(6);
  cutflow2->Draw("HIST same");
 c->cd(2);
  cutflow_S->Draw("HIST");
 c->cd(3);
  cutflow_B->Draw("HIST");
}

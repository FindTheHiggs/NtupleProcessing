#include "NtupAnaSkeleton.h"

#include <TFile.h>
#include <TChain.h>
#include <TLorentzVector.h>

#include <fstream>
#include <iostream>

# define DEBUG 1

using std::cout;
using std::endl;
using std::string;

NtupAnaSkeleton::NtupAnaSkeleton(const std::string& pInFileName, const std::string& pTreeName, const std::string& pOutFileName, const std::string& pInFileList) {

  if (DEBUG)
    cout << __FILE__ << "in NtupAnaSkeleton::NtupAnaSkeleton " << endl;

  if (""==pInFileList) {
    // get a tree to analyse
    TFile *tFile = new TFile(pInFileName.c_str(),"READ"); 
    if (!tFile || !tFile->IsOpen()) {
      cout << __FILE__<< " ERROR: file could not be opened : " << pInFileName << endl;
    }
    if (DEBUG)
      cout << __FILE__<< " fetching tree from file : " << pTreeName << " from " << pInFileName << endl;
    tFile->GetObject(pTreeName.c_str(),mTree);
  }
  else {
    // we want to analyse a list of files
    if (FILE* tFile = fopen(pInFileList.c_str(), "r")) {
      fclose(tFile);
    }
    else {
      cout << __FILE__ << " ERROR: cannot read list of input files : " << endl;
      cout << pInFileList << endl;
    }
    if (DEBUG) {
      cout << __FILE__ << " chaining file from list , tree : " << pInFileList << " , "<< pTreeName<< endl;
    }
    std::ifstream tIFS(pInFileList.c_str());
    string tThisFile;
    TChain* tChain=new TChain(pTreeName.c_str());

    while(std::getline(tIFS, tThisFile)) {
      if (DEBUG) {
        cout << " ..... "<< tThisFile <<endl;
      }
      tChain->Add(tThisFile.c_str());
    }
    mTree=(TTree*)(tChain);
  }
  
  // and initialize its branches 
  if (DEBUG) {
    cout << __FILE__ << " init tree " << endl;
  }
  init(mTree);

  // setting output file name from command line
  mOutFile.open(pOutFileName.c_str());

}

void NtupAnaSkeleton::init(TTree* pTree) {

  // TODO: init branches here
  pTree->SetBranchAddress("photon_n", &photon_n, &b_photon_n);
  pTree->SetBranchAddress("photon_pt",&photon_pt, &b_photon_pt);
  pTree->SetBranchAddress("photon_eta",&photon_eta, &b_photon_eta);
  pTree->SetBranchAddress("photon_phi",&photon_phi, &b_photon_phi);
  pTree->SetBranchAddress("photon_E",&photon_E, &b_photon_E);
  pTree->SetBranchAddress("jet_n", &jet_n, &b_jet_n);
  pTree->SetBranchAddress("jet_pt",&jet_pt, &b_jet_pt);
  pTree->SetBranchAddress("jet_eta",&jet_eta, &b_jet_eta);
  pTree->SetBranchAddress("jet_phi",&jet_phi, &b_jet_phi);
  pTree->SetBranchAddress("jet_E",&jet_E, &b_jet_E);
  pTree->SetBranchAddress("photon_isTightID",&photon_isTightID, &b_photon_isTightID);
  pTree->SetBranchAddress("photon_ptcone30",&photon_ptcone30, &b_photon_ptcone30);
  pTree->SetBranchAddress("photon_etcone20",&photon_etcone20, &b_photon_etcone20);

  // open input file for writing:
  

  return;
} // end of init


// loop over events and fill histograms
void NtupAnaSkeleton::analyse(int pNevents) {

  bool write_jets = false;
  // cuts on tight ID and isolation;
  // apply the criterion?
  bool applyTI = false;
  // if so what should the TI criterion be? (disregarded if applyTI = false)
  // TI = false gives NTNI background data
  bool TI = false;
  
  int tAllEntries = (pNevents<0) ? mTree->GetEntries() : pNevents;

  if (DEBUG) {
    cout << __FILE__<< "Analyising # entries : "<<tAllEntries<<endl;
  }
  
  // TODO: insert your code here
  //for (int iEntry = 0; iEntry < 1000; ++iEntry) {
  for (int iEntry = 0; iEntry < tAllEntries; ++iEntry) {
    mTree->GetEntry(iEntry);
    if (DEBUG && 0==iEntry%10000) { 
      cout << " .... processing entry "<< iEntry << endl;
    }
    
    // example: 
    //mOutFile << "# photons: " << photon_n << std::endl;
    //for (auto t : (*photon_pt)) {
    //   mOutFile << "photon pt: " << t << std::endl;
    //}
    //
    if (2==photon_n) {
      if (applyTI) {
        bool isTight = ((*photon_isTightID)[0]==true && (*photon_isTightID)[1]==true);
        bool isIsolated = true;
        double y1_ptiso = (*photon_ptcone30)[0]/(*photon_pt)[0];
        double y2_ptiso = (*photon_ptcone30)[1]/(*photon_pt)[1];
        double y1_etiso = (*photon_etcone20)[0]/(*photon_pt)[0];
        double y2_etiso = (*photon_etcone20)[1]/(*photon_pt)[1];
        double ptiso_relcut = 0.15;
        double etiso_relcut = 0.2;
        if (y1_ptiso>=ptiso_relcut || y2_ptiso>=ptiso_relcut
            || y1_etiso>=etiso_relcut || y2_etiso>=etiso_relcut) {
          isIsolated = false;
        }
        if (TI && (!isTight || !isIsolated)) {
          continue;
        }
        else if (!TI && (isTight && isIsolated)) {
          continue;
        }
      }

      double myy = -999.;
      TLorentzVector y1(0.,0.,0.,0.);
      TLorentzVector y2(0.,0.,0.,0.);
      y1.SetPtEtaPhiE((*photon_pt)[0],(*photon_eta)[0],(*photon_phi)[0],(*photon_E)[0]);
      y2.SetPtEtaPhiE((*photon_pt)[1],(*photon_eta)[1],(*photon_phi)[1],(*photon_E)[1]);
      myy = (y1+y2).M()/1000.; // GeV

      // drop events with myy very far from the higgs mass peak
      double myy_low = 105; // GeV
      double myy_high = 160; // GeV
      if (myy < myy_low || myy > myy_high){
        continue;
      }

      // scaled values: 
      /*
      mOutFile << (*photon_pt)[0]/(myy*1000.) << "," << (*photon_eta)[0] << ","
               << (*photon_phi)[0] << "," << (*photon_E)[0]/(myy*1000.) << ","
               << (*photon_pt)[1]/(myy*1000.) << "," << (*photon_eta)[1] << ","
               << (*photon_phi)[1] << "," << (*photon_E)[1]/(myy*1000.) << "," << myy;
      */      
      mOutFile << (*photon_pt)[0]/1000. << "," << (*photon_eta)[0] << ","
               << (*photon_phi)[0] << "," << (*photon_E)[0]/1000. << ","
               << (*photon_pt)[1]/1000. << "," << (*photon_eta)[1] << ","
               << (*photon_phi)[1] << "," << (*photon_E)[1]/1000. << "," << myy;

      if (write_jets) {
        if (jet_n>1) {
          mOutFile << "," << (*jet_pt)[0]/1000. << "," << (*jet_eta)[0] << ","
                   << (*jet_phi)[0] << "," << (*jet_E)[0]/1000.;
        }
        else {
          mOutFile << "," << -9.9 << "," << -9.9 << "," << -9.9 << "," << -9.9;
        }
        if (jet_n>2) {
          mOutFile << "," << (*jet_pt)[1]/1000. << "," << (*jet_eta)[1] << ","
                   << (*jet_phi)[1] << "," << (*jet_E)[1]/1000.;
        }
        else {
          mOutFile << "," << -9.9 << "," << -9.9 << "," << -9.9 << "," << -9.9;
        }
      }
      mOutFile << std::endl;
      
    }
    
  }// end of loop over all entries
  
  // all done, clean-up and return
  finalise();
  return;

}// end of analyse

// 
void NtupAnaSkeleton::finalise() {

  mOutFile.close();
  return;

}// end of finalise


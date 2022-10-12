#include "NtupAnaSkeleton.h"

#include <TFile.h>
#include <TChain.h>

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
  pTree->SetBranchAddress("photon_isTightID",&photon_isTightID, &b_photon_isTightID);
  pTree->SetBranchAddress("photon_ptcone30",&photon_ptcone30, &b_photon_ptcone30);
  pTree->SetBranchAddress("photon_etcone20",&photon_etcone20, &b_photon_etcone20);

  // open input file for writing:
  

  return;
} // end of init


// loop over events and fill histograms
void NtupAnaSkeleton::analyse(int pNevents) {

  int tAllEntries = (pNevents<0) ? mTree->GetEntries() : pNevents;

  if (DEBUG) {
    cout << __FILE__<< "Analyising # entries : "<<tAllEntries<<endl;
  }
  
  // TODO: insert your code here
  for (int iEntry = 0; iEntry < tAllEntries; ++iEntry) {
    mTree->GetEntry(iEntry);
    if (DEBUG && 0==iEntry%10000) { 
      cout << " .... processing entry "<< iEntry << endl;
    }
    mOutFile << "# photons: " << photon_n << std::endl;
    for (auto t : (*photon_pt)) {
       mOutFile << "photon pt: " << t << std::endl;
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


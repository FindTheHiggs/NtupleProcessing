#ifndef CNTUPANASKELETON_H_
#define CNTUPANASKELETON_H_

#include <TROOT.h>
#include <TTree.h>

/*

liza.mijovic@cern.ch
TODO: add your contact here 

Minimal skeleton for analysing flat ntuples.
See README for instructions. 

 */

class CNtupAnaSkeleton {

 public :
  TTree* mTree;
  std::string mOutFileName;
  CNtupAnaSkeleton(const std::string& pInFileName, const std::string& pTreeName, const std::string& pOutFileName, const std::string& pInFileList="");
  void fInit(TTree* pTree);
  void fAnalyse(int pNevents=-1);

  // TODO:
  //your variables and branches here + init them in Init
  //for pointers, intialize to 0
  
  UInt_t          jet_n;
  TBranch *b_jet_n = 0;
  
  std::vector<float>  *photon_pt=0;
  TBranch        *b_photon_pt=0; //!
  
};

#endif

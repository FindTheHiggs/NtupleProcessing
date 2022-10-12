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
  
  UInt_t          photon_n;
  std::vector<float>   *photon_pt=0;;
  std::vector<float>   *photon_eta=0;;
  std::vector<float>   *photon_phi=0;;
  std::vector<float>   *photon_E=0;;
  std::vector<bool>    *photon_isTightID=0;;
  std::vector<float>   *photon_ptcone30=0;;
  std::vector<float>   *photon_etcone20=0;;

  TBranch        *b_photon_n=0;  //!
  TBranch        *b_photon_pt=0; //!
  TBranch        *b_photon_eta=0; //!
  TBranch        *b_photon_phi=0;   //!
  TBranch        *b_photon_E=0;   //!
  TBranch        *b_photon_isTightID=0;   //!
  TBranch        *b_photon_ptcone30=0;   //!
  TBranch        *b_photon_etcone20=0;   //!


};

#endif

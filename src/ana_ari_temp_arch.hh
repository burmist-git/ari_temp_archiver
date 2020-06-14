#ifndef ana_ari_temp_arch_hh
#define ana_ari_temp_arch_hh

//My
#include "ana_ari_temp_archbase.hh"

//root
#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;


class ana_ari_temp_arch: public ana_ari_temp_archbase {
public:
  ana_ari_temp_arch(TString fileList) : ana_ari_temp_archbase(fileList)
  {
  }

  ana_ari_temp_arch(TString file, Int_t key) : ana_ari_temp_archbase(file, key)
  {
  }

  void Loop(TString histOut);
  TString getLocalTimeStringFromUnixTime( double ut );
  
};

#endif

/***********************************************************************
* Copyright(C) 2019 - LBS - (Single person developer.)                 *
* Sun Apr 21 23:13:52 JST 2019                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//c, c++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>

//root
#include <TTree.h>
#include <TFile.h>

const int nDataLogMax = 100000;

void ari_temp_archiver_converter (TString outRootFile, int nData, int utint[nDataLogMax], float data[nDataLogMax]) {
  Int_t _nData = nData;
  Int_t _unixTime[nDataLogMax];
  Float_t _data[nDataLogMax];
  for(Int_t i = 0;i<nDataLogMax;i++){
    _unixTime[i] = 0;
    _data[i] = 0.0;
  }
  for(Int_t i = 0;i<nData;i++){
    _unixTime[i] = utint[i];
    _data[i] = data[i];
  }
  //
  TFile *hfile = new TFile( outRootFile, "UPDATE", "pc stat log", 1);
  if (hfile->IsZombie()) {
    std::cout << "PROBLEM with the initialization of the output ROOT ntuple " 
         << outRootFile << ": check that the path is correct!!!"
         <<std::endl;
    assert(0);
  }
  //
  TString ut_ss = "unixTime["; ut_ss+=nDataLogMax; ut_ss+="]/I";
  TString data_ss = "data["; data_ss+=nDataLogMax; data_ss+="]/F";
  TTree *tree;
  if(!(TTree*)hfile->Get("T")){
    //cout<<" FIRST TIME"<<endl;
    tree = new TTree("T", "pc stat log tree");
    tree->Branch("nData",&_nData, "nData/I");
    tree->Branch("unixTime",_unixTime, ut_ss.Data());
    tree->Branch("data", _data, data_ss.Data());
  }
  else {
    //cout<<" NOT FIRST TIME"<<endl;
    tree = (TTree*)hfile->Get("T");
    tree->SetBranchAddress("nData", &_nData);
    tree->SetBranchAddress("unixTime", &_unixTime);
    tree->SetBranchAddress("data", &_data);
  }
  //
  hfile->SetCompressionLevel(2);
  tree->SetAutoSave(1000000);
  // Create new event
  TTree::SetBranchStyle(0);
  tree->Fill();
  hfile->Write();
  hfile->Close();
}

#ifdef ARI_TEMP_ARCHIVER_CONVERT_MAIN
# ifndef __CINT__
int main(int argc, char *argv[]) {
  if(argc > 3 ){
    //std::cout<<"argc = "<<argc<<std::endl;
    int utint[nDataLogMax];
    float data[nDataLogMax];
    Int_t exeKeyID = atoi(argv[1]);
    Int_t nData = atoi(argv[2]);
    TString outRootF = argv[3];
    std::cout<<"exeKeyID "<<exeKeyID<<std::endl
	     <<"nData    "<<nData<<std::endl
	     <<"outRootF "<<outRootF<<std::endl;
    if( nData > nDataLogMax ){
      std::cout<<" ERROR ---> nData > nDataLogMax "<<std::endl
	       <<"            nData = "<<nData<<std::endl
	       <<"      nDataLogMax = "<<nDataLogMax<<std::endl;
      assert(0);
    }
    if(exeKeyID == 0 && argc == (4 + nData*2)){
      for(Int_t i = 0;i<nData;i++){
	utint[i] = atoi(argv[4 + 2*i]);
	data[i]  = atof(argv[4 + 2*i + 1]);
	//std::cout<<"utint[i] "<<utint[i]<<std::endl
	//	 <<"data[i]  "<<data[i]<<std::endl;
      }
      ari_temp_archiver_converter ( outRootF, nData, utint, data);
    }
    else{
      std::cout<<" ---> ERROR in input arguments "<<std::endl;
      assert(0);
    }    
  }
  else{
    std::cout<<" ---> ERROR in input arguments "<<std::endl;
    assert(0);
  }
  return 0;
}
# endif //ifndef __CINT__
#endif //ifdef ARI_TEMP_ARCHIVER_CONVERT_MAIN

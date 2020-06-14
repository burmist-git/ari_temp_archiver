//my
#include "ana_ari_temp_arch.hh"

//root
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TRandom3.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TPad.h>
#include <TText.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

const Double_t xtMin = 25; //Nominal
const Double_t xtMax = 50; //Nominal

void ana_ari_temp_arch::Loop(TString histOut){
  Int_t i = 0;
  Int_t i_tmp = 0;
  TGraph *gr_t[nChannels];
  tGraphInit(gr_t, "gr_t_ARI_tmp", "ARI tmp");
  TH1D *h1_t[nChannels];
  h1D1Init(h1_t,"h1_t_ARI_tmp","ARI tmp ",100,0.0,100.0);
  TH1D *h1_samplingTime[nChannels];
  h1D1Init(h1_samplingTime,"h1_samplingTime_ARI_tmp","Sampling time ARI tmp ",1000,0.0,100.0);
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  if(nentries > nChannels){
    cout<<" ERROR ---> nentries > nChannels "<<endl
	<<"            nentries = "<<nentries<<endl
	<<"           nChannels = "<<nChannels<<endl;
    assert(0);
  }
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    i_tmp = (Int_t)jentry;
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(nData > nDataLogMax)
      assert(0);
    for(i = 0;i<nData;i++){
      gr_t[i_tmp]->SetPoint(gr_t[i_tmp]->GetN(), unixTime[i], data[i]);
      h1_t[i_tmp]->Fill(data[i]);
      if(i>0)
	h1_samplingTime[i_tmp]->Fill(unixTime[i] - unixTime[i-1]);
    }
  }
  /////////////////////////////////////////
  Double_t markerSize = 0.5;
  Double_t lineWidth = 2.0;
  const Int_t colorArr[nChannels] = { kBlack, kRed, kBlue, kGreen + 3, kMagenta, kGray+1};
  const Int_t markerArr[nChannels] = { 20, 20, 20, 21, 21, 21};
  for(i = 0;i<nChannels;i++){
    gr_t[i]->SetLineColor(colorArr[i]);
    gr_t[i]->SetLineWidth(lineWidth);
    gr_t[i]->SetMarkerColor(colorArr[i]);
    gr_t[i]->SetMarkerStyle(markerArr[i]);
    gr_t[i]->SetMarkerSize(markerSize);
    gr_t[i]->GetYaxis()->SetRangeUser(xtMin, xtMax);
    gr_t[i]->GetXaxis()->SetTimeDisplay(1);
    gr_t[i]->GetXaxis()->SetTitle("Time, h");
    gr_t[i]->GetYaxis()->SetTitle("ARICH temperature, C^{o}");
    //
    h1_t[i]->SetLineWidth(lineWidth);
    h1_t[i]->SetLineColor(colorArr[i]);
    h1_t[i]->GetXaxis()->SetTitle("ARICH temperature, C^{o}");
    //
    h1_samplingTime[i]->SetLineWidth(lineWidth);
    h1_samplingTime[i]->SetLineColor(colorArr[i]);
    h1_samplingTime[i]->GetXaxis()->SetTitle("Sampling time, s");
  }
  /////////////////////////////////////////
  gStyle->SetPalette(kRainBow);
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1600,1200);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  c1->SetTitle("ARICH Temperature Sensor");
  c1->SetName("c1_arich_temperature_sensor");
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->SetTopMargin(0.1);
  c1->SetBottomMargin(0.15);
  c1->Divide(3,2);
  //
  c1->cd(1);
  c1->GetPad(1)->SetGrid();
  TMultiGraph *mg1 = new TMultiGraph();
  TString mg1Title = "ARICH Temperature Sensor";
  TString mg1Name = "mg1_ARI_TEMP";
  mg1->SetTitle(mg1Title.Data());
  mg1->SetName(mg1Name.Data());
  mg1->Add(gr_t[0]);
  mg1->Add(gr_t[1]);
  mg1->Add(gr_t[2]);
  mg1->SetMinimum(xtMin);
  mg1->SetMaximum(xtMax);
  mg1->Draw("APL");
  mg1->GetXaxis()->SetTimeDisplay(1);
  mg1->GetXaxis()->SetLabelSize(0.025);
  //mg1->GetXaxis()->SetTitleSize(10);
  mg1->GetXaxis()->SetTitle("Time, h");
  mg1->GetYaxis()->SetTitle("ARICH temperature sensor, C^{o}");
  //
  c1->cd(2);
  c1->GetPad(2)->SetGrid();
  TMultiGraph *mg2 = new TMultiGraph();
  TString mg2Title = "ARICH Temperature Sensor";
  TString mg2Name = "mg2_ARI_TEMP";
  mg2->SetTitle(mg2Title.Data());
  mg2->SetName(mg2Name.Data());
  mg2->Add(gr_t[3]);
  mg2->Add(gr_t[4]);
  mg2->Add(gr_t[5]);
  mg2->SetMinimum(xtMin);
  mg2->SetMaximum(xtMax);
  mg2->Draw("APL");
  mg2->GetXaxis()->SetTimeDisplay(1);
  mg2->GetXaxis()->SetLabelSize(0.025);
  //mg2->GetXaxis()->SetTitleSize(10);
  mg2->GetXaxis()->SetTitle("Time, h");
  mg2->GetYaxis()->SetTitle("ARICH temperature sensor, C^{o}");
  //
  c1->cd(3);
  c1->GetPad(3)->SetGrid();
  TLegend *leg = new TLegend(0.1,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_t[0], "ARI_TEMP_1 (Right)","lp");
  leg->AddEntry(gr_t[1], "ARI_TEMP_2 (Top)","lp");
  leg->AddEntry(gr_t[2], "ARI_TEMP_3 (Left)","lp");
  leg->AddEntry(gr_t[3], "ARI_TEMP_4 (Bottom)","lp");
  leg->AddEntry(gr_t[4], "ARI_TEMP_5 (ARICH side wall)","lp");
  leg->AddEntry(gr_t[5], "ARI_TEMP_6 (IDS)","lp");
  leg->Draw();
  double utstart;
  double utstop;
  double temper1;
  gr_t[0]->GetPoint(1, utstart, temper1);
  TString timeStr_start = "Time start : ";
  timeStr_start += getLocalTimeStringFromUnixTime( utstart );
  gr_t[0]->GetPoint(gr_t[0]->GetN()-1, utstop, temper1);
  TString timeStr_stop = "Time stop : ";
  timeStr_stop += getLocalTimeStringFromUnixTime( utstop );
  TText *text1_start = new TText(0.1,0.5,timeStr_start.Data());
  //text1_start->SetTextAlign(22);
  text1_start->SetTextSize(0.05);
  text1_start->Draw();
  TText *text1_stop = new TText(0.1,0.45,timeStr_stop.Data());
  //text1_stop->SetTextAlign(22);
  text1_stop->SetTextSize(0.05);
  text1_stop->Draw();
  //
  c1->cd(4);
  c1->GetPad(4)->SetGrid();
  h1_t[0]->Draw();
  h1_t[1]->Draw("sames");
  h1_t[2]->Draw("sames");
  //
  c1->cd(5);
  c1->GetPad(5)->SetGrid();
  h1_t[3]->Draw();
  h1_t[4]->Draw("sames");
  h1_t[5]->Draw("sames");
  //
  c1->cd(6);
  c1->GetPad(6)->SetGrid();
  c1->GetPad(6)->SetLogy();
  for(i = 0;i<nChannels;i++){
    if(i == 0)
      h1_samplingTime[i]->Draw();
    else
      h1_samplingTime[i]->Draw("sames");
  }
  /////////////////////////////////////////
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", "Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  c1->Write();
  mg1->Write();
  mg2->Write();
  for(i = 0;i<nChannels;i++)
    gr_t[i]->Write();
  for(i = 0;i<nChannels;i++)
    h1_t[i]->Write();
  for(i = 0;i<nChannels;i++)
    h1_samplingTime[i]->Write();  
  rootFile->Close();
  //
  TString histOutPdf = histOut;
  histOutPdf += ".pdf";
  c1->SaveAs(histOutPdf.Data());
}

TString ana_ari_temp_arch::getLocalTimeStringFromUnixTime( double ut ){
  time_t t_ut = ut;
  struct tm * timeinfo = localtime(&t_ut);
  TString timeStr = asctime(timeinfo);
  //printf ("Current local time and date: %s", asctime(timeinfo));
  return timeStr;
}

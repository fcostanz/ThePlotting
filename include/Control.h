/* template class to plot Control plots 

Author: OS
*/

#pragma once
#include <TPad.h>
#include <TH1D.h>
#include <THStack.h>
#include <TString.h>
#include <cmath>
#include "MakeUp.h"
namespace plotting{
  
  template<class dat_type, class bkg_type, class sig_type>  class Control :Pad<dat_type,bkg_type,sig_type>{
  private:
    MakeUp makeup;  
  public:
    Control(SizePad_t s, PositionPad_t p, TString t):Pad<dat_type,bkg_type,sig_type>(s,p,t){};

    TPad* DrawPlot(dat_type*,bkg_type* data = 0,sig_type* signal = 0);
    
  };

  template<class dat_type, class bkg_type, class sig_type> 
  TPad* plotting::Control<dat_type,bkg_type,sig_type>::DrawPlot(dat_type* data,bkg_type* background, sig_type* signal)
  {
    //Assumptions:
    //dat_type is derived from TH1
    //background will be used to style TPad
    bool Reverse = false;
    makeup.AddLegend(data,"data");
    makeup.AddLegend(background);
    if(signal) 
      makeup.AddLegend(signal);
    TPad* pad2= Pad<dat_type,bkg_type,sig_type>::AllocPad(data->GetName(),background->GetName()+(TString)"_hs");
    pad2->Draw();
    pad2->cd();
    background->Draw("hist");

    background->SetTitle("");
    background->GetXaxis()->SetNdivisions(505);
    background->GetYaxis()->SetLabelFont(45); //font in pixels
    background->GetYaxis()->SetLabelSize(16); //in pixels
    if(Pad<dat_type,bkg_type,sig_type>::pos==kTop) background->GetXaxis()->SetLabelSize(0);    
    else     background->GetXaxis()->SetTitle(background->GetTitle());
    background->GetYaxis()->SetTitleOffset(1.4); 
    background->GetXaxis()->SetTitleOffset(1.2); 
    if(data) 
      {
	data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);
	data->SetLineColor(1);
	if(data->GetMaximumBin()>(data->GetXaxis()->GetLast()-data->GetXaxis()->GetFirst())/2) Reverse = true; //to plot the legend on the empty side
      }
    background->GetXaxis()->SetNdivisions(505);


    pad2->cd();

    if(data) data->Draw("SAME,EP");
    if(signal!=0)
      {
	signal->Draw("SAME,HIST,NOSTACK");
	signal->SetMinimum(1);
      }
    pad2->Update();
    
    //Set the visible range on Y axis 
    if(data)
      if(background->GetMaximum() > data->GetMaximum()) 
	{    
	  background->SetMaximum(background->GetMaximum()*9);
	  background->SetMinimum(0.7);
	  background->GetYaxis()->SetRangeUser(0.5,background->GetMaximum());
	  pad2->Update();
	}
      else
	{
	  background->SetMaximum(data->GetMaximum()*9);
	  background->SetMinimum(0.7);
	  background->GetYaxis()->SetRangeUser(0.5,data->GetMaximum());
	  pad2->Update();
	}
    makeup.Reverse=Reverse;
    makeup.rock(pad2);
   
    return pad2;
  }
};



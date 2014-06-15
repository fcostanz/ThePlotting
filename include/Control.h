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
  
  template<class bkg_type, class dat_type, class sig_type>  class Control :Pad<bkg_type,dat_type,sig_type>{
  private:
    MakeUp makeup;  
  public:
    Control(SizePad_t s, PositionPad_t p, TString t):Pad<bkg_type,dat_type,sig_type>(s,p,t){};

    TPad* DrawPlot(bkg_type*,dat_type* data = 0,sig_type* signal = 0);
    
  };

  template<class bkg_type, class dat_type, class sig_type> 
  TPad* plotting::Control<bkg_type,dat_type,sig_type>::DrawPlot(bkg_type* background, dat_type* data, sig_type* signal)
  {
    //Assumptions:
    //dat_type is derived from TH1
    //background will be used to style TPad
    bool Reverse = false;
    if(data) makeup.AddLegend(data,"data");
    makeup.AddLegend(background);
    if(signal) 
      makeup.AddLegend(signal);
    TPad *pad2;
    if(data)    pad2= Pad<bkg_type,dat_type,sig_type>::AllocPad(data->GetName(),background->GetName()+(TString)"_hs");
    else    pad2= Pad<bkg_type,dat_type,sig_type>::AllocPad(background->GetName());
    pad2->Draw();
    pad2->cd();
    background->Draw("hist");

    background->SetTitle("");
    background->GetXaxis()->SetNdivisions(505);
    background->GetYaxis()->SetLabelFont(45); //font in pixels
    background->GetYaxis()->SetLabelSize(16); //in pixels
    if(Pad<bkg_type,dat_type,sig_type>::pos==kTop) background->GetXaxis()->SetLabelSize(0);    
    else background->GetXaxis()->SetTitle(background->GetTitle());

    background->GetYaxis()->SetTitleOffset(1.4); 
    background->GetXaxis()->SetTitleOffset(1.2); 
    background->GetXaxis()->SetNdivisions(505);
    if(data) 
      {
	data->SetMarkerStyle(20);
	data->SetMarkerSize(0.5);
	data->SetLineColor(1);
	if(data->GetMaximumBin()>(data->GetXaxis()->GetLast()-data->GetXaxis()->GetFirst())/2) Reverse = true; //to plot the legend on the empty side
	data->Draw("SAME,EP");
      }

    pad2->cd();
    
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
	  background->SetMaximum(background->GetMaximum()*18);
	  pad2->Update();
	}
      else
	{
	  background->SetMaximum(data->GetMaximum()*18);
	  pad2->Update();
	}
    else  background->SetMaximum(background->GetMaximum()*18);
    background->SetMinimum(1);
    makeup.Reverse=Reverse;
    makeup.rock(pad2);
   
    return pad2;
  }
};



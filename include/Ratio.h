/* Template class for ratio plots 
Author: OS
*/

#ifndef Ratio_h
#define Ratio_h
#include <TPad.h>
#include <TH1D.h>
#include <THStack.h>
#include <TString.h>
#include <cmath>
#include <iostream>
#include <TLine.h>
#include "MakeUp.h"
namespace plotting{
   
  template<class dat_type, class bkg_type, class sig_type>  class Ratio : Pad<dat_type,bkg_type,sig_type>{
  public:
    Ratio(SizePad_t s, PositionPad_t p, TString t):Pad<dat_type,bkg_type,sig_type>(s,p,t){};
    ~Ratio(){};
    
    TPad* DrawPlot(dat_type*,bkg_type*,sig_type* signal = 0);
    
  };
  template<class dat_type, class bkg_type, class sig_type> TPad* plotting::Ratio<dat_type,bkg_type,sig_type>::DrawPlot(dat_type* data,bkg_type* background, sig_type* signal)
    {

      TPad* pad1= this->AllocPad(data->GetName(),background->GetName());
      pad1->Draw();
      

      TString name = (TString)"Ratio plot of "+data->GetName()+" vs "+background->GetName();
      dat_type* ratio = (dat_type*)data->Clone(name);
      
      pad1->cd();
      ratio->GetYaxis()->SetLabelFont(45); //font in pixels
      ratio->GetYaxis()->SetLabelSize(16); //in pixels
      ratio->SetStats(0);
      
      ratio->SetTitle("");
      ratio->Divide(background);
      double min;
      double max;
      
      ratio->GetYaxis()->SetTitle((TString)"#frac{data}{MC}");
      ratio->GetYaxis()->SetTitleFont(45);
      ratio->GetYaxis()->CenterTitle();
      ratio->GetYaxis()->SetTitleSize(15); 
      ratio->GetYaxis()->SetTitleOffset(1.75); 
      ratio->SetMarkerStyle(1);
     
      if(Pad<dat_type,bkg_type,sig_type>::pos==kTop) ratio->SetLabelSize(0,"X");
      else {
	ratio->GetXaxis()->SetLabelSize(16); //in pixel
	ratio->GetXaxis()->SetLabelFont(45);
	ratio->GetXaxis()->SetTitle(background->GetTitle());
	ratio->GetXaxis()->SetTitleFont(45); 
	ratio->GetXaxis()->SetTitleSize(15.5); 
	ratio->GetXaxis()->SetTitleOffset(4.5);

      }

      ratio->GetYaxis()->SetNdivisions(505);
      ratio->GetXaxis()->SetNdivisions(505);
      if(fabs(1.-ratio->GetMinimum())>(fabs(ratio->GetMaximum()-1.)) && ratio->GetMinimum()!= 0)
	{
	  double max=1.+fabs(1.-ratio->GetMinimum())-ratio->GetBinError(ratio->GetMinimumBin());
	  if(max>2)
	    { ratio->SetMaximum(3.001); ratio->SetMinimum(-0.001); }
	  else if(max>1.5)
	    { ratio->SetMaximum(2.001); ratio->SetMinimum(-0.001); }
	  else
	    { ratio->SetMaximum(1.001); ratio->SetMinimum(-0.001); }
	  
	}
      else 
	{
	  double max=fabs(ratio->GetMaximum()+ratio->GetBinError(ratio->GetMaximumBin()));
	  if(max>2)
	    { ratio->SetMaximum(3.001); ratio->SetMinimum(-0.001); }
	  else if(max>1.5)
	    { ratio->SetMaximum(2.001); ratio->SetMinimum(-0.001); }
	  else
	    { ratio->SetMaximum(1.501); ratio->SetMinimum(0.499); }

	}
      
      pad1->Update();
      pad1->SetTicky();
      pad1->SetTickx();
      ratio->SetMarkerColor(kRed+4);
      ratio->SetLineColor(kRed+4);
      ratio->Draw("ep");
      TLine* line = new TLine(ratio->GetXaxis()->GetXmin(),1,ratio->GetXaxis()->GetXmax(),1);
      line->Draw();
      pad1->Update();
      return pad1;
    }


};
#endif 

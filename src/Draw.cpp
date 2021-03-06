/*please see the header file for class definition
Author: OS
Do not modify the code (it is tested and it works properly) unless you really know what you are doing and unless it is stated with capital letters (i.e 
YOU CAN ADD YOUR REVISION HISTORY HERE)
ozgur[no_spam].sahin[spam_not]@cern.ch 
*/

#include "Draw.h"
#include "Properties.h"
#include "Dir.h"
#include <iostream>
#include <algorithm>
#include "Histo.h"
#include <vector>
#include "TString.h"
#include <TH1D.h>
#include <TAxis.h>
#include <TFile.h>
#include <TCanvas.h>
#include <cstdlib>
#include "Pad.h"
#include "Ratio.h"
#include "Control.h"
#include <THStack.h>
#include "THistPainter.h"
#include "TError.h"
#include "Color.h"
#include "TObject.h"
#include "TLegend.h"
/* Everything starts from this method (since it is called in the constructor :)), 
 loop over path files and arrange samples*/
using namespace plotting;
void plotting::Draw::arrange_hists(const TString& config_path)
{
  TH1::SetDefaultSumw2(true);
  gErrorIgnoreLevel = kBreak;
  properties property(config_path);
  std::vector<TString*>::iterator path_it;
  //Don't worry we are not moving the objects, just put their addresses together.
  dat_hists = new std::vector<Dir_container>;
  bkg_hists = new std::vector<Dir_container>;
  sig_hists = new std::vector<Dir_container>;
  //YOU CAN SET COLOR COMP FOR THE SAMPLES HERE
  
  for(path_it = property.paths.begin(); path_it != property.paths.end(); path_it++)
    {
      if(dat == property.sample_prop[(**path_it)])
	{	
	  Histo* sample= new Histo(property.sample_prop[(**path_it)],(*path_it));
	  dat_hists->push_back((sample->hists));
	}
      else if(bkg == property.sample_prop[(**path_it)])
	{	
	  ColorStyle.SetColorComp(kMultiComp);
	  Histo* sample= new Histo(property.sample_prop[(**path_it)],(*path_it),ColorStyle.GetColor());
	  bkg_hists->push_back((sample->hists));
	}
      else if(sig == property.sample_prop[(**path_it)])
	{	
	  ColorStyle.SetColorComp(kRedComp);
	  Histo* sample= new Histo(property.sample_prop[(**path_it)],(*path_it),ColorStyle.GetColor());
	  sig_hists->push_back((sample->hists));
	}
    }
  //Here the objects are sorted and THStacks are created
  if(bkg_hists->size()!=0)
    {
      bkg_hists_stack = new std::vector<Hists_container>;
      mc_sequence(bkg_hists,bkg_hists_stack,true,true);
    }
  if(sig_hists->size()!=0)
    {
      sig_hists_stack = new std::vector<Hists_container>;
      mc_sequence(sig_hists,sig_hists_stack,false,true);
    }
}
/*This method creates the bkg stacks and it makes the life easier for the Pad class. The sort function is called here as well
PS: I am well aware of the fact that looping over objects starting from second index is wrong (due to the memory allocation) 
yet it is necessary for the sorting in this case
*/
void plotting::Draw::mc_sequence(std::vector<Dir_container>* mc_hists, std::vector<Hists_container>* mc_hists_stack, bool addhists, bool sorthists)
{
  int col;
  int i;
  int j;
  Hists_container * mc_dir_stack;
  //Identical directory structure among different samples is assumed here
  //To sort over the samples [first index of the container] for each selection region/directory [second index] we started to loop
  // starting from second index
  for(i=0;i<mc_hists->at(0)->size();i++) 
    {
      if(sorthists){
	sort_hist.i = i;
	std::sort(mc_hists->begin(),mc_hists->end(),sort_hist);
      }
      for(j=0;j<mc_hists->size();j++)
	{
	  //create the objects for the first sample
	  if(j==0)
	    {
	      std::vector<Hist>::iterator hist_container_it;
	      mc_dir_stack = new Hists_container;
	      Hist* mc_stack = new Hist;
	      //loop iver hist containers
	      for(hist_container_it=mc_hists->at(j)->at(i).begin();hist_container_it!=mc_hists->at(j)->at(i).end();hist_container_it++)
		{
		  if(addhists)
		    {
		      mc_stack->h=(TH1D*)hist_container_it->h->Clone();
		    }
		  mc_stack->stack= new THStack((TString)"hs "+hist_container_it->h->GetName(),(TString)hist_container_it->h->GetTitle());
		  mc_stack->stack->Add(hist_container_it->h);
		  mc_dir_stack->push_back((*mc_stack));
		}
	      mc_hists_stack->push_back(*mc_dir_stack);	     
	    }
	  else
	    {

	      int index = 0;
	      std::vector<Hist>::iterator hist_container_it;
	      for(hist_container_it=mc_hists->at(j)->at(i).begin();hist_container_it!=mc_hists->at(j)->at(i).end();hist_container_it++)
		{
		  if(addhists)
		    {
		      mc_hists_stack->at(i).at(index).h->Add(hist_container_it->h);
		    }
		  mc_hists_stack->at(i).at(index).stack->Add(hist_container_it->h);
		  index++;
		}
	    }
	}
    }
}

//YOU CAN COPY THIS METHOD TO CREATE YOUR OWN CANVASES
//Control plots are produced here.
void plotting::Draw::ControlRatioPlot(const bool createfiles,const TString& extension)
{
  TCanvas *c1;
  TPad* cont,*rat;
  Dir* PlotDir= new Dir("RatioControlPlots");
  //  PlotDir->print_mDir();//prints the main dir
  TFile * ratiocontrol = new TFile ("RatioControlPlots.root", "RECREATE");
  // HERE YOU CAN CHANGE THE ORDER OF THE PADS
  Ratio<TH1D,TH1D,TH1D> RatioPlot( kSmall, kTop,(TString) "ratio");
  Control<THStack,TH1D,THStack> ControlPlot( kBig, kBottom,(TString) "control");
  //iterates over the sample objects
  std::vector<Hists_container>::iterator bkg_dir_it;
  std::vector<Hists_container>::iterator sig_dir_it;
  if(sig_hists->size()!=0) sig_dir_it =  sig_hists_stack->begin();;
  std::vector<Hists_container>::iterator data_dir_it;  
  if(dat_hists->size()!=0)  data_dir_it = dat_hists->at(0)->begin();
  //Hist Containers
  std::vector<Hist>::iterator sig_hist_it;
  std::vector<Hist>::iterator bkg_hist_it;
  std::vector<Hist>::iterator data_hist_it;
  //same file structure is assumed here
  for(bkg_dir_it = bkg_hists_stack->begin(); bkg_dir_it != bkg_hists_stack->end(); bkg_dir_it++)
    {

      if(sig_hists->size()!=0)  sig_hist_it  = sig_dir_it->begin();
      if(dat_hists->size()!=0)  data_hist_it = data_dir_it->begin();
      
      TString canvas_name;
      for(bkg_hist_it =(bkg_dir_it)->begin(); bkg_hist_it != (bkg_dir_it)->end(); bkg_hist_it++)
	{
	  canvas_name = (TString)bkg_hist_it->h->GetName();
	  canvas_name.Remove(0,canvas_name.First('_')+1);//strip the sample name from canvas
	  c1 = new TCanvas(canvas_name,canvas_name,600, 700); 
	  if(dat_hists->size()!=0) rat = RatioPlot.DrawPlot((TH1D*)bkg_hist_it->h, (TH1D*)data_hist_it->h);
	  c1->cd();
	  if(sig_hists->size()!=0 && dat_hists->size()!=0)  cont =ControlPlot.DrawPlot( (THStack*)bkg_hist_it->stack,(TH1D*)data_hist_it->h, (THStack*)sig_hist_it->stack);
	  else if(sig_hists->size()!=0)  cont =ControlPlot.DrawPlot((THStack*)bkg_hist_it->stack,0, (THStack*)sig_hist_it->stack);
	  else if(dat_hists->size()!=0)  cont =ControlPlot.DrawPlot((THStack*)bkg_hist_it->stack,(TH1D*)data_hist_it->h,0);
	  else cont =ControlPlot.DrawPlot((THStack*)bkg_hist_it->stack);
	  c1->Update();
	  c1->Write();
	  if(createfiles && dat_hists->size()!=0)  PlotDir->SaveCanvas(extension,data_hist_it->dir,c1);
	  if(dat_hists->size()!=0)  data_hist_it++; 
	  if(sig_hists->size()!=0)  sig_hist_it++; 
	  c1->Delete();
	}
      if(dat_hists->size()!=0) data_dir_it++;
      if(sig_hists->size()!=0)  sig_dir_it++;
    }
  ratiocontrol->Close();
}

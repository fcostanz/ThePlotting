/*
Please see Histo.h file for the class definition
Author:OS
*/

#include "Histo.h"
#include <TString.h>
#include <TH1D.h>
#include <TKey.h>
#include <TFile.h>
#include <iostream>
#include <cstdlib>
using namespace std;
//simple method that sets the integral for the given value to Hist container 
void plotting::Histo::Set_integral(Hist* hist_it,int min, int max)  {
  
  (*hist_it).integ_reg=(*hist_it).h->Integral(min,max);
  //cout <<"integral " << (*hist_it).integ_reg << endl;
}
/*
For each given path iteratively loop over the directories
*/
void plotting::Histo::fill_hist (Histo_t* sample_type, TString* file_path){
  vector<TString> dirName;
  float min = 0., max = 100.; //numbers and generally the structure are dummy, will add the proper treatment later
  sample_name = new TString(*file_path);
  sample_name->Remove(0,sample_name->Last('/')+1);
  sample_name->Remove(sample_name->First('.'),sample_name->Length()-1);
  cout <<*sample_name << endl;
  TFile *File = new TFile(*file_path,"READ");
  if ( File->IsZombie() ) 
    {
      cout << "File in path \n"<< *file_path << "could not opened successfully\n";
      exit(1);
    } 
  Loop_histos((TDirectory*) File,sample_type,dirName);
  File->Close();
}
//loop over the histograms and fill the container.
void plotting::Histo::Loop_histos(TDirectory * dir,Histo_t * type, vector<TString>& dirName,int dir_depth,  TString dName, TString mName){ //pass pointer later
  TDirectory *cur_dir = gDirectory;   
  TString hName="";
  TIter nextkey(dir->GetListOfKeys()); 
  TKey *key;

  while ((key=(TKey*)nextkey())) {
    if(key->IsFolder()){
      if(0 == dir_depth ) 
	{
	  dName = (TString)key->GetName();
	  mName = dName;
	  (&dirName)->push_back((TString)key->GetName());
	  cout << dName << endl;
	}
      else
	{
	  (&dirName)->push_back((TString)key->GetName());
	  dName = dName+(TString)"_"+(TString)key->GetName();  

	}
      dir_depth++;
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      plotting::Histo::Loop_histos(subdir,type,dirName,dir_depth, dName,mName);
      dir_depth--;
      dName = mName;
      (&dirName)->pop_back();
      cur_dir->cd();}
    else {
      Hist hist_container;
      if(key->GetClassName()=="TH2D")//replace this with find function
	{
	  hist_container.h2= (TH2D*)(key->ReadObj())->Clone();
	  hist_container.h2->SetDirectory(0);
	}
      else
	{	
	  hist_container.h= (TH1D*)(key->ReadObj())->Clone();
	  hist_container.h->SetDirectory(0);
	  Set_integral(&hist_container,hist_container.h->GetMinimumBin(),hist_container.h->GetMaximumBin());
	  hName = (*sample_name)+(TString)"_"+dName+(TString)"_"+(TString)key->GetName();  
	  hist_container.h->SetName(hName);
	  if(*type==bkg) hist_container.h->SetFillColor(col);
	  if(*type==sig) hist_container.h->SetLineWidth(3);
	  if(*type==sig) hist_container.h->SetOption("HIST");
	  hist_container.h->SetLineColor(col); 
	}
      hist_container.sample_name=sample_name;      
      hist_container.dir=dirName;
      hist_container.type=type;
      dir_container->push_back(hist_container);                  
    }
  }
  //the logic reaches this point either after looping over the histograms in a dir or while finalizing the loop over dirs. Therefore, this "if" statement is needed
  if(dir_container->size()) 
    { 
      hists->push_back(*dir_container);
      dir_container=new Hists_container;
    }
 
}

int plotting::Histo::Print() const {
  cout<<"Hello world!"<<endl;
  return 0;
}

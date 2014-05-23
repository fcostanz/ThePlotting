/* Draw is the main class to create final plots.
->arrange samples, and index them together in a vector <,bkg,sig,dat>
->put the received pads into canvases

All objects are connected to this class therefore please treat it carefully. 

Author: OS */

#ifndef Draw_h
#define Draw_h
#include <algorithm>
#include <Histo.h>
#include <iostream>
#include <vector>
#include "Histo.h"
#include <THStack.h>
#include "Color.h"
namespace plotting{
  class Draw: public Histo_base{
  public: 
    Draw(){
      arrange_hists("./config.txt");};
    Draw(const TString& config_path){
      arrange_hists(config_path);
    };
    ~Draw(){};
    void arrange_hists(const TString&);
    void ControlRatioPlot(bool createfiles = false, const TString & extension = "pdf");
  private:
    //operator to std::sort the Hists_container according to the integ_reg value of the given hist container at pos_of_ref
    struct sort_ref : public std::binary_function<Hists_container*, Hists_container*,bool>
    {  
      int i;
      static const int ref_var = 5; //njets - one can do this dynamic as well but I am too lazy to do it now...
      //compare function the variable location is hard coded for the moment
      //YOU CAN CHANGE THE REFERENCE VARIABLE TO COMPARE SAMPLES HERE
      bool operator()(Dir_container compare_begin, Dir_container compare_end) 
      {
	return (compare_begin->at(i).at(ref_var).integ_reg < compare_end->at(i).at(ref_var).integ_reg);
      }
    } sort_hist;
    //containers
    Dir_container bkg_hists_stack;
    Dir_container sig_hists_stack;

    std::vector<Dir_container>* bkg_hists;//Bkg   container:vector<vector<vector<struct>*>*>
    std::vector<Dir_container>* sig_hists;//Signal
    std::vector<Dir_container>* dat_hists;//Data

    void mc_sequence(std::vector<Dir_container>* mc_hists, Dir_container mc_hists_stack,bool addhists = true, bool sorthists = false);
    Color ColorStyle; 
  };
};
#endif

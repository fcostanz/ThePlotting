/* basic container class to arrange large number of histograms
Author: OS
*/

#ifndef Histo_h
#define Histo_h
#include <TString.h>
#include <TH1D.h>
#include <TH2F.h>
#include <vector>
#include <iostream>
#include <THStack.h>
/*Purpose of this class is to arrange histogram containers for the plotting tool
  The Histo base class is inherited to variety of different classes among the tool, 
  thus, a basic understanding of this class is necessary to do modifications on the
  tool*/

namespace plotting{
  enum Histo_t{dat, bkg, sig};   
  class Histo_base{
  public:    
    /* This is the basic histogram container. Some members may seem redundant, but
       they do not have too much impact on total memory usage and give accessiblity
       to different methods. 
       (assuming #histos<1e6) */
    struct Hist{
      float integ_reg;
      Histo_t* type;
      TString* sample_name;
      std::vector<TString> dir; 
      THStack *stack;
      TH1D* h;
      TH2D* h2;   
    } hist_type;
    
    typedef std::vector<Hist> Hists_container;
    typedef std::vector<Hists_container>* Dir_container;//vector<vector<struct>*>
  };
  
  class Histo: public Histo_base {
  public:
    Histo(Histo_t sample_type,  TString* path){
      init();
      fill_hist(&sample_type, path);
      col=1; 
    };
    
    Histo(Histo_t sample_type,  TString* path, int c){
      init();
      col = c;
      fill_hist(&sample_type, path);
      };
    Histo(){};
    ~Histo(){};
    Dir_container hists;//this object will be partitioned wrt to the dirs
  private:
    Hists_container * dir_container; //this is to be used in Loop_histos method
    void init()
    {
      hists=new std::vector<Hists_container>;
      dir_container = new Hists_container;
    }
    void Set_integral( Hist* hist_it, int min, int max);
    int col;
    TString* sample_name;
    int Print() const;
    void Loop_histos(TDirectory *, Histo_t*, std::vector<TString>& dirName, int dir_depth = 0, TString dName="",TString mName="");
    void fill_hist (Histo_t *, TString*); 
  };
};
#endif

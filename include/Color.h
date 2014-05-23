/*This is very simple class handle color compositions for the plots
Author: OS
*/

#ifndef Color_h
#define Color_h
#include <TPad.h>
#include <TH1D.h>
#include <THStack.h>
#include <TString.h>
#include <map>
#include <vector>
#include "Histo.h"
#include "THStack.h"
/*kWhite =0, kBlack =1, kGray=920, kRed =632, kGreen =416, kBlue=600, 
  kYellow=400, kMagenta=616, kCyan=432, kOrange=800, kSpring=820, 
  kTeal=840, kAzure=860, kViolet=880, kPink=900*/
namespace plotting{
  enum ColorStyle_t {kRedComp, kBlueComp, kGreenComp, kMultiComp, kBlueShadeComp};
  class Color{
  public:
    
    int GetColor();

    Color(){
      initColorComp();
      colorcomp = kBlueComp;
      indexRC=0;indexGC=0;indexMC=0;indexBSC=0;indexBC=0;
    }; 
    void SetColorComp(ColorStyle_t c)
    {
      colorcomp=c;
    }
    ~Color(){}; 
    
  private:
    void initColorComp();
    ColorStyle_t colorcomp;

    int indexRC,indexBC,indexGC,indexMC,indexBSC;

    std::map<int,int> RedComp;
    std::map<int,int> BlueComp;
    std::map<int,int> GreenComp;
    std::map<int,int> MultiComp;
    std::map<int,int> BlueShadeComp;
  };  
};
#endif

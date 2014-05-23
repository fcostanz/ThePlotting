/* template base class for the different plot types
If you would like to add a different type please create a different header file and use Pad as the base class  
Author: OS
Do not modify the code (it is tested and it works properly) unless you really know what you are doing and unless it is stated with capital letters (i.e 
YOU CAN ADD YOUR REVISION HISTORY HERE)
ozgur[no_spam].sahin[spam_not]@cern.ch 
*/

#ifndef Pad_h
#define Pad_h
#include <TPad.h>
#include <TH1D.h>
#include <THStack.h>
#include <TString.h>
namespace plotting{
  enum SizePad_t {kSmall, kMedium, kBig};
  enum PositionPad_t {kTop,kBottom,kMiddle};
  
  template<class dat_type, class bkg_type, class sig_type> class Pad{
  public:
    Pad(SizePad_t s, PositionPad_t p, TString t):size(s),pos(p),type(t){
    };
    Pad(){};
    ~Pad(){};
    
    virtual TPad* DrawPlot(dat_type*,bkg_type*,sig_type*)=0;//we do not aim for very high perf here so it is ok to use virtual funcs;
    int Print() const;

  protected:
    TPad* AllocPad(TString name1 = "custom", TString name2 = "pad");
    SizePad_t size;
    PositionPad_t pos;    
    TString type;
  };
  
  template<class dat_type, class bkg_type, class sig_type> TPad* plotting::Pad<dat_type,bkg_type,sig_type>::AllocPad(TString name1, TString name2)
  {
    TPad *pad =new TPad(name1+name2,name1+name2,0,0,1,1);
    //Probably there is a better way of doing this but for the moment I am happy with it
    
    if(kBottom == pos){
      if(kBig == size)
	{
	  pad->SetTopMargin(0.02);
	  pad->SetBottomMargin(0.1);
	  pad->SetPad(0,0,1,0.75);
	}
      else if( kMedium == size)
	{
	  pad->SetPad(0,0,1,0.50);
	  pad->SetTopMargin(0.06);
	  pad->SetBottomMargin(0.3);
	}
      else if(kSmall == size)
	{
	  pad->SetPad(0,0,1,0.25);
	  pad->SetTopMargin(0.06);
	  pad->SetBottomMargin(0.3);
	}
      
    }
    else if(kTop == pos){
      if(size == kBig)
	{
	  pad->SetPad(0,0.25,1,1);
	  pad->SetTopMargin(0.04);
	  pad->SetBottomMargin(0.015);
	}
      else if (kMedium == size)
	{
	  pad->SetPad(0,0.50,1,1);
	  pad->SetTopMargin(0.08);
	  pad->SetBottomMargin(0.030);
	}
      else if(kSmall == size)
	{
	  pad->SetPad(0,0.75,1,1);
	  pad->SetTopMargin(0.12);
	  pad->SetBottomMargin(0.045);
	}
      
  }
    else if(kMiddle == pos){
      if(size == kBig)
	pad->SetPad(0,0.125,1,0.875);
      else if (kMedium == size)
	pad->SetPad(0,0.25,1,0.75);
      else if(kSmall == size)
	pad->SetPad(0,0.375,1,0.625);
      pad->SetTopMargin(0.3);
    pad->SetBottomMargin(0.3);      
    }
    return pad;
  }
};
#endif 

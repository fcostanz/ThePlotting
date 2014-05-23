#include "Color.h"
#include <iostream>
#include <TString.h>
#include <TLegend.h>
#include <TH1D.h>
#include "THStack.h"
#include <TList.h>
#include "TObject.h"
#include "TCollection.h"
using namespace std;

int plotting::Color::GetColor()
{

  if(colorcomp==kRedComp)
    {
      indexRC++;
      return RedComp[indexRC];
    } 
 else if(colorcomp==kBlueComp)
    {
      indexBC++;
      return BlueComp[indexBC];
    }
 else if(colorcomp==kMultiComp)
    {
      indexMC++;
      return MultiComp[indexMC];
    }
  else if(colorcomp==kGreenComp)
    {
      indexGC++;
      return GreenComp[indexGC];
    }
  else if(colorcomp==kBlueShadeComp)
    {
      indexBSC++;
      return BlueShadeComp[indexBSC];
    }

}

void plotting::Color::initColorComp()
{

  RedComp[1]=632;
  RedComp[2]=807;
  RedComp[3]=628;
  RedComp[4]=634;
  RedComp[5]=801;
  RedComp[6]=800;

  BlueComp[1]=603;
  BlueComp[2]=600;
  BlueComp[3]=597;
  BlueComp[4]=887;
  BlueComp[5]=870;
  BlueComp[6]=432;

  BlueShadeComp[1]=604;
  BlueShadeComp[2]=596;
  BlueShadeComp[3]=593;
  BlueShadeComp[4]=592;
  BlueShadeComp[5]=851;
  BlueShadeComp[6]=428;

  MultiComp[1]=602;
  MultiComp[2]=874;
  MultiComp[3]=888;
  MultiComp[4]=419;
  MultiComp[5]=635;
  MultiComp[6]=kYellow+3;

}

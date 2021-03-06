/* simple class to read the config file which includes the sample path and type information
Author: OS
Do not modify the code (it is tested and it works properly) unless you really know what you are doing and unless it is stated with capital letters (i.e 
YOU CAN ADD YOUR REVISION HISTORY HERE)
ozgur[no_spam].sahin[spam_not]@cern.ch 
*/


#ifndef Properties_h
#define Properties_h
#include <TPad.h>
#include <TH1D.h>
#include <THStack.h>
#include <TString.h>
#include <cstdlib>
#include <map>
#include <vector>
#include "Histo.h"

namespace plotting{
  //make this class singleton later 
  class properties{
  public:
    std::map<TString, plotting::Histo_t> sample_prop;
    ~properties(){};
    properties(){};
    properties(TString config_path) {
         readConfig(config_path);};
    std::vector<TString*> paths;//sample paths
    typedef struct config 
    {
      TString colorComp;
      bool sort;
      bool add;
    } configProp;
  private:
    void readConfig(TString & config_path , int trial = 0);
  };  
};
#endif

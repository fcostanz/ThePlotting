/*please see the header file for class definition
Author: OS
Do not modify the code (it is tested and it works properly) unless you really know what you are doing and unless it is stated with capital letters (i.e 
YOU CAN ADD YOUR REVISION HISTORY HERE)
ozgur[no_spam].sahin[spam_not]@cern.ch 
*/

#include "Properties.h"
#include <TString.h>
#include <iostream>
#include <fstream>
#include <string>
#include <TObjString.h>
#include <TList.h>
#include <TObject.h>
#include <cstdlib>
using std::cout;
using std::cin;
using std::endl;

void plotting::properties::readConfig(TString & config_path, int trial) {
  std::ifstream config_file (config_path.Data());
  //I believe 4 times is enough for someone to write correct path of the config file
  if(!config_file.is_open() && trial < 4)
    {
      cout << "could not find the config file at \n" << config_path << "\n please enter the path of the config file (i.e. ./config.txt)" << endl; 
      cin >> config_path;
      trial++;
      plotting::properties::readConfig(config_path, trial);
    }
  else if(!config_file.is_open())
    {
      cout<< "you could not even manage to enter the correct path of the config file in four tries. I weep for the future of science... " << endl;
      exit(0);
    }
  std::string line;
  TObjArray* list;
  while(getline(config_file,line))
    {
      if('#' != line[0]) //lines starting with "#" reserved for the comments
	{
	  list = ((TString)line).Tokenize(" ");
	  if(list->GetEntriesFast()!= 2) {cout << "please check the config file structure: <sample path> <sample type>" << endl; exit(0);}
	  TIter next(list);//unfortunately TString can not be stored (or can not be converted to TObject) as TObject so TObjString it is...
	  paths.push_back(&((TObjString*)next())->String());//The first word is the path and the second one is type of the sample- these to words are seperated with empty space
	  cout << "path:"<<*paths.back() << " ";
	  TString type = ((TObjString*)next())->String();
	  cout << "type:"<<type << endl;
	  if(type == "bkg")
	    sample_prop[*paths.back()]=bkg;
	  else if(type == "sig"){
	    sample_prop[*paths.back()]=sig;}
	  else if(type == "dat")
	    sample_prop[*paths.back()]=dat;
	}
    }
  config_file.close();
}

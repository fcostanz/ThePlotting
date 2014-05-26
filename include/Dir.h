#ifndef Dir_h
#define Dir_h
#include <TString.h>
#include <vector>
#include "Histo.h"
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <TCanvas.h>
//this module can be improved by adding the time information to the first dir. 
namespace plotting{
  class Dir{
  public:
    Dir(){};
    Dir(const TString& path){
      mDir=getcwd(dir, sizeof(dir));
      if(chdir(path))
	{
	  mkdir(path,S_IRWXU|S_IRGRP|S_IXGRP);
	  if(chdir(path)) { std::cout << "can not enter to the plotting directory" << std::endl; exit(0);}
	  pDir = getcwd(dir, sizeof(dir));
	}
      else
 	pDir = getcwd(dir, sizeof(dir));
    };
    ~Dir(){chdir(mDir);};
    void print_mDir() {std::cout << "mother dir is " << mDir << std::endl;}
    void print_curDir() {curDir = getcwd(dir, sizeof(dir)); std::cout << "current dir is " << curDir << std::endl;}
    void SaveCanvas(const TString& option, const std::vector<TString>&dirName, TCanvas* c1);    
  private:
    char dir[100];
    TString mDir;//main dir
    TString pDir;//plotting dir
    TString curDir;

    std::vector<TString> prev_path;
  };  
};
#endif

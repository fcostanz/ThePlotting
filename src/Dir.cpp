/*please see the header file for class definition
Author: OS
Do not modify the code (it is tested and it works properly) unless you really know what you are doing and unless it is stated with capital letters (i.e 
YOU CAN ADD YOUR REVISION HISTORY HERE)
ozgur[no_spam].sahin[spam_not]@cern.ch 
*/

#include "Dir.h"
#include <TString.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <TCanvas.h>
using std::cout;
using std::cin;
using std::endl;
//Simple method to save canvases with the given option (*.pdf,*.jpeg,*.png etc) by conserving the initial directory structure
//YOU CAN OPTIMIZE THIS FUNCTION
void plotting::Dir::SaveCanvas(const TString &option, const std::vector<TString> & dirName, TCanvas* c1 )
{
  bool eq = false;
  //if the previous file is from the same directory no need to open a new one...  
  if (prev_path.size() > 0 )
    {
      eq = std::equal(dirName.begin(), dirName.end(), prev_path.begin());
    }
  if(eq)
    {
      c1->SaveAs((TString)c1->GetName()+"."+option);
    }
  else {
    if(chdir(pDir)) { cout << "can not go back to the plotting directory" << endl; exit(0);}
    std::vector<TString>::const_iterator dir_it;
    for(dir_it = dirName.begin(); dir_it != dirName.end(); dir_it++)
      {
	if(chdir(*dir_it))
	  {
	    mkdir(*dir_it,S_IRWXU|S_IRGRP|S_IXGRP);
	    if(chdir(*dir_it)) { cout << "can not enter to the plotting directory" << endl; exit(0);}
	  }
	
      }
    c1->SaveAs((TString)c1->GetName()+option);
  }
  prev_path = dirName;
}


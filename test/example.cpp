#include <iostream>
#include "Properties.h"
#include "Histo.h"
#include "Pad.h"
#include "Draw.h"
#include "TString.h"
#include <ctime>
using std::cout;
using std::endl;
using namespace plotting;

int main(int argc, const char* argv[]){

  time_t start = time(0);


  Draw draw("./config.txt");
  draw.ControlRatioPlot(true);

  time_t end = time(0);
  double time = difftime(end, start);
  cout << time << endl;
  return 0;
}

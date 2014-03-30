#include <iostream>

#include "Pad.h"

using std::cout;
using std::endl;
using namespace plotting;

int main(int argc, const char* argv[]){

  Pad* myPad = new Pad();
  
  myPad->Print();

  return 0;
}

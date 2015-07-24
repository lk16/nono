#pragma once

#include <vector>
#include <cstdlib>

using namespace std;

struct nonogram{
  int width,height;
  int* fields;
  // indexes:
  // 0 1 2
  // 3 4 5
  // 6 7 8 ..
  
  nonogram(int h,int w);
  ~nonogram();
  
  void randomise();
  
};



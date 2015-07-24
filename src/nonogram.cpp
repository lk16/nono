#include "nonogram.hpp"

nonogram::nonogram(int h,int w){
  fields = new int[w*h];
  width = w;
  height = h;
}

nonogram::~nonogram(){
  delete fields;
}

void nonogram::randomise(){
  for(int i=0;i<width*height;++i){
    fields[i] = rand() % 2;
  }
}
  

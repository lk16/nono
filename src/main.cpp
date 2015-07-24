#include <iostream>
#include <algorithm>

#include "nonogram.hpp"

using namespace std;


int main(){
  
  srand(time(NULL));

  nonogram nono(10,10);
  nono.randomise();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);
  
  return 0;
}
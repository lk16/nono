#include "includes.hpp"
#include "nonogram.hpp"

using namespace std;


int main(){
  
  timeval t;
  gettimeofday(&t,NULL);
  srand(t.tv_sec ^ t.tv_usec);

  set<colour> colours;
  colours.insert(BLACK);
  colours.insert(WHITE);
  
  
  
  nonogram nono(20,20,colours);
  nono.init_randomised(0.3);
  nono.make_solvable();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);

  return 0;
}
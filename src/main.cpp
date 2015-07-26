#include "includes.hpp"
#include "nonogram.hpp"
#include "combinations.hpp"

using namespace std;


int main(){
  
  srand(time(NULL));

  nonogram nono(20,20);
  nono.init_randomised(0.3);
  nono.make_solvable();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);

  return 0;
}
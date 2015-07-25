#include "includes.hpp"
#include "nonogram.hpp"
#include "combinations.hpp"

using namespace std;


int main(){
  
  srand(time(NULL));

  nonogram nono(8,4);
  nono.randomise();
  nono.make_solvable();
  nono.print();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);

  return 0;
}
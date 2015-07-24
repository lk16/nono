#include "includes.hpp"
#include "nonogram.hpp"
#include "combinations.hpp"

using namespace std;


int main(){
  
  srand(time(NULL));

  nonogram nono(10,10);
  nono.randomise();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);
  
  
  
  vector<int> seq = {3};
  combinations combi(seq,5);
  
  vector<int> given = {-1,1,-1,-1,-1};
  
  
  
  vector<int> out = combi.try_solving(given,1000);
  for(auto x: out){
    if(x==BLACK){
      cout << "@";
    }
    else{
      cout << "-";
    }
  }
  cout << '\n';
  
  return 0;
}
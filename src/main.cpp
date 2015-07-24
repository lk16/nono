#include <iostream>
#include <algorithm>
#include <vector>

#include "nonogram.hpp"
#include "combinations.hpp"

using namespace std;


int main(){
  
  srand(time(NULL));

  nonogram nono(10,10);
  nono.randomise();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);
  
  
  
  vector<int> seq = {2,3,5};
  combinations combi(seq,16);
  vector<int> out;
  while(combi.next(&out)){
    for(auto x: out){
      if(x==nonogram::BLACK){
        cout << "@";
      }
      else{
        cout << " ";
      }
    }
    cout << '\n';
  }
  
  
  return 0;
}
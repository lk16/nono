#include "includes.hpp"
#include "nonogram.hpp"

using namespace std;

void seed_well(){
  timeval t;
  gettimeofday(&t,NULL);
  srand(t.tv_sec ^ t.tv_usec);
}


int main(){
  seed_well();
  
  
  set<colour> colours;
  colours.insert(BLACK);
  colours.insert(WHITE);
  colours.insert(RED);
  //colours.insert(BLUE);
  
  
  
  
  nonogram nono(15,15,colours);
  nono.init_randomised(0.5);
  nono.make_solvable();
  nono.save_as_svg("puzzle.svg",false);
  nono.save_as_svg("solution.svg",true);
  
  
  /*
  vector<pair<colour,int>> seq_info;
  seq_info.push_back(make_pair(BLACK,2));
  seq_info.push_back(make_pair(RED,3));
  seq_info.push_back(make_pair(GREEN,2));
  seq_info.push_back(make_pair(GREEN,1));
  
  nonogram::sequence_t seq(seq_info,20);
  seq.solve(vector<colour>(20,UNKNOWN));
  */
  return 0;
}
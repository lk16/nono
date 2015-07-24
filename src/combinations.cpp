#include "combinations.hpp"

combinations::combinations(const vector<int>& sequence, int _max_id)
{
  max_id = _max_id;
  seq = sequence;
  offset.assign(seq.size(),0);
  for(unsigned i=1;i<offset.size();++i){
    offset[i] = offset[i-1] + seq[i-1] + 1;
  }
  first_result = true;
}

bool combinations::next(vector<int>* out)
{
  if(!first_result){
    // move will be index of the lowest offset that we move
    int move = offset.size()-1;
    int sum = 0;
    while(true){
      sum += seq[move] + 1;
      if(offset[move] + sum + 1 < (max_id+1)){
        break;
      }
      --move; 
      if(move<0){
        return false;
      }
    };
    
    ++offset[move];
    for(unsigned i=move+1;i<offset.size();++i){
      offset[i] = offset[i-1] + seq[i-1] + 1;
    }
  }
  else{
    first_result = false;
  }
  
  out->assign(max_id,0);
  for(unsigned i=0;i<offset.size();++i){
    for(int j=0;j<seq[i];++j){
      (*out)[offset[i]+j] = nonogram::BLACK;
    }
  }
  
  return true;
}

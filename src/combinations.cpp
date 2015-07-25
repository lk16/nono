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
  
  out->assign(max_id,WHITE);
  for(unsigned i=0;i<offset.size();++i){
    for(int j=0;j<seq[i];++j){
      (*out)[offset[i]+j] = BLACK;
    }
  }
  
  return true;
}

vector<int> combinations::try_solving(const vector<int>& given,unsigned max_tries)
{
  {
    bool found_all = true;
    for(const auto& x:given){
      if(x==UNKNOWN){
        found_all = false;
        break;
      }
    }
    if(found_all){
      return given;
    }
  }
  
  
  unsigned tries = 0;
  
  assert(given.size() == (unsigned)max_id);
  
  vector<int> combi;
  
  vector<int> intersection; 
  bool first = true;
  
  
  while(next(&combi)){
    if(combi_match(combi,given)){
      if(first){
        intersection = combi;
        first = false;
      }
      else{
        assign_intersection_lhs(intersection,combi);
      }
    }
    ++tries;
    if(tries >= max_tries){
      return given;
    }
  }
  
  return intersection;
}

bool combi_match(const vector<int>& lhs, const vector<int>& rhs)
{
  vector<int>::const_iterator lit,rit;
  lit = lhs.begin();
  rit = rhs.begin();
  while(lit != lhs.end()){
    if(*lit != *rit && *lit!=UNKNOWN && *rit!=UNKNOWN){
      return false;
    }
    ++lit;
    ++rit;
  }
  return true;
}

void assign_intersection_lhs(vector<int>& lhs, const vector<int>& rhs)
{
  vector<int>::const_iterator rit;
  vector<int>::iterator lit;
  lit = lhs.begin();
  rit = rhs.begin();
  while(lit != lhs.end()){
    if(*lit != *rit){
      *lit = UNKNOWN;
    }
    ++lit;
    ++rit;
  }
}




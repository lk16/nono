#pragma once

#include <vector>

#include "nonogram.hpp"

using namespace std;



class combinations{

  
  vector<int> seq,offset;
  int max_id;
  bool first_result;
public:
  combinations(const vector<int>& sequence,int _max_id);
  
  bool next(vector<int>* out);
};
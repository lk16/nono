#pragma once

#include "includes.hpp"
#include "nonogram.hpp"

class combinations{

  
  vector<int> seq,offset;
  int max_id;
  bool first_result;

  bool next(vector<int>* out);

  static bool combi_match(const vector<int>& lhs,const vector<int>& rhs);

  static void assign_intersection_lhs(vector<int>& lhs,const vector<int>& rhs);


public:
  combinations(const vector<int>& sequence,int _max_id);

  vector<int> try_solving(const vector<int>& given,unsigned max_tries);
  
};
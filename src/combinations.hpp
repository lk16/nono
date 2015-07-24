#pragma once

#include "includes.hpp"
#include "nonogram.hpp"

using namespace std;



class combinations{

  
  vector<int> seq,offset;
  int max_id;
  bool first_result;
public:
  combinations(const vector<int>& sequence,int _max_id);
  
  bool next(vector<int>* out);
  
  vector<int> try_solving(const vector<int>& given,unsigned max_tries);
};


bool combi_match(const vector<int>& lhs,const vector<int>& rhs);

void assign_intersection_lhs(vector<int>& lhs,const vector<int>& rhs);
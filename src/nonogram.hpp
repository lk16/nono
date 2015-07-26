#pragma once


#include "includes.hpp"
#include "svg.hpp"

class nonogram{
  
  
  class combi_t{

    vector<int> seq,offset;
    int max_id;
    bool first_result;

    bool next(vector<int>* out);

    static bool combi_match(const vector<int>& lhs,const vector<int>& rhs);

    static void assign_intersection_lhs(vector<int>& lhs,const vector<int>& rhs);


  public:
    combi_t(const vector<int>& sequence,int _max_id);

    vector<int> try_solving(const vector<int>& given,unsigned max_tries);
    
  };

  int width,height;
  vector<int> fields;
  // indexes:
  // 0 1 2
  // 3 4 5
  // 6 7 8 ..
  
  void try_solving(vector<int>& sol) const;

  
  
public:
  
  nonogram(int h,int w);
  ~nonogram() = default;
  
  void init_randomised(double chance);
  void init_clustered();
  
  
  
  vector<int> get_col_seq(int x) const;
  vector<int> get_row_seq(int y) const;
  
  void save_as_svg(const string& filename,bool solved) const;
  

  
  void make_solvable();
  
  void print() const;
  
  
};


void print_table(const vector<int>& tab,int height,int width);
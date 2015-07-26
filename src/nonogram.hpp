#pragma once


#include "includes.hpp"
#include "svg.hpp"
#include "colour.hpp"

class nonogram{
  
  class combi_t{

    vector<pair<colour,int>> seq;
    vector<int> offset;
    int max_id;
    bool first_result;

    bool next(vector<colour>* out);

    static bool combi_match(const vector<colour>& lhs,const vector<colour>& rhs);

    static void assign_intersection_lhs(vector<colour>& lhs,const vector<colour>& rhs);


  public:
    combi_t(const vector<pair<colour,int>>& sequence,int _max_id);

    vector<colour> try_solving(const vector<colour>& given,unsigned max_tries);
    
  };
  

  int width,height;
  vector<colour> fields;
  set<colour> colours;
  // indexes:
  // 0 1 2
  // 3 4 5
  // 6 7 8 ..
  
  void try_solving(vector<colour>& sol) const;

  colour random_colour() const;
  
public:
  
  nonogram(int h,int w,const set<colour>& _colours);
  ~nonogram() = default;
  
  void init_randomised(double chance);
  void init_clustered();
  
  
  
  vector<pair<colour,int>> get_col_seq(int x) const;
  vector<pair<colour,int>> get_row_seq(int y) const;
  
  void save_as_svg(const string& filename,bool solved) const;
  

  
  void make_solvable();
  
  void print() const;
  
  
};


void print_table(const vector<int>& tab,int height,int width);
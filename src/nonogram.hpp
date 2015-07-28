#pragma once


#include "includes.hpp"
#include "svg.hpp"
#include "colour.hpp"

struct nonogram{
  
  struct sequence_t{

    vector<pair<colour,int>> seq;
    int max_id;
    

    static bool combi_match(const vector<colour>& lhs,const vector<colour>& rhs);

    static void assign_intersection_lhs(vector<colour>& lhs,const vector<colour>& rhs);
    
    // idea: put down sequence item `move' for all its possibilities
    // and call recursively with move+1
    // restore state 
    void generate_possibilities(vector<int>* offset,int move,vector<vector<colour>>* out);

  public:
    sequence_t(const vector<pair<colour,int>>& sequence,int _max_id);

    vector<colour> solve(const vector<colour>& given);
    
  };
  

  int width,height;
  vector<colour> fields;
  set<int> given_fields;
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


void print_table(const vector<colour>& tab,int height,int width);
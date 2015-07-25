#pragma once


#include "includes.hpp"
#include "svg.hpp"
#include "combinations.hpp"

using namespace std;

struct nonogram{
  
  int width,height;
  vector<int> fields;
  // indexes:
  // 0 1 2
  // 3 4 5
  // 6 7 8 ..
  
  nonogram(int h,int w);
  ~nonogram() = default;
  
  void randomise();
  
  
  
  vector<int> get_col_seq(int x) const;
  vector<int> get_row_seq(int y) const;
  
  void save_as_svg(const string& filename,bool solved) const;
  
  void try_solving(vector<int>& sol) const;
  
  void make_solvable();
  
  void print() const;
  
  
};


void print_table(const vector<int>& tab,int height,int width);
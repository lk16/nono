#pragma once

#include <string>
#include <iostream>

#include "string.hpp"

using namespace std;

struct colour{
  int r,g,b;
  colour(int _r,int _g,int _b);
  string str() const;
  bool operator<(const colour& rhs) const;
  bool operator==(const colour& rhs) const;
  bool operator!=(const colour& rhs) const;
  int rgb_total() const;
};

ostream& operator<<(ostream& lhs,const colour& rhs);

extern const colour WHITE,BLACK,UNKNOWN,RED,BLUE,GREEN;
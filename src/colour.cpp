#include "colour.hpp"

const colour WHITE(255,255,255);
const colour BLACK(0,0,0);
const colour UNKNOWN(-1,-1,-1);
const colour RED(255,0,0);
const colour GREEN(0,255,0);
const colour BLUE(0,0,255);

string colour::str() const
{
  string res = "rgb:(" + to_str<int>(r);
  res += "," + to_str<int>(g);
  res += "," + to_str<int>(b) + ")";
  return res;
}

int colour::rgb_total() const
{
  return r+g+b;
}


bool colour::operator<(const colour& rhs) const
{
  if(r!=rhs.r){
    return r<rhs.r;
  }
  if(g!=rhs.g){
    return g<rhs.g;
  }
  return b<rhs.b;
}

bool colour::operator==(const colour& rhs) const
{
  return r==rhs.r && b==rhs.b && g==rhs.g;
}

colour::colour(int _r, int _g, int _b)
{
  r = _r;
  g = _g;
  b = _b;
}

bool colour::operator!=(const colour& rhs) const
{
  return !(*this == rhs);
}

ostream& operator<<(ostream& lhs, const colour& rhs)
{
  return lhs << rhs.str();
}

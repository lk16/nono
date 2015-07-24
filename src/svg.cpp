#include "svg.hpp"

string svg_line(int x1,int y1,int x2,int y2,const string& tags){
  string res = "<line x1=\"" + to_str<int>(x1) + "\" y1=\"" + to_str<int>(y1);
  res += "\" x2=\"" + to_str<int>(x2) + "\" y2=\"" + to_str<int>(y2) + "\" ";
  res += tags + " />\n";
  return res;
}

string svg_rectangle(int x,int y,int width,int height, const string& tags){
  string res = "<rect x=\"" + to_str<int>(x) + "\" y=\"" + to_str<int>(y);
  res += "\" width=\"" + to_str<int>(width) + "\" height=\"" + to_str<int>(height);
  res += "\" " + tags + " />\n";
  return res;
}

string svg_header(int width, int height)
{
  string res = "<svg width=\"" + to_str<int>(width) + "\" height=\"" + to_str<int>(height) + "\">\n";
  res += svg_rectangle(0,0,width,height,"style=\"fill:white\"");
  return res;
}

string svg_footer()
{
  return "</svg>\n";
}

string svg_text_centered(int x,int y,const string& text){
  string res = "<text x=\"" + to_str<int>(x) + "\" y=\"";
  res += to_str<int>(y) + "\" style=\"text-anchor:middle;alignment-baseline=central\">";
  res += text + "</text>\n";
  return res;
}





#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>

#include "string.hpp"
#include "nonogram.hpp"


using namespace std;

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






int main(){
  
  srand(time(NULL));
  
  std::string style = "style=\"stroke:rgb(0,0,0);stroke-width:1\"";
  
  nonogram nono(10,10);
  nono.randomise();
  
  
  ofstream file("bla.svg");
  file << "<svg height=\"400\" width=\"400\">\n";
  
  
  for(int i=0;i<=10;++i){
    int x = 100 + 20*i;
    file << svg_line(x,50,x,300,style);
  }
    
  for(int i=0;i<=10;++i){
    int y = 100 + 20*i;
    file << svg_line(50,y,300,y,style);
  }
  
  for(int i=0;i<100;++i){
    int x = 100 + 20*(i%10);
    int y = 100 + 20*(i/10);
    if(nono.fields[i] == 1){
      file << svg_rectangle(x,y,20,20,"style=\"fill:black\"");
    }
  }
  
  
  file << "</svg>\n";
  return 0;
}
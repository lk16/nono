#pragma once

#include "includes.hpp"
#include "string.hpp"

using namespace std;



string svg_header(int width,int height);

string svg_footer();


string svg_line(int x1,int y1,int x2,int y2,const string& tags);

string svg_rectangle(int x,int y,int width,int height, const string& tags);

string svg_text_centered(int x,int y,const string& text);

#include "nonogram.hpp"

nonogram::nonogram(int h,int w){
  fields = new int[w*h];
  width = w;
  height = h;
}

nonogram::~nonogram(){
  delete fields;
}

void nonogram::randomise(){
  for(int i=0;i<width*height;++i){
    fields[i] = rand() % 2;
  }
}
  
vector<int> nonogram::get_col_seq(int x) const
{
  vector<int> res;
  int seq = 0;
  for(int y=0;y<height;++y){
    int cur = y*height+x;
    if(fields[cur]!=WHITE){
      ++seq;
    }
    else if(seq > 0){
      res.push_back(seq);
      seq = 0;
    }
  }
  if(seq > 0){
    res.push_back(seq);
  }
  return res;
}

vector<int> nonogram::get_row_seq(int y) const
{
  vector<int> res;
  int seq = 0;
  for(int x=0;x<width;++x){
    int cur = y*height+x;
    if(fields[cur]!=WHITE){
      ++seq;
    }
    else if(seq > 0){
      res.push_back(seq);
      seq = 0;
    }
  }
  if(seq > 0){
    res.push_back(seq);
  }
  return res;
}

void nonogram::save_as_svg(const string& filename) const
{
  const std::string style = "style=\"stroke:rgb(0,0,0);stroke-width:1\"";
  
  
  
  
  const int SQUARE_SIZE = 20;
  
  int SEQ_WIDTH = 0;
  for(int i=0;i<height;++i){
    SEQ_WIDTH = max((size_t)SEQ_WIDTH,get_row_seq(i).size());
  }
  SEQ_WIDTH *= SQUARE_SIZE;
  
  int SEQ_HEIGHT = 0;
  for(int i=0;i<width;++i){
    SEQ_HEIGHT = max((size_t)SEQ_HEIGHT,get_col_seq(i).size());
  }
  SEQ_HEIGHT *= SQUARE_SIZE;
    
  const int FIELD_X_START = SEQ_WIDTH;
  const int FIELD_Y_START = SEQ_HEIGHT;
  const int FIELD_WIDTH = width*SQUARE_SIZE;
  const int FIELD_HEIGHT = height*SQUARE_SIZE;
  
  
  
  const int TOTAL_WIDTH = SEQ_WIDTH + FIELD_WIDTH + 10;
  const int TOTAL_HEIGHT = SEQ_HEIGHT + FIELD_HEIGHT + 10;
  
  
  ofstream file(filename);
  file << svg_header(TOTAL_WIDTH,TOTAL_HEIGHT);
  
  
  for(int i=0;i<=10;++i){
    int x = FIELD_X_START + SQUARE_SIZE*i;
    file << svg_line(x,0,x,SEQ_HEIGHT+FIELD_HEIGHT,style);
  }
    
  for(int i=0;i<=10;++i){
    int y = FIELD_Y_START + SQUARE_SIZE*i;
    file << svg_line(0,y,SEQ_WIDTH+FIELD_WIDTH,y,style);
  }
  
  for(int i=0;i<100;++i){
    int x = FIELD_X_START + SQUARE_SIZE*(i%width);
    int y = FIELD_Y_START + SQUARE_SIZE*(i/width);
    if(fields[i] == 1){
      file << svg_rectangle(x,y,SQUARE_SIZE,SQUARE_SIZE,"style=\"fill:black\"");
    }
  }

  for(int r=0;r<height;++r){
    vector<int> seq = get_row_seq(r);
    for(unsigned i=0;i<seq.size();++i){
      int x = SEQ_WIDTH - (SQUARE_SIZE/2) - (SQUARE_SIZE*i);
      int y = SEQ_HEIGHT + (SQUARE_SIZE/2) + (SQUARE_SIZE*r);
      file << svg_text_centered(x,y,to_str<int>(seq[seq.size()-i-1]));
    }
  }
  
  for(int c=0;c<height;++c){
    vector<int> seq = get_col_seq(c);
    for(unsigned i=0;i<seq.size();++i){
      int x = SEQ_WIDTH + (SQUARE_SIZE/2) + (SQUARE_SIZE*c);
      int y = SEQ_HEIGHT - (SQUARE_SIZE/2) - (SQUARE_SIZE*i);
      file << svg_text_centered(x,y,to_str<int>(seq[seq.size()-i-1]));
    }
  }
    
  file << svg_footer();
  
}

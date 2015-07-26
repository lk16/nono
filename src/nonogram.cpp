#include "nonogram.hpp"

nonogram::nonogram(int h,int w){
  fields.assign(w*h,WHITE);
  width = w;
  height = h;
}


void nonogram::init_randomised(double chance){
  for(int i=0;i<width*height;++i){
    fields[i] = (rand() < chance*RAND_MAX) ? BLACK : WHITE;
  }
}
  
vector<int> nonogram::get_col_seq(int x) const
{
  vector<int> res;
  int seq = 0;
  for(int y=0;y<height;++y){
    int cur = y*width+x;
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
    int cur = y*width+x;
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

void nonogram::save_as_svg(const string& filename,bool solved) const
{
  const std::string thinline = "style=\"stroke:black;stroke-width:1\"";
  const std::string fatline = "style=\"stroke:black;stroke-width:3\"";
  
  
  
  
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

  if(solved){
    for(int i=0;i<width*height;++i){
      if(fields[i] == BLACK){
        int x = FIELD_X_START + SQUARE_SIZE*(i%width);
        int y = FIELD_Y_START + SQUARE_SIZE*(i/width);
        file << svg_rectangle(x,y,SQUARE_SIZE,SQUARE_SIZE,"style=\"fill:black\"");
      }
    }
  }
  else{
    file << svg_rectangle(SEQ_WIDTH,SEQ_HEIGHT,FIELD_WIDTH,FIELD_HEIGHT,"style=\"fill:rgb(200,200,200)\"");
  }
  
    
  for(int i=0;i<=width;++i){
    int x = FIELD_X_START + SQUARE_SIZE*i;
    file << svg_line(x,0,x,SEQ_HEIGHT+FIELD_HEIGHT,(i%5==0) ? fatline : thinline);
  }
    
  for(int i=0;i<=height;++i){
    int y = FIELD_Y_START + SQUARE_SIZE*i;
    file << svg_line(0,y,SEQ_WIDTH+FIELD_WIDTH,y,(i%5==0) ? fatline : thinline);
  }

  
  
  for(int r=0;r<height;++r){
    vector<int> seq = get_row_seq(r);
    for(unsigned i=0;i<seq.size();++i){
      int x = SEQ_WIDTH - (SQUARE_SIZE/2) - (SQUARE_SIZE*i);
      int y = SEQ_HEIGHT  + (SQUARE_SIZE*r) + (SQUARE_SIZE*3/4);
      file << svg_text_centered(x,y,to_str<int>(seq[seq.size()-i-1]));
    }
  }
  
  for(int c=0;c<width;++c){
    vector<int> seq = get_col_seq(c);
    for(unsigned i=0;i<seq.size();++i){
      int x = SEQ_WIDTH + (SQUARE_SIZE/2) + (SQUARE_SIZE*c);
      int y = SEQ_HEIGHT - (SQUARE_SIZE/4) - (SQUARE_SIZE*i);
      file << svg_text_centered(x,y,to_str<int>(seq[seq.size()-i-1]));
    }
  }
    
  file << svg_footer();
  file.close();
}

void nonogram::print() const
{
  print_table(fields,height,width);
}


void print_table(const vector<int>& tab,int height,int width){
    
  map<int,string> printed;
  printed[UNKNOWN] = " ";
  printed[BLACK] = "@";
  printed[WHITE] = ".";

  
  cout << "+-";
  for(int x=0;x<width;++x){
    cout << "--";
  }
  cout << "+\n";
  
  for(int y=0;y<height;++y){
    cout << "| ";
    for(int x=0;x<width;++x){
      cout << printed[tab[y*width+x]] << ' ';
    }
    cout << "|\n";
  }
  
  cout << "+-";
  for(int x=0;x<width;++x){
    cout << "--";
  }
  cout << "+\n";
}



void nonogram::try_solving(vector<int>& sol) const
{
  sol.assign(width*height,UNKNOWN);
  
  struct line_t{
    vector<int> indexes;
    vector<int> seq;
  };
  
  
  
  vector<line_t> lines;
  
  for(int y=0;y<height;++y){
    line_t line;
    for(int x=0;x<width;++x){
      line.indexes.push_back(y*width+x);
    }
    line.seq = get_row_seq(y);
    lines.push_back(line);
  }
  for(int x=0;x<width;++x){
    line_t line;
    for(int y=0;y<height;++y){
      line.indexes.push_back(y*width+x);
    }
    line.seq = get_col_seq(x);
    lines.push_back(line);
  }
  
  bool change;
  do{
    change = false;
    for(const auto& l: lines){
      combinations c(l.seq,l.indexes.size());
      vector<int> given;
      for(const auto& i: l.indexes){
        given.push_back(sol[i]);
      }
      vector<int> solved_line = c.try_solving(given,1000);
      int s = 0;
      for(const auto& i: l.indexes){
        if(sol[i] != solved_line[s]){
           sol[i] = solved_line[s];
          change = true;
        }
        ++s;
      }
    }
  }while(change);
  
  for(int i=0;i<width*height;++i){
    if(sol[i] != fields[i] && sol[i]!=UNKNOWN){
      cout << "found inequality at (" << i%width << "," << i/width << ")\n";
      cout << sol[i] << " != " << fields[i] << '\n';
    }
  }
  
}

void nonogram::make_solvable()
{
  vector<int> solution;
  bool solved;
  const int max_tries = 30;
  
  while(true){
    int tries_left = max_tries;
    while(tries_left>0){
      --tries_left;
      solved = true;
      try_solving(solution);
      for(int i=0;i<width*height;++i){
        if(solution[i]==UNKNOWN){
          solved = false;
          break;
        }
      }
      if(solved){
        return;
      }
      for(int i=0;i<width*height;++i){
        if(solution[i]==UNKNOWN){
          solution[i] = rand() % 2;
        }
      }
      fields = solution;
    }
    for(int i=0;i<10;++i){
      fields[rand() % width*height] = rand() % 2;
    }
  }
}

void nonogram::init_clustered()
{
  // this code was copied from my own fire spreading simulation project
  // http://github.com/lk16/fire
  
  init_randomised(0.1);
  
  const int cluster_steps = 0;
  const int k = 4;
  
  int non_white = 0;
  int neighbours = 0;
  double chance;
  for(int c=0;c<cluster_steps;c++){
    for(int i=0;i<width*height;++i){
      int x = i%width;
      int y = i/width;
      non_white = neighbours = 0;
      if(y>0){
        neighbours++;
        if(fields[i-width] != WHITE){
          non_white++; 
        }
      }
      if(y<height){
        neighbours++;
        if(fields[i+width] != WHITE){
          non_white++; 
        }
      }
      if(x>0){
        neighbours++;
        if(fields[i-1] != WHITE){
          non_white++; 
        }
      }
      if(x<width){
        neighbours++;
        if(fields[i+1] != WHITE){
          non_white++;
        }
      }
      if(fields[i] != WHITE){
        non_white += k;
      }
      chance = (double)non_white / (k+neighbours);
      if(chance >= 1.0){
        fields[i] = BLACK;
      }
      else if(rand() < RAND_MAX*chance){
        fields[i] = BLACK;
      }
      else{
        fields[i] = WHITE;
      }
    }
  }
}

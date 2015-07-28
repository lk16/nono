#include "nonogram.hpp"

nonogram::nonogram(int h,int w,const set<colour>& _colours){
  fields.assign(w*h,WHITE);
  width = w;
  height = h;
  colours = _colours;
}


void nonogram::init_randomised(double chance){
  for(int i=0;i<width*height;++i){
    fields[i] = (rand() < chance*RAND_MAX) ? BLACK : WHITE;
  }
}
  
vector<pair<colour,int>> nonogram::get_col_seq(int x) const
{
  vector<pair<colour,int>> res;
  pair<colour,int> p(WHITE,0);
  for(int y=0;y<height;++y){
    colour cur = fields[y*width+x];
    if(cur == p.first){
      ++p.second;
    } 
    else{
      if(p.first != WHITE){
        res.push_back(p);
      }
      p.first = cur;
      p.second = 1;
    }
  }
  if(p.first != WHITE){
    res.push_back(p);
  }
  return res;
}

vector<pair<colour,int>> nonogram::get_row_seq(int y) const
{
  vector<pair<colour,int>> res;
  pair<colour,int> p(WHITE,0);
  for(int x=0;x<width;++x){
    colour cur = fields[y*width+x];
    if(cur != p.first){
      if(p.first != WHITE){
        res.push_back(p);
      }
      p.first = cur;
      p.second = 1;
    }
    else{
      ++p.second;
    }
  }
  if(p.first != WHITE){
    res.push_back(p);
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
        string style = "style=\"fill:" + fields[i].str() + "\"";
        
        
        file << svg_rectangle(x,y,SQUARE_SIZE,SQUARE_SIZE,style);
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
    vector<pair<colour,int>> seq = get_row_seq(r);
    for(unsigned i=0;i<seq.size();++i){
      int x = SEQ_WIDTH - (SQUARE_SIZE/2) - (SQUARE_SIZE*i);
      int y = SEQ_HEIGHT  + (SQUARE_SIZE*r) + (SQUARE_SIZE*3/4);
      file << svg_text_centered(x,y,to_str<int>(seq[seq.size()-i-1].second));
    }
  }
  
  for(int c=0;c<width;++c){
    vector<pair<colour,int>> seq = get_col_seq(c);
    for(unsigned i=0;i<seq.size();++i){
      int x = SEQ_WIDTH + (SQUARE_SIZE/2) + (SQUARE_SIZE*c);
      int y = SEQ_HEIGHT - (SQUARE_SIZE/4) - (SQUARE_SIZE*i);
      file << svg_text_centered(x,y,to_str<int>(seq[seq.size()-i-1].second));
    }
  }
    
  file << svg_footer();
  file.close();
}

void nonogram::try_solving(vector<colour>& sol) const
{
  sol.assign(width*height,UNKNOWN);
  
 
  
  vector<vector<int>> indexes(width+height);
  vector<sequence_t> sequences;
  
  
  for(int y=0;y<height;++y){
    for(int x=0;x<width;++x){
      indexes[y].push_back(y*width+x);
    }
    sequences.push_back(sequence_t(get_row_seq(y),width));
  }
  for(int x=0;x<width;++x){
    for(int y=0;y<height;++y){
      indexes[height+x].push_back(y*width+x);
    }
    sequences.push_back(sequence_t(get_col_seq(x),height));
  }
  
  
  
  
  
  bool change;
  do{
    change = false;
    for(unsigned i=0;i<sequences.size();++i){
      vector<colour> given;
      for(const auto& j: indexes[i]){
        given.push_back(sol[j]);
      }
      vector<colour> solved_seq = sequences[i].solve(given);
      for(unsigned s=0; s<solved_seq.size();++s){
        if(sol[indexes[i][s]] != solved_seq[s]){
          assert(sol[indexes[i][s]] == UNKNOWN);
          sol[indexes[i][s]] = solved_seq[s];
          change = true;
        }
      }
    }
  }while(change);
  
  for(int i=0;i<width*height;++i){
    if(sol[i] != fields[i] && sol[i]!=UNKNOWN){
      cout << "found inequality at (" << i%width << "," << i/width << ")\n";
      cout << sol[i].str() << " != " << fields[i].str() << '\n';
    }
  }
  
}

void nonogram::make_solvable()
{
  vector<colour> solution;
  bool solved;
  const int max_tries = 30;
  
  while(true){
    cout << '\n';
    print();
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
      int count = 0;
      for(int i=0;i<width*height;++i){
        if(solution[i]==UNKNOWN){
          ++count;
          solution[i] = random_colour();
        }
      }
      cout << count << " unsolved fields\n";
      fields = solution;
    }
    for(int i=0;i<10;++i){
      fields[rand() % width*height] = random_colour();
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


nonogram::sequence_t::sequence_t(const vector<pair<colour,int>>& sequence, int _max_id)
{
  max_id = _max_id;
  seq = sequence;
}



vector<colour> nonogram::sequence_t::solve(const vector<colour>& given)
{
  {
    bool found_all = true;
    for(const auto& x:given){
      if(x==UNKNOWN){
        found_all = false;
        break;
      }
    }
    if(found_all){
      return given;
    }
  }
  if(seq.empty()){
    return vector<colour>(max_id,WHITE);
  }
  
  assert(given.size() == (unsigned)max_id);
  
  map<colour,string> print_val;
  print_val[RED] = "2";
  print_val[BLACK] = "1";
  print_val[WHITE] = "-";
  print_val[UNKNOWN] = " ";
  print_val[GREEN] = "3";
  print_val[BLUE] = "4";
  
  
  vector<vector<colour>> possibilities;
  vector<int> offset;
  generate_possibilities(&offset,0,&possibilities);
  
  /*
  if(possibilities.empty()){
    cout << "impossible to solve sequence:\nseq: ";
    for(auto s:seq){
      cout << s.second << " ";
    }
    cout << "\ngiven:";
    for(auto g:given){
      cout << print_val[g] << " "; 
    }
    cout << "\n";
  }
  */
  
  vector<colour> intersection(possibilities.front()); 
  


  
  //cout << "========================================================\n";
  for(auto& p: possibilities){
    /*for(auto x: p){
      cout << print_val[x] << " ";
    }
    cout << "\n";*/
    assign_intersection_lhs(intersection,p);
  }
  //cout << "\n";
  /*cout << "intersection: ";
  for(auto x: intersection){
    cout << print_val[x] << " ";
  }
  cout << "\n";*/
  
  return intersection;
}

void nonogram::sequence_t::generate_possibilities(vector<int>* offset, int move, vector<vector<colour>>* out)
{
  if((unsigned)move==seq.size()){
    if(offset->back() + seq.back().second <= max_id){
      vector<colour> res(max_id,WHITE);
      for(unsigned i=0;i<offset->size();++i){
        for(int j=0;j<seq[i].second;++j){
          res[(*offset)[i]+j] = seq[i].first;
        }
      }
      out->push_back(res);
    }
    return;
  }
  
  int start;
  if(move==0){
    start = 0;
  }
  else{
    assert(!offset->empty());
    start = offset->back() + seq[move-1].second + (seq[move-1].first==seq[move].first ? 1 : 0);
  }
  int end = max_id + 1;
  for(unsigned i=move;i<seq.size();++i){
    end -= seq[i].second;
  }
  
  for(int i=start;i<end;++i){
    offset->push_back(i);
    generate_possibilities(offset,move+1,out);
    offset->pop_back();
  }

  
}




bool nonogram::sequence_t::combi_match(const vector<colour>& lhs, const vector<colour>& rhs)
{
  assert(lhs.size()==rhs.size());
  vector<colour>::const_iterator lit,rit;
  lit = lhs.begin();
  rit = rhs.begin();
  while(lit != lhs.end()){
    if(*lit != *rit && *lit!=UNKNOWN && *rit!=UNKNOWN){
      return false;
    }
    ++lit;
    ++rit;
  }
  return true;
}

void nonogram::sequence_t::assign_intersection_lhs(vector<colour>& lhs, const vector<colour>& rhs)
{
  assert(lhs.size()==rhs.size());
  vector<colour>::const_iterator rit;
  vector<colour>::iterator lit;
  lit = lhs.begin();
  rit = rhs.begin();
  while(lit != lhs.end()){
    if(*lit != *rit){
      *lit = UNKNOWN;
    }
    ++lit;
    ++rit;
  }
}

colour nonogram::random_colour() const
{
  auto it = colours.begin();
  advance(it,rand() % colours.size());
  return *it;
}

void nonogram::print() const
{
  map<colour,string> print_map;
  print_map[WHITE] = "-";
  print_map[BLACK] = "@";
  print_map[UNKNOWN] = "?";
  
  for(int y=0;y<height;++y){
    for(int x=0;x<width;++x){
      cout << print_map[fields[y*width+x]] << " ";
    }
    cout << "\n";
  }
}

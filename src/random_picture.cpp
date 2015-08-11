#include "random_picture.hpp"

string random_picture(const string& adjective,const string& noun)
{
  string url = "http://freeimages.pictures/api/user/1089487859513610/?keyword=" + adjective + "%20" + noun;
  const string tmpfile = ".tmpfile";
  
  
  download_file(url,tmpfile);
  
  Json::Value root;
  Json::Reader jsonreader;
  
  ifstream tmpfilestream(tmpfile);
  
  jsonreader.parse(tmpfilestream,root,false);
  
  remove(tmpfile.c_str());
  
  vector<string> candidates;
  Json::Value sources = root["sources"];
  for(auto source=sources.begin();source!=sources.end();++source){
    Json::Value results = (*source)["result"];
    for(auto result=results.begin();result!=results.end();++result){
      Json::Value candidate_value = (*result)["url"];
      string tmp_str = candidate_value.toStyledString();
      tmp_str = tmp_str.substr(1,tmp_str.size()-3);
      candidates.push_back(tmp_str);
    }
  }  
  
  return candidates[rand() % candidates.size()];
}

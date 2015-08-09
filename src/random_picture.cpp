#include "random_picture.hpp"

string random_picture()
{
  string adjective = "happy";
  string noun = "girl";
  
  string url = "http://freeimages.pictures/api/user/1089487859513610/?keyword=" + adjective + "%20" + noun;
  const string tmpfile = ".tmpfile";
  
  
  download_file(url,tmpfile);
  
  
  return "";
}

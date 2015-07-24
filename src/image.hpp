#if 0
#include <CImg.h>

using namespace cimg_library;

typedef CImg<unsigned char> image_t;

unsigned char get_avg_value(const image_t* im,int blocksize,int x_offset,int y_offset,int channel){
  long res = 0;
  long count = 0;
  for(int y=y_offset;y<std::min(y_offset+blocksize,im->height());y++){
    for(int x=x_offset;x<std::min(x_offset+blocksize,im->width());x++){
      res += (*im)(x,y,0,channel);
      count++;
    }
  }
  return (unsigned char)(res/count);  
}





int main(int argc,char** argv){
  const int blocksize = 5;
  
  image_t input_file(argv[1]);
  
  int out_blocks_x = input_file.width() / blocksize;
  int out_blocks_y = input_file.height() / blocksize;
  
  
  
  image_t output_file(out_blocks_x*blocksize,out_blocks_y*blocksize,1,3,0);
  
  for(int y=0;y<out_blocks_y*blocksize;y+=blocksize){
    for(int x=0;x<out_blocks_x*blocksize;x+=blocksize){
      for(int c=0;c<3;c++){
        
        unsigned char v = get_avg_value(&input_file,blocksize,x,y,c);
        //v = (v<85) ? 0 : ((v>170) ? 255 : 128);
        v = (v<128) ? 0 : 255;
        
        
        for(int a=0;a<blocksize;a++){
          for(int b=0;b<blocksize;b++){
            output_file(x+b,y+a,0,c) = v;
          }
        }
        
      }
    }
  }
  
  output_file.save(argv[2]);
  return 0;
  
}

#endif
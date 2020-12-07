#include "draw.h"
#include <png.h>
#include <zlib.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include <cstring>
#include <string>

using std::string;

/* Contact: Abdulla Alwabel alwabel@usc.edu */
#define H 1000
#define W 1000
namespace draw{
  bool drawn = false;
  struct Pixel  {
    Pixel(int r=255,int g=255,int b=255) {
      red = r;
      green = g;
      blue = b;
    }
    Pixel(Color c) { 
      red = c.red;
      green = c.green;
      blue = c.blue;
    }
    void setcolor(Color c) { 
      red = c.red;
      green = c.green;
      blue = c.blue;
    }
    /*
    void setcolor(int r,int g,int b){
      red=r; green=g; blue= b;
    }
    */
    char red;
    char green;
    char blue;
  };

  int width=512;
  int height=512;
  int penwidth = 1;
  double ymin=0,ymax = 1; //Coordinate ranges, default 0-1
  double xmin=0,xmax = 1; //Coordinate ranges, default 0-1

  string filename;
  FILE *out = NULL;
  int sequence = 0;
  int frames = 0;
  static int inline norm_x(double x) {
    return (width)*(x-xmin)/(xmax-xmin);
  }
  static int inline norm_y(double y) { 
   // return height - ( (height)*(y-ymin)/(ymax-ymin) ) -1;
    return ( (height)*(y-ymin)/(ymax-ymin) ) ;

  }
  static bool inline in_range(int x,int y) { 
    return (x>=0 && x < width && y>=0 && y< height);
  }
  Color current(0,0,0); //Default is black
  Pixel img[H][W];

  //Actual drawing

  void plot(int x,int y) { 
    drawn = true;;
    img[y][x].setcolor(current);
    double x0 = x-penwidth/2;
    double y0 = y-penwidth/2;
    double x1 = x+penwidth/2;
    double y1 = y+penwidth/2;
      for(int x=x0;x<=x1;x++){ 
        if( in_range(x,(int)y0) )
          img[(int)y0][x].setcolor(current);
        for(int y=y0;y<=y1;y++) { 
          if(in_range(x,y) )
            img[y][x].setcolor(current);
        }
      }
  }
  void point(double _x,double _y) {
    int x = norm_x(_x);
    int y = norm_y(_y);
    y = height-y-1;
    //img[(int)y][(int)x].color(0,0,0);
    
    //if(in_range(x,y)) img[y][x].setcolor(current); 
    //if(in_range(x,width-y-1)) img[y][x].setcolor(current);
    //if(penwidth > 1) { 
//      filled_square(_x,_y,penwidth/2);
    //}
    if(in_range(x,y)) plot(x,y);
  }
  void line(double x1,double y1,double x2,double y2) 
  {
    //DDA algorithm
    drawn = true;
    x1 = (double)norm_x(x1);
    x2 = (double)norm_x(x2);

    y1 = (double)norm_y(y1);
    y1 = height-y1-1;
    y2 = (double)norm_y(y2);
    y2 = height-y2-1;

    int dx = x2-x1;
    int dy = y2-y1;

    int steps=abs(dx)>abs(dy) ? abs(dx) : abs(dy);

    double Xinc = dx/(double)steps;
    double Yinc = dy/(double)steps;
    double X = x1;
    double Y = y1;
    for(int i=0;i<=steps;i++) {
      if(in_range(X,Y)) plot(X,Y);
      X += Xinc;
      Y += Yinc;
    }
    
    /*
    drawn = true;;

   if(x2 < x1 ) { 
      double s_x=x2,s_y=y2;
      x2 = x1; y2 = y1;

      y1 = s_y; 
      x1 = s_x;
    }
    x1 = (double)norm_x(x1);
    x2 = (double)norm_x(x2);

    y1 = (double)norm_y(y1);
    y1 = height-y1-1;
    y2 = (double)norm_y(y2);
    y2 = height-y2-1;
    //check height and width
    double dx = x2-x1;
    double dy = y2- y1;

    for(int x=x1;x<=x2;x++){ 
      int y = y1+dy*(x-x1)/dx;
      //if(in_range(x,y)) img[height-y-1][x].setcolor(current);
     //if(in_range(x,height-y-1)) plot(x,height-y-1);
     if(in_range(x,y)) plot(x,y);

    }
    */
  }


  void rectangle(double x0,double y0,double x1,double y1) 
  {
    drawn = true;;
    x0 = (double)norm_x(x0);
    x1 = (double)norm_x(x1);

    y0 = (double)norm_y(y0);
    y1 = (double)norm_y(y1);


    for(int x=x0;x<=x1;x++){ 
      if(in_range(x,(int)y0 ) )
        img[(int)y0][x].setcolor(current);

      if(in_range(x,(int)y0) )
        img[(int)y1][x].setcolor(current);
    }

    for(int y=y0;y<=y1;y++) { 
      if(in_range((int)x0,y) )
        img[y][(int)x0].setcolor(current);
      if(in_range((int)x1,y) )        
        img[y][(int)x1].setcolor(current);
    }
  }

  void square(double cx,double cy,double s) 
  {
    rectangle(cx-s/2,cy-s/2,cx+s/2,cy+s/2);
  }

  void filled_rectangle(double x0,double y0,double x1,double y1) 
  { 
    drawn = true;;
    x0 = norm_x(x0);
    x1 = norm_x(x1);

    y0 = norm_y(y0);
    y1 = norm_y(y1);

    for(int x=x0;x<=x1;x++){ 
      if( in_range(x,(int)y0) )
        img[(int)y0][x].setcolor(current);
      for(int y=y0;y<=y1;y++) { 
        if(in_range(x,y) )
          img[y][x].setcolor(current);
      }
    }
  }

  void filled_square(double cx,double cy,double s) 
  {
    filled_rectangle(cx-s/2,cy-s/2,cx+s/2,cy+s/2);
  }

  void ellipse(double cx,double cy,double rx,double ry) 
  {
    drawn = true;;
    rx = (double)norm_x(rx);
    ry = (double)norm_y(ry);

    cx =(double)norm_x(cx);
    cy = (double)norm_y(cy);
    for(double theta=0;theta<=2*M_PI;theta+=0.01){ 
      int x =cx+rx*cos(theta);
      int y = cy+ry*sin(theta);
      if(in_range(x,y))
        img[y][x].setcolor(current);
    }

  }
  void circle(double cx,double cy,double r) 
  {
    ellipse(cx,cy,r,r);
  }

  void filled_ellipse(double cx,double cy,double rx,double ry)
  {
    drawn = true;;
    cx = (double)norm_x(cx);
    cy = (double)norm_y(cy);

    rx = (double)norm_x(rx);
    ry = (double)norm_y(ry);
   
    for(int y=-ry;y<=ry;y++) {
      for(int x=-rx;x<=rx;x++){ 
       if(x*x+y*y <= rx*ry) 
        if(in_range(x+(int)cx,y+(int)cy) )
          img[y+(int)cy][x+(int)cx].setcolor(current);
      }
    }
  }

  void filled_circle(double cx,double cy,double r)
  {
    filled_ellipse(cx,cy,r,r);
  }

  void polygon(int np,const double x[],const double y[]) { 
    drawn = true;;
    for(int i=0;i<np;i++) {
      double x0,y0,x1,y1;
      x0 = x[i];
      y0 = y[i];
      if(i<np-1) {
        x1 = x[i+1];
        y1 = y[i+1];
      } else {
        x1 = x[0];
        y1 = y[0];
      }
      line(x0,y0,x1,y1);
    }
  }

  void filled_polygon(int np, const double x[], const double y[],Pixel **img){ 
    //Not implemented at the moment
  }

  void clear() {
    drawn = false;
    for(int i=0;i<H;i++)
      for(int j=0;j<W;j++)
        img[i][j].setcolor(WHITE);
  }

  //Setters
  void setcolor(int r,int g,int b) { 
    current.red = r;
    current.green = g;
    current.blue = b;
  }
  void setcolor(Color c ) { 
    current = c;
  }

  void setpenwidth(double w) { 
    penwidth = (int)w;    
  }
  
  void setwindowsize(int w,int h) { 
    if(w >=0 && w<W && h>=0 && h<H  && !drawn) {   
    printf("%d %d\n",w,h);

      width = w;
      height = h;
    } 
    else if(drawn) { 
      fprintf(stderr,"Cannot resize the window\n");
    }
    else {
      fprintf(stderr,"Invalid windowsize\n");
    }
  }

  void setxrange(double x0,double x1  ) {
    if(x0 < x1) { 
      xmin = x0;
      xmax = x1;
    } else {
      fprintf(stderr,"setxrange failed, invalid parameter\n");
    }
  }

  void setyrange(double y0,double y1) { 
    if(y0 < y1 ) { 
      ymin = y0;
      ymax = y1;
    } else {
      fprintf(stderr,"setyrange failed, invalid parameter\n");
    }
  }

  void setrange(double min,double max) { 
    if(min<max) { 
      xmin = ymin = min;
      xmax= ymax = max;
    }else {
      fprintf(stderr,"setrange failed, invalid parameter\n");
    }
  }
  void settransparency(double t) { 
    //not implemented
    fprintf(stderr,"settransparency() is not implemented\n");
  }

  void setfontsize(int s) { 
    //not implemented
    fprintf(stderr,"setfontsize() is not implemented\n");
  }

  void play(const char filename[]) { 
    //not implemented
    fprintf(stderr,"play() is not implemented\n");
  }

  void image(const char filename[],double ,double) { 
    //not implemented
    fprintf(stderr,"image() is not implemented\n");
  }

  void text(const char text[],double ,double) { 
    //not implemented
    fprintf(stderr,"text() is not implemented\n");
  }


  bool save(const char filename[]) { 
    FILE *fp = fopen(filename,"wb");
    if(!fp) { 
      return false;
    }

   png_structp png_ptr = png_create_write_struct(
      PNG_LIBPNG_VER_STRING,/*(png_voidp)user_error_ptr,
      user_error_fn,user_warning_fn);*/ NULL,NULL,NULL);
    if(!png_ptr) return false;

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr) {
      png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
      return false;
    }

    if(setjmp(png_jmpbuf(png_ptr)) ) 
    {
      png_destroy_write_struct(&png_ptr,&info_ptr);
      fclose(fp);
      return false;
    }


    png_set_IHDR (png_ptr,
                  info_ptr,
                  width,
                  height,
                  8, /*depth*/
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    
    png_init_io(png_ptr,fp);
    png_write_info(png_ptr,info_ptr);
    for(int i=0;i<height;i++) { 
      png_bytep row_pointer = (png_bytep) img[i];
      png_write_row(png_ptr,row_pointer);
    }
    png_write_end(png_ptr,info_ptr);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    return true;
    } 

  struct acTL { 
    char type[4];
    int num_frames;
    int num_plays;
  }; 

  struct fcTL { 
    char type[4];
    int sequence_number;
    int width;
    int height;
    int x_offset;
    int y_offset;
    short delay_num;
    short delay_den;
    char dispose_op;
    char blend_op;
  }; 

  //write aPNG frame
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;

  enum w_state {WRITE_ALL,F_IDAT,S_IDAT,IGNORE};
  w_state current_state = WRITE_ALL;
  int ms = 0;
  acTL a; //actl struct
  void draw_png_write(png_structp png_ptr, png_bytep data, png_size_t length)
  {
    if(out) { 
      switch(current_state) { 
        case WRITE_ALL:{
          fwrite(data,length,1,out);
          break;
        }
        case F_IDAT: { 
          
          //acTL a;
          strncpy((char *)a.type,"acTL",4);
          int len = htonl(8);
          a.num_frames = 1;//htonl(1);
          a.num_plays = 0;
          fwrite(&len,sizeof(len),1,out);
          fwrite(&a,12,1,out);
          uint32_t c = crc32(0 , (const Bytef*)&a,12);
          c = htonl(c);
          fwrite(&c,sizeof(c),1,out);
         
          
          char tRNS[] = "\x00\x00\x00\x06\x74\x52\x4e\x53\x00\x00\x00\x00\x00\x10\x73\x11\x17\xf5";

          fwrite(tRNS,sizeof(char),sizeof(tRNS)-1,out);

          fcTL f;
          f.sequence_number = htonl(sequence++);
          f.width =htonl(width);
          f.height = htonl(height);
          f.x_offset = 0;
          f.y_offset = 0;
          
          f.delay_num= htons(ms);
          f.delay_den = htons(0x64);
          f.dispose_op=0;
          f.blend_op=0;
          strncpy(f.type,"fcTL",4);

          len = htonl(0x1a);

          fwrite(&len,sizeof(len),1,out);
          fwrite(&f,30,1,out);

          c = crc32(0 , (const Bytef*)&f,30);
          c = htonl(c);
          fwrite(&c,sizeof(c),1,out);
          
          fwrite(data,length,1,out);
          current_state = WRITE_ALL;
          break;
        }
        case S_IDAT: { 
          fcTL f;
          a.num_frames ++;

          f.sequence_number = htonl(sequence++);
          f.width =htonl(width);
          f.height = htonl(height);
          f.x_offset = 0;
          f.y_offset = 0;
          
          f.delay_num= htons(ms);
          f.delay_den = htons(0x64);
          f.dispose_op=0;
          f.blend_op=0;
          strncpy(f.type,"fcTL",4);

          int len = htonl(0x1a);

          fwrite(&len,sizeof(len),1,out);
          fwrite(&f,30,1,out);

          uint32_t c = crc32(0 , (const Bytef*)&f,30);
          c = htonl(c);
          fwrite(&c,sizeof(c),1,out);

          len =  *(int *)(data);

          len = ntohl(len);
          len+=4;
          len = htonl(len);
          fwrite(&len,sizeof(len),1,out);
          char type[4];
          strncpy(type,"fdAT",4);
          fwrite(type,sizeof(type),1,out);
          int s = sequence++;
          s = htonl(s);
          fwrite(&s,sizeof(s),1,out);
          data += 8;
          fwrite(data,length-8,1,out);
          current_state = WRITE_ALL;

          break;
        }
        default: 
          break;
      }
    } else {
      fprintf(stderr,"Error writing png data\n");
    }
  }

  void draw_png_flush(png_structp png_ptr) { 
  }
  void write_frame(bool last,int ms) { 
    if(!out) { 
      out = fopen(filename.c_str(),"wb");
      if(!out) { 
          fprintf(stderr,"Failed to open file '%s' for writing!\n",filename.c_str());
          return ;
        }

        png_structp png_ptr = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,/*(png_voidp)user_error_ptr,
        user_error_fn,user_warning_fn);*/ NULL,NULL,NULL);
        if(!png_ptr){
          fprintf(stderr,"Failed to write frame\n");
          return ;
        }
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if(!info_ptr) {
          png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
          fprintf(stderr,"Failed to write frame\n");
          return ;
        }

        if(setjmp(png_jmpbuf(png_ptr)) ) 
        {
          png_destroy_write_struct(&png_ptr,&info_ptr);
          fclose(out);
          fprintf(stderr,"Failed to write frame\n");
          return ;

        }

         png_set_IHDR (png_ptr,
                    info_ptr,
                    width,
                    height,
                    8, /*depth*/
                    PNG_COLOR_TYPE_RGB,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT);
        current_state = WRITE_ALL;

        //png_init_io(png_ptr,out);
        png_set_write_fn(png_ptr,(void *)NULL,draw_png_write,draw_png_flush);
        /*
        png_unknown_chunk chunks[2];
        strncpy((char*)chunks[0].name,"acTl",4);
        acTL a;
        a.num_frames = htonl(1);
        a.num_plays= 0;
        chunks[0].size = sizeof(a);
        chunks[0].data = (png_byte*)&a;

        chunks[0].location = PNG_HAVE_PLTE;//AFTER_IDAT;
 
        fcTL f;
        f.sequence_number = htonl(sequence++);
        f.width =htonl(width);
        f.height = htonl(height);
        f.x_offset = 0;
        f.y_offset = 0;
        f.delay_num= htons(ms);
        f.delay_den = htons(0x64);
        f.dispose_op=0;
        f.blend_op=0;
        strncpy(f.type,"fctl",4);
        //strncpy((char*)chunks[1].name,"fcTl",4);
        memset((char*)chunks[1].name,0,4);
        chunks[1].size = 30;
        chunks[1].data = (png_byte*)&f;
        chunks[1].location=PNG_HAVE_PLTE;

        png_set_unknown_chunks(png_ptr,info_ptr,chunks,2);
        png_set_unknown_chunk_location(png_ptr,info_ptr,0,PNG_HAVE_PLTE);
        png_set_unknown_chunk_location(png_ptr,info_ptr,1,PNG_HAVE_PLTE);

        */
        png_write_info(png_ptr,info_ptr);

        current_state = F_IDAT;
        //png_write_flush(png_ptr);
         for(int i=0;i<height;i++) { 
            png_bytep row_pointer = (png_bytep) img[i];
            png_write_row(png_ptr,row_pointer);
          }
         current_state = WRITE_ALL;
         //png_write_end(png_ptr,info_ptr);
         png_destroy_write_struct(&png_ptr,&info_ptr);
    } 
    else if(!last) {
      current_state = IGNORE;
      //subsequent frames
      png_structp png_ptr = png_create_write_struct(
        PNG_LIBPNG_VER_STRING,/*(png_voidp)user_error_ptr,
        user_error_fn,user_warning_fn);*/ NULL,NULL,NULL);
        if(!png_ptr){
          fprintf(stderr,"Failed to write frame\n");
          return ;
        }
        png_infop info_ptr = png_create_info_struct(png_ptr);
        if(!info_ptr) {
          png_destroy_write_struct(&png_ptr,(png_infopp)NULL);
          fprintf(stderr,"Failed to write frame\n");
          return ;
        }

        if(setjmp(png_jmpbuf(png_ptr)) ) 
        {
          png_destroy_write_struct(&png_ptr,&info_ptr);
          fclose(out);
          fprintf(stderr,"Failed to write frame\n");
          return ;

        }

         png_set_IHDR (png_ptr,
                    info_ptr,
                    width,
                    height,
                    8, /*depth*/
                    PNG_COLOR_TYPE_RGB,
                    PNG_INTERLACE_NONE,
                    PNG_COMPRESSION_TYPE_DEFAULT,
                    PNG_FILTER_TYPE_DEFAULT);

        //png_init_io(png_ptr,out);
       png_set_write_fn(png_ptr,(void *)NULL,draw_png_write,draw_png_flush);
       png_write_info(png_ptr,info_ptr);
//      png_write_flush(png_ptr);
       current_state = S_IDAT;

       for(int i=0;i<height;i++) { 
          png_bytep row_pointer = (png_bytep) img[i];
          png_write_row(png_ptr,row_pointer);
        }
//        png_write_end(png_ptr,info_ptr);
       png_destroy_write_struct(&png_ptr,&info_ptr);
    }
    else if(last && out ) { 
      char end [] = "\x00\x00\x00\x00\x49\x45\x4e\x44\xae\x42\x60\x82";
      fwrite(end,1,12,out);

      fseek(out,0x25,SEEK_SET);
      a.num_frames = htonl(a.num_frames);
      fwrite(&a,12,1,out);
      uint32_t c = crc32(0 , (const Bytef*)&a,12);
      c = htonl(c);
      fwrite(&c,sizeof(c),1,out);
 
      fclose(out);
    }
  }
  void show(int milliseconds) {
    //printf("HERE \n");
    ms = milliseconds;
    write_frame(false,milliseconds);
  }

class dummy { 
public:
  dummy() { 
    const char *s = getenv("_");
    filename = s;
    size_t p;
    if( (p=filename.rfind("/")) != string::npos) { 
      filename = filename.substr(p+1);
    }
    filename += ".png";

  }
  ~dummy() { 
    if(sequence == 0 )
      draw::save(filename.c_str());
    else write_frame(true,0);
    /* 
    const char *s = getenv("_");
    string filename(s);
    size_t p;
    if( (p=filename.rfind("./")) != string::npos) { 
      filename = filename.substr(p+2);
    }
    filename += ".png";
    draw::save(filename.c_str());
    */
    //write_frame(last);
  }
};
dummy d;


} 
//end namespace 




/* 
  This is a reimplementation of the https://github.com/daveagp/draw
  instead of using Qt GUI it produces animated PNG

  Contact: Abdulla Alwabel alwabel@usc.edu
  
*/

#ifndef _H_DRAW
#define _H_DRAW

// user-facing API

namespace draw {
// drawing shapes. cx, cy means center
   void point(double x, double y);
   void line(double x0, double y0, double x1, double y1);
   void square(double cx, double cy, double side_length);
   void rectangle(double x0, double y0, double x1, double y1);
   void polygon(int num_points, const double x[], const double y[]);
   void circle(double cx, double cy, double r);
   void ellipse(double cx, double cy, double rx, double ry);
// drawing filled shapes
   void filled_square(double cx, double cy, double side_length);
   void filled_rectangle(double x0, double y0, double x1, double y1);
   void filled_polygon(int num_points, const double x[], const double y[]);
   void filled_circle(double cx, double cy, double r);
   void filled_ellipse(double cx, double cy, double rx, double ry);
// draw image or text centered at a given position
   void image(const char filename[], double, double);
   void text(const char text[], double, double);
// set coordinates for boundaries of screen. default is from 0 to 1
   void setxrange(double xmin, double ymax);
   void setyrange(double ymin, double ymax);
   void setrange(double min, double max); // sets both ranges
// set color. default is black
   void setcolor(int r, int g, int b);
// other settings
   void setpenwidth(double w); // default: 1
   void settransparency(double t); // 1 transparent, 0 opaque. default: 0
   void setfontsize(int s); // default: 12 pt
   void setwindowsize(int width, int height); // default: 512x512 pixels
// show current frame, pause this many milliseconds, 
// & turn on animation mode: nothing will display until next call to show
   void show(int milliseconds);
// misc
   void clear(); // fill with white
   bool save(const char filename[]); // save image to file. true = ok, false = error
   void play(const char filename[]); // play a sound file

}

// new type for pre-defined colors
#ifndef CS103_COLOR
#define CS103_COLOR
struct Color {
   int red;
   int green;
   int blue;
   Color() {} // uninitialized color
   Color(int r, int g, int b) {red = r; green = g; blue = b;}
   bool same_as(Color c) {return red==c.red && green==c.green && blue==c.blue;}
};
#endif

namespace draw {
   
   // let setcolor work with pre-defined colors
   void setcolor(Color c); 

   // some pre-defined colors
   const Color RED(255, 0, 0);
   const Color LIME(0, 255, 0);
   const Color BLUE(0, 0, 255);
   const Color GREEN(0, 127, 0);
   const Color YELLOW(255, 255, 0);
   const Color CYAN(0, 255, 255);
   const Color MAGENTA(255, 0, 255);
   const Color PINK(255, 127, 255);
   const Color WHITE(255, 255, 255);
   const Color BLACK(0, 0, 0);
   const Color GRAY(127, 127, 127);
   const Color ORANGE(255, 127, 0);
   const Color PURPLE(127, 0, 127);
   const Color TEAL(0, 127, 127);
   const Color OLIVE(127, 127, 0);
   const Color MAROON(127, 0, 0);
   const Color NAVY(0, 0, 127);
   const Color MINT(127, 255, 127);
   const Color CORAL(255, 127, 127);
   const Color ROSE(255, 0, 127);
   const Color CHARTREUSE(127, 255, 0);
   const Color VIOLET(127, 0, 255);
   const Color AZURE(0, 127, 255);
      
}

#endif


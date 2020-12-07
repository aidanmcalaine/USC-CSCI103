#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

int main() {
   unsigned char image[SIZE][SIZE];

   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }

   for(int i=0; i < SIZE; i++) {
      image[i][128] = 0;
      image[128][i] = 0;
   }
    
   for(int i=0; i < SIZE; i++) {
      image[i][i] = 0;
   }

   double r = 50;
   for (double theta=0.0; theta < 2*M_PI; theta += .01) {
      double x = r*cos(theta);
      double y = r*sin(theta);
      x += SIZE/2;
      y += SIZE/2;
      image[(int)y][(int)x] = 0;
   }
     
   // save to file
   showGSBMP(image);
   writeGSBMP("cross.bmp", image);
   return 0;
}

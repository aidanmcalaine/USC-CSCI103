#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
  //set bounds 
  
  //copy variables
  int upperBound1 = left + width; 
  int upperBound2 = top + height; 
  if (upperBound1 > 255) {
    upperBound1 = 255; 
  }
  if (upperBound2 > 255){
    upperBound2 = 255; 
  }
  
  //draw rows 
  for (int a = left; a <= upperBound1; a++) {
  //out of bounds check
    if (a >= 0 && a < 256) {
      image[upperBound2][a] = 0;
      image[top][a] = 0; 
    }
  }
  //draw columns
  for (int b = top; b <= upperBound2; b++) {
    if (b >= 0 && b < 256)  {
      if (left > 0) {
        image[b][upperBound1] = 0; 
        image[b][left] = 0;
      }
      else {
        image[b][upperBound1] = 0; 
      }
    }
  } 
}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {
  for (double theta = 0.00; theta < 2*M_PI; theta += 0.01) {
    double x = cx + (width/2)*cos(theta); 
    double y = cy + (height/2)*sin(theta); 
    //out of bounds check 
    if ((x >= 0 && x <= 256) && (y >= 0 && y <= 256)) {
      image[(int)y][(int)x] = 0; 
    }
  }
}

int main() {
   // initialize the image to all white pixels
   for (int i=0; i < SIZE; i++) {
      for (int j=0; j < SIZE; j++) {
         image[i][j] = 255;
      }
   }
   // Main program loop here
   int user = 0; 
   int x1, x2, x3, x4; 
   while (user != 2) {
     //prompt user
     cout << "To draw a rectangle, enter: 0 top left height width" << endl; 
     cout << "To draw an ellipse, enter: 1 cy cx height width" << endl; 
     cout << "To save your drawing as \"output.bmp\" and quit, enter: 2" << endl; 
     //obtain input
     cin >> user;
     if (user == 0) {
       cin >> x1 >> x2 >> x3 >> x4; 
       draw_rectangle(x1,x2,x3,x4); 
     }
     else if (user == 1){
       cin >> x1 >> x2 >> x3 >> x4; 
       draw_ellipse(x1,x2,x3,x4); 
     }
     else {
       break; 
     }
   } 
   // Write the resulting image to the .bmp file
   writeGSBMP("output.bmp", image);
   
   return 0;
}

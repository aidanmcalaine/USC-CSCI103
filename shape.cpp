#include "turtle.h"
#include "draw.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cerr << "Usage: shape N\nwhere N is an integer >= 3" << endl;
      std::exit(1);
   }   
   int N = atoi(argv[1]);
   
   draw::setrange(-100, 100);
   
   Turtle t(-25, -50, 0);
   for (int i=0; i<N; i++) {
      t.move(300.0/N); // draw a shape with perimeter 300 steps
      t.turn(360.0/N); // do a full turn in N parts
   }
   
   if (N<0) { // easter egg
      for (int i=0; i<4; i++) {
         t.move(50); t.turn(-45); t.move(50); t.turn(135); 
      }
   }
   
   return 0;
}

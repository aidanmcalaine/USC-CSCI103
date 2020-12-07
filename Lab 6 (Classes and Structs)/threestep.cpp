#include "draw.h"
#include "turtle.h"

int main() {
   // set corners
   draw::setrange(-100, 100);

   // create turtle at x-position 0, y-position 0, facing angle 0 (east)   
   Turtle leonardo(0, 0, 0); 
   
   // tell turtle to do some things
   leonardo.move(80);
   leonardo.turn(90);
   leonardo.move(80);
   leonardo.turn(120); // direction is now 0+90+120 = 210
   leonardo.move(160); 

   return 0;
}

#include "turtle.h"
#include "draw.h"

int main() {
   draw::setpenwidth(10); // thick lines
   draw::setrange(-100, 100);

   // start at A
   Turtle raphael(50, 50, 240); 
   raphael.setColor(draw::RED);
   raphael.move(100); // go to B
   raphael.turn(-105);
   raphael.move(50);  // go to C
   raphael.off();     // ninja vanish
   raphael.turn(180); // turn around
   raphael.move(90);  // go to D
   raphael.turn(-135);
   raphael.setColor(draw::GREEN);
   raphael.on();      // ninja unvanish
   raphael.move(60);  // go to E

   return 0;
}

#include "turtle.h"
#include "draw.h"

int main() {
   draw::setpenwidth(10); // thick lines
   draw::setrange(-100, 100);
   // get in position
   Turtle michaelangelo(80, 80, 0);
   Turtle leonardo(80, -80, 135);
   michaelangelo.turn(-135);
   michaelangelo.setColor(draw::ORANGE);
   leonardo.setColor(draw::BLUE);

   leonardo.move(100); // blue, from bottom right to below center
   leonardo.off();
   michaelangelo.move(226); // orange, from top right to bottom left
   leonardo.move(26); // invisible, from below to above center
   leonardo.on();
   leonardo.move(100); // blue, from above center to top left
   leonardo.off(); 

   return 0;
}

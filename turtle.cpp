//This file also starts out empty.
//Implement the Turtle class here.
#include <cmath>
#include "turtle.h"
Turtle::Turtle(double x0, double y0, double dir0){
	x = x0;
	y = y0;
	dir = dir0;
  col = draw::BLACK; 
  check = 0; 
  draw::setcolor(col);
}

//move Turtle around
void Turtle::move(double dist){
  if (check == 0) {
    draw::setcolor(col);
    draw::line(x,y, 
				  (x+(dist*cos((M_PI/180)*dir))),
				  (y+(dist*sin((M_PI/180)*dir))));
  }
  //set new values 
	x = (x+(dist*cos((M_PI/180)*dir)));
	y = (y+(dist*sin((M_PI/180)*dir)));
}
//turn the Turtle 
void Turtle::turn(double deg){
	dir = dir + deg;
}
void Turtle::on() {
  //0 value means the Turtle can keep drawing 
  check = 0; 
}
void Turtle::off () {
  check = 1; 
}
void Turtle::setColor(Color c) {
  col = c; 
}
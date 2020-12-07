#include "turtle.h"
#include <cmath>

using namespace std;
//constructor
Turtle::Turtle(double x0, double y0, double dir0){
  x = x0;
  y = y0;
  dir = dir0;
  color = draw::BLACK;
  value = 0;
}
// implementation of the member function
void Turtle::move(double dist){
  double xNew = x + (dist*cos(dir*M_PI/180));
  double yNew = y + (dist*sin(dir*M_PI/180));
  draw::setcolor(color);
  // means drawing has not been turned off yet;
  if(value == 0){
    draw::line(x,y,xNew,yNew);
  }
  //update x and y to their new locations
  x = xNew;
  y = yNew;
}

void Turtle::turn(double deg){
  dir+=deg;
}

void Turtle::setColor(Color c){ 
    color = c;
}

void Turtle::on(){
    value = 0;
}

void Turtle::off(){
    value = 1;
}



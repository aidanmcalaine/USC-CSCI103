#include "draw.h"

class Turtle {
  //need to introduce public prototypes for constructor and 2 member functions  
  public:
    Turtle(double x0, double y0, double dir0);
    void move(double dist);
    void turn(double deg);
    void setColor(Color c);
    void on();
    void off();
  //private section for data members 
  private:
    double x;
    double y;
    double dir;
    Color color;
    int value; //will be used to determine wether drawing is on or off
};
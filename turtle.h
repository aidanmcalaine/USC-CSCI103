//This file starts out empty!
//Define the Turtle class here.
#include "draw.h"
class Turtle {
  public:
    //constructor
    Turtle(double x0, double y0, double dir0);
    //methods 
	  void move(double dist);
	  void turn(double deg);
    void setColor(Color c); //change color that this Turtle draws now on
    void off(); //stop drawing lines 
    void on(); //resume drawing 
    
   
  private: 
    //fields 
    double x;
	  double y;
	  double dir;
    Color col; 
    int check; //0 for on, 1 for off 
};
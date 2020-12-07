//file name:tri.cpp
#include <iostream>
#include <cmath>
using namespace std; 

int main () {
  //query the user for a value of theta between 15 and 75
  int theta; 
  cout << "Enter the angle theta in degrees" << endl; 

  //angle in degrees 
  cin >> theta; 
  
  //convert theta to radians 
  float thetaRadians = theta * (M_PI/180); 
  //find x value
  float tanTheta = tan(thetaRadians);
  
  cout << tanTheta << endl; 
   
  
  //building the triangle 
  for (int i = 0; i < 31; i++) {
    int counter = tanTheta*i; 
  
    for (int j = 0; ((j <= counter) && (counter < 20 || counter > 30)); j++) {
      if (j <= counter) {
        
        cout << "*"; 
        
    }
  }
  if (counter >= 20 && counter <= 30) {
    cout << "********************"; 
  }
  cout << "\n";  
  }
}
  


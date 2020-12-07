//file name:prime23.cpp
#include <iostream>
using namespace std; 

//Step 1 - prompting the user
int main () {
 
  int userInput; 
  cout << "Enter a positive integer: " << endl;
  
  //Step 2 - receive integer input 
  cin >> userInput;
  
  //the algorithm
  int twos = 0; 
  int threes = 0; 
  
  while (userInput != 1) {
    if (userInput % 2 == 0) {
      userInput = userInput / 2; 
      twos++; 
    }
    else if (userInput % 3 == 0) {
      userInput = userInput / 3; 
      threes++; 
    }
    else{
      cout << "No" << endl; 
      return 0; 
    }
  }
  
  cout << "Yes" << endl; 
  cout << "Twos=" << twos << " Threes=" << threes << endl; 
  
  
}

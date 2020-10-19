//Aidan McAlaine, CSCI103
//Hailstone Sequences

#include <iostream>
using namespace std; 

int main() {
  
  //prompt user and get input
  cout << "Enter a number: " << endl; 
  int userInput; 
  cin >> userInput; 
  
  int counter = 0; 
  //Hailstone length loop 
  while (userInput != 1) {
    
    //even 
    if (userInput % 2 == 0) {
      userInput /= 2;
      cout << userInput << " ";
      counter++; 
    } 
    //odd
    else {
      userInput = userInput * 3 + 1; 
      cout << userInput << " ";
      counter++;
    }
  }
  cout << "\n"; 
  cout << "Length: " << counter << endl; 
  
}
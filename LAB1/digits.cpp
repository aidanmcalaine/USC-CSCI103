//Author: Aidan McAlaine 
//Program: digits.cpp
#include <iostream>
#include <sstream>
using namespace std; 

int main() {
  //obtain user input 
  string userInput; 
  cout << "Enter an integer between 0 and 999: " << endl; 
  cin >> userInput; 
    
  //extract and print digits
  
  //convert string to an int  
  stringstream degree(userInput); 
  int digits = 0; 
  degree >> digits; 
  
  //extract digits
  int hundredsDigit; 
  int tensDigit; 
  int onesDigit; 
  
  if (digits / 100 < 1) {
    hundredsDigit = 0; 
  }
  else {
    hundredsDigit = digits / 100;
  }
  
  if (digits / 10 < 1) {
    tensDigit = 0;
  }
  else {
    tensDigit = (digits % 100) / 10; 
  }  
  onesDigit = (digits % 10); 
  
  //print digits 
  cout << "1's digit is " << onesDigit << endl; 
  cout << "10's digit is " << tensDigit << endl; 
  cout << "100's digit is: " << hundredsDigit << endl; 
}
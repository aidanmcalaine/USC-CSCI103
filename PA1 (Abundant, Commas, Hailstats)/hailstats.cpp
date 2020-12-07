//Aidan McAlaine, CSCI103
//Hailstats

#include <iostream>
using namespace std; 

//establish variables
int min1, max1, length, n1, n2;  
int bottom, top; 

int main() {
  
  //take user input for the range 
  cout << "Enter the range that you want to search: " << endl; 
  
  cin >> bottom; 
  cin >> top; 
  
  
  //Hailstats loop 
  for (int i = bottom; i <= top; i++) {
    //inner hailstone loop 
    while (i != 1) {
      //even 
      if (i % 2 == 0) {
        i /= 2;
        length++; 
      } 
      //odd
      else if (i % 2 == 1) {
        i = i * 3 + 1; 
        length++;
      }
      cout << i << endl; 
    } 
    //establish first min 
    if (i == bottom) {
      min1 = length; 
      n1 = i; 
    }
    //adjust min and mix 
     if (length < min1) {
      min1 = length;
      n1 = i; 
    }
    if (length > max1) {
      max1 = length; 
      n2 = i; 
    }
  }
  
  //break if bottom is greater than top 
  if (bottom >= top) {
    cout << "Invalid range" << endl; 
    return 0; 
  }
  
  //Printing statements
  cout << "Minimum length: " << min1 << endl; 
  cout << "Achieved by: " << n1 << endl; 
  cout << "Maximum length: " << max1 << endl; 
  cout << "Achieved by: " << n2 << endl; 
}
  
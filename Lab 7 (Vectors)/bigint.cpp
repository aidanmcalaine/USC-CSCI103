#include "bigint.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

BigInt::BigInt(string s) {
  //run through the string
  for (int i = 0; i < s.size(); i++) {
    //convert the character to an int
    int num = (int) s[i]; 
    //subtract 48
    num -= 48; 
    //add it to the vector
    ints.push_back(num); 
  }
}

string BigInt::to_string() {
  //start with an empty string 
  string str = ""; 
  for (int i = ints.size()-1; i >= 0; i--) {
    //convert the integer to a char and add it to the string 
    char letter = (char) (ints[i] + 48); 
    str += letter; 
  }
  //return the string 
  return str; 
}
  
void BigInt::add(BigInt b) {
  sum = 0; 
  carry = 0; 
  //set the vectors the same length
  while (ints.size() != b.ints.size()) {
    if (ints.size() > b.ints.size()) {
      b.ints.push_back(0); 
    }
    else {
      ints.push_back(0); 
    }
  }
  //add the values
  for (int i = 0; i < ints.size(); i++) {
    
    //set sum 
    sum = ints[i] + b.ints[i] + carry; 
    carry = sum / 10; 
    ints[i] = sum % 10; 
  }
  if (carry > 0) {
    ints.push_back(carry); 
  }
}
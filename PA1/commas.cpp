/********************************************************
 * CS 103 PA 1: Commas
 * Name: Aidan McAlaine 
 * USC email: amcalain@usc.edu 
 * Comments (you want us to know):
 *
 * Description:
 *  Displays a 64-bit integer (long long) with
 *   commas for thousands, millions, billions, etc.
 *
 * ** ABSOLUTELY NO ARRAYS, NO `string`, NO `vector` **
 *  usage is allowed.
 *
 * Instead, you may only declare:
 *
 *    bool,
 *    int, or
 *    int64_t (long long)
 *
 *  The only library function allowed is pow(base, exp)
 *    defined in the <cmath> library.
 *
 *
 ********************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  long long n;
  cout << "Enter an integer:" << endl;

  /* Your code here */
  cin >> n; 
  
  //establish our variables 
  int numDigits = 0; 
  long long userValue = n; 
  
  //establish number of digits 
  while (userValue >= 1 || userValue <= -1) {      
    userValue /= 10;  
    numDigits ++; 
  }
  
  //loop and print 
  if (numDigits > 0) {
    for (int i = numDigits; i > 0; i--) {
      long long divisor = pow(10,i-1); 
      //handle negative cases
      if (i < numDigits && n < 0) {
        n = n * -1; 
      }
      cout << (n / divisor % 10);
      //check to see if a comma should be printed 
      if ((i-1) % 3 == 0 && i > 1) {
        cout << ","; 
      }   
    }
    cout << "\n";
  }
  else {
    cout << "0" << endl; 
  }
  /* End of your code */
  return 0;

}

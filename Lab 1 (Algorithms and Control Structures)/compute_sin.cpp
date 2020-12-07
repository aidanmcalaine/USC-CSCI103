/* Author: Aidan McAlaine 
 * Program: compute_sin
 * Description: Reads a number x from input, an angle in radians. 
 *    Computes an approximation to sin(x) using an 4th-order Taylor series.
 */
#include <iostream>
#include <cmath>

using namespace std;

int fact(int); // declares a function the skeleton defines for you.

int main(int argc, char *argv[])
{
   // Declare any variables you need here
   
   
   // Prompt the user
   cout << "Enter x in radians:  ";
   
   // get input
   float inputValue; 
   cin >> inputValue; 
   
   // Do some operations
   float total; 
   //step 1
   total = inputValue; 
   //step 2
   total = total - pow(inputValue, 3.0)/fact(3); 
   //step 3
   total = total + (pow(inputValue, 5.0))/(fact(5)); 
   //step 4
   total = total - (pow(inputValue, 7.0))/(fact(7)); 
   // Print the result to the user
   
   cout << total; 
   
   // You're done
   return 0;
   
}

// here's the actual definition of fact, declared earlier.
int fact(int n)
{
   int result = 1;
   for (int i = 1; i <= n; i++) {
      result = result * i;
   }
   return result;
}


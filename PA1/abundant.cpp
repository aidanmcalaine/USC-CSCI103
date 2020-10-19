/********************************************************
 * CS 103 PA 1: Abundant numbers
 * Name: Aidan McAlaine 
 * USC email: amcalain@usc.edu
 * Comments (you want us to know):
 *
 * Description:
 *   Displays the top 3 most "abundant" (see writeup)
 *   numbers in the input sequence.  The input sequence
 *   is assumed to be valid natural numbers separated
 *   by spaces and ending with 0.
 *
 *   ABSOLUTELY NO ARRAY or `string`/`vector`/etc. usage
 *   is allowed!

 *   You may only declare: bool, int, or unsigned int
 *   No library functions (beyond cin/cout) are allowed.
 *
 *   You may NOT modify any of the given template code.
 *   This ensures our automated checkers can parse your
 *   output.  Failure to follow this direction will lead
 *   to a score of 0 on this part of the assignment.
 ********************************************************/

#include <iostream>
using namespace std;

int main()
{
  // n1 is the number with the highest abundance, a1
  // n2 is the number with the 2nd-highest abundance, a2
  // n3 is the number with the 3rd-highest abundance, a3
  unsigned int n1 = 0, n2 = 0, n3 = 0;
  int a1 = 0, a2 = 0, a3 = 0;

  // num_abundant counts how many numbers in the input
  // sequence are abundant
  int num_abundant = 0;

  cout << "Enter a sequence of natural numbers, separated by spaces, ";
  cout << "and ending with 0."<< endl;

  /* Your code here */
  
  //obtain user input:
  int user;
  cin >> user;
  
  //begin loop 
  while(user > 0) {
    
    //determine if number is abundant 
    int abundanceCounter = 0; 
    for (int i = 1; i < user; i++) {
      if (user % i == 0) {
        abundanceCounter = abundanceCounter + i; 
      }
    }
    
    if (abundanceCounter > user) {
      //x is abundant 
      num_abundant++;
      
      //determine if x is a top 3 largest number 
      if (abundanceCounter > a1) {
        //adjustment of other n values
        n3 = n2; 
        a3 = a2; 
        
        n2 = n1; 
        a2 = a1; 
        //replace n1 and a1
        n1 = user; 
        a1 = abundanceCounter;         
      }
      else if(abundanceCounter > a2) {
        //adjustment of other n values
        n3 = n2; 
        a3 = a2; 
        //replace n2 and a2
        n2 = user;
        a2 = abundanceCounter; 
      }
      else if(abundanceCounter > a3) {
        //replace n3 and a3
        n3 = user; 
        a3 = abundanceCounter; 
      }
    }
  cin >> user;     
  }
     
  /* End of your code */

  cout << "Abundant number count: " << num_abundant << endl;
  cout << "Top 3 most abundant numbers: " << endl;
  cout << n1 << " : " << a1 << endl;
  cout << n2 << " : " << a2 << endl;
  cout << n3 << " : " << a3 << endl;


  return 0;

}

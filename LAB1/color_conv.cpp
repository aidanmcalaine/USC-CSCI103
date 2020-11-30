/* Author: Aidan McAlaine 
 * Program: color_conv
 * Description: Converts RGB -> CMYK color representation
 */
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
   cout << "Enter 3 integers (red, green, and blue), in that order:";
   // Enter your code here
   cout <<"\n"; 
   //calculate values
   int red, green, blue; 
   cin >> red >> green >> blue; 
   float redFloat = (float) red;
   float greenFloat = (float) green; 
   float blueFloat = (float) blue; 
   float white = max(redFloat, max(greenFloat, blueFloat)); 
   
   
   float cyan = (white - redFloat)/white; 
   float magenta = (white - greenFloat)/white; 
   float yellow = (white - blueFloat)/white; 
   float black = (1 - (white/255)); 
  
   cout << "cyan: " << cyan << endl; 
   cout << "magenta: " << magenta << endl; 
   cout << "yellow: " << yellow << endl; 
   cout << "black: " << black << endl; 
   
   
   return 0;
}
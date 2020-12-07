//File: Diceplot
//Name: Aidan McAlaine 

#include <iostream> 
#include <cstdlib>
#include <ctime>
using namespace std; 

//roll function - find a random number between 1 and 6
int roll() { 
  int r = rand() % 6 + 1; 
  return r; 
}
//printHistogram function 
void printHistogram(int counts[]) {
  for (int i = 0; i <= 20; i++) {
    cout << i+4 << ":";
    //print xs
    for (int j = 0; j < counts[i]; j++) {
      cout << "x"; 
    }
    cout << "\n"; 
  }
}
//main method
int main() {
  srand(time(0)); 
  
  //obtain user input
  cout << "Please enter a number, n: " << endl; 
  int n; 
  cin >> n; 
  
  //variables
  int ourArray[21] = {};  
  
  //run n experiments 
  for (int i = 0; i < n; i++) { 
    int total = roll() + roll() + roll() + roll(); 
    //keep track of sums
    ourArray[total-4]++;   
  }
  printHistogram(ourArray); 
}

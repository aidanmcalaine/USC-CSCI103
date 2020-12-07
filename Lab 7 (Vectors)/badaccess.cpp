#include <iostream>
#include "bigint.h"
using namespace std; 

int main() {
  BigInt a("10"); 
  BigInt b("15"); 
  cout << a.ints[0] << endl; 
  return 0;
}
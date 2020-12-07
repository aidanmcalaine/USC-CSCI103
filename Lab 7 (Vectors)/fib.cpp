#include "bigint.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cout << "Usage: fib N\nwhere N is an integer >= 2" << endl;
      return 1;
   }   
   int N = atoi(argv[1]);
   
   BigInt x("1");
   cout << x.to_string() << endl;
   BigInt y("1");
   cout << y.to_string() << endl;
   for (int i=3; i<=N; i++) {
      BigInt tmp = y;
      y.add(x);
      cout << y.to_string() << endl;
      x = tmp;
   }
}

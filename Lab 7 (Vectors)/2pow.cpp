#include "bigint.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 2) {
      cout << "Usage: 2pow N\nwhere N is an integer >= 0" << endl;
      return 1;
   }   
   int N = atoi(argv[1]);
   
   BigInt x("1");
   for (int i=1; i<=N; i++) {
      x.add(x);
      cout << x.to_string() << endl;
   }
}

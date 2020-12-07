#include "bigint.h"
#include <iostream>
using namespace std;

int main() {
   BigInt myInt("103");
   cout << myInt.to_string() << endl;
   return 0;
}

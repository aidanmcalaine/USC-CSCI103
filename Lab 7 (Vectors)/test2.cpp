#include "bigint.h"
#include <iostream>
using namespace std;

// extra test
// expected output:  10000000000000000000000

int main() {
   BigInt a("1234567890123456789012");
   BigInt b("8765432109876543210988");
   a.add(b);
   cout << a.to_string() << endl;
   return 0;
}

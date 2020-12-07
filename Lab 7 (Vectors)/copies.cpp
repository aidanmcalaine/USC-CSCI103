#include "bigint.h"
#include <iostream>
using namespace std;

int main() {
   BigInt A("15");
   BigInt B(A);
   BigInt C = A;
   A.add(B);
   cout << A.to_string() << endl;
   cout << B.to_string() << endl;
   cout << C.to_string() << endl;
}

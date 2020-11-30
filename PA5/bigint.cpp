#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <sstream>
#include <cmath> 
using namespace std;

/*
//   Create a default BigInt with base 10.
*/
BigInt::BigInt(){

    /******** You complete ****************/
    base = 10; 
    isPositive = true;    
}

/*
//  Create a BigInt with a specified base.
*/
BigInt::BigInt(int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase; 
    isPositive = true;   
}

/*
//  Create a BigInt from int (base 10) with a specified base.
//  Here you would convert an int (base 10) into a specified base.
//  e.g., (10,2) <-- 10 base 10 to base 2 --> result:  BigInt with value 1010 base 2
//  e.g., (100,16) <--- 100 base 10 to base 16 --> result: BigInt with value 64 base 16
*/
BigInt::BigInt(int input,int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    //conversions for base 2, 10, and 16
    base = setbase; 
    if (input < 0) {
        isPositive = false; 
        input = -1*input; 
    }
    else {
        isPositive = true; 
    }
    
    if (input == 0) {
        vec.push_back(0); 
    }
    while (input != 0) {
        vec.push_back(input%setbase); 
        input /= setbase; 
    }
}

/*
//  Create a BigInt from string with a specified base.
//  You can assume that the string number input is in the same
//      base as the setbase input.
*/
BigInt::BigInt(const string &s, int setbase){
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    /************* You complete *************/
    base = setbase; 
    int index = 0; 
    if (s[0] == '-') {
        isPositive = false; 
        index = 1; 
    }
    else {
        isPositive = true; 
    }
    for (int i = s.length()-1; i >= index; i--) {
        if (s[i] >= 48 && s[i] <= 57) {
            vec.push_back(s[i] - 48); 
        }
        else {
            vec.push_back(s[i] - 55); 
        }
    }
}

/*
//  Create a BigInt from another BigInt.
//  This is a copy constructor.
//  Simply use the assignment operator.
*/
BigInt::BigInt(const BigInt &b){

    /************* You complete *************/
    base = b.base; 
    isPositive = b.isPositive; 
    vec = b.vec; 
     
}

/*
// Destructure. You do not have to add anything.
// This function is complete
*/
BigInt::~BigInt(){}


/*
// Convert to string and return the string
//  Display it in its corresponding base
*/
string BigInt::to_string(){

    /************* You complete *************/
    
    //get it into an int, then into a string
    if (!vec.size()) {
        return "0"; 
    }
    string output = ""; 
    if (!isPositive) {
        output += "-"; 
    }       
    for (int i = vec.size() - 1; i >= 0; i--) {
        if (vec[i] >= 0 &&vec[i] <= 9) {
            output += char(vec[i]+48); 
        }   
        else {
            output += char(vec[i] + 55); 
        }
    }
    return output;      
}

/*
//  Convert BigInt to integer base 10 and return that int
//    If BigInt > INT_MAX, return INT_MAX.
//    If BigInt < INT_MIN, return INT_MIN.
*/
int BigInt::to_int() const{

    /************* You complete *************/
    long long int baseTen = 0; 
    for (int i = 0; i < (int)vec.size(); i++) {
        baseTen += (vec[i]*pow(base, i)); 
    }
    if (!isPositive) {
        baseTen *= -1; 
    }
    if (baseTen > INT_MAX) {
        return INT_MAX; 
    }
    else if (baseTen < INT_MIN) {
        return INT_MIN; 
    }
    return baseTen; 
}

/*
//  Compare a and b.
//     If a = b, return 0.
//     If a < b, return -1.
//     If a > b, return 1.
*/
int BigInt::compare(const BigInt &b) const{
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    
    //both positive 
    if (isPositive && b.isPositive) {
        //a > b
        if (vec.size() > b.vec.size()) {
            return 1; 
        }
        //a < b
        else if (vec.size() < b.vec.size()) {
            return -1; 
        }
        else {
            for (int i = vec.size()-1; i >= 0; i--) {
                if (vec[i] != b.vec[i]) {
                    if (vec[i] > b.vec[i]) {
                        return 1; 
                    }
                    else {
                        return -1; 
                    }
                }
            }
        }
        //equal
        return 0; 
    }
    //both negative
    if (!isPositive && !b.isPositive) {
        //a < b
        if (vec.size() > b.vec.size()) {
            return -1; 
        }
        //a > b
        else if (vec.size() < b.vec.size()) {
            return 1; 
        }
        else {
            for (int i = vec.size()-1; i >= 0; i--) {
                if (vec[i] != b.vec[i]) {
                    if (vec[i] > b.vec[i]) {
                        return -1; 
                    }
                    else {
                        return 1; 
                    }
                }
            }
        }
        //equal 
        return 0; 
    }
    if (isPositive && !b.isPositive) {
        return 1; 
    }  
    //last condition 
    return -1; 
}

/*
//  Assignment operator. (i.e., BigInt a = b;)
*/
const BigInt & BigInt::operator = (const BigInt &b){

    /************* You complete *************/  
    base = b.base; 
    isPositive = b.isPositive; 
    vec = b.vec; 
    return *this; 
}

/*
//  Addition assignment operator.
//    - Compute a = a + b.
*/
const BigInt & BigInt::operator += (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    //if signs are different:
    if (isPositive != b.isPositive) {
        if (isPositive) {
            BigInt temp = b; 
            temp.isPositive = true; 
            *this -= temp; 
            if (vec[0] == 0 && vec.size() == 1) {
                isPositive = true; 
            }
        }
        else {
            isPositive = true; 
            *this -= b; 
            if (vec[0] == 0 && vec.size() == 1) {
                isPositive = true; 
            }
            else {
                isPositive = !isPositive; 
            }
        }
        return *this;    
    }
    else {
        //signs are the same
        unsigned int largeInt = max(vec.size(), b.vec.size()); 
        int carry = 0; 
        for (unsigned int i = 0; i < largeInt; i++) {
            int num = 0; 
            int bNum = 0;
            //if possible, get the next num from this and b
            if (i < vec.size()) {
                num = vec[i]; 
            }
            if (i < b.vec.size()) {
                bNum = b.vec[i]; 
            }
            //add the numbers together
            int sum = num + bNum + carry; 
            //calculate the carry 
            carry = sum/base; 
            if (i < vec.size()) {
                vec[i] = sum % base; 
            }
            else {
                vec.push_back(sum % base); 
            }
        }
        if (carry) {
            vec.push_back(1); 
        }
    }
    if (to_int() == 0) {
        isPositive = true; 
    }
    return *this; 
}

/*
//  Subtraction assignment operator.
//    - Compute a = a - b
*/
const BigInt & BigInt::operator -= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    if (isPositive != b.isPositive) {
        if (isPositive) {
            BigInt temp = b; 
            temp.isPositive = true; 
            *this += temp; 
            if (vec[0] == 0 && vec.size() == 1) {
                isPositive = true; 
            }
        }
        else {
            isPositive = true; 
            *this += b; 
            if (vec[0] == 0 && vec.size() == 1) {
                isPositive = true; 
            }
            else {
                isPositive = !isPositive; 
            }
        }
        return *this;    
    }
    
    else {
        //same signs
        BigInt temp = *this; 
        unsigned int largeInt = max(vec.size(), b.vec.size()); 
        int carry = 0; 
        for (unsigned int i = 0; i < largeInt; i++) {
            int top = 0; 
            int bottom = 0; 
            //define top and bottom for subtraction
            if ((*this < b && isPositive) || (*this >= b && !isPositive)) {
                if (i < vec.size()) {
                    bottom = vec[i]; 
                }
                if (i < b.vec.size()){
                    top = b.vec[i]; 
                }
            }
            else {
                if (i < vec.size()) {
                    top = vec[i]; 
                }
                if (i < b.vec.size()) {
                    bottom = b.vec[i]; 
                }
            }
            int dif = top - bottom + base + carry; 
            carry = dif/base - 1; 
            if (i < vec.size()) {
                vec[i] = dif % base; 
            }
            else {
                vec.push_back(dif % base); 
            }
        }
        isPositive = temp >= b; 
    }
    int i = vec.size() - 1; 
    while (vec[i] == 0 && i > 0) {
        vec.pop_back(); 
        i--; 
    }
    return *this; 
}
/*
//  Multiplication assignment operator.
//    - Compute a = a * b;
*/
const BigInt & BigInt::operator *= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    /************* You complete *************/
    
    //BC
    BigInt zero(0, base); 
    if (*this == zero || b == zero) {
        *this = zero; 
        return *this; 
    }
    //determine sign
    bool resultSign; 
    if (isPositive != b.isPositive) {
        resultSign = false; 
    }
    else {
        resultSign = true; 
    }
    
    BigInt one(1, base); 
    BigInt negone(-1, base); 
    if (b.vec.size() == 1 && b.vec[0]==1) {
        *this = *this; 
        isPositive = resultSign; 
        return *this; 
    }
    else if (vec.size() == 1 && vec[0] == 1) {
        vec = b.vec; 
        isPositive = resultSign; 
        return *this; 
    }
    
    BigInt tempSum(0, base); 
    int carry = 0; 
    int product = 0; 
    for (size_t i = 0; i < b.vec.size(); i++) {
        string buffer(i, '0'); 
        BigInt temp(buffer, base); 
        for (size_t j = 0; j < vec.size(); j++) {
            product = (b.vec[i]*vec[j]) + carry; 
            carry = product / base; 
            temp.vec.push_back(product%base); 
        }
        if (carry != 0) {
            temp.vec.push_back(carry); 
        }
        tempSum += temp; 
        carry = 0; 
    }
    *this = tempSum; 
    isPositive = resultSign; 
    return *this; 
}

/*
//  Division assignment operator.
//    - Call 'divisionMain' to compute a = a / b;
*/
const BigInt & BigInt::operator /= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
    BigInt quotient(base); 
    BigInt remainder(base); 
    divisionMain(b, quotient, remainder); 
    *this = quotient; 
    return *this; 

}

/*
//  Modulus assignment operator.
//    - Call 'divisionMain' to compute a = a % b.
//    - Note: remainder takes the sign of the dividend.
*/
const BigInt & BigInt::operator %= (const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    /************* You complete *************/
    BigInt quotient(base); 
    BigInt remainder(base); 
    divisionMain(b, remainder, quotient); 
    *this = quotient; 
    return *this; 
    
}

/*
//  Main function for the Division and Modulus operator.
//     - Compute (q)uotient and (r)emainder: a = (b * q) + r.
//     - Note: NO fraction. This should behave like integer division
//             where 2/10 = 0, not 0.2
*/
void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){

    /************* You complete *************/  
    
    bool resultSign; 
    if (isPositive != b.isPositive) {
        resultSign = false; 
    }
    else {
        resultSign = true; 
    }
    //need a and b positive
    bool originalsignofA = isPositive; 
    isPositive = true; 
    //copy b and change its sign 
    BigInt copyB = b; 
    copyB.isPositive = true; 
    
    BigInt zero(0, base); 
    //BC
    if (vec.size() == 1 && vec[0] == 0) {
        quotient = zero; 
        quotient.isPositive = true; 
        remainder = zero; 
        remainder.isPositive = true; 
        return; 
    }
    else if (b.vec.size() == 1 && b.vec[0] == 1) {
        quotient = *this; 
        quotient.isPositive = resultSign; 
        remainder = zero; 
        remainder.isPositive = true; 
        return; 
    }
    else if (*this == b) {
        quotient = BigInt(1, base); 
        quotient.isPositive = resultSign; 
        remainder = zero; 
        remainder.isPositive = true; 
        return; 
    }
    else if (*this < copyB) {
        quotient = zero; 
        quotient.isPositive = true; 
        remainder = *this; 
        remainder.isPositive = originalsignofA; 
        return; 
    }
    //long division 
    int position = vec.size() - 1; 
    BigInt seq(vec[position], base); 
    while (seq < copyB) {
        position -= 1; 
        seq.vec.insert(seq.vec.begin(), vec[position]); 
    }
    
    while (position >= 0){
        int times = 0; 
        while (seq >= copyB) {
            seq -= copyB; 
            times += 1; 
        }
    
        quotient.vec.insert(quotient.vec.begin(), times); 
        if (seq.vec.size()== 1 && seq.vec[0] == 0) {
            seq.vec.clear(); 
        }
        if (position - 1 >= 0) {
            seq.vec.insert(seq.vec.begin(), vec[position-1]); 
        }
        position -= 1; 
    }
    //check if empty 
    if (seq.vec.size()== 0) {
        remainder.vec.push_back(0); 
        remainder.isPositive = true; 
    }
    else {
        remainder = seq; 
        remainder.isPositive = originalsignofA; 
    }
    quotient.isPositive = resultSign; 
                 
}


/*
//  Exponentiation assignment function.
//     - Compute a BigInt whose value is a = pow(a,b).
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    //Don’t convert to an int b.to_int()
    BigInt zero(0, base); 
    BigInt one(1, base); 
    BigInt two(2, base); 
    BigInt res(*this); 
    BigInt exp = b;  
    bool even; 
    
    if (b.vec.size()== 1 && b.vec[0] == 0) {
        *this = one; 
        return *this; 
    }
    if (b== one) {
        return *this; 
    }
    BigInt a = one; 
    while (exp > one) {
       even = ((exp % two).to_int() == 0); 
        if (even) {
            res *= res; 
        }
        else {
            a *= res; 
            exp -= one; 
            res *= res; 
        }
        exp /= two; 
    }
    res *= a; 
    *this = res; 
    return *this; 
}

/*
//  Modulus Exponentiation assignment function.
//     - Compute a = (a ^ b) % m.
//     - Do NOT compute a^b directly and then % m. 
//         This is too computationally expensive.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    //should not convert to an int b.to_int()
    //Instead:
    //Don’t convert to an int b.to_int()
    BigInt zero(0, base); 
    BigInt one(1, base); 
    BigInt two(2, base); 
    BigInt res(*this); 
    BigInt exp = b;  
    bool even; 
    
    if (b.vec.size()== 1 && b.vec[0] == 0) {
        *this = one; 
        return *this; 
    }
    if (b== one) {
        return *this; 
    }
    BigInt a = one; 
    while (exp > one) {
        even = ((exp % two).to_int() == 0); 
        if (even) {
            res *= res; 
            res %= m; 
        }
        else {
            a *= (res % m); 
            res *= res; 
            res %= m; 
            a %= m; 
            exp -= one; 
        }
        exp /= two; 
    }
    res *= a; 
    res %= m; 
    *this = res; 
    return *this; 
}


//----------------------------------------------------
//* Operator overloading, non-member functions
//----------------------------------------------------


//Call the += function above to compute a BigInt whose value is a + b
BigInt operator + (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a; 
    return temp += b; 
  
}
//Call the -= function above to compute a BigInt whose value is a - b
BigInt operator - (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a; 
    return temp -= b; 
  
}
//Call the *= function above to compute a BigInt whose value is a * b
BigInt operator * (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a; 
    temp *= b; 
    return temp; 
  
}

//Call the /= function above to compute a BigInt whose value is a / b
BigInt operator / (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp =a; 
    temp /= b; 
    return temp; 
  
}

//Call the %= function above to compute a BigInt whose value is a % b
BigInt operator % (const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a; 
    temp %= b; 
    return temp; 

  
}
//Call the exponentiation function above to compute a BigInt whose value is pow(a,b)
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt temp = a; 
    temp.exponentiation(b); 
    return temp; 
  
}

//Call the modulusExp function above to compute a BigInt whose value is (a ^ b) mod c
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    /************* You complete *************/
    BigInt temp = a; 
    temp.modulusExp(b, m); 
    return temp; 
  
}

//Call the compare function above to check if a == b
bool operator == (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return !(a.compare(b)); 
  
}

//Call the compare function above to check if a != b
bool operator != (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return (a.compare(b)); 
  
}

//Call the compare function above to check if a <= b
bool operator <= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return a.compare(b) == -1 || !a.compare(b); 
  
}

//Call the compare function above to check if a >= b
bool operator >= (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return a.compare(b) == 1 || !a.compare(b); 
  
}

//Call the compare function above to check if a > b
bool operator > (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return a.compare(b) == 1; 
  
}

//Call the compare function above to check if a < b
bool operator < (const BigInt &a, const BigInt &b){
  
    /************* You complete *************/
    return a.compare(b) == -1; 
  
  
}
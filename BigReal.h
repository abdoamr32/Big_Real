// FCAI-CU OOP Assignment-2 task-2
// Authors:
//Abdelrhman Amr Fathy_20210228_bondok735489@gmail.com
//Abdelrhman Ashraf El-Sayed_20210198_Abdelrhmanashrafelsayed1@gmail.com
//Mohamed Samy Sayed_20210339_Samy45790@gmail.com
// Date: 5/11/2023

#ifndef BIGREAL_H
#define BIGREAL_H

#include<iostream>
#include<string>
#include<cstring>
//#include "BigDecimalIntClass.h"
//#include "bigdecimalintclass.cpp"
using namespace std;
class BigDecimalInt{
private:
    
    char sign;
    void setNumber(string num);
    bool checkValidInput(string input);

public:
    string number;
    bool operator < (const BigDecimalInt& anotherDec);
    bool operator > (const BigDecimalInt& anotherDec);
    bool operator == (const BigDecimalInt anotherDec);
    BigDecimalInt& operator = (const BigDecimalInt& anotherDec);
    BigDecimalInt operator + (BigDecimalInt number2);

    BigDecimalInt operator - (BigDecimalInt anotherDec);

    friend ostream &operator << (ostream &out, BigDecimalInt num);
    int size();
    int Sign();
    
    

    BigDecimalInt(){}
    BigDecimalInt(string num)
    {
        setNumber(num);
    }
};


class BigReal {
    string digits = ".0";
    int dot_index = 0;

    // return true iff   abs(n1)  <  abs(n2)
    static bool is_less_than(string n1, string n2);
    // return true if str1 is valid real number
    // and may modify the value of str1
    bool is_valid_real(string& str1);
    static bool is_positive(const string& num);
    static int get_dot_index(const string& str1);
    string get_digits_afterDot();
    string get_digits_beforeDot();
    // return the sum of two real number (abs value)
    BigReal addition(BigReal n2);
    // returns the difference between two numbers
    BigReal subtraction(BigReal n2);

public:
    BigReal(string real_number);
    BigReal(double real_number = 0.0);
    BigReal(const BigDecimalInt& bigDec);
    BigReal (const BigReal& other);
    BigReal (BigReal&& other);
    BigReal& operator= (const BigReal& other);
    BigReal& operator= (BigReal&& other);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);

    friend ostream& operator<< (ostream& out, const BigReal& num) ;
    friend istream& operator >> (istream& in, BigReal& num);

    
    int size();
    int sign();

};

#endif //BIGREAL_H

// FCAI-CU OOP Assignment-2 task-2
// Authors:
//Abdelrhman Amr Fathy_20210228_bondok735489@gmail.com
//Abdelrhman Ashraf El-Sayed_20210198_Abdelrhmanashrafelsayed1@gmail.com
//Mohamed Samy Sayed_20210339_Samy45790@gmail.com
// Date: 5/11/2023

#include "BigReal.h"
#include<iostream>
#include<string>
#include<cstring>
#include<regex>
#include<deque>

using namespace std;


// regex function that checks the validation of the input.
bool BigDecimalInt :: checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void BigDecimalInt :: setNumber(string num)
{
    bool validNumber = checkValidInput(num);
    if(validNumber)
    {
        number = num;
        if(number[0] == '+')
        {
            number.erase(0,1);
            sign = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            sign = '-';
        }
        else
        {
            sign = '+';
        }
    }
}


// operator < overloading function.
bool BigDecimalInt :: operator < (const BigDecimalInt& anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(sign == '-' && anotherDec.sign == '+')
    {
        return true;
    }
    else if(sign == '+' && anotherDec.sign == '-')
    {
        return false;
    }
    else if(sign == '+' && anotherDec.sign == '+')
    {
        return comp1 < comp2;
    }
    else
    {
        return comp1 > comp2;
    }
}

// operator > overloading function.
bool BigDecimalInt :: operator > (const BigDecimalInt &anotherDec)
{
    if (*this == anotherDec){
        return false;
    }
    return *this < anotherDec;

   
}

// operator == overloading function.
bool BigDecimalInt :: operator == (const BigDecimalInt anotherDec)
{
    if (sign == anotherDec.sign && number == anotherDec.number)
    {
        return true;

    }
    else
    {
        return false;
    }
}
// operator = overloading function.
BigDecimalInt& BigDecimalInt :: operator = (const BigDecimalInt &anotherDec)
{
    sign = anotherDec.sign;
    number = anotherDec.number;
    return *this;
}

// // operator + overloading function.
BigDecimalInt BigDecimalInt :: operator + (BigDecimalInt number2)
{
    BigDecimalInt result;
    char signNumber1 = sign, signNumber2 = number2.sign;

    string num1 = number, num2 = number2.number;
    while (num1.length() < num2.length()){
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()){
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2){
        result.sign = signNumber1;

        auto it1 = num1.rbegin();
        auto it2 = num2.rbegin();
        int carry = 0;

        while (it1 != num1.rend()){
            int twoDigitsSum;
            carry = 0;
            twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
            if(twoDigitsSum >= 10){
                carry = 1;
            }
            result.number = char((twoDigitsSum % 10) + '0') + result.number;
            *(it1 + 1) = char (((*(it1 + 1) - '0') + carry) + '0');
            it1++;
            it2++;
        }

        if(carry){
            result.number = char ((carry) + '0') + result.number;
        }

    }else{
        deque<long long> d;
        string res = "";

        if (num1 < num2)
        {
            swap(num1, num2);
            swap(signNumber1,signNumber2);
        }

        for (long long i = num1.length() - 1; i >= 0; i--)
        {
            if (num1[i] < num2[i])
            {
                num1[i] = char (((num1[i] - '0') + 10) + '0');
                num1[i - 1] = char (((num1[i - 1] - '0') - 1) + '0');
                d.push_front((num1[i] - '0') - (num2[i] - '0'));
            }
            else
            {
                d.push_front((num1[i] - '0') - (num2[i] - '0'));
            }
        }

        bool right = false;
        for (auto i : d)
        {
            res += to_string(i);
        }

        for (long long i = 0; i < res.length(); i++)
        {
            if (res[i] != '0')
            {
                right = true;
            }
            if (!right && res[i] == '0')
            {
                res.erase(i, 1);
                i--;
            }
        }
        if(res.empty())res="0";
        result.sign = signNumber1;
        result.number = res;
    }
    return result;
}

// operator - overloading function.
BigDecimalInt BigDecimalInt :: operator - (BigDecimalInt anotherDec)
{
    BigDecimalInt obj;
    string strmin = "", res = "";
    deque<long long> d;


    if (number.length() > anotherDec.number.length())
    {
        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++)
        {
            strmin += '0';
        }
        strmin += anotherDec.number;
        anotherDec.number = strmin;
    }
    else if (number.length() < anotherDec.number.length())
    {
        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++)
        {
            strmin += '0';
        }
        strmin += number;
        number = strmin;
    }
    bool ok = false;
    if (number < anotherDec.number)
    {
        swap(number, anotherDec.number);
        ok = true;
    }
    bool nv = true;
    if (sign == '-' && anotherDec.sign == '-')
    {
        for (long long i = number.length() - 1; i >= 0; i--)
        {
            if (number[i] < anotherDec.number[i])
            {
                number[i] = char (((number[i] - '0') + 10) + '0');
                number[i - 1] = char (((number[i - 1] - '0') - 1) + '0');
                d.push_front((number[i] - '0') - (anotherDec.number[i] - '0'));
            }
            else
            {
                d.push_front((number[i] - '0') - (anotherDec.number[i] - '0'));
            }
        }
        ok = !ok;
    }
    else if ((sign == '-' || anotherDec.sign == '-'))
    {
        string num1 = number, num2 = anotherDec.number;
        auto it1 = num1.rbegin();
        auto it2 = num2.rbegin();
        int carry = 0;

        while (it1 != num1.rend())
        {
            int twoDigitsSum;
            carry = 0;
            twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
            if (twoDigitsSum >= 10)
            {
                carry = 1;
            }
            res = char((twoDigitsSum % 10) + '0') + res;
            *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
            it1++;
            it2++;
        }

        if (carry)
        {
            res = char((carry) + '0') + res;
        }
        if (sign == '-')
        {
            nv = false;
        }
    }
    else
    {
        for (long long i = number.length() - 1; i >= 0; i--)
        {
            if (number[i] < anotherDec.number[i])
            {
                number[i] = char (((number[i] - '0') + 10) + '0');
                number[i - 1] = char (((number[i - 1] - '0') - 1) + '0');
                d.push_front((number[i] - '0') - (anotherDec.number[i] - '0'));
            }
            else
            {
                d.push_front((number[i] - '0') - (anotherDec.number[i] - '0'));
            }
        }
        nv = true;
    }
    if (!nv || ok) {
        obj.sign = '-';
    }else{
        obj.sign = '+';
    }
    bool right = false;
    for (auto i : d)
    {
        res += to_string(i);
    }
    for (long long i = 0; i < res.length(); i++)
    {
        if (res[i] != '-' && res[i] != '0')
        {
            right = true;
        }
        if (!right && res[i] == '0')
        {
            res.erase(i, 1);
            i--;
        }
    }
    if(res.empty())res="0";
    obj.number = res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt :: size()
{
    return number.size();
}

int BigDecimalInt :: Sign()
{
    if (sign == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// operator << overloading function.
ostream &operator << (ostream &out, BigDecimalInt num)
{
    if(num.sign == '+')
    {
        out << num.number << endl;
    }
    else
    {
        out << num.sign << num.number << endl;
    }
    return out;
}





/// constructors
//-------------------------------------------------------------------------------------------------------------------//

BigReal::BigReal(string real_number){
    if (is_valid_real(real_number)){
        digits = real_number;
        dot_index = get_dot_index(digits);
    }
    else{
        cerr << "invalid BigReal number! \n"<< real_number << '\n';
        exit(1);
    }
}


BigReal::BigReal(double real_number){
    string tmp = to_string(real_number);
    if (is_valid_real(tmp)){
        digits = tmp;
        dot_index = get_dot_index(digits);
    }
    else{
        cerr << "invalid BigReal number! \n"<< real_number << '\n';
        exit(1);
    }
}


BigReal::BigReal(const BigDecimalInt& bigInteger){
    digits = bigInteger.number;
    digits += ".0";
    dot_index = get_dot_index(digits);
}

// copy constructor
BigReal::BigReal (const BigReal &other){
    digits = other.digits;
    dot_index = other.dot_index;
}

// move constructor
BigReal::BigReal(BigReal &&other) {
    digits = other.digits;
    dot_index = other.dot_index;
    other.digits.clear();
    other.dot_index = 0;
}



//-------------------------------------------------------------------------------------------------------------------//


/// operators overloading
//-------------------------------------------------------------------------------------------------------------------//

// assignment operator
BigReal& BigReal::operator= (const BigReal& other){
    digits = other.digits;
    dot_index = other.dot_index;
    return *this;
}

// move assignment
BigReal& BigReal::operator= (BigReal&& other){
    if (this != &other){
        digits = other.digits;
        dot_index = other.dot_index;
        other.digits.clear();
        other.dot_index = 0;
    }
    return *this;
}


bool BigReal::operator< (BigReal anotherReal) {
    // +ve and +ve
    if (is_positive(digits) && is_positive(anotherReal.digits)){
        // if the decimal digits are equal check the fraction digits
        if (get_digits_beforeDot() == anotherReal.get_digits_beforeDot()){
            return is_less_than(get_digits_afterDot(), anotherReal.get_digits_afterDot());
        }
        return is_less_than(get_digits_beforeDot(), anotherReal.get_digits_beforeDot());
    }
    // -ve and -ve
    else if(!is_positive(get_digits_beforeDot()) && !is_positive(anotherReal.get_digits_beforeDot())) {
        // if the decimal digits are equal check the fraction digits
        if (get_digits_beforeDot() == anotherReal.get_digits_beforeDot()){
            return !is_less_than(get_digits_afterDot(), anotherReal.get_digits_afterDot());
        }
        return !is_less_than(get_digits_beforeDot(), anotherReal.get_digits_beforeDot());
    }
    // -ve and +ve
    else if (!is_positive(get_digits_beforeDot()) && is_positive(anotherReal.get_digits_beforeDot())) {
        //num1 is -ve
        return true;
    }
    // +ve and -ve
    else if (is_positive(get_digits_beforeDot()) && !is_positive(anotherReal.get_digits_beforeDot())) {
        //num2 is -ve
        return false;
    }
    return false;
}


bool BigReal::operator> (BigReal anotherReal) {
    if (anotherReal < *this){
        return true;
    }
    return false;
}


bool BigReal::operator== (BigReal anotherReal){
    if (strcmp(anotherReal.get_digits_beforeDot().c_str(), get_digits_beforeDot().c_str()) == 0) {
        if (strcmp(anotherReal.get_digits_afterDot().c_str(), get_digits_afterDot().c_str()) == 0){
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}


ostream& operator<< (ostream& out, const BigReal& num) {
    out << num.digits;
    return out;
}


istream& operator>> (istream& in, BigReal& num){
    string tmp = " ";
    in >> tmp;
    if (num.is_valid_real(tmp)) {
        num.digits = tmp;
        num.dot_index = num.get_dot_index(tmp);
        return in;
    }
    else{
        cerr << "invalid BigReal number! \n"<< tmp << '\n';
        exit(1);
    }
}


BigReal BigReal::operator+(BigReal &other) {
    BigReal result;
    // if pos + pos
    if (is_positive(digits) && is_positive(other.digits)){
        // just add the two nums
        result = addition(other);
    }
    // if negative + negative
    // add the two nums, then insert -ve to the result
    else if(!is_positive(digits) && !is_positive(other.digits)){
        result = addition(other);
        result.digits.insert(0, 1, '-');
        result.dot_index++;
    }
    // if we add numbers with different signs
    // get the difference between the two nums
    // then add the sign of the abs(greater number) to the final result
    else {
        char sign = '+';
        // make the sign as the greater num is
        if (this->digits[0] == '-'){
            this->digits.erase(0, 1);
            sign = (this->digits > other.digits) ? '-' : '+';
            this->digits.insert(0, 1, '-');
        }
        else if (other.digits[0] == '-'){
            other.digits.erase(0, 1);
            sign = (other.digits > this->digits) ? '-' : '+';
            other.digits.insert(0, 1, '-');
        }
        // get the difference between n1 and n2
        result = subtraction(other);
        // insert the sign of the abs(greater num) to the result
        if (sign == '-'){
            result.digits.insert(0, 1, '-');
            result.dot_index++;
        }
    }
    return result;
}


BigReal BigReal::operator-(BigReal &other) {
    // if positive - positive
    if (is_positive(digits) && is_positive(other.digits)){
        BigReal negative_other = other;
        negative_other.digits.insert(0, 1, '-');
        negative_other.dot_index++;
        return *this + negative_other;
    }
    // if negative - positive
    else if (!is_positive(digits) && is_positive(other.digits)){
        BigReal negative_other = other;
        negative_other.digits.insert(0, 1, '-');
        negative_other.dot_index++;
        return *this + negative_other;
    }
    // if negative - negative
    else if (!is_positive(digits) && !is_positive(other.digits)){
        BigReal pos_other = other;
        pos_other.digits.erase(0, 1);
        pos_other.dot_index--;
        return *this + pos_other;
    }
    // if positive - negative
    else if (is_positive(digits) && !is_positive(other.digits)){
        BigReal pos_other = other;
        pos_other.digits.erase(0, 1);
        pos_other.dot_index--;
        return *this + pos_other;
    }
    return *this;
}

//-------------------------------------------------------------------------------------------------------------------//



/// private methods
//-------------------------------------------------------------------------------------------------------------------//

bool BigReal::is_positive(const string & num){
    return num[0] != '-';
}

// return true if str1 is valid real number
// and may modify the value of str1 if it's in the form of (1.) (1.) (1)
bool BigReal::is_valid_real(string& str1){
    regex valid_real_regex;
    // group #1 for the sign, #2 for the beforeDot digits, #3 for the dot, #4 for the digits afterDot
    // #5 for numbers in case of only integers, #6 for integers sign
    valid_real_regex = "^([-\\+])?([0-9])*(\\.)([0-9])*$|(^([-\\+])?[0-9]+)$";
    smatch group;
    if (!regex_match(str1, group, valid_real_regex)){
        return false;
    }
    // couldn't handle this case in regex
    if (str1 == "."){
        return false;
    }
    // add the zero in case of these forms: ( .1 ) or ( 1. ) ( 1 )
    // if ( +\- .1 )
    if (group.str(2).empty() && !group.str(4).empty()){
        // if ( .1 )
        if (group.str(1).empty()){
            str1.insert(0, 1, '0');
        }// else if ( +\- .1 )
        else{
            str1.insert(1, 1, '0');
        }
    }
    // else if ( +\- 1. )
    else if (group.str(4).empty() && !group.str(3).empty()){
        str1.push_back('0');
    }
    // else if ( +\- 1 )
    if (!group.str(5).empty()){
        str1.push_back('.');
        str1.push_back('0');
    }
    return true;
}


int BigReal::get_dot_index(const string & str1){
    for (int i = 0; i < str1.size(); ++i) {
        if (str1[i] == '.'){
            return i;
        }
    }
    return 0;
}

// returns true iff  abs(n1)  <  abs(n2)
bool BigReal::is_less_than(string n1, string n2){
    // remove -ve if it's found
    if (n1[0] == '-'){
        n1.erase(0, 1);
    }
    if (n2[0] == '-'){
        n2.erase(0, 1);
    }
    if (n1.size() < n2.size()) {
        return true;
    }
    else if (n1.size() == n2.size()) {
        return n1 < n2;
    }
    // else n2.size() > n1.size()
    else{
        return false;
    }
}


int BigReal::size() {
    return (digits.size() - 1);
}

// returns the sign of the number
int BigReal::sign() {
    return (digits[0] == '-' ? '-' : '+');
}


string BigReal::get_digits_afterDot(){
    string after = digits;
    return after.erase(0,dot_index + 1);
}


string BigReal::get_digits_beforeDot(){
    string before = digits;
    return before.erase(dot_index,digits.size() - dot_index);
}

// return the sum of two real number (abs value)
BigReal BigReal::addition(BigReal n2){
    // final result
    BigReal result;
    // make a copy of *this to avoid changing its value, n2 is also a copy
    BigReal n1 = *this;
    // delete -ve sign
    if (n1.sign() == '-'){
        n1.digits.erase(0, 1);
        n1.dot_index--;
    }
    if (n2.sign() == '-'){
        n2.digits.erase(0, 1);
        n2.dot_index--;
    }
    // sum of numbers before dot
    BigDecimalInt beforeDot_result = BigDecimalInt(n1.get_digits_beforeDot())
                                     + BigDecimalInt(n2.get_digits_beforeDot());
    // n of digits after dot
    int sz1 = n1.get_digits_afterDot().size();
    int sz2 = n2.get_digits_afterDot().size();

    // make the size of digits afterDot same for n1 and n2
    if (sz1 > sz2){
        // insert zeros to end of the shorter number
        for (int i = 0; i < sz1 - sz2; ++i) {
            n2.digits.push_back('0');
        }
    }
    else if (sz1 < sz2){
        // insert zeros to end of the shorter number
        for (int i = 0; i < sz2 - sz1; ++i) {
            n1.digits.push_back('0');
        }
    }
    // then add the two nums
    // the sum of numbers after dot
    BigDecimalInt afterDot_result = BigDecimalInt(n1.get_digits_afterDot())
                                    + BigDecimalInt(n2.get_digits_afterDot());
    // if there is a carry from the sum (the left-most digit), add it to the beforeDot digits
    if (afterDot_result.size() > n1.get_digits_afterDot().size()){
        BigDecimalInt tmp(to_string(afterDot_result.number[0] - '0'));
        afterDot_result.number.erase(0, 1);
        beforeDot_result = beforeDot_result + tmp;
    }
    // final result
    result.digits = beforeDot_result.number + '.' + afterDot_result.number;
    result.dot_index = beforeDot_result.number.size();
    return result;
}

// return the difference between two numbers
BigReal BigReal::subtraction(BigReal n2){
    // final result
    BigReal result;
    // make a copy of *this to avoid changing its value, n2 is also a copy
    BigReal n1 = *this;
    // delete -ve sign
    if (n1.sign() == '-'){
        n1.digits.erase(0, 1);
        n1.dot_index--;
    }
    if (n2.sign() == '-'){
        n2.digits.erase(0, 1);
        n2.dot_index--;
    }
    // MAKE n1 THE GREATER NUMBER
    if (n2 > n1){
        swap(n2, n1);
    }
    // difference between numbers before dot
    BigDecimalInt beforeDot_result = BigDecimalInt(n1.get_digits_beforeDot())
                                     - BigDecimalInt(n2.get_digits_beforeDot());
    // n of digits after dot
    int sz1 = n1.get_digits_afterDot().size();
    int sz2 = n2.get_digits_afterDot().size();

    // make the size of digits afterDot same for n1 and n2
    // ex: ( 9.07 - 8.9 ) will be ( 9.07 - 8.90 )
    if (sz1 > sz2){
        for (int i = 0; i < sz1 - sz2; ++i) {
            n2.digits.push_back('0');
        }
    }
    else if (sz2 > sz1){
        for (int i = 0; i < sz2 - sz1; ++i) {
            n1.digits.push_back('0');
        }
    }
    // digits after dot
    BigDecimalInt n1_afterDot(n1.get_digits_afterDot());
    BigDecimalInt n2_afterDot(n2.get_digits_afterDot());
    BigDecimalInt afterDot_result("0");
    // get the difference between the afterDot digits
    if (n1_afterDot > n2_afterDot){
        afterDot_result = n1_afterDot - n2_afterDot;
    }
    else if (n1_afterDot < n2_afterDot){
        // borrow one from the digits beforeDot and place it after the dot
        beforeDot_result = beforeDot_result - BigDecimalInt("1");
        n1_afterDot.number.insert(0, 1, '1');
        afterDot_result = n1_afterDot - n2_afterDot;
    }
    // add zeros to the left of afterDot result
    // ex: as the result of ( 0090 - 0070 ) = 20 , and we want it = 0020
    if (afterDot_result.size() < (sz1 > sz2 ? sz1 : sz2)){
        afterDot_result.number.insert(0,  max(sz1, sz2) - afterDot_result.size(), '0');
    }
    // final result
    result.digits = beforeDot_result.number + '.' + afterDot_result.number;
    result.dot_index = beforeDot_result.number.size();
    return result;
}

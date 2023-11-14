// FCAI-CU OOP Assignment-2 task-2
// Authors:
//Abdelrhman Amr Fathy_20210228_bondok735489@gmail.com
//Abdelrhman Ashraf El-Sayed_20210198_Abdelrhmanashrafelsayed1@gmail.com
//Mohamed Samy Sayed_20210339_Samy45790@gmail.com
// Date: 5/11/2023

#include "BigReal.h"
#include "bigreal.cpp"
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int main() {
    BigReal num1("2333333333339.1134322222222292");
    BigReal num2("-11.9000000000000000000000000000000001");

    BigReal num3;
    cout << "Enter number 3 : ";
    cin >> num3;

    cout << "num1: " << num1 << endl;
    cout << "num2: " << num2 << endl;
    cout << "num3: " << num3 << endl;
    cout<<"num1 + num2 ="<<num1 + num2<<endl;
    cout<<"num2 + num1 = "<<num2 + num1<<endl;
    cout<<"num1 - num2 = "<<num1 - num2<<endl;
    cout<<"num2 - num1 = "<<num2 - num1<<endl;


    // using BigDecInt constructor
    BigReal bigdecimal(BigDecimalInt("0110110111011124545484815187114518877111751577151501111448414848484848451147555848884851011"));

    cout << "bigReal from bigDec: " << bigdecimal << endl;

    if (num1 == num2) {
        cout << "num1 == num2\n";
    }
    if (num1 < num2) {
        cout << "num1 < num2\n";
    }
    if (num1 > num2){
        cout << "num1 > num2\n";
    }

    
    // using assignment operator
    num2 = num1;

}
#include "triple.h"
#include "operations.h"
#include "global.h"
#include <iostream>

using namespace std;

int main(int argc,char* argv[]) {
    triple number1, number2;
    triple res;
    char action;
    //setPrecision(atoi(argv[3]));
    cin >> number1 >> number2 >> action >> precision;
    switch (action) {
    case '+': res = number1 + number2; //This is for summation
        break;
    case '-': res = number1 - number2; //This is for substraction
        break;
    case '*': res = number1 * number2; //This is for multiplication
        break;
    case '/': res = number1 / number2; //This is for division
        break;
    default: cout << "No such operation retard!";
        break;
    }
    cout << res;
}


#ifndef TRIPLE_H
#define TRIPLE_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class triple {
public:
    bool negative;
    std::vector<int> integer;
    std::vector<int> floating;
    int decimal_pos;
    void input();
    void print();
    friend istream& operator>>(istream& in, triple& hf);
    friend ostream& operator<<(ostream& out, triple& hf);
    friend triple operator+(triple& a, triple& b);
    friend triple operator-(triple& a, triple& b);
    friend triple operator*(triple& a, triple& b);
    friend triple operator/(triple& a, triple& b);
    friend bool operator<(triple& a, triple& b);
    friend bool operator>(triple& a, triple& b);
    friend bool operator==(triple& a, triple& b);
    friend bool operator!=(triple& a, triple& b);
};

#endif

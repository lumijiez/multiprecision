#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "triple.h"
#include "operations.h"
using namespace std;

bool negative = false;
vector<int> integer;
vector<int> floating;
int decimal_pos = -1;

void triple::input() {
    std::string line;
    std::getline(std::cin, line);

    bool negative = false;
    if (line[0] == '-') {
        negative = true;
        line = line.substr(1);
    }

    decimal_pos = line.find('.');
    if (decimal_pos != std::string::npos) {
        std::transform(line.begin(), line.begin() + decimal_pos, std::back_inserter(integer),
            [](char c) { return c - '0'; });
        std::transform(line.begin() + decimal_pos + 1, line.end(), std::back_inserter(floating),
            [](char c) { return c - '0'; });
    }
    else {
        std::transform(line.begin(), line.end(), std::back_inserter(integer),
            [](char c) { return c - '0'; });
    }

    this->negative = negative;
}


void triple::print() {
    if (negative) cout << '-';
    for (int i : integer) cout << i;
    if (floating.size() == 0) {
        cout << ".0";
        return;
    }
    else {
        cout << '.';
        for (int x : floating) cout << x;
    }
    cout << '\n';
}

istream& operator>>(istream& in, triple& hf) {
    hf.input();
    return in;
}

ostream& operator<<(ostream& out, triple& hf) {
    hf.print();
    return out;
}

bool operator<(triple& a, triple& b) {
    if (a.negative && !b.negative) return true;
    if (!a.negative && b.negative) return false;
    if (a.negative && b.negative) {
        swap(a, b);
    }
    int int_size_a = a.integer.size();
    int int_size_b = b.integer.size();
    if (int_size_a != int_size_b) {
        return int_size_a < int_size_b;
    }
    for (int i = 0; i < int_size_a; ++i) {
        if (a.integer[i] != b.integer[i]) {
            return a.integer[i] < b.integer[i];
        }
    }
    int float_size_a = a.floating.size();
    int float_size_b = b.floating.size();
    if (float_size_a != float_size_b) {
        return float_size_a < float_size_b;
    }
    for (int i = 0; i < float_size_a; ++i) {
        if (a.floating[i] != b.floating[i]) {
            return a.floating[i] < b.floating[i];
        }
    }
    return false;
}

bool operator>(triple& a, triple& b) {
    if (a.negative && !b.negative) return false;
    if (!a.negative && b.negative) return true;
    if (a.negative && b.negative) {
        swap(a, b);
    }
    int int_size_a = a.integer.size();
    int int_size_b = b.integer.size();
    if (int_size_a != int_size_b) {
        return int_size_a < int_size_b;
    }
    for (int i = 0; i < int_size_a; ++i) {
        if (a.integer[i] != b.integer[i]) {
            return a.integer[i] > b.integer[i];
        }
    }
    int float_size_a = a.floating.size();
    int float_size_b = b.floating.size();
    if (float_size_a != float_size_b) {
        return float_size_a > float_size_b;
    }
    for (int i = 0; i < float_size_a; ++i) {
        if (a.floating[i] != b.floating[i]) {
            return a.floating[i] > b.floating[i];
        }
    }
    return false;
}

bool operator==(triple& a, triple& b) {
    if (a.integer == b.integer && a.floating == b.floating) return true;
    return false;
}

bool operator!=(triple& a, triple& b) {
    if (a.integer == b.integer && a.floating == b.floating) return false;
    return true;
}



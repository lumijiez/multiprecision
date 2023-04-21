#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "triple.h"
#include "global.h"
#include "operations.h"

using namespace std;

triple operations::add(triple& a, triple& b) {
        if (a.negative && !b.negative) {
            a.negative = false;
            triple res = b - a;
            return res;
        }
        if (!a.negative && b.negative) {
            b.negative = false;
            triple res = a - b;
            return res;
        }
        if (a.negative && b.negative) {
            a.negative = false;
            b.negative = false;
            triple res = a + b;
            res.negative = true;
            a.negative = true;
            b.negative = true;
            return res;
        }
    triple res;
    int next = 0;
    int int_size = max(a.integer.size(), b.integer.size());
    int float_size = max(a.floating.size(), b.floating.size());
    vector<int> int_result;
    vector<int> floating_result;
    while (a.integer.size() < int_size)
        a.integer.insert(a.integer.begin(), 0);
    while (b.integer.size() < int_size)
        b.integer.insert(b.integer.begin(), 0);
    while (a.floating.size() < float_size)
        a.floating.push_back(0);
    while (b.floating.size() < float_size)
        b.floating.push_back(0);

    for (auto av = a.floating.rbegin(), bv = b.floating.rbegin(); av != a.floating.rend() && bv != b.floating.rend(); ++av, ++bv) {
        int sum = *av + *bv + next;
        floating_result.insert(floating_result.begin(), sum % 10);
        next = sum / 10;
    }
    for (auto av = a.integer.rbegin(), bv = b.integer.rbegin(); av != a.integer.rend() && bv != b.integer.rend(); ++av, ++bv) {
        int sum = *av + *bv + next;
        int_result.insert(int_result.begin(), sum % 10);
        next = sum / 10;
    }
    if (next != 0) int_result.insert(int_result.begin(), next);
    res.integer = int_result;
    res.floating = floating_result;
    return res;
}

triple operations::subtract(triple& a, triple& b) {
    triple res;
    int borrow = 0;
    bool negative = false;
    int int_size = max(a.integer.size(), b.integer.size());
    int float_size = max(a.floating.size(), b.floating.size());
    vector<int> int_result;
    vector<int> floating_result;
    while (a.integer.size() < int_size)
        a.integer.insert(a.integer.begin(), 0);
    while (b.integer.size() < int_size)
        b.integer.insert(b.integer.begin(), 0);
    while (a.floating.size() < float_size)
        a.floating.push_back(0);
    while (b.floating.size() < float_size)
        b.floating.push_back(0);

    if (a < b) { 
        swap(a, b);
        negative = true;
    }

    if (a.negative && !b.negative) {
        res = a + b;
        res.negative = true;
        return res;
    }
    else if (!a.negative && b.negative) {
        res = a + b;
        res.negative = false;
        return res;
    }

    for (int i = float_size - 1, j = float_size - 1; i >= 0 || j >= 0; i--, j--) {
        int digit1 = (i >= 0) ? a.floating[i] : 0;
        int digit2 = (j >= 0) ? b.floating[j] : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else borrow = 0;
        floating_result.insert(floating_result.begin(), diff);
    }

    for (int i = int_size - 1, j = int_size - 1; i >= 0 || j >= 0; i--, j--) {
        int digit1 = (i >= 0) ? a.integer[i] : 0;
        int digit2 = (j >= 0) ? b.integer[j] : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else borrow = 0;
        int_result.insert(int_result.begin(), diff);
    }

    while (!int_result.empty() && int_result.front() == 0) int_result.erase(int_result.begin());
    while (!floating_result.empty() && floating_result.back() == 0) floating_result.pop_back();
    if (int_result.empty()) {
        int_result.push_back(0);
    }
    res.negative = negative;
    res.integer = int_result;
    res.floating = floating_result;
    return res;
}

triple operations::multiply(triple& a, triple& b) {
    triple res;
    vector<int> int_result, floating_result;
    vector<int> num1, num2;
    int decimal = a.floating.size() + b.floating.size();
    num1 = a.integer;
    num2 = b.integer;

    num1.insert(num1.end(), a.floating.begin(), a.floating.end());
    num2.insert(num2.end(), b.floating.begin(), b.floating.end());

    vector<int> result(num1.size() + num2.size());

    if (a.negative && !b.negative || !a.negative && b.negative) res.negative = true;

    for (int i = a.integer.size() + a.floating.size() - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = b.integer.size() + b.floating.size() - 1; j >= 0; j--) {
            int prod = num1[i] * num2[j] + result[i + j + 1] + carry;
            result[i + j + 1] = prod % 10;
            carry = prod / 10;
        }
        result[i] += carry;
    }

    int i = 0;
    for (auto it = result.rbegin(); it != result.rend() && i < decimal; it++, i++) 
        floating_result.insert(floating_result.begin(), *it);
    i = 0;
    for (auto it = result.begin(); it != result.end() && i < result.size() - decimal; it++, i++) 
        int_result.push_back(*it);
 
    while (!int_result.empty() && int_result.front() == 0) int_result.erase(int_result.begin());
    while (!floating_result.empty() && floating_result.back() == 0) floating_result.pop_back();
    res.integer = int_result;
    res.floating = floating_result;
    return res;
}

triple operations::divide(triple& a, triple& b) {
    vector<int> dividend;
    vector<int> divisor;
    for (auto i : a.integer) dividend.push_back(i);
    for (auto i : a.floating) dividend.push_back(i);
    for (auto i : b.integer) divisor.push_back(i);
    for (auto i : b.floating) divisor.push_back(i);
    if (a.floating.size() > b.floating.size()) {
        int add = a.floating.size() - b.floating.size();
        while (add--) divisor.push_back(0);
    }
    if (a.floating.size() < b.floating.size()) {
        int add = b.floating.size() - a.floating.size();
        while (add--) dividend.push_back(0);
    }

    triple tempb;
    int count = 0;
    triple result;
    result.integer = { 0 };
    result.floating = {};

    triple one;
    triple ten;
    triple zero;
    zero.integer = { 0 };
    zero.floating = { 0 };
    ten.integer = { 1, 0 };
    ten.floating = {};
    one.integer = { 1 };
    one.floating = { 0 };

    triple res = a;
    int currentPrecision = 0;
    while (!(res < b)) {
        tempb = b;
        res = res - tempb;
        if (!res.negative) result = result + one;
    }
    result.floating.clear();
    bool first = false;
    res.negative = false;
    while (currentPrecision < precision) {
        res.negative = false;
        while (res < b && res != zero && res != b) {
            if (res.integer.empty() && res.floating.empty() || (res.integer.size() == 1 && res.integer.at(0) == 0) && (res.floating.size() == 1 && res.floating.at(0) == 0)) {
                break;
            }
            if (first) result.floating.push_back(0);
            first = true;
            res = res * ten;
        }
        first = false;
        count = 0;
        while (!(res < b) && !(res == zero)) {
            tempb = b;
            res = res - tempb;
            count++;
        }
        res.negative = false;
        if (count != 0) result.floating.push_back(count);
        currentPrecision++;
    }
    return result;
}


triple operator+(triple& a,triple& b) {
    operations op;
    triple res = op.add(a, b);
    return res;
}

triple operator-(triple& a, triple& b) {
    operations op;
    triple res = op.subtract(a, b);
    return res;
}

triple operator*(triple& a, triple& b) {
    operations op;
    triple res = op.multiply(a, b);
    return res;
}

triple operator/(triple& a, triple& b) {
    operations op;
    triple res = op.divide(a, b);
    return res;
}

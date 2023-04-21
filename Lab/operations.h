#include <vector>
#include <string>
#include <algorithm>
#include "triple.h"

class operations {
public:
    triple add(triple& a, triple& b) ;
    triple subtract(triple& a, triple& b);
    triple multiply(triple& a, triple& b);
    triple divide(triple& a, triple& b);
    friend triple operator+(triple& a, triple& b);
    friend triple operator-(triple& a, triple& b);
};

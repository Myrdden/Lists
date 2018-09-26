#include "string.h"
#include "stringio.h"
#include <iostream>
using std::cin;
using std::cout;

int main()
{   String a, b, c, d, e, out;
    a = "abcdabcdabcdabcee";
    a.intercalate('.', a);
    cout << a << "\n";
}
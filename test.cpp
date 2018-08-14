#include "list.h"
#include <iostream>
using namespace L;
int main()
{   int i[5];
    i[0] = 1;
    i[1] = 2;
    i[2] = 3;
    i[3] = 4;
    i[4] = 5;
    List<int> a;
    List<int> b(i, 5);
    77 * b;
    b + 6;
    b + 7;
    drop(2,b);
    77 * b;
    /*std::cout << b.length() << "\n";
    std::cout << b[0] << ',' << b[1] << ',' << b[2] << ',' << b[3] << ',' << b[4] << ',' << b[5] << ',' << b[6] << "\n";
    std::cout << a.length() << "\n";
    std::cout << b.length() << "\n";
    std::cout << b.count() << "\n";
    b.squish();
    std::cout << b.length() << "\n";
    std::cout << b.count() << "\n";
    std::cout << b[0] << ',' << b[1] << ',' << b[2] << ',' << b[3] << ',' << b[4] << ',' << b[5] << ',' << b[6] << "\n";
    take(4, b, a);
    std::cout << a.length() << "\n";
    std::cout << a.count() << "\n";
    std::cout << a[0] << ',' << a[1] << ',' << a[2] << ',' << a[3] << '\n';*/
    std::cout << isElem(4, b) << isElem(8, b) << '\n';
}
#include "list.h"
#include "listio.hpp"
#include <iostream>
using std::cin;
using std::cout;

int main()
{   List<int> a, b, c;
    for(int i = 1; i < 6; i++)
        {a += i;}
    for(int i = 3; i < 5; i++)
        {b += i;}
    c += 1; c += 3; c += 5;
    for(Node<int>* it = a.begin(); it != a.end(); it++)
    {cout << it->at << "\n";}
}
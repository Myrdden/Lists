#ifndef LISTIO_H
#define LISTIO_H
#include "list.h"
#include <iostream>

template <class T>
std::ostream& operator<<(std::ostream& out, const List<T> &xs)
{   if(!xs.null())
    {   out << xs.head();
        out << xs.body();
    }
    return out;
}
#endif
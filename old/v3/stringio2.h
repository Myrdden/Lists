#ifndef STRINGIO_H
#define STRINGIO_H
#include "string.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const Substring &xs)
{   if(xs.null())
        {return out;}
    else
    {   out << xs.head();
        out << xs.body();
        return out;
    }
}
/*
std::istream& operator>>()
{}*/
#endif
#include "string.h"
#include "stringio.h"
#include "list.h"
#include "listio.hpp"
#include <fstream>
#include <iostream>
using std::ifstream;
using std::hash;
using std::cin;
using std::cout;

unsigned hashStr(const String &xs)
{   hash<char> hash;
    unsigned hashed = 0;
    for(int i = 0; i < xs.size(); i++)
        {hashed = hashed + hash(xs[i]);}
    return hashed;
}

void readBook(List<String> &book, int &bookNum)
{   String name, temp, metatemp, asdfghjkl;
    //ifstream file;
    cout << "Enter file name: ";
    cin >> name;
    /*if(name.elem("Potter"))
        {file.open("Potter.txt");}
    else if(name.elem("check"))
        {file.open("check.txt");}*/
    ifstream file(name.cStr());
    if(file.good())
    {   while(getline(file, temp))
        {   if(temp.elem(' '))
            {   while(!temp.null())
                {   temp.word(temp, metatemp);
                    metatemp.lower(metatemp);
                    metatemp.filter("==", ",.\'\";-:?!()\n\r", asdfghjkl); // Self filter still not working.
                    book += asdfghjkl;
                    bookNum++;
                }
            }
            else if(!temp.null())
            {   temp.lower(temp);
                temp.filter("==", ",.\'\";-:?!()\n\r", asdfghjkl);
                book += asdfghjkl;
                bookNum++;
            }
        }
    }
    else
        {cout << "\nFile not found.\n";}
}

void readDict(List<String> dict[], int &dictNum)
{   ifstream file("dict.txt");
    if(file.good())
    {   String temp;
        int hashed;
        while(getline(file, temp))
        {   temp.filter("==", '\r', temp);
            hashed = hashStr(temp) % 1373;
            dict[hashed] += temp;
            dictNum++;
        }
    }
    else
        {cout << "\nDict.txt is bad.\n";}
}

bool check(const String &x, const List<String> &dict)
{   if(dict.null())
        {return false;}
    else
    {   if(x == dict.head())
            {return true;}
        else
            {return check(x, dict.body());}
    }
}

void spellcheck(const List<String> dict[], List<String> &bad, int &mis, const List<String> &xs)
{   if(!xs.null())
    {   int hashed = hashStr(xs.head()) % 1373;
        if(!check(xs.head(), dict[hashed]))
            {bad += xs.head(); mis++;}
        spellcheck(dict, bad, mis, xs.body());
    }
}

void showbad(const List<String> &bad)
{   if(!bad.null())
    {   cout << bad.head() << "\n";
        showbad(bad.body());
    }
}

int main()
{   List<String> dict[1373];
    List<String> book;
    List<String> bad;
    String in;
    int dictNum = 0;
    int bookNum = 0;
    int mispelled = 0;
    readDict(dict, dictNum);
    readBook(book, bookNum);
    spellcheck(dict, bad, mispelled, book);
    bad.nub(bad);
    cout << "\nWords in dictionary: " << dictNum;
    cout << "\nWords in file: " << bookNum;
    cout << "\nWords mispelled: " << mispelled;
    cout << "\nShow mispellings? (Y/N): ";
    cin >> in;
    if(in.single() && (in.elem('Y') || in.elem('y')))
        {showbad(bad);}
}
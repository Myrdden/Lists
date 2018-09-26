#ifndef LIST_H
#define LIST_H
#include <iostream>
template <class T>
class List
{protected:
    T* cur;
    List* nxt;

    void cons(const T &a)
    {   if(cur == nullptr)
        {   cur = new T;
            *cur = a;
        }
        else
        {   List* x = new List;
            x->cur = new T;
            *(x->cur) = *cur;
            x->nxt = nxt;
            *cur = a;
            nxt = x;
        }
    }
    /*void append(const List &a)
    {   if(!a.null())
        {   if()

        }
    }*/
public:
    ~List()
        {clear();}
    void clear()
    {   if(cur != nullptr)
            {delete cur; cur = nullptr;}
        if(nxt != nullptr)
            {delete nxt; nxt = nullptr;}
    }
    List()
        {cur = nullptr; nxt = nullptr;}
    // List(const T &a)
    //     {*cur = a; nxt = nullptr; sub = false;}

// ======== ACCESSORS ========
    T& head() const
    {   if(cur != nullptr)
            {return *cur;}
        T* x = new T;
        return *x;
    }
    T& at() const
    {   if(cur != nullptr)
            {return *cur;}
        T* x = new T;
        return *x;
    }
    List& tail() const
    {   if(nxt != nullptr)
            {return *nxt;}
        List* x = new List;
        return *x;
    }
    List& next() const
    {   if(nxt != nullptr)
            {return *nxt;}
        List* x = new List;
        return *x;
    }
    bool null() const
        {return (cur == nullptr);}
    bool empty() const
        {return (cur == nullptr);}
    bool single() const
        {return (nxt == nullptr);}
    int length() const
    {   if(cur != nullptr)
        {   if(nxt != nullptr)
                {return 1 + nxt->length();}
            return 1;
        }
        return 0;
    }

// ======== MUTATORS ========
    template <class U> friend List<U>& operator*(const U &a, List<U> &b);
};
template <class T>
List<T>& operator*(const T &a, List<T> &b)
{   if(b.cur == nullptr)
    {   b.cur = new T;
        *b.cur = a;
    }
    else
    {   List<T>* x = new List<T>;
        x->cur = new T;
        *(x->cur) = *b.cur;
        x->nxt = b.nxt;
        *b.cur = a;
        b.nxt = x;
    }
    return b;
}
template <class T>
std::ostream& stream(std::ostream &a, const List<T> &b)
{   if(!b.null())
    {   a << b.at();
        if(!b.single()) {a << ",";}
        return stream(a, b.next());
    }
    a << "]";
    return a;
}
template <class T>
std::ostream& operator<<(std::ostream &a, const List<T> &b)
{   a << "[";
    return stream(a, b);
}
class String : public List<char>
{

};
template <>
std::ostream& operator<<(std::ostream &a, const List<char> &b)
{   if(!b.null())
    {   a << b.at();
        a << b.next();
    }
    return a;
}
#endif
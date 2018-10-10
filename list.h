#ifndef LIST_H
#define LIST_H
#include <iostream>
namespace L
{   template <class T>
    class Link
    {   T* data;
        unsigned int len;
        unsigned int link;
    public:
        Link()
            {data = nullptr; len = 0; link = 0;}
        ~Link()
            {delete[] data;}
        template <class U> friend class List;
    };
    template <class T>
    class List
    {   Link<T>* cur;
        unsigned int ins;
        List* head;
        List* tail;
    public:
        List()
            {cur = nullptr; ins = 0; head = tail = nullptr;}
        ~List()
        {
        }
        List& operator=(const List& a)
        {   unsigned int lHead = 0;
            unsigned int lTail = 0;
            List* x = this;
            List* y = nullptr;
            while(x != nullptr && x->cur->link == 0)
            {   lHead = lHead + x->cur->len;
                y = x->tail;
                while(y != nullptr)
                {   lTail = lTail + y->cur->len;
                    y = y->tail;
                }
                x = x->head;
            }
            Link<T>* xs = nullptr;
            List<T>* ys = nullptr;
            if(lHead != 0)
            {   xs = new Link<T>;
                xs->cur->data = new T[lHead]; xs->cur->len = lHead;
                xs->cur->link = 1;
            }
            if(lTail != 0)
            {   ys = new List; ys->cur = new Link<T>;
                ys->cur->data = new T[lTail]; ys->cur->len = lTail;
                ys->cur->link = 1;
            }
            x = this; y = nullptr;
            while(x != nullptr)
            {   if(x->cur->link != 0)
                {   

                }
                else
                {}
            }
            return *this;
        }
        template <class U> friend List<U>& operator*(const U &, const List<U> &);
        template <class U> friend List<U>& operator+(const List<U> &, const U &);

    };
    template <class T>
    inline List<T>& operator*(const T &a, const List<T> &b)
    {   Link<T>* x = new Link<T>;
        x->data = new T[1]; x->len = 1; x->data[0] = a;
        List<T>* xs = new List<T>;
        xs->cur = x;
        if(b.cur == nullptr)
            {return *xs;}
        xs->head = b;
        return *xs;
    }
    template <class T>
    inline List<T>& operator+(const List<T> &b, const T &a)
    {   Link<T>* x = new Link<T>;
        x->data = new T[1]; x->len = 1; x->data[0] = a;
        List<T>* xs = new List<T>;
        xs->cur = x;
        if(b.cur == nullptr)
            {return *xs;}
        List<T>* y = new List<T>;
        y->head = b; y->tail = xs;
        return *y;
    }
}
#endif
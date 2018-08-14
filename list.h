#ifndef LIST_H
#define LIST_H
#include <iostream>
namespace L
{   template <class T>
    class List
    {   T* cur;
        int len;
        List* nxt;
        List* prv;
        void assign(const List &a)
            {cur = a.cur; len = a.len; nxt = a.nxt; prv = a.prv;}
    public:
        List()
            {cur = nullptr; len = 0; nxt = prv = nullptr;}
        List(const T &a)
            {cur = new T[1]; cur[0] = a; len = 1; nxt = nullptr; prv = this;}
        List(const T* a, int size)
        {   cur = new T[size];
            int i = 0;
            while(i < size)
                {cur[i] = a[i]; i++;}
            len = size; nxt = nullptr; prv = this;
        }
        List(const List &a)
            {}
        ~List()
            {clear();}
        void clear()
        {   if(cur != nullptr)
                {delete[] cur; len = 0;}
            if(nxt != nullptr)
                {delete nxt; nxt = nullptr;}
            prv = nullptr;
        }
        void squish()
        {   List* x = new List;
            x->assign(*this);
            len = length();
            cur = new T[len];
            nxt = nullptr; prv = this;
            int i = 0; int j = 0;
            int n = len;
            List* y = x;
            while(i < n)
            {   if(i < y->len)
                    {cur[j] = y->at(i); i++; j++;}
                else
                {   n = n - i; i = 0;
                    if(y->nxt != nullptr)
                        {y->assign(*(y->nxt));}
                }
            }
            delete x;
        }
        void compress()
            {squish();}
        void expand()
        {   List* x = new List;
            x->assign(*this);
            cur = new T[1]; len = 1;
            cur[0] = x->at();
            nxt = nullptr;
            int n = x->length();
            int i = 1;
            List* xs = x;
            List* y = this;
            List* z;
            while(i < n)
            {   if(i < xs->len)
                {   z = new List;
                    z->cur = new T[1]; z->len = 1;
                    z->cur[0] = x->at(i);
                    z->nxt = nullptr; z->prv = y;
                    y->nxt = z;
                    y = z; z = nullptr;
                    i++;
                }
                else
                {   n = n - i; i = 0;
                    if(xs->nxt != nullptr)
                        {xs->assign(*(xs->nxt));}
                }
            }
            prv = y;
        }

        bool null() const
            {return cur == nullptr;}
        bool single() const
            {return len == 1;}
        int length() const
        {   if(cur != nullptr)
            {   if(nxt != nullptr)
                    {return len + nxt->length();}
                return len;
            }
            return 0;
        }
        int count() const
        {   if(cur != nullptr)
            {   if(nxt != nullptr)
                    {return 1 + nxt->count();}
                return 1;
            }
            return 0;
        }
        bool alone() const
            {return nxt == nullptr;}
        bool together() const
            {return nxt != nullptr;}

        T& at() const
        {   if(cur != nullptr)
                {return cur[0];}
            T* x = new T;
            return *x;
        }
        List& next() const
        {   if(len == 1)
            {   if(nxt != nullptr)
                    {return *nxt;}
            }
            if(cur != nullptr)
            {   List* x = new List;
                x->cur = &cur[1];
                x->len = len - 1;
                x->nxt = nxt;
                x->prv = prv;
                return *x;
            }
            List* x = new List;
            return *x;
        }
        T& at(const int &i) const
        {   if(i >= len)
            {   if(nxt == nullptr)
                    {return cur[i];} //Obviously this will fail, I'm just leaving exceptions to something else.
                return nxt->at(i - len);
            }
            return cur[i];
        }
        T& operator[](const int &i) const
        {   if(i >= len)
            {   if(nxt == nullptr)
                    {return cur[i];}
                return nxt->at(i - len);
            }
            return cur[i];
        }
        //No touchy my datas
        template <class U> friend List<U>& cons(const U&, List<U>&);
        //This is gonna be pretty I can already tell
        template <class U> friend List<U>& operator*(const U&, List<U>&);
        template <class U> friend List<U>& append(const U&, List<U>&);
        template <class U> friend List<U>& operator+(List<U>&, const U&);
        //Why must you be like this?
        template <class U> friend List<U>& drop(List<U> &);
        template <class U> friend List<U>& dropTail(List<U>&);
        template <class U> friend List<U>& take(const int&, List<U>&);
        template <class U> friend List<U>& take(const int&, List<U>&, List<U>&);
        template <class U> friend bool isElem(const U&, const List<U>&);
        template <class U> friend bool isPrefix(const U&, const List<U>&);
        template <class U> friend bool isSuffix(const U&, const List<U>&);
        template <class U> friend bool isInfix(const U&, const List<U>&);
    };
    template <class T>
    List<T>& cons(const T &a, List<T> &b)
    {   if(b.cur != nullptr)
        {   List<T>* x = new List<T>;
            x->cur = b.cur; x->len = b.len;
            x->nxt = b.nxt; x->prv = &b;
            b.cur = new T[1]; b.len = 1;
            b.cur[0] = a;
            b.nxt = x;
            if(x->nxt == nullptr)
                {b.prv = x;}
            return b;
        }
        b.cur = new T[1]; b.len = 1;
        b.cur[0] = a; b.prv = &b;
        return b;
    }
    template <class T>
    List<T>& operator*(const T &a, List<T> &b)
    {   if(b.cur != nullptr)
        {   List<T>* x = new List<T>;
            x->cur = b.cur; x->len = b.len;
            x->nxt = b.nxt; x->prv = &b;
            b.cur = new T[1]; b.len = 1;
            b.cur[0] = a;
            b.nxt = x;
            if(x->nxt == nullptr)
                {b.prv = x;}
            return b;
        }
        b.cur = new T[1]; b.len = 1;
        b.cur[0] = a; b.prv = &b;
        return b;
    }
    template <class T>
    List<T>& append(const T &a, List<T> &b)
    {   if(b.prv != nullptr)
        {   List<T>* x = new List<T>;
            x->cur = new T[1]; x->len = 1;
            x->cur[0] = a;
            x->nxt = nullptr; x->prv = b.prv;
            b.prv->nxt = x; b.prv = x;
            return b;
        }
        b.cur = new T[1]; b.len = 1;
        b.cur[0] = a; b.prv = &b;
        return b;
    }
    template <class T>
    List<T>& operator+(List<T> &a, const T &b)
    {   if(a.prv != nullptr)
        {   List<T>* x = new List<T>;
            x->cur = new T[1]; x->len = 1;
            x->cur[0] = b;
            x->nxt = nullptr; x->prv = a.prv;
            a.prv->nxt = x; a.prv = x;
            return a;
        }
        a.cur = new T[1]; a.len = 1;
        a.cur[0] = b; a.prv = &a;
        return a;
    }
    template <class T>
    List<T>& drop(List<T> &a)
    {   if(a.cur != nullptr)
        {   if(a.len == 1)
            {   List<T>* x = a.nxt;
                a.cur = x->cur; x->cur = nullptr;
                a.len = x->len;
                a.nxt = x->nxt; x->nxt = nullptr;
                delete x;
            }
            else
            {   T* x = new T[a.len - 1];
                int i = 0;
                while(i < (a.len - 1))
                    {x[i] = a.cur[i + 1]; i++;}
                delete[] a.cur; a.cur = x;
                a.len = a.len - 1;
            }
        }
        return a;
    }
    template <class T>
    inline List<T>& drop(const int &a, List<T> &b)
    {   int i = 0;
        while(i < a)
            {drop(b); i++;}
        return b;
    }
    template <class T>
    inline List<T>& operator-(const int &a, List<T> &b)
    {   int i = 0;
        while(i < a)
            {drop(b); i++;}
        return b;
    }
    template <class T>
    List<T>& dropTail(List<T> &a)
    {   if(a.prv->cur != nullptr)
        {   if(a.prv->len == 1)
            {   List<T>* x = a.prv->prv;
                delete a.prv; a.prv = x;
                a.prv->nxt = nullptr;
            }
            else
            {   T* x = new T[a.prv->len - 1];
                int i = 0;
                while(i < (a.prv->len - 1))
                    {x[i] = a.prv->cur[i]; i++;}
                delete[] a.prv->cur; a.prv->cur = x;
                a.prv->len = a.prv->len - 1;
            }
        }
        return a;
    }
    template <class T>
    inline List<T>& dropTail(const int &a, List<T> &b)
    {   int i = 0;
        while(i < a)
            {dropTail(b); i++;}
        return b;
    }
    template <class T>
    inline List<T>& operator-(List<T> &a, const int &b)
    {   int i = 0;
        while(i < b)
            {dropTail(a); i++;}
        return a;
    }
    template <class T>
    List<T>& remove(const int &a, List<T> &b)
    {
        return b;
    }
    template <class T>
    List<T>& take(const int &a, List<T> &b)
    {   if(b.cur != nullptr)
        {   List<T>* x = new List<T>;
            x->assign(b);
            b.len = a;
            b.cur = new T[a];
            b.nxt = nullptr; b.prv = &b;
            int i = 0; int j = 0;
            int n = a;
            List<T>* y;
            y->assign(*x);
            while(i < n)
            {   if(i < y->len)
                    {b.cur[j] = y->at(i); i++; j++;}
                else
                {   n = n - i; i = 0;
                    if(y->nxt != nullptr)
                        {y->assign(*(y->nxt));}
                }
            }
            delete x;
        }
        return b;
    }
    template <class T>
    List<T>& take(const int &a, List<T> &b, List<T> &c)
    {   c.clear();
        int n = b.length();
        if(n > a)
            {n = a;}
        c.cur = new T[n]; c.len = n;
        c.nxt = nullptr; c.prv = &c;
        if(b.cur != nullptr)
        {   List<T>* x = &b;
            int i = 0; int j = 0;
            while(i < n)
            {   if(i < x->len)
                    {c.cur[j] = x->at(i); i++; j++;}
                else
                {   n = n - i; i = 0;
                    if(x->nxt != nullptr)
                        {x->assign(*(x->nxt));}
                }
            }
        }
        return c;
    }
    template <class T>
    inline bool isElem(const T &a, const List<T> &b)
    {   List<T>* y = new List<T>; //const :(
        y->assign(b);
        List<T>* x = y;
        int i = 0;
        bool found = false;
        while(!found)
        {   if(i < x->len)
            {   if(x->cur[i] == a)
                    {found = true;}
                i++;
            }
            else
            {   i = 0;
                if(x->nxt != nullptr)
                    {x->assign(*x->nxt);}
                else
                    {break;}
            }
        }
        y->cur = nullptr; y->nxt = nullptr; y->prv = nullptr;
        delete y;
        return found;
    }
    template <class T>
    inline bool isElem(const List<T> &a, const List<T> &b)
    {   List<T>* y = new List<T>; List<T>* z = new List<T>;
        y->assign(a); z->assign(b);
        List<T>* w = y; List<T>* x = z;
        int i = 0; int j = 0; int k = 0;
        bool found = false;
        while(!found)
        {   if(i < x->len)
            {   k = i;
                while(x->cur[k] == w->cur[j])
                {   

                }
                i++;
            }
            else
            {   i = 0;
                if(x->nxt != nullptr)
                    {x->assign(*x->nxt);}
                else
                    {break;}
            }
        }
        y->cur = nullptr; y->nxt = nullptr; y->prv = nullptr;
        delete y;
        z->cur = nullptr; z->nxt = nullptr; z->prv = nullptr;
        delete z;
        return found;
    }
    template <class T>
    bool isPrefix(const T &a, const List<T> &b)
    {return true;}
    template <class T>
    bool isSuffix(const T &a, const List<T> &b)
    {return true;}
    template <class T>
    bool isInfix(const T &a, const List<T> &b)
    {return true;}

    class String : public List<char>
    {};
}
#endif
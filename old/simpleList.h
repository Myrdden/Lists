#ifndef SIMPLELIST_H
#define SIMPLELIST_H
#include <thread>
namespace L
{   template <class T>
    class List
    {   T* cur;
        List* nxt;
        List* prv;
    public:
        List()
            {cur = nullptr; nxt = prv = nullptr;}
        List(const T &a)
            {cur = new T; *cur = a; prv = this; nxt = nullptr;}
        List(const T* a, int size)
            {}
        ~List()
            {clear();}
        void clear()
        {   if(cur != nullptr)
                //{std::thread([=]{delete cur;}).detach(); cur = nullptr;}
                {delete cur; cur = nullptr;}
            if(nxt != nullptr)
                {delete nxt; nxt = nullptr;}
            prv = nullptr;
        }

        //Accessors:
        bool null() const
            {return cur == nullptr;}
        bool single() const
            {return (cur != nullptr) && (nxt == nullptr);}
        int length() const
        {   if(cur != nullptr)
            {   if(nxt != nullptr)
                    {return 1 + nxt->length();}
                return 1;
            }
            return 0;
        }
        T& at() const
        {   if(cur != nullptr)
                {return *cur;}
            T* null = new T;
            return *null;
        }
        List& next() const
        {   if(nxt != nullptr)
                {return *nxt;}
            List* null = new List;
            return *null;
        }
        T& at(const int &i) const
        {   if(i == 0)
            {   if(cur != nullptr)
                    {return *cur;}
            }
            if(nxt != nullptr)
                {return nxt->at(i - 1);}
            T* null = new T;
            return *null;
        }
        T& operator[](const int &i) const
        {   if(i == 0)
            {   if(cur != nullptr)
                    {return *cur;}
            }
            if(nxt != nullptr)
                {return nxt->at(i - 1);}
            T* null = new T;
            return *null;
        }

        //Mutators:
        template <class U> friend List<U>& cons(const U&, List<U>&);
        template <class U> friend List<U>& operator*(const U&, List<U>&);
        template <class U> friend List<U>& append(const U&, List<U>&);
        template <class U> friend List<U>& operator+(List<U>&, const U&);
        template <class U> friend List<U>& cons(const List<U>&, List<U>&);
        template <class U> friend List<U>& operator*(const List<U>&, List<U>&);
        template <class U> friend List<U>& append(const List<U>&, List<U>&);
        template <class U> friend List<U>& operator+(List<U>&, const List<U>&);
        template <class U> friend List<U>& pop(List<U>&);
        template <class U> friend List<U>& pop(const int&, List<U>&);

        //Higher Orders
        template <class U, class F, class ...A> friend List<U>& filter(List<U>&, List<U>&, F, const A&...);
    };
    template <class T>
    inline List<T>& cons(const T &a, List<T> &b)
    {   if(b.cur == nullptr)
            {b.cur = new T; *(b.cur) = a; b.prv = &b; return b;}
        List<T>* x = new List<T>;
        x->cur = b.cur; x->nxt = b.nxt; x->prv = &b;
        b.cur = new T; *(b.cur) = a;
        b.nxt = x;
        if(x->nxt == nullptr)
            {b.prv = x;}
        return b;
    }
    template <class T>
    inline List<T>& operator*(const T &a, List<T> &b)
    {   if(b.cur == nullptr)
            {b.cur = new T; *(b.cur) = a; b.prv = &b; return b;}
        List<T>* x = new List<T>;
        x->cur = b.cur; x->nxt = b.nxt; x->prv = &b;
        b.cur = new T; *(b.cur) = a;
        b.nxt = x;
        if(x->nxt == nullptr)
            {b.prv = x;}
        return b;
    }
    template <class T>
    inline List<T>& append(const T &a, List<T> &b)
    {   if(b.cur == nullptr)
            {b.cur = new T; *(b.cur) = a; b.prv = &b; return b;}
        List<T>* x = new List<T>;
        x->cur = new T; *(x->cur) = a;
        x->prv = b.prv; b.prv->nxt = x; b.prv = x;
        return b;
    }
    template <class T>
    inline List<T>& operator+(List<T> &b, const T &a)
    {   if(b.cur == nullptr)
            {b.cur = new T; *(b.cur) = a; b.prv = &b; return b;}
        List<T>* x = new List<T>;
        x->cur = new T; *(x->cur) = a;
        x->prv = b.prv; b.prv->nxt = x; b.prv = x;
        return b;
    }
    template <class T>
    inline List<T>& cons(const List<T> &a, List<T> &b)
    {   if(a.nxt != nullptr)
            {cons(a.next(), b);}
        if(a.cur != nullptr)
            {cons(*(a.cur), b);}
        return b;
    }
    template <class T>
    inline List<T>& operator*(const List<T> &a, List<T> &b)
    {   if(a.nxt != nullptr)
            {cons(a.next(), b);}
        if(a.cur != nullptr)
            {cons(*(a.cur), b);}
        return b;
    }
    template <class T>
    inline List<T>& append(const List<T> &a, List<T> &b)
    {   if(a.cur != nullptr)
            {append(*(a.cur), b);}
        if(a.nxt != nullptr)
            {append(a.next(), b);}
        return b;
    }
    template <class T>
    inline List<T>& operator+(List<T> &b, const List<T> &a)
    {   if(a.cur != nullptr)
            {append(*(a.cur), b);}
        if(a.nxt != nullptr)
            {append(a.next(), b);}
        return b;
    }
    template <class T>
    inline List<T>& pop(List<T> &a)
    {   if(a.cur != nullptr)
        {   delete a.cur;
            List<T>* x = a.nxt;
            if(x != nullptr)
                {a.cur = x->cur; a.nxt = x->nxt;}
            x->cur = nullptr; x->nxt = nullptr;
            delete x;
        }
        return a;
    }
    template <class T>
    inline List<T>& pop(const int &a, List<T> &b)
    {   int i = 0;
        while(i < a)
            {pop(b); i++;}
        return b;
    }

    template <class T, class F, class ...A>
    List<T>& filter(const List<T> &a, List<T> &b, F f, const A& ...p)
    {   if(a.cur != nullptr)
        {   if(f(a.at(), p...))
                {append(a.at(), b);}
        }
        if(a.nxt != nullptr)
            {return filter(a.next(), b, f, p...);}
        return b;
    }

    class String : public List<char>
    {   template <class U> friend String cons(char*, String&);


    };
    template <class T>
    String cons(char* a, String &b)
    {   
        return b;
    }

    template <class T>
    bool eq(T a, T b)
        {return a == b;}
    template <class T>
    bool neq(const T &a, const T &b)
        {return a != b;}
    template <class T>
    bool gt(const T &a, const T &b)
        {return a > b;}
    template <class T>
    bool lt(const T &a, const T &b)
        {return a < b;}
}
#endif
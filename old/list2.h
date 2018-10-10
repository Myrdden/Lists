#ifndef LIST_H
#define LIST_H
namespace L
{   template <class T>
    class List
    {   T* cur;
        int cLen;
        int tLen;
        List* nxt;
        List* end;
        void assign(const List &a)
            {cur = a.cur; cLen = a.cLen; tLen = a.tLen; nxt = a.nxt; end = a.end;}
    public:
        List()
            {cur = nullptr; cLen = tLen = 0; nxt = nullptr;}
        List(const T &a)
            {}
        ~List()
            {clear();}
        void clear()
        {   if(cur != nullptr)
                {delete[] cur; cur = nullptr;}
            if(nxt != nullptr)
                {delete nxt; nxt = nullptr;}
            cLen = tLen = 0;
        }
        List operator=(const List &a)
        {   clear();
            if(a.cur != nullptr)
            {   cur = new T[a.tLen];
                cLen = tLen = a.tLen;
                List* x = a;
                int i = 0; int n = 0;
                while(x != nullptr)
                {   while(i < x->cLen)
                        {cur[n] = x->cur[i]; i++; n++;}
                    x = x->nxt; i = 0;
                }
            }
        }

        //Accessors
        T& operator[](const int &i) const
        {

        }
        T& head() const
        {   if(cur != nullptr)
                {return cur[0];}
            T* x = new T;
            return *x;
        }
        List& tail() const
        {   if(cLen > 1)
            {}

        }
        int length() const
            {return tLen;}

        //Mutators
        template <class U> friend List<U>& cons(const U &, const List<U> &);
        template <class U> friend List<U>& operator*(const U &, const List<U> &);
        template <class U> friend List<U>& append(const U &, const List<U> &);
        template <class U> friend List<U>& operator+(const List<U> &, const U &);
    };
    template <class T>
    inline List<T>& cons(const T &a, const List<T> &b)
    {   if(b.tLen == 0)
        {   List<T>* x = new List<T>;
            x->cur = new T[1]; x->cur[0] = a;
            x->cLen = 1; x->tLen = 1;
            x->nxt = nullptr;
            return *x;
        }
        List<T>* x = new List<T>;
        List<T>* xs = new List<T>;
        xs->assign(b); xs->tLen = xs->tLen + 1;
        x->cur = new T[1]; x->cur[0] = a;
        x->cLen = 1; x->tLen = xs->tLen;
        x->nxt = xs;
        return *x;
    }
    template <class T>
    inline List<T>& operator*(const T &a, const List<T> &b)
    {   if(b.tLen == 0)
        {   List<T>* x = new List<T>;
            x->cur = new T[1]; x->cur[0] = a;
            x->cLen = 1; x->tLen = 1;
            x->nxt = nullptr;
            return *x;
        }
        List<T>* x = new List<T>;
        List<T>* xs = new List<T>;
        xs->assign(b); xs->tLen = xs->tLen + 1;
        x->cur = new T[1]; x->cur[0] = a;
        x->cLen = 1; x->tLen = xs->tLen;
        x->nxt = xs;
        return *x;
    }
    template <class T>
    inline List<T>& append(const T &a, const List<T> &b)
    {   if(b.tLen == 0)
        {   List<T>* x = new List<T>;
            x->cur = new T[1]; x->cur[0] = a;
            x->cLen = 1; x->tLen = 1;
            x->nxt = nullptr;
            return *x;
        }
        List<T>* x = new List<T>;
        List<T>* xs = new List<T>;
        xs->assign(b); xs->tLen = xs->tLen + 1;
        x->cur = new T[1]; x->cur[0] = a;
        x->cLen = 1; x->tLen = xs->tLen;
        x->nxt = nullptr;
        return *x;
    }
    template <class T>
    inline List<T>& operator+(const List<T> &b, const T &a)
    {   if(b.tLen == 0)
        {   List<T>* x = new List<T>;
            x->cur = new T[1]; x->cur[0] = a;
            x->cLen = 1; x->tLen = 1;
            x->nxt = nullptr;
            return *x;
        }
        List<T>* x = new List<T>;
        List<T>* xs = new List<T>;
        xs->assign(b); xs->tLen = xs->tLen + 1;
        x->cur = new T[1]; x->cur[0] = a;
        x->cLen = 1; x->tLen = xs->tLen;
        x->nxt = nullptr;
        return *x;
    }
    template <class T>
    inline List<T>& append(const List<T> &a, const List<T> &b)
    {   if(b.tLen == 0)
        {   if(a.tLen == 0)
            {

            }
        }
        if(a.tLen == 0)
        {

        }
        List<T>* as = new List<T>;
        List<T>* bs = new List<T>;
        as->assign(a); bs->assign(b);

    }
}
#endif
#ifndef LIST_H
#define LIST_H
template <class T>
class List
{   T* cur;
    int len;
    List* nxt;
public:
    List()
        {cur = nullptr; len = 0; nxt = nullptr;}
    List(const T &a)
        {cur = new T[1]; cur[0] = a; len = 1; nxt = nullptr;}
    List(const List &a)
    {   int n = a.length();
        cur = new T[n];
        int i = 0; int j;
        List* x = &a;
        while(x != nullptr)
        {   j = 0;
            while(j < x->len)
            {   cur[i] = x->cur[j];
                j++; i++;
            }
            x = x->nxt;
        }
    }
    List& operator=(const T &a)
        {clear(); cur = new T[1]; cur[0] = a; len = 1; return *this;}
    List& operator=(const List &a)
    {   //clear()?
        if(&a == this)
            {return *this;}
        cur = a.cur; len = a.len; nxt = a.nxt;
        return *this;
    }
    ~List()
        {clear();}
    void clear()
    {   if(cur != nullptr)
            {delete[] cur; cur = nullptr; len = 0;}
        if(nxt != nullptr)
            {delete nxt; nxt = nullptr;}
    }

    bool null() const
        {return (cur == nullptr);}
    bool single() const
    {}
    int length() const
    {   if(nxt != nullptr)
            {return (len + nxt->length());}
        else
            {return len;}
    }
    int listLength() const
    {   if(cur != nullptr)
        {   if(nxt != nullptr)
                {return 1 + nxt->listLength();}
            return 1;
        }
        return 0;
    }
    T& head() const
    {   if(cur != nullptr)
            {return cur[0];}
        T* x = new T;
        return *x;
    }
    List& tail() const
    {}
};
#endif
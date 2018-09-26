#ifndef LIST_H
#define LIST_H
template <class T>
struct Node
    {   T at;
        Node<T>* xs;
    };

template <class T>
class List
{

    Node<T>* headP;
    Node<T>* tailP;
    Node<T>* i;

    List(Node<T>* a, Node<T>* b, Node<T>* c)
        {headP = a; i = b; tailP = c;}
    void copy(const T &a, List &b)
    {   if(b.headP != nullptr)
        {   b.clear();
            b.append(a);
        }
        else
            {b.append(a);}
    }
    void copy(Node<T>* a, List &b)
    {   if(headP != nullptr)
        {   Node<T>* x = b.headP;
            Node<T>* y = a;
            Node<T>* xs = nullptr;
            while(x != nullptr)
            {   if(y->xs == nullptr)
                {   b.tailP = x;
                    xs = x->xs;
                    x->xs = nullptr;
                    x = xs;
                    while(x != nullptr)
                    {   xs = x->xs;
                        delete x;
                        x = xs;
                    }
                    y = y->xs;
                    break;
                }
                else
                {   x->at = y->at;
                    xs = x->xs;
                    y = y->xs;
                    x = xs;
                }
            }
            while(y != nullptr)
                {b.append(y->at); y = y->xs;}
            b.i = b.headP;
        }
        else
            {b.append(a);}
    }
    bool predicate(const char* cmp, const T &left, const T &right) const
    {   if(cmp[0] == '=' && cmp[1] == '=' && cmp[2] == '\0')
            {return left == right;}
        else if(cmp[0] == '!' && cmp[1] == '=' && cmp[2] == '\0')
            {return left != right;}
        else if(cmp[0] == '<' && cmp[2] == '\0')
            {return left < right;}
        else if(cmp[0] == '>' && cmp[2] == '\0')
            {return left > right;}
        else if(cmp[0] == '<' && cmp[1] == '=' && cmp[2] == '\0')
            {return left <= right;}
        else if(cmp[0] == '>' && cmp[1] == '=' && cmp[2] == '\0')
            {return left >= right;}
        else
            {return false;}
    }
    void popFrom(const int &a)
    {   Node<T>* x = headP;
        Node<T>* xs = nullptr;
        int n = 0;
        if(headP == tailP)
            {delete headP; headP = nullptr; tailP = nullptr; i = nullptr; return;}
        while(n < (a-1))
        {   if(x == nullptr)
                {return;}
            else
                {x = x->xs; n++;}
        }
        if(x != nullptr)
        {   tailP = x;
            xs = x->xs;
            x->xs = nullptr;
            x = xs;
        }
        while(x != nullptr)
        {   xs = x->xs;
            delete x;
            x = xs;
        }
    }


public:
// ======== CONSTRUCTORS ========
    List()
        {headP = nullptr; tailP = nullptr; i = nullptr;}
    List(const T &a)
        {headP = nullptr; tailP = nullptr; i = nullptr; append(a);}
    List(const List &a)
        {headP = nullptr; tailP = nullptr; i = nullptr; append(a);}
    ~List()
        {clear();}
    void operator=(const T &a)
        {copy(a, *this);}
    //void copy(List &a)
    //    {copy(headP, a);}
    void operator=(const List &a)
        {copy(a.i, *this);}


// ======== ACCESSORS ========
    bool null() const
        {return i == nullptr;}
    bool top() const
        {return i == headP;}
    bool sub() const
        {return i != headP;}
    bool single() const
        {return i == tailP;}
    T head() const
        {if(i != nullptr) {return i->at;} else {return '\0';}}
    T front() const
        {return head();}
    T tail() const
        {if(tailP != nullptr) {return tailP->at;} else {return '\0';}}
    T back() const
        {return tail();}
    T operator[](const int &a) const
    {   int n = 0;
        Node<T>* x = headP;
        while(n < a)
        {   if(x == nullptr)
                {return '\0';}
            else
                {x = x->xs; n++;}
        }
        return x->at;
    }
    int size() const
    {   int n = 0;
        Node<T>* x = headP;
        while(x != nullptr)
            {x = x->xs; n++;}
        return n;
    }
    int length() const
        {return size();}
    List body() const
    {   if(i != nullptr)
        {   if(i->xs != nullptr)
                {return List(headP, i->xs, tailP);}
        }
        return List();
    }
    List rest() const
        {return body();}
    List operator++() const
        {return body();}


// ======== ITERATOR FUNCTIONS =========
    //List iterate(List &a)
    //    {return}
    Node<T>* begin()
    {   if(top())
            {List xs = List(headP, i->xs, tailP); return xs.headP;}
        else
            {List xs = List(headP, i, tailP); return xs.i;}
    }
    Node<T>* end()
        {return tailP;}
    Node<T>* operator++()
    {   if(top())
            {List xs = List(headP, i->xs, tailP); return xs.i;}
        else
            {i = i->xs; return i;}
    }

// ======== MUTATORS ========
    void clear()
    {   if(top())
        {   Node<T>* x;
            while(headP != nullptr)
            {   x = headP;
                headP = headP->xs;
                delete x;
            }
            i = nullptr;
            tailP = nullptr;
        }
        else
        {   headP = nullptr;
            i = nullptr;
            tailP = nullptr;
        }
    }
    void cons(const T &a)
    {   if(top())
        {   Node<T>* n = new Node<T>;
            n->at = a;
            n->xs = nullptr;
            if(headP != nullptr)
                {n->xs = headP; headP = n;}
            else
                {headP = n; tailP = n;}
            i = headP;
        }
    }
    void append(const T &a)
    {   if(top())
        {   Node<T>* n = new Node<T>;
            n->at = a;
            n->xs = nullptr;
            if(tailP != nullptr)
                {tailP->xs = n; tailP = n;}
            else
                {headP = n; tailP = n; i = headP;}
        }
    }
    void operator+=(const T &a)
        {append(a);}
    void append(Node<T>* a)
    {   if(top())
        {   Node<T>* x = a;
            Node<T>* xs = nullptr;
            while(x != nullptr)
            {   append(x->at);
                xs = x->xs;
                x = xs;
            }
        }
    }
    void append(const List &a)
        {append(a.headP);}
    void operator+=(const List &a)
        {append(a);}
    void chop()
    {   if(top())
        {   Node<T>* xs = nullptr;
            if(headP != nullptr)
            {   if(headP == tailP)
                    {delete headP; headP = nullptr; tailP = nullptr; i = nullptr;}
                else
                    {xs = headP->xs; delete headP; headP = xs; i = headP;}
            }
        }
    }
    void pop()
    {   if(top())
        {   Node<T>* x = headP;
            Node<T>* xs = nullptr;
            if(headP == tailP)
                {delete headP; headP = nullptr; tailP = nullptr; i = nullptr;}
            while(x != nullptr)
            {   xs = x->xs;
                if(xs == tailP)
                    {delete xs; tailP = x; return;}
                else
                    {x = xs;}
            }
        }
    }
    bool removeAt(const int &a)
    {   if(top())
        {   Node<T>* x = headP;
            Node<T>* xs = nullptr;
            int n = 1;
            if(a < 1)
                {chop(); return true;}
            if(x != nullptr)
                {xs = x->xs;}
            while(xs != nullptr)
            {   xs = x->xs;
                if(n == a)
                {   if(xs == tailP)
                        {tailP = x;}
                    x->xs = xs->xs;
                    delete xs;
                    return true;
                }
                else
                    {x = xs; n++;}
            }
            return false;
        }
        return false;
    }
    bool remove(const T &a)
    {   if(top())
        {   Node<T>* x = headP;
            Node<T>* xs = nullptr;
            if(x != nullptr)
            {   xs = x->xs;
                if(x->at == a)
                    {chop(); return true;}
            }
            while(xs != nullptr)
            {   xs = x->xs;
                if(xs->at == a)
                    {x->xs = xs->xs; delete xs; return true;}
                else
                    {x = xs;}
            }
            return false;
        }
        return false;
    }
    void swap(List &a)
    {   if(top() && a.top())
        {   Node<T>* x = headP;
            Node<T>* y = tailP;
            headP = a.headP; tailP = a.tailP; i = headP;
            a.headP = x; a.tailP = y; a.i = a.headP;
        }
    }


// ======== FUNCTIONS ========
    List drop(const int &a, List &b)
    {   int n = 0;
        if(&b == this)
        {   if(top())
            {   while(n < a)
                    {chop(); n++;}
            }
            /*else
            {   Node<T>* x = i;
                i = headP;
                while(headP != x)
                    {chop();}
                while(n < a)
                    {chop(); n++;}
            }*/
            return *this;
        }
        else
        {   Node<T>* x = i;
            while(n < a)
            {   if(x == nullptr)
                    {b.clear(); return b;}
                x = x->xs; n++;
            }
            copy(x,b);
            return b;
        }
    }
    List take(const int &a, List &b)
    {   if(&b == this)
        {   if(top())
                {popFrom(a);}
            /*else
            {   Node<T>* x = i;
                i = headP;
                while(headP != x)
                    {chop();}
                popFrom(a);
            }*/
            return *this;
        }
        else
        {   Node<T>* x = i;
            Node<T>* y = b.headP;
            int n = 0;
            while(n < a && x != nullptr)
            {   if(y != nullptr)
                {   y->at = x->at;
                    x = x->xs; y = y->xs;
                    n++;
                }
                else
                {   b.append(x->at);
                    x = x->xs;
                    n++;
                }
            }
            b.popFrom(n);
            return b;
        }
    }
    List filter(const T* a, const T &b, List &c)
    {   if(&c == this)
        {   if(top())
            {   Node<T>* x = headP;
                Node<T>* xs = nullptr;
                if(x != nullptr)
                {   if(predicate(a, x->at, b))
                        {chop(); x = headP;}
                }
                while(x != nullptr)
                {   xs = x->xs;
                    if(xs != nullptr)
                    {   if(predicate(a, xs->at, b))
                            {x->xs = xs->xs; delete xs;}
                    }
                    x = x->xs;
                }
            }
            return *this;
        }
        else
        {   Node<T>* x = i;
            Node<T>* y = c.headP;
            int n = 0;
            while(x != nullptr)
            {   if(!predicate(a, x->at, b))
                {   if(y != nullptr)
                        {y->at = x->at; y = y->xs; n++;}
                    else
                        {c.append(x->at); n++;}
                }
                x = x->xs;
            }
            c.popFrom(n);
            return c;
        }
    }
    List filter(const T* a, const List &b, List &c)
    {   if(&c == this)
        {   if(top())
            {   Node<T>* x = headP;
                Node<T>* y = b.i;
                Node<T>* xs = nullptr;
                bool cnd = false;
                if(x != nullptr)
                {   while(y != nullptr)
                    {   if(predicate(a, x->at, y->at))
                            {cnd = true; break;}
                        y = y->xs;
                    }
                    if(cnd)
                        {chop(); x = headP; cnd = false;}
                    y = b.i;
                }
                while(x != nullptr)
                {   xs = x->xs;
                    if(xs != nullptr)
                    {   while(y != nullptr)
                        {   if(predicate(a, xs->at, y->at))
                                {cnd = true; break;}
                            y = y->xs;
                        }
                        if(cnd)
                            {x->xs = xs->xs; delete xs; cnd = false;}
                        else
                            {x = x->xs;}
                        y = b.i;
                    }
                    x = x->xs;
                }
            }
            return *this;
        }
        else
        {   Node<T>* x = i;
            Node<T>* y = c.headP;
            Node<T>* z = b.i;
            int n = 0;
            bool cnd = false;
            while(x != nullptr)
            {   while(z != nullptr)
                {   if(predicate(a, x->at, z->at))
                        {cnd = true; break;}
                    z = z->xs;
                }
                if(!cnd)
                {   if(y != nullptr)
                        {y->at = x->at; y = y->xs; n++;}
                    else
                        {c.append(x->at); n++;}
                }
                x = x->xs;
                z = b.i;
                cnd = false;
            }
            c.popFrom(n);
            return c;
        }
    }
    List operator-(const List& a)
        {return filter("==", a, *this);}
    List nub(List &a)
    {   if(&a == this)
        {   if(top())
            {   Node<T>* x = headP;
                Node<T>* y = nullptr;
                Node<T>* ys = nullptr;
                while(x != nullptr)
                {   y = x;
                    while(y != nullptr)
                    {   ys = y->xs;
                        if(ys != nullptr)
                        {   if(ys->at == x->at)
                            {   if(ys == tailP)
                                    {tailP = y;}
                                y->xs = ys->xs; delete ys;
                            }
                        }
                        y = y->xs;
                    }
                    x = x->xs;
                }
                return *this;
            }
            else
                {return List();}
        }
        else
        {
            return a;
        }
    }


// ======== COMPARISONS =========
    bool elem(const T &a) const
    {   Node<T>* x = i;
        while(x != nullptr)
        {   if(x->at == a)
                {return true;}
            else
                {x = x->xs;}
        }
        return false;
    }
    bool notElem(const T &a) const
        {return !elem(a);}
    bool elem(const List &a) const
    {   Node<T>* x = i;
        Node<T>* xs = nullptr;
        Node<T>* y = a.i;
        while(x != nullptr)
        {   if(y != nullptr)
            {   if(x->at == y->at)
                {   xs = x;
                    y = a.i;
                    while(y != nullptr)
                    {   if(xs == nullptr)
                            {return false;}
                        else if(xs->at != y->at)
                            {break;}
                        y = y->xs; xs = xs->xs;
                    }
                    if(y == nullptr)
                        {return true;}
                }
            }
            x = x->xs;
        }
        return false;
    }
    bool operator==(const List &a) const
    {   Node<T>* x = i;
        Node<T>* y = a.i;
        while(x != nullptr)
        {   if(y == nullptr)
                {return false;}
            else if(x->at != y->at)
                {return false;}
            else
                {x = x->xs; y = y->xs;}
        }
        if(y == nullptr)
            {return true;}
        else
            {return false;}
    }
    bool operator !=(const List &a) const
        {return !(*this == a);}
    bool operator<(const List &a) const
    {   Node<T>* x = i;
        Node<T>* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at > y->at)
                {return false;}
            else if(x->at == y->at && y->xs == nullptr)
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }
    bool operator>(const List &a) const
    {   Node<T>* x = i;
        Node<T>* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at < y->at)
                {return false;}
            else if(x->at == y->at && x->xs == nullptr)
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }
    bool operator<=(const List &a) const
    {   Node<T>* x = i;
        Node<T>* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at > y->at)
                {return false;}
            else if(x->at == y->at && (x->xs != nullptr && y->xs == nullptr))
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }
    bool operator>=(const List &a) const
    {   Node<T>* x = i;
        Node<T>* y = a.i;
        while(x != nullptr && y != nullptr)
        {   if(x->at < y->at)
                {return false;}
            else if(x->at == y->at && (x->xs == nullptr && y->xs != nullptr))
                {return false;}
            x = x->xs; y = y->xs;
        }
        return true;
    }


// ======== ARRAY FUNCTIONS ========
T* toPtr() const
{   if(i != nullptr)
    {   T* ret = new T[size()];
        Node<T>* x = i;
        int n = 0;
        while(x != nullptr)
        {   ret[n] = x->at;
            x = x->xs;
            n++;
        }
        return ret;
    }
    else
    {   T* ret = new T[0];
        return ret;
    }
}
List fromPtr(const T* a, const int &b)
{   if(top())
    {   Node<T>* x = headP;
        int n = 0;
        while(n < b)
        {   if(x != nullptr)
            {   x->at = a[n];
                x = x->xs;
            }
            else
                {append(a[n]);}
            n++;
        }
        popFrom(n);
        return *this;
    }
    else
        {return List();}
}
List(const T* a, const int &b)
    {fromPtr(a, b);}
};
#endif
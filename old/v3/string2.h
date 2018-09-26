#ifndef STRING_H
#define STRING_H
struct Letter
{   char c;
    Letter* xs;
};

class String;

class Substring
{   Letter* headP;
    Letter* tailP;
public:
    Substring()
        {headP = nullptr; tailP = nullptr;}
    Substring(const Substring &ys)
        {headP = ys.headP; tailP = ys.tailP;}
    Substring(Letter* head, Letter* tail)
        {headP = head; tailP = tail;}
    ~Substring()
        {headP = nullptr; tailP = nullptr;}
    bool null() const
        {return (this->headP == nullptr);}
    int size() const
    {   int i = 0;
        Letter* x = this->headP;
        Letter* xs = nullptr;
        while(x != nullptr)
            {xs = x->xs; x = xs; i++;}
        return i;
    }
    int length() const
        {return this->size();}
    char head() const
        {return this->headP->c;}
    char last() const
        {return this->tailP->c;}
    Substring body() const
        {return Substring(this->headP->xs, this->tailP);}
};

class String : public Substring
{   Letter* headP;
    Letter* tailP;
    bool predicate(String prd, char left, char right) const
    {   if(prd == "==")
            {return left == right;}
        else if(prd == "!=")
            {return left != right;}
        else if(prd == "<")
            {return left < right;}
        else if(prd == ">")
            {return left > right;}
        else if(prd == "<=")
            {return left <= right;}
        else if(prd == ">=")
            {return left >= right;}
        else
            {return false;}
    }
public:
    String()
        {headP = nullptr; tailP = nullptr;}
    String(const String &ys)
        {headP = nullptr; tailP = nullptr; append(ys);}
    String(const Substring &ys)
        {headP = nullptr; tailP = nullptr; append(ys);}
    String(const char* ys)
        {headP = nullptr; tailP = nullptr; append(ys);}
    String& operator=(const String& ys)
        {clear(); append(ys); return *this;}
    String& operator=(const Substring& ys)
        {clear(); append(ys); return *this;}
    String& operator=(const char* ys)
        {clear(); append(ys); return *this;}
    String& operator=(const char c)
        {clear(); append(c); return *this;}
    ~String()
        {clear();}
    String cBody()
    {   String ret;
        Letter* x;
        if(headP != nullptr)
            {x = headP->xs;}
        else
            {x = nullptr;}
        Letter* xs = nullptr;
        while(x != nullptr)
        {   ret.append(x->c);
            xs = x->xs;
            x = xs;
        }
        return ret;
    }
    char* cStr()
    {   if(headP != nullptr)
        {   char* ret = new char[size() + 1];
            Letter* x = headP;
            Letter* xs = nullptr;
            int i = 0;
            while(x != nullptr)
            {   ret[i] = x->c;
                xs = x->xs;
                x = xs;
                i++;
            }
            ret[size() + 1] = '\0';
            return ret;
        }
        else
        {   char* ret = new char[0];
            return ret;
        }
    }



bool null() const
    {return (this->headP == nullptr);}
int size() const
{   int i = 0;
    Letter* x = this->headP;
    Letter* xs = nullptr;
    while(x != nullptr)
        {xs = x->xs; x = xs; i++;}
    return i;
}
int length() const
    {return this->size();}
char head() const
    {return this->headP->c;}
char last() const
    {return this->tailP->c;}
char operator[](const int &i) const
{   int n = 0;
    Letter* x = this->headP;
    Letter* xs = nullptr;
    while(n < i)
    {   if(x == nullptr)
            {return '\0';}
        else
            {xs = x->xs; x = xs; n++;}
    }
    return x->c;
}
Substring body() const
    {return Substring(this->headP->xs, this->tailP);}



    void clear()
    {   if(headP != nullptr)
        {   Letter* x = headP;
            Letter* xs = nullptr;
            while(x != nullptr)
            {   xs = x->xs;
                delete x;
                x = xs;
            }
            headP = nullptr;
            tailP = nullptr;
        }
    }
    void cons(const char &d)
    {   Letter* c = new Letter;
        c->c = d;
        c->xs = nullptr;
        if(headP != nullptr)
            {c->xs = headP; headP = c;}
        else
            {headP = c; tailP = c;}
    }
    void append(const char &d)
    {   Letter* c = new Letter;
        c->c = d;
        c->xs = nullptr;
        if(tailP != nullptr)
        {   tailP->xs = c;
            tailP = c;
        }
        else
            {headP = c; tailP = c;}
    }
    void operator+=(const char &d)
        {append(d);}
    void append(const String &ys)
    {   Letter* x = ys.headP;
        Letter* xs = nullptr;
        while(x != nullptr)
        {   append(x->c);
            xs = x->xs;
            x = xs;
        }
    }
    void operator+=(const String &ys)
        {append(ys);}
    void append(const Substring &ys)
    {   if(!ys.null())
        {   append(ys.head());
            append(ys.body());
        }
    }
    void operator+=(const Substring &ys)
        {append(ys);}
    void append(const char* ys)
    {   int i = 0;
        while(*(ys+i) != '\0')
            {append(*(ys+i)); i++;}
    }
    void operator+=(const char* ys)
        {append(ys);}
    void insert(const char &d, const int &p)
    {   Letter* c = new Letter;
        c->c = d;
        c->xs = nullptr;
        int i = 0;
        Letter* x = headP;
        Letter* xs = nullptr;
        while(i != p)
        {   if(x == nullptr)
                {return;}
            else
                {xs = x->xs; x = xs; i++;}
        }
        c->xs = x->xs;
        x->xs = c;
    }

    String remove(const int &i)
    {   String ret;
        Letter* x = headP;
        Letter* xs = nullptr;
        int n = 0;
        while(x != nullptr)
        {   if(n == i)
                {xs = x->xs; x = xs; n++;}
            else
                {ret.append(x->c); xs = x->xs; x = xs; n++;}
        }
        return ret;
    }
    String remove(const char &c)
    {   String ret;
        Letter* x = headP;
        Letter* xs = nullptr;
        while(x != nullptr)
        {   if(x->c == c)
                {xs = x->xs; x = xs;}
            else
                {ret.append(x->c); xs = x->xs; x = xs;}
        }
        return ret;
    }
    String drop(int i)
    {   String ret;
        Letter* x = headP;
        Letter* xs = nullptr;
        int n = 0;
        while(n != i)
        {   if(x == nullptr)
                {break;}
            else
                {xs = x->xs; x = xs; n++;}
        }
        while(x != nullptr)
            {ret.append(x->c); xs = x->xs; x = xs;}
        return ret;
    }
    String take(int i)
    {   Letter* x = headP;
        Letter* xs = nullptr;
        String ret;
        int n = 0;
        while(n != i)
        {   if(x == nullptr)
                {return String(*this);}
            else
                {ret.append(x->c); xs = x->xs; x = xs; n++;}
        }
        return ret;
    }
    String dropWhile(const String &con, const char &prd)
    {   String ret;
        Letter* x = headP;
        Letter* xs = nullptr;
        while(x != nullptr)
        {   if(predicate(con, x->c, prd))
                {xs = x->xs; x = xs;}
            else
                {break;}
        }
        while(x != nullptr)
            {ret.append(x->c); xs = x->xs; x = xs;}
        return ret;
    }
    String dropWhile(const char* con, const char &prd)
        {return dropWhile(String(con), prd);}
    String takeWhile(const String &con, const char &prd)
    {   String ret;
        Letter* x = headP;
        Letter* xs = nullptr;
        while(x != nullptr)
        {   if(predicate(con, x->c, prd))
                {ret.append(x->c); xs = x->xs; x = xs;}
            else
                {break;}
        }
        return ret;
    }
    String takeWhile(const char* con, const char &prd)
        {return takeWhile(String(con), prd);}
    String filter(const String &con, const char &prd)
    {   String ret;
        Letter* x = headP;
        Letter* xs = nullptr;
        while(x != nullptr)
        {   if(predicate(con, x->c, prd))
                {xs = x->xs; x = xs;}
            else
                {ret.append(x->c); xs = x->xs; x = xs;}
        }
        return ret;
    }
    String filter(const char* &con, const char &prd)
        {return filter(String(con), prd);}

    bool operator==(const String &cmp)
    {   Letter* x = headP;
        Letter* y = cmp.headP;
        Letter* xs = nullptr;
        Letter* ys = nullptr;
        while(x != nullptr)
        {   if(y == nullptr)
                {return false;}
            else if(x->c != y->c)
                {return false;}
            else
                {xs = x->xs; ys = y->xs; x = xs; y = ys;}
        }
        return true;
    }
    bool operator==(const char* ys)
        {return (*this == String(ys));}
    bool operator!=(const String &cmp)
        {return !(*this == cmp);}
    bool operator!=(const char* ys)
        {return (*this != String(ys));}
};

String operator"" _s(const char* str)
    {return String(str);}
#endif
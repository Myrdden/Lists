#ifndef TREE_H
#define TREE_H
#include <iostream>
template <class T>
class Tree
{   struct Node
    {   T at;
        Node* ls;
        Node* rs;
        int h;
    };
    Node* root;

    Node* left(Node* a)
    {   Node* x = a->ls;
        a->ls = x->rs;
        a->h = a->ls->h > (a->rs->h + 1) ? a->ls->h : a->rs->h;
        x->rs = a;
        x->h = x->ls->h > (x->rs->h + 1) ? x->ls->h : x->rs->h;
        return x;
    }
    Node* right(Node* a)
    {   Node* x = a->rs;
        a->rs = x->ls;
        a->h = a->rs->h > (a->ls->h + 1) ? a->rs->h : a->ls->h;
        x->ls = a;
        x->h = x->rs->h > (x->ls->h + 1) ? x->rs->h : x->ls->h;
        return x;
    }
    int size(Node* a) const
    {   if(a != nullptr)
            {return (1 + size(a->ls) + size(a->rs));}
        return 0;
    }
    void preorder(Node* a) const
    {   if(a != nullptr)
        {   std::cout << a->at;
            preorder(a->ls);
            preorder(a->rs);
        }
    }
    void inorder(Node* a) const
    {   if(a != nullptr)
        {   inorder(a->ls);
            std::cout << a->at;
            inorder(a->rs);
        }
    }
    void postorder(Node* a) const
    {   if(a != nullptr)
        {   postorder(a->ls);
            postorder(a->rs);
            std::cout << a->at;
        }
    }
public:
    Tree()
        {root = nullptr;}
    Tree(const T &a)
        {}

    void add(Node* x, Node* a)
    {   a->h++;
        if(a->at < x->at)
        {   if(x->ls == nullptr)
                {x->ls = a;}
            else
                {add(x->ls, a);}
        }
        else
        {   if(x->rs == nullptr)
                {x->rs = a;}
            else
                {add(x->rs, a);}
        }
        if((x->ls->h - x->rs->h) > 1)
        {   if(a->at < x->ls->at)
                {x = right(x);}
            else
                {x->ls = left(x->ls); x = right(x);}
        }
        else if((x->ls->h - x->rs->h) < -1)
        {   if(a->at < x->rs->at)
                {x = left(x);}
            else
                {x->rs = right(x->rs); x = left(x);}
        }
    }
    void add(const T &a)
    {   Node* y = new Node;
        y->at = a;
        y->ls = nullptr; y->rs = nullptr;
        y->h = 0;
        if(root == nullptr)
            {root = y;}
        else
            {add(root, y);}
    }


    int size() const
        {return size(root);}
    void preorder() const
        {preorder(root);}
    void inorder() const
        {inorder(root);}
    void postorder() const
        {postorder(root);}
};
#endif
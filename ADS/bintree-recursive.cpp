//============================================================================
// Name        : Assignment1.cpp
// Author      : 2179
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<queue>
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;
public:
    node()
{
        data=0;
        left=NULL;
        right=NULL;
}
    ~node(){}
    friend class Btree;
};

class Btree
{
    node *root;
public:
    Btree()
{
        root=NULL;
}
    node *ret_root()
    {
        return root;
    }
    void rec_create();
    node *rec_insert(node*);
    void rec_display_inorder(node*);
    void rec_display_post(node*);
    void rec_display_pre(node*);
    int rec_height(node*);
    int rec_leafnodes(node*);
    int rec_int_nodes(node*);
    void mirror(Btree);
    void operator = (Btree);
    node *copy(node*);
    node *rec_mirror(node*);
    void rec_delete(node*);
};

int Btree::rec_leafnodes(node *t)
{
    if(t==NULL)
        return 0;
    if(t->left==NULL && t->right==NULL)
        return 1;
    else
        return rec_leafnodes(t->left) + rec_leafnodes(t->right);
}

int Btree::rec_int_nodes(node *t)
{
    if(t==NULL || (t->left==NULL && t->right==NULL))
    {
        return 0;
    }
    return 1 + rec_int_nodes(t->left) + rec_int_nodes(t->right);
}

node *Btree::copy(node *t)
{
    node *c_root=NULL;
    if(t==NULL)
        {
            return NULL;
        }
            c_root=new node;
            c_root->data=t->data;
            c_root->left=copy(t->left);
            c_root->right=copy(t->right);
            return c_root;
}

void Btree::operator =(Btree b1)
{
    root=b1.copy(b1.ret_root());
}

void Btree::rec_create()
{
    node *p;

    if(root==NULL)
    {
        p=new node;
        cout<<"Enter node data\n";
        cin>>p->data;
        root=p;
    }
    else
    {
        cout<<"Tree is created\n";
        rec_insert(root);
    }
}

node *Btree::rec_insert(node *t)
{
    char ans;
    if(t==NULL)
    {
        node *p=new node;
        cout<<"Enter node data\n";
        cin>>p->data;
        p->left=NULL; p->right=NULL;
        return(p);
    }
    else
    {
        cout<<"Where do you want to insert on left(l) or right(r) of "<<t->data;
        cin>>ans;
        if(ans=='l')
        {
            t->left=rec_insert(t->left);
        }
        else
        {
            t->right=rec_insert(t->right);
        }
        return t;
    }
}

void Btree::rec_delete(node *ptr)
{
    if(ptr)
    {
        rec_delete(ptr->left);
        rec_delete(ptr->right);
        ptr->left=NULL;
        ptr->right=NULL;
        delete(ptr);
    }
}

void Btree::rec_display_inorder(node *c)
{
    if(c)
    {
        rec_display_inorder(c->left);
        cout<<c->data<<" ";
        rec_display_inorder(c->right);
    }
}

void Btree::rec_display_post(node *c)
{
    if(c)
        {
        rec_display_post(c->left);
        rec_display_post(c->right);
            cout<<c->data<<" ";
        }
}
void Btree::rec_display_pre(node *c)
{
    if(c)
    {
        cout<<c->data<<" ";
        rec_display_pre(c->left);
        rec_display_pre(c->right);
    }
}

node *Btree::rec_mirror(node *t)
{
    node *m_root=NULL;
    if(t==NULL)
    {
        return NULL;
    }
        m_root=new node;
        m_root->data=t->data;
        m_root->left=rec_mirror(t->right);
        m_root->right=rec_mirror(t->left);
        return m_root;

}

void Btree::mirror(Btree b1)
{
    root=b1.rec_mirror(b1.ret_root());
}


int Btree::rec_height(node *t)
{
    int h1=0,h2=0;
    if(t==NULL)
    {
        return 0;
    }

    h1=rec_height(t->left);
    h2=rec_height(t->right);

    if(h1>h2)
    {
        return h1+1;
    }
    else
    {
        return h2+1;
    }
}

int main()
{
    char ch;int c=0,h,ln,in;
    Btree b,b2,b3;

    do
    {
        cout<<"1.Create\n";
        cout<<"2.Display traversals\n";
        cout<<"3.Height + Internal and leaf nodes \n";
        cout<<"4.Display copied tree\n";
        cout<<"5.Mirror Image\n";
        cout<<"6.Delete tree\n";
        cout<<"7.Exit\n";
        switch(c)
        {
        case 1:
        do
        {
            b.rec_create();
            cout<<"Stop creating? y/n \n";
            cin>>ch;
        }while(ch!='y');
        break;
        case 2:
        cout<<"\nBinary Tree inorder\n";
        b.rec_display_inorder(b.ret_root());
        cout<<"\nBinary Tree postorder\n";
        b.rec_display_post(b.ret_root());
        cout<<"\nBinary Tree preorder\n";
        b.rec_display_pre(b.ret_root());
        break;
        case 3:
          h = b.rec_height(b.ret_root());
          cout<<"Height is"<<h<<endl;
          ln = b.rec_leafnodes(b.ret_root());
          cout<<"leaf nodes"<<ln<<endl;
          in = b.rec_int_nodes(b.ret_root());
          cout<<"internal nodes"<<in-1<<endl;
        break;
        case 4:
            b3=b;
            cout<<"\nBinary Tree inorder\n";
            b3.rec_display_inorder(b3.ret_root());
            cout<<"\nBinary Tree postorder\n";
            b3.rec_display_post(b3.ret_root());
            cout<<"\nBinary Tree preorder\n";
            b3.rec_display_pre(b3.ret_root());
            break;
        case 5:
            b2.mirror(b);
            cout<<"\nBinary Tree inorder\n";
            b2.rec_display_inorder(b2.ret_root());
            cout<<"\nBinary Tree postorder\n";
            b2.rec_display_post(b2.ret_root());
            cout<<"\nBinary Tree preorder\n";
            b2.rec_display_pre(b2.ret_root());
            break;

        case 6:
            b.rec_delete(b.ret_root());

            break;
        }
        cout<<" Enter choice\n";
        cin>>c;
    }while(c<7);


    return 0;
}


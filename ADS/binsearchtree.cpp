//============================================================================
// Name        : Assignment2.cpp
// Author      : 2179
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string>
using namespace std;

class node
{
    string word,def;
    node *left=NULL;
    node *right=NULL;
public:
    friend class BST;
};

class BST
{
    node *root,*loc,*par;
public:
    BST()
{
        root=NULL;
        loc=NULL;
        par=NULL;
}
    node *rt_root()
    {
        return root;
    }
    void search(string);
    void modify(string);
    void create();
    void rec_create(string,string);
    node *rec_insert(node *,string,string);
    node *copy(node*);
    void operator=(BST);
    void display_ascend(node*);
    void display_descend(node*);
    void deletion(string);
    void delete1(node *,node *);
    void delete2();
};

node *BST::copy(node *t)
{
    node *croot=NULL;
    if(t==NULL)
        {
            return NULL;
        }
            croot=new node;
            croot->word=t->word;
            croot->def=t->def;
            croot->left=copy(t->left);
            croot->right=copy(t->right);
            return croot;
}

void BST::operator =(BST b1)
{
    root=b1.copy(root);
}

void BST::create()
{
    node *new1=NULL,*par=NULL,*c;
    new1=new node;
    cout<<"Enter word\n";
    cin>>new1->word;
    cout<<"Enter meaning\n";
    cin>>new1->def;
    new1->left=NULL;
    new1->right=NULL;
    if(root==NULL)
    {
        new1->left=NULL;
        new1->right=NULL;
        root=new1;
        return;
    }
    else
    {
        c=root;
        while(1)
        {
            par=c;
            if(new1->word < c->word)
            {
                c=c->left;
                if(c==NULL)
                {
                    par->left=new1;
                    return;
                }
            }
            else
            {
                c=c->right;
                if(c==NULL)
                {
                    par->right=new1;
                    return;
                }
            }
        }
    }

}

void BST::rec_create(string word,string defn)
{
    if(root==NULL)
    {
        root=new node;
        root->word=word;
        root->def=defn;
        root->left=NULL;
        root->right=NULL;
    }
    else
    {
        rec_insert(root,word,defn);
    }
}

node *BST::rec_insert(node *t, string word,string defn)
{
    if(t==NULL)
    {
        node *p=new node;
        p->word=word;
        p->def=defn;
        p->left=NULL;
        p->right=NULL;
        return p;
    }
    else if(word < t->word)
    {
        t->left=rec_insert(t->left,word,defn);
    }
    else if(word > t->word)
    {
        t->right=rec_insert(t->right,word,defn);
    }
    return t;

}

void BST::display_ascend(node *t)
{
    if(t==NULL)
    {
        return;
    }
    display_ascend(t->left);
    cout<<t->word<<" means "<<t->def<<"\n";
    display_ascend(t->right);
}

void BST::display_descend(node *t)
{
    if(t==NULL)
        {
            return;
        }
        display_descend(t->right);
        cout<<t->word<<" means "<<t->def<<"\n";
        display_descend(t->left);
}

void BST::search(string key)
{

    node *c=NULL;
    if(root==NULL)
    {
        cout<<"No tree found\n";
        loc=NULL; par=NULL;
        return;
    }
    par=NULL; loc=NULL;
    c=root;
    while(c!=NULL)
    {
        if(key==c->word)
        {
            loc=c;
            cout<<c->word<<" means "<<c->def<<"\n";
            break;
        }
        else if(key<c->word)
        {
            par=c;
            c=c->left;
        }
        else
        {
            par=c;
            c=c->right;
        }
    }
    if(loc==NULL)
    {
        cout<<"word not found\n";
    }

}

void BST::modify(string key)
{
    string new1,newm;
    node *c=NULL;

        if(root==NULL)
        {
            cout<<"No tree found\n";
            return;
        }
        c=root;
        while(c!=NULL)
        {
            if(key==c->word)
            {
                loc=c;
                cout<<c->word<<" means "<<c->def<<"\n";
                cout<<"Enter new meaning\n";
                cin>>newm;
                c->def=newm;
                break;
            }
            else if(key<c->word)
            {
                loc=c;
                c=c->left;
            }
            else
            {
                loc=c;
                c=c->right;
            }
        }
        if(loc==NULL)
        {
            cout<<"word not found\n";
        }
}

void BST::deletion(string k)
{

    node *t=NULL;
    search(k);
    t=loc;
    if(t==NULL)
    {
        cout<<"Word not found\n";
    }
    else
    {
        if(t->left!=NULL && t->right!=NULL)
            {
                delete2();
            }
        else
        {
            delete1(loc,par);
            t=NULL;
            delete(t);
        }
    }
}

void BST::delete1(node *p1,node *p2)
{
    node *child;

    if(p1->left==NULL &&p1->right==NULL)
    {
        child=NULL;
    }
    else if(p1->left!=NULL)
    {
        child=p1->left;
    }
    else
    {
        child=p1->right;
    }
    if(p2!=NULL)
    {
        if(p1==p2->left)
        {
            cout<<"deleted\n";
            p2->left=child;
        }
        else
        {
            cout<<"deleted\n";
            p2->right=child;
        }
    }
    else
    {
        root=child;
    }

}

void BST::delete2()
{
    node *c=NULL,*ptr1=NULL,*ptr2=NULL;
    c=par;

        ptr1=loc;
        ptr2=loc->right;
        while(ptr2->left!=NULL)
        {
            ptr1=ptr2;
            ptr2=ptr2->left;  //inorder_successor
        }
        delete1(ptr2,ptr1);
    if(c!=NULL)
    {
        if(loc==par->left)
        {
            c->left=ptr2;
        }
        else
        {
            c->right=ptr2;
        }
    }
    else
    {
        root=ptr2;

    }
    ptr2->left=loc->left;
    ptr2->right=loc->right;
}

int main() {
    char ch; int c;
    string word,defn;
    BST b,b1;
    do
    {
        cout<<"1.Create \n2.Ascending Order \n3.Descending order \n4.Search \n5.Modify \n6.Delete \n7.Copy \n8.Exit \n";
        switch(c)
        {
        case 1:
            do
                {
                    cout<<"Enter word\n";
                    cin>>word;
                    cout<<"Enter meaning\n";
                    cin>>defn;
                    b.rec_create(word,defn);
                    cout<<"Stop creating y/n\n";
                    cin>>ch;
                }while(ch!='y');
            break;
        case 2:
            cout<<"Ascending order\n";
            b.display_ascend(b.rt_root());
            break;
        case 3:
            cout<<"Descending order\n";
            b.display_descend(b.rt_root());
            break;
        case 4:
            cout<<"Enter the word to be searched\n";
            cin>>word;
            b.search(word);
            break;
        case 5:
            cout<<"Enter the word to be modified\n";
            cin>>word;
            b.modify(word);
            break;
        case 6:
            cout<<"Enter the word to be deleted\n";
            cin>>word;
            b.deletion(word);
            break;
        case 7:
            b1=b;
            b1.display_ascend(b.rt_root());
            break;
        }
        cout<<"Enter choice\n";
        cin>>c;

    }while(c<8);



    return 0;
}

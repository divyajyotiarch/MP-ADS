//============================================================================
// Name        : Assignment3.cpp
// Author      : 2179
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class node
{
    int lbit,rbit;
    int data;
    node *left,*right;
public:
    node(int x)
    {
        lbit=0; rbit=0;
        data=x;
        left=NULL;
        right=NULL;
    }
    friend class TBT;
};

class TBT
{
    node *root,*header,*loc,*par;
public:
    TBT()
{
        root=NULL;
        loc=NULL; par=NULL;
        header=new node(10);
        header->right=header;
        header->left=header;
        header->rbit=1;
}
    void create(int);
    node *in_successor(node*);
    node *predecessor(node*);
    node *in_predecessor(node*);
    void inorder();
    void pre();
    void preorder();
    void search(int);
    void deletion();
    void delete1(node*,node*);
    void delete2();
};

void TBT::create(int info)
{
    node *new1=NULL,*par=NULL,*c=NULL;
    if(root==NULL)
    {
        root=new node(info);
        root->left=header;
        root->right=header;
        header->left=root;
        header->lbit=1;
    }
    else
    {
        c=root;
        new1=new node(info);
        while(1)
        {
            par=c;
            if(new1->data < c->data)
            {
                if(c->lbit==0)
                {
                    new1->left=par->left;
                    par->left=new1;
                    new1->right=par;
                    par->lbit=1;
                    return;
                }
                c=c->left;
            }
            else
            {
                if(c->rbit==0)
                {
                    new1->right=par->right;
                    par->right=new1;
                    new1->left=par;
                    par->rbit=1;
                    return;
                }
                c=c->right;
            }
        }

    }
}

void TBT::inorder()
{
    node *ptr;
    ptr=root;
    while(ptr->lbit!=0 && ptr!=header)
    {
        ptr=ptr->left;
    }
    while(ptr!=header)
    {
        cout<<ptr->data<<" ";
        ptr=in_successor(ptr);
    }
    cout<<"\n";
}

void TBT::pre()
{
    node *ptr;
        ptr=root;
        while(ptr!=header)
        {
            cout<<ptr->data<<" ";
            cout<<"l"<<ptr->lbit<<"r"<<ptr->rbit<<"  ";
              ptr=predecessor(ptr);
        }
        cout<<"\n";
}

void TBT::preorder()
{
    int flag=0;
    node *ptr;
    ptr=root;

    while(ptr!=header)
    {
        if(flag==0)
        {
            cout<<ptr->data<<" ";
        }

        if(flag==0 && ptr->lbit==1)
        {
            ptr=ptr->left;
        }
        else
        {
            if(ptr->rbit)
            {
                flag=0;
            }
            else
            {
                flag=1;
            }
            ptr=ptr->right;
        }
    }
}

void TBT::search(int x)
{
    node *c;
    c=root; loc=NULL; par=NULL;
    while(c->left!=header || c->right!=header)
    {
        if(c->data==x)
        {
            loc=c;
            cout<<"Found "<<c->data<<endl;
            break;
        }
        else if(x > c->data && c->rbit==1)
        {
            par=c;
            c=c->right;
        }
        else if(x < c->data && c->lbit==1)
        {
            par=c;
            c=c->left;
        }
    }

}

void TBT::deletion()
{
    node *t,*p;
    int x;
    cout<<"\nEnter integer to be deleted\n";
    cin>>x;
    search(x);
    t=loc;    p=par;
    if(t==header)
    {
        cout<<"Word not found\n";
    }
    else
    {
        if(t->lbit!=0 && t->rbit!=0)
        {
            delete2();
        }
        else
        {
            delete1(t,p);
        }
    }

}

void TBT::delete1(node *p1,node *p2)
{
    node *child=NULL;

    if(p1->lbit==0 && p1->rbit==0)
    {
        if(p2->right==p1)
        {
            child=p1->right;
            if(p2!=root)
                p2->rbit=0;
        }
        else if(p2->left==p1)
        {
            child=p1->left;
            if(p2!=root)
                p2->lbit=0;
        }
        else
        {
            p2=p1->right;
        }

    }
    else if(p1->lbit==1)
    {
        child=p1->left;
        child->right=p1->right;
    }
    else if(p1->rbit==1)
    {
        child=p1->right;
        child->left=p1->left;
    }
        if(p2!=header)
        {
            if(p1==p2->left)
            {
                cout<<"deleted "<<endl;
                p2->left=child;

            }
            else if(p1==p2->right)
            {
                cout<<"deleted right\n";
                p2->right=child;

            }
        }
        else
        {
            root=child;
        }
}

void TBT::delete2()
{
    node *p=NULL,*ptr1=NULL,*ptr2=NULL;  //children of children
    p=par;

            ptr1=loc;
            ptr2=in_successor(ptr1);
            delete1(ptr2,ptr1);
            cout<<ptr1->data<<ptr2->data;
        if(p!=header)
        {
            if(ptr1==p->left)
            {
                p->left=ptr2;
                ptr2->right=ptr1->right;
                ptr2->left=ptr1->left;
                ptr2->lbit=ptr1->lbit;
                predecessor(ptr1)->right=ptr2;

            }
            else
            {
                p->right=ptr2;
                ptr2->left=ptr1->left;
                ptr2->right=ptr1->right;
                ptr2->lbit=ptr1->lbit;
                predecessor(ptr1)->right=ptr2;
            }
        }
        else
        {
            ptr2->left=root->left;
            ptr2->lbit=root->lbit;
            ptr2->right=root->right;
            ptr2->rbit=root->rbit;
            in_predecessor(root)->right=ptr2;
            in_successor(root)->left=ptr2;
            root=ptr2;

        }
}

node *TBT::in_successor(node *ptr)
{
    if(ptr->rbit==0)
    {
        return ptr->right;
    }
    else
    {
        ptr=ptr->right;
        while(ptr->lbit==1)
        {
            ptr=ptr->left;
        }
        return ptr;
    }
}

node *TBT::predecessor(node *ptr)
{
    if(ptr->lbit==1)
    {
        return ptr->left;
    }
    else
    {
        while(ptr->rbit==0)
        {
            ptr=ptr->right;
        }
        return ptr->right;
    }
}

node *TBT::in_predecessor(node *ptr)
{
    if(ptr->lbit==0)
    {
        return ptr->left;
    }
    else
    {
        ptr=ptr->left;
        while(ptr->rbit==1)
        {
            ptr=ptr->right;
        }
        return ptr;
    }
}
int main() {

    TBT b;
    //char ch;
    int key;
    //int x;
    b.create(6);
    b.create(9);
    b.create(10);
    b.create(8);
    b.create(7);
    b.create(4);
    b.create(5);
    b.create(3);
    b.create(2);
/*    do
    {
        cout<<"Enter integer data\n";
        cin>>x;
        b.create(x);
        cout<<"Stop creating? \n";
        cin>>ch;
    }while(ch!='y');
*/
    cout<<"Inorder\n";
    b.inorder();
    cout<<"Preorder\n";
    b.preorder();
    cout<<"\npreorder using predecessor\n";
    b.pre();
    cout<<"\nEnter integer to be searched\n";
    cin>>key;
    b.search(key);

    b.deletion();

    b.inorder();

}


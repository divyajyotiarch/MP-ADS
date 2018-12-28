//============================================================================
// Name        : Assignment8.cpp
// Author      : 2179
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<algorithm>
using namespace std;

class node
{
    int data;
    node *left,*right;
public:
    node()
{
        data=-1;
        left=NULL; right=NULL;
}
    friend class obst;
};

class obst
{
    node *root=NULL;
    int sn,a[100];
    float w[100][100],c[100][100],p[100],q[100];
    int r[100][100];

public:
    obst(int x)
{    sn=x;
        for(int i=0;i<x;i++)
        {
            for(int j=0;j<x;j++)
            {
                c[i][j]=-1;
            }
        }
}
    node *ret_root()
        {
            return root;
        }
    void rec_display_inorder(node *);
    void input();
    void calwt(int,int);
    void caltable();
    void optcost(int,int);
    void construct();
    node* rec_constr(int,int);
};

void obst::rec_display_inorder(node *c)
{
    if(c)
    {
        rec_display_inorder(c->left);
        cout<<c->data<<" ";
        rec_display_inorder(c->right);
    }
}

void obst::input()
{

    cout<<"Enter successful probabilities\n";
    for(int i=1;i<=sn;i++)
    {
        cin>>p[i];
    }
    cout<<"Enter unsuccessful probabilities\n";
    for(int i=0;i<sn+1;i++)
    {
        cin>>q[i];
    }
}

void obst::calwt(int i,int j)
{
    if(i==j)
    {
        w[i][j]=q[i];
    }
    else if(i+1==j)
    {
        w[i][j]=q[i]+q[i+1]+p[i+1];
    }
    else
    {
        w[i][j]=w[i][j-1]+p[j]+q[j];
    }
}

void obst::optcost(int i,int j)
{
    int K=i+1;
    float temp,om=9999999,nm=9999999,T;
    if(i==j)
        {
            c[i][j]=0; r[i][j]=0;
        }
        else if(i+1==j)
        {
            c[i][j]=q[i]+q[i+1]+p[i+1];
            r[i][j]=i+1;
        }
        else
        {
            for(int k=i+1;k<=j;k++)
            {
                temp=c[i][k-1]+c[k][j]+w[i][j];
                nm=min(nm,temp);
                if(om!=nm)
                {
                    K=k;
                    T=temp;
                    om=nm;
                }
            }
            r[i][j]=K;
            c[i][j]=T;
        }
}

void obst::construct()
{
    node *new1=NULL;

    int i,j,I,J;
    float om=-1,nm=-1;
    for(int k=0;k<=sn;k++)
    {
        i=0;j=k;
        for(int l=sn;l>=k;l--)
        {
            nm=max(nm,c[i][j]);
            if(om!=nm)
            {
                om=nm;
                I=i;
                J=j;
            }
            i++;
            j=i+k;
        }
    }
    cout<<"max cost\n";
    cout<<c[I][J]<<"\n";

    root=rec_constr(I,J);


}

node* obst::rec_constr(int i,int j)
{
    node *new1=NULL;
    if(r[i][j]!=0)
    {
        new1=new node;
        new1->data=r[i][j];

        new1->left=rec_constr(i,r[i][j]-1);    //k=r[i][j];
        new1->right=rec_constr(r[i][j],j);
        return new1;
    }
    return NULL;

}
void obst::caltable()
{
    int i,j;
    for(int k=0;k<=sn;k++)
    {
        i=0;j=k;
        for(int l=sn;l>=k;l--)
        {
            calwt(i,j);
            optcost(i,j);
            cout<<i<<" "<<j<<" "<<w[i][j]<<" "<<c[i][j]<<" "<<r[i][j]<<"\n";
            i++;
            j=i+k;
        }
    }

}

int main() {

    int n;
    cout<<"Enter no. of successful nodes\n";
    cin>>n;
    obst o(n);
    o.input();
    o.caltable();
    o.construct();
    o.rec_display_inorder(o.ret_root());
    return 0;
}


//============================================================================
// Name        : Assignment4.cpp
// Author      : 2179
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<bits/stdc++.h>
#include<iomanip>
using namespace std;

bool comp(const vector<int>&v1,const vector<int>&v2)
{
    return(v1[2] < v2[2]);
}

class adjgraph
{
    string ct1,ct2,cities[20];
    int n,adj[20][20],e;
    vector < vector <int> > edges;

public:
    adjgraph(int x)
    {
        e=0;
        n=x;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                adj[i][j]=0;
            }
        }
    }
    int ret_edges()
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(adj[i][j]!=0)
                    e++;
            }
        }
        return e;
    }

    int index(string);
    void create();
    void connect();
    void display();
    void prims();
    int minkey(int*,bool*);
    void kruskal();
    void prims2();
};

int adjgraph::minkey(int key[],bool visited[])
{
    int min=99999,minv;

    for(int i=1;i<=n;i++)
        if(visited[i]==false && key[i] < min)
            min = key[i], minv=i;

    return minv;
}
int adjgraph::index(string c)
    {
        for(int i=1;i<=n;i++)
        {
            if(c==cities[i])
            {
                return i;
            }
        }
        return 0;
    }

void adjgraph::create()
{
        cout<<"Enter the cities\n";
        for(int i=1;i<=n;i++)
        {
            cin>>cities[i];
        }
        for(int k=1;k<=n;k++)
        {
            cout<<cities[k]<<" ";
        }
        cout<<"\n";
    }

void adjgraph::connect()
{
    int wt;
    vector < int > a(3);
        cout<<"Enter the pair of cities that you want to connect\n";
        cin>>ct1>>ct2;
        while(!index(ct1))
        {
            cout<<"Enter correct city name\n";
            cin>>ct1;
        }
        while(!index(ct2))
        {
            cout<<"Enter correct city name\n";
            cin>>ct2;
        }
        cout<<"Enter the cost between them\n";
        cin>>wt;
        adj[index(ct1)][index(ct2)]=wt;
        adj[index(ct2)][index(ct1)]=wt;

                        a[0]=index(ct1);
                        a[1]=index(ct2);
                        a[2]=wt;
                        cout<<a[2];
                        edges.push_back(a);
    }

void adjgraph::display()
{
        cout<<"  ";
        for(int k=1;k<=n;k++)
        {
            cout<<cities[k]<<" ";
        }
        cout<<endl;
        for(int kr=1;kr<=n;kr++)
        {
            cout<<cities[kr]<<" ";
            for(int kc=1;kc<=n;kc++)
            {

                cout<<adj[kr][kc]<<"  ";
            }
            cout<<endl;
        }
    }

void adjgraph::prims()
{
    int no=1,mst[n],key[n],mincost=0;    //mst is visited set
    bool vset[n];
    for(int i=1;i<=n;i++)
    {
        key[i]=99999; vset[i]=false;
    }

    key[1]=0;
    mst[1]=-1;
    while(no <= n)
    {
        int i=minkey(key,vset);

        vset[i]=true;

        for(int j=1;j<=n;j++)
        {
            if(adj[i][j] && vset[j]==false && adj[i][j]<key[j])
            {
                mst[j] = i;
                key[j]=adj[i][j];
            }
        }
        no++;
    }
    cout<<"MST by Prims\n";
    cout<<"Src  Dest  Wt\n";
    for(int k=2;k<=n;k++)
    {
        cout<<cities[mst[k]]<<" ";
        cout<<cities[k]<<" ";
        cout<<adj[k][mst[k]]<<"\n";
    }
    for(int k=2;k<=n;k++)
    {
        mincost=mincost+adj[k][mst[k]];
    }
    cout<<"Path length ";
    cout<<mincost<<"\n";
}
void adjgraph::prims2()
{
    int visited[n],no=0,mincost=0,min=99;
    int x,y;
    for(int i=1;i<=n;i++)
    {
        visited[i]=0;
    }

    visited[1]=1;
    x=1; y=1;
    while(no < n-1)
    {
        x=y;
                for(int j=1;j<=n;j++)
                {
                    if(!visited[j] && adj[x][j]!=0)
                    {
                        if(min > adj[x][j])
                        {
                            min = adj[x][j];
                             y=j;
                        }
                    }
                }
                min=99999;
        mincost+=adj[x][y];
        cout<<cities[x]<<" - "<<cities[y]<<" wt "<<adj[x][y]<<endl;
        visited[y]=1;
        no++;
    }
    cout<<"Path length ";
    cout<<mincost<<endl;

}

void adjgraph::kruskal()
{
    int visited[n],set[n],mincost=0;

    vector < vector < int > > mst;
    vector < int > b(3);

    for(int i=1;i<=n;i++)
    {
        visited[i]=0;
    }
    for(int i=1;i<=n;i++)
    {
        set[i]=i;
    }
    sort(edges.begin(),edges.end(),comp);
    int m=edges.size();
    cout<<"Src   Dest   Wt    Sorted\n";
    for(int i=0;i<m;i++)
    {
        cout<<cities[edges[i][0]]<<"  "<<cities[edges[i][1]]<<"  "<<edges[i][2]<<"\n";
    }

    int I,J,w;

    for(int i=0;i<edges.size();i++)
    {
        I = edges[i][0];
        J = edges[i][1];
        w = edges[i][2];

        if(set[I]!=set[J] && ( visited[I]==0||visited[J]==0) )
        {
            set[I]=J;
            set[J]=J;
            visited[I]=1; visited[J]=1;
            b[0]=I; b[1]=J;    b[2]=w;
            mst.push_back(b);
        }
    }
    int ms=mst.size();
    cout<<"MST by Kruskal\n";
    cout<<"Src  Dest  Wt\n";
    for(int i=0;i<ms;i++)
    {
        cout<<cities[mst[i][0]]<<"  "<<cities[mst[i][1]]<<"  "<<mst[i][2]<<"\n";
    }
    for(int k=0;k<ms;k++)
    {
        mincost=mincost+mst[k][2];
    }
    cout<<"Path length ";
    cout<<mincost<<"\n";

}


int main()
{
    int n,c;
    cout<<"No.of cities??\n"; cin>>n;
    adjgraph ag(n);
    ag.create();
    do
    {
    ag.connect();
    cout<<"enter edges?? 1/0 \n";
    cin>>c;
    }while(c!=0);
    ag.display();
    ag.prims();
    ag.kruskal();
    return 0;
}


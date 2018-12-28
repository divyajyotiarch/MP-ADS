#include<iostream>
#include<list>
#include<queue>
#include<stack>
using namespace std;

class node
{
    string city;
    float time;
    node *next;
public:
    friend class graph;

};

class graph
{
    list<node *>g[100];
    string cities[100];
    int v;
public:
    graph(int x)
{
        v=x;

}
    int index(string);
    void insertv();
    void deletev();
    void inserte();
    void delete_e();
    void create();
    void connect();
    void degree();
    void display();
    void depth_first();
    void breadth_first();
};

int graph::index(string cname)
{
    for(int i=1;i<=v;i++)
    {
        if(cities[i]==cname)
            return i;
    }
    return 0;
}

void graph::create()
{
    for(int i=1;i<=v;i++)
    {
        cout<<"Enter city name "<<i<<endl;
        cin>>cities[i];
    }

}

void graph::insertv()
{
    int n;
    cout<<"Enter the no. of extra vertices to be added\n";
    cin>>n;
    for(int i=v+1;i<=v+n;i++)
    {
        cout<<"Enter city name\n";
        cin>>cities[i];
    }
    v=v+n;
}

void graph::deletev()
{
    string city1;    int k;
    cout<<"Enter the city to be deleted\n";
    cin>>city1;
    k=index(city1);
    while(!g[k].empty())
    {
        g[k].pop_back();
    }
    for(int i=k;i<=v;i++)
    {
        cities[i]=cities[i+1];
        g[i]=g[i+1];
    }
    v=v-1;
}

void graph::inserte()
{
    string city1;    node *new1=NULL;
    cout<<"Enter source city \n";
    cin>>city1;
    cout<<"Enter destination city\n";
    new1=new node;
    cin>>new1->city;
    g[index(city1)].push_back(new1);

}

void graph::delete_e()
{
    string city1,city2;
    list<node *>::iterator it;
    cout<<"Enter the source city\n";
    cin>>city1;
    cout<<"Enter the destination city between which the edge lies\n";
    cin>>city2;
    it=g[index(city1)].begin();
    while(it!=g[index(city1)].end())
    {
        if(city2==(*it)->city)
        {
            g[index(city1)].remove((*it));
            break;
        }
        it++;
    }

}

void graph::connect()
{
    int n;
    string city1;
    for(int i=1;i<=v;i++)
    {
        cout<<"How many cities are connected to "<<cities[i]<<endl;
        cin>>n;
        for(int j=0;j<n;j++)
        {
            node *new2=NULL;
            new2=new node;
            cout<<"Enter city\n";
            cin>>city1;
            if(!index(city1))
            {
                cout<<"Enter correct city name\n";
                delete(new2); j--;
            }
            else
            {
                new2->city=city1;
                g[i].push_back(new2);
            }
        }
    }
}

void graph::degree()
{
    list<node *>::iterator it;
    int indeg,outdeg;
    string city2;

    for(int i=1;i<=v;i++)
    {
        outdeg=0;    indeg=0;
        cout<<"In-degree of "<<cities[i]<<" ";
        for(int j=0;j<v;j++)
        {
            it=g[j].begin();
            while(it!=g[j].end())
            {
                city2=(*it)->city;
                if(cities[i]==city2)
                {
                    indeg++;
                }
                it++;
            }
        }
        cout<<indeg<<endl;

        outdeg=g[i].size();
        cout<<"Out-degree of "<<cities[i]<<" "<<outdeg<<endl;

        cout<<"degree of city "<<cities[i]<<" (if was an undirected graph) "<<(indeg+outdeg)<<endl;
    }



}

void graph::depth_first()
{
    int visited[v],v1,v2;

    string city2,city1;
    list<node *>::iterator it;
    stack<string>s;

    cout<<"Enter the city visited first\n";
    cin>>city2;

    v2=index(city2);
    for(int i=1;i<=v;i++)
    {
        visited[i]=0;
    }
    s.push(cities[v2]);
    while(!s.empty())
    {
        city1=s.top();
        s.pop();
        v1=index(city1);
        if(visited[v1]==0)
        {
            cout<<city1<<" ";
            visited[v1]=1;
        }

        it=g[v1].begin();
        while(it!=g[v1].end())
        {
            if(visited[index((*it)->city)]==0)
            {
                s.push(cities[index((*it)->city)]);
            }
            it++;
        }

    }

}

void graph::breadth_first()
{
    int visited[v],v1,v2;

        string city2,city1;
        list<node *>::iterator it;
        queue<string>q;

        cout<<"Enter the city visited first\n";
        cin>>city2;

        v2=index(city2);
        for(int i=1;i<=v;i++)
        {
            visited[i]=0;
        }
        q.push(cities[v2]);
        while(!q.empty())
        {
            city1=q.front();
            q.pop();
            v1=index(city1);
            if(visited[v1]==0)
            {
                cout<<city1<<" ";
                visited[v1]=1;
            }

            it=g[v1].begin();
            while(it!=g[v1].end())
            {
                if(visited[index((*it)->city)]==0)
                {
                    q.push(cities[index((*it)->city)]);
                }
                it++;
            }

        }
}

void graph::display()
{
    list<node *>::iterator it;
    for(int i=1;i<=v;i++)
    {
        cout<<"Cities connected to "<<cities[i]<<" -> ";
        it=g[i].begin();
        while(it!=g[i].end())
        {
            cout<<(*it)->city<<" ";
            it++;
        }
        cout<<endl;
    }

}

int main()
{
    int n,x;
    cout<<"Enter no. of cities(vertices)? \n";
    cin>>n;
    graph g(n);
    do
    {
        cout<<"\n1.Create \n2.Display \n3.In-degree and out-degree \n4.Add new city \n5.Delete City \n6.Connect city \n7.Delete edge \n";
        cout<<"8.DFS traversal \n9.BFS traversal \n";
        cout<<"Enter option\n";
        cin>>x;
        switch(x)
        {
            case 1: g.create();
                g.connect();
            break;

            case 2:    g.display();
            break;

            case 3: g.degree();
            break;

            case 4: g.insertv();
            break;

            case 5:    g.deletev();
            break;

            case 6: g.inserte();
            break;

            case 7: g.delete_e();
            break;

            case 8: g.depth_first();
            break;

            case 9: g.breadth_first();
            break;

        }
    }while(x<10);




}



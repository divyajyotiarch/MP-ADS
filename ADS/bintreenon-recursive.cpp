#include<iostream>
#include<queue>
using namespace std;

class node
{
    int data;
    node *left;
    node *right;
public:
    friend class Btree;
    friend class Queue;
};

class Queue
{
    int front,rear;
    node *q[20];
public:
    Queue()
{
    front = -1;
    rear = -1;
}
    node *f()
    {
        return q[front];
    }
    void pop();
    void push(node*);
    int sizeq()
    {
        int count=0;
        for(int i=front;i!=rear+1;i++)
        {
            count++;
        }
        return count;
    }
    bool empty()
    {
        if(front==-1&&rear==-1)
        {
            return true;
        }
        return false;
    }
};

class Stack
{
    int top;
    node *st[10];
public:
    Stack()
{
        top=-1;
}
    node *t()
        {
            return st[top];
        }
        void pop();
        void push(node*);
        bool empty()
        {
            if(top==-1)
            {
                return true;
            }
            return false;
        }
        friend class Btree;
};

class Btree
{
    Queue q1,q2;
    Stack s1,s2;
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
    void create();
    void height_nodecount();
    void display_inorder();
    void display_post();
    void display_pre();
};

void Btree::height_nodecount()
{
    int h,nc;
    node *temp;
    queue<node *>q;
    if(root==NULL)
    {
        return;
    }
    q.push(root);
    h=0;
    while(1)
    {
        nc=q.size();
        if(nc==0)
        {
            cout<<"Height of tree is "<<h<<"\n";
            break;
        }
        h++;
        while(nc>0)
        {
            temp=q.front();
            q.pop();
            if(temp->left!=NULL)
            {
                q.push(temp->left);
            }
            if(temp->right!=NULL)
            {
                q.push(temp->right);
            }
            nc--;
        }
    }
    while(!q.empty())
        {
            q.pop();
        }
        q.push(root);
        int in=0,ln=0;
        while(h>=1)
        {
            int n=q.size();
            h--;
            while(n > 0)
            {
                temp=q.front();
                q.pop();
                if(temp!=root&&(temp->left!=NULL || temp->right!=NULL))
                {
                    in++;
                }
                if(temp!=root && temp->left==NULL && temp->right==NULL)
                {
                    ln++;
                }
                if(temp->left!=NULL)
                {
                    q.push(temp->left);
                }
                if(temp->right!=NULL)
                {
                    q.push(temp->right);
                }
                n--;
            }
        }
        cout<<"internal nodes "<<in<<"\nleaf nodes "<<ln;
}

void Queue::push(node *new2)
{
    if(rear==-1&&front==-1)
    {
        rear=0; front=0;
        q[rear]=new2;
    }
    else
    {
        rear=rear+1;
        q[rear]=new2;
    }
}

void Stack::push(node *new2)
{
    if(top==-1)
    {
        top=0;
        st[top]=new2;
    }
    else
    {
        top=top+1;
        st[top]=new2;
    }
}

void Queue::pop()
{
    if(rear==-1&&front==-1)
    {
        cout<<"Underflow\n";
    }
    else if(front==rear)
    {
        front=-1; rear=-1;
    }
    else
    {
        front=front+1;
    }
}

void Stack::pop()
{
    if(top==-1)
    {
        cout<<"Underflow\n";
    }
    else
    {
        top=top-1;
    }
}

void Btree::create()
{
    node *new1=NULL,*par=NULL;
    char ch;
    if(root==NULL)
    {
        root=new node;
        cout<<"Enter data\n";
        cin>>root->data;
        root->left=NULL;
        root->right=NULL;
        q1.push(root);
    }
    else
    {
        par = q1.f();
        q1.pop();
        if(par->left==NULL)
        {
            cout<<"Do you want to enter left child of "<<par->data<<"? y/n \n";
            cin>>ch;
            if(ch=='y')
            {
                new1=new node;
                cout<<"Enter data\n";
                cin>>new1->data;
                par->left=new1;
                new1->left=NULL;
                new1->right=NULL;
                q1.push(new1);
            }
        }
        if(par->right==NULL)
        {
            cout<<"Do you want to enter right child of "<<par->data<<"? y/n \n";
            cin>>ch;
            if(ch=='y')
            {
                new1=new node;
                cout<<"Enter data\n";
                cin>>new1->data;
                par->right=new1;
                new1->left=NULL;
                new1->right=NULL;
                q1.push(new1);
            }
        }
    }
}

void Btree::display_inorder()
{
    s1.top=-1;
    node *ptr;
    ptr=root;
    step2:
    while(ptr!=NULL)
    {
        s1.push(ptr);
        ptr=ptr->left;
    }
    while(!s1.empty())
    {
        ptr=s1.t();
        cout<<ptr->data<<" ";
        s1.pop();
        if(ptr->right!=NULL)
        {
            ptr=ptr->right;
            goto step2;
        }
    }
}

void Btree::display_post()
{
    s1.top=-1; s2.top=-1;
    node *ptr=NULL;
    ptr=root;
    s1.push(root);
    while(!s1.empty())
    {
        ptr=s1.t();
        s1.pop();
        s2.push(ptr);
        if(ptr->left!=NULL)
            s1.push(ptr->left);
        if(ptr->right!=NULL)
            s1.push(ptr->right);
    }
    ptr=s2.t();
    while(!s2.empty())
    {
        s2.pop();
        cout<<ptr->data<<" ";
        ptr=s2.t();
    }
}

void Btree::display_pre()
{
    s1.top=-1;
    node *ptr=NULL;
    ptr=root;
    s1.push(root);
    while(!s1.empty())
    {
        ptr=s1.t();
        s1.pop();
        cout<<ptr->data<<" ";
        if(ptr->right!=NULL)
            s1.push(ptr->right);
        if(ptr->left!=NULL)
            s1.push(ptr->left);
    }
}

int main()
{
    char c;
    Btree b;
    do
    {
        b.create();
        cout<<"Stop creating? y/n \n";
        cin>>c;
    }while(c!='y');
    cout<<"\nBinary Tree inorder\n";
    b.display_inorder();
    cout<<"\nBinary Tree postorder\n";
    b.display_post();
    cout<<"\nBinary Tree preorder\n";
    b.display_pre();
    cout<<"\n";
    b.height_nodecount();
    return 0;
}

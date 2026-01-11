#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
class Queue
{
    public:
    int val;
    Queue* next;
};
Queue* front=NULL;
Queue* Enqueue(Queue* q,int n)
{
    Queue* temp=new Queue();
    temp->val=n;
    temp->next=NULL;
    Queue*rear=NULL;
    if(q==NULL)
    {
        front=temp;
        temp->next=temp;
        return temp;
    }
    else{
        temp->next=front->next;
        front->next=temp;
        return front;
    }
}
void print(Queue* q)
{
    if(front==NULL)
    {
        cout<<"Queue is empty\n";
        return;
    }
    Queue* temp=front->next;
    while(true)
    {
        cout<<temp->val<<" ";
        if(temp==front)
        break;
        temp=temp->next;
    }
}
int dequeue(Queue* q)
{
    if(front==NULL)
    {
        cout<<"Queue is empty,no element to delete\n";
        q=NULL;
        return -1;
    }
    if(front==front->next)
    {
        int x=front->val;
        front=NULL;
        return x;
    }
    else{
        Queue* prev=NULL;
        Queue* curr=front->next;
        int x;
        while(true)
        {
            if(curr==front)
            {
                x=curr->val;
                prev->next=curr->next;
                front=prev;
                curr->next=NULL;
                return x;
            }
            else{
                prev=curr;
                curr=curr->next;
            }
        }
        
    }
}
int peek(Queue* q)
{
    if(front==NULL)
    {
        return -1;
    }
    else
    {
        return front->val;
    }
}
int size(Queue* q)
{
    
    if(front==NULL) return 0;
    else
    {
        Queue* temp=front->next;
    int count=0;
        while(true)
        {
            count++;
            if(front==temp) return count;
            temp=temp->next;
        }
    }
}

int main()
{
    Queue*q = NULL;
    int c;
    do
    {
        cout<<"Queue Menu:\n";
        cout<<"1.Enqueue\n2.Dequeue\n3.peek\n4.Size\n5.Print\n6.Exit\n";
        cout<<"Enter your choice:\n";
        cin>>c;
        if(c<1 || c>6){cout<<"Invalid\n"; continue;} 
        if(c==6)break;
        if(c==1)
        {
            int n;
            cout<<"Enter the value:";
            cin>>n;
            q=Enqueue(q,n);
        }
        else if(c==2)
        {
            if(dequeue(q)==-1)
            {
                cout<<"No elements in Queue to peek\n";

            }
            else
            cout<<"Deleted Element: "<<dequeue(q)<<"\n";
        }
        else if(c==3)
        {
            if(peek(q)==-1)
            {
                cout<<"No elements in Queue to peek\n";

            }
            else
            cout<<"Peeked Element"<<peek(q)<<"\n";
        }
        else if(c==4)
        {
            cout<<"Size:"<<size(q)<<"\n";
        }
        else if(c==5)
        {
            print(q);
        }
    } while (true);
    
}
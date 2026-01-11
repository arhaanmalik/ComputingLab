#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* next;

    Node(int data1, Node* next1 = nullptr){
        data = data1;
        next = next1;
    }
};

Node* arrtoll(int ll[], int n){
   int val=0;
    Node* head = new Node(ll[0]);
    val += pow(10,n-1) * ll[0];
       Node* nxt=head;
     
       int x =n-2;
    for(int i =0;i<n;i++){

        Node* temp = new Node(ll[i]);
        nxt->next = temp;
        val += pow(10,x) * ll[i];
        x--;
    }

 

   
}



int main(){

    Node* head;
int n;
cout<<"Enter the size of LL 1 :";

cin>>n;

int ll1[n];

cout<<"Enter Your LL 1: ";
for(int i=0;i<n;i++){
cin>>ll1[i];
}
int x=n-1;
int val1=0;
for(int i=0;i<n;i++){
 val1 += pow(10,x) * ll1[i];
 x--;
}
arrtoll(ll1,n);

int m;
cout<<"Enter the size of LL 2 :";
cin>>m;

int ll2[n];
cout<<"Enter Your LL 2: ";
for(int i=0;i<n;i++){
cin>>ll2[i];
}

int y=m-1;
int val2=0;
for(int i=0;i<n;i++){
 val1 += pow(10,y) * ll2[i];
 y--;
}

arrtoll(ll1,n);
int result = val1+val2;
cout<<result;
}

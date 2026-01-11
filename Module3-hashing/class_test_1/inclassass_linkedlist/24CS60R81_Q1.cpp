#include<iostream>
using namespace std;

struct Node{
    public:
    int data;
    Node* next;

    Node(int data1, Node* next1 = nullptr){
        data = data1;
        next = next1;
    }
};

Node* arrtoll(int ll[], int n){

    Node* head = new Node(ll[0]);
       Node* nxt=head;
    for(int i =0;i<n;i++){

        Node* temp = new Node(ll[i]);
        nxt->next = temp;
    }
  
   
}

Node* searchitterative(Node* head, int find){
         Node* current =head;
         int x=0;
        // if(current == nullptr){
         //   return 0;
         //}
         while(current->next != nullptr){
          cout<<current->data;
            if(current->data==find){
                x=1;
                break;
            
            }
            
               current = current->next;
            
         }
            //free(temp);
         if(x==1){
            cout<<"1";
         }
         else{
         cout<<"0";
         }
}




Node* searchrecursive(Node* head, int find){
         Node* temp =head;
         int x=0;
         if(temp == nullptr){
            return 0;
         }
         while(temp->next != nullptr){
            if(temp->data==find){
                x=1;
                break;
            
            }
            
               temp = temp->next;
            
         }
            //free(temp);
         if(x==1){
            cout<<"1";
         }
         else{
         cout<<"0";
         }
}



int main(){

    struct Node* head;
int n;
cout<<"Enter the size of LL :";
cin>>n;
int ll[n];
cout<<"Enter Your LL : ";
for(int i=0;i<n;i++){
cin>>ll[i];
}

 head = arrtoll(ll,n);

 int find;
 cout<<"Enter the number you want to search in LL: ";
 cin>>find;
 int choice;
 cout<<"Press 1 for Itterative approch  and 2 for Recursive approch : ";
 cin>>choice;

if(choice ==1){
      searchitterative(head,find);
}
else{
    searchrecursive(head,find);
}

}
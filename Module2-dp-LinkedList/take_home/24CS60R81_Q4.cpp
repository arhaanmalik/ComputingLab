#include <iostream>
#include<bits/stdc++.h>
using namespace std;

 class Stack{

    public : 
        int* arr;
        int top;
        int size;
        Stack(int size){
           this->size = size;
            arr = new int[size];
            top =-1;

        }

     void push(int element){

        if(size - top > 1){
            
            top++;
            arr[top]=element;
        }
        else{
            cout<<"Stack overflow";
        }
      }

      void pop(){

        if(top >=0){
            top--;
        }
        else{
            cout<<"Underflow";
        }
      }

     int peek(){
        if(top>=0 && top<size){
            return arr[top];
        }
        else{
            cout<<"Empty";

            return -1;
        }
     } 

     bool isEmpty(){
        if(top== -1){
            return true;
        }
        else{
            return false;
        }
     }

  };

  int lengthh(string s){
    int i=0;
    int cnt=0;
    while(s[i] !='\0'){
        cnt++;
        i++;

    }
    return cnt;
  }

int lvp(string s) {
    
    int n =lengthh(s);

    Stack stk(n); 
    stk.push(-1);  
    int maxLength = 0;

    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            
            stk.push(i);
        } else {
           
            stk.pop();
            
            if (stk.isEmpty()) {
                
                stk.push(i);
            } else {
               
                maxLength = max(maxLength, i - stk.peek());
            }
        }
    }

    return maxLength;
}

int main() {
    string s;
    cout << "Enter input: ";
    cin >> s;

    int result = lvp(s);
    cout << "Length of the longest valid parentheses substring: " << result << endl;

    return 0;
}

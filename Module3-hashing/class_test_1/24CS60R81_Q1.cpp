#include<iostream>
#include<bits/stdc++.h>

using namespace std;


int main(){
 int row;

 int val=1;
 
 cout<<"Enter the No. of Rows : ";
 cin>>row;
  
  for(int i =0;i<row;i++){
   
     for(int j=0;j<=i;j++){
          if(j==0|| i==0){
            val=1;
          }
          else{
            val=val*(i-j+1)/j;
          }
          cout<<val<<" ";
     }
    
    for(int b=1;b<=row-i;b++){
     cout<<" ";
   }
     cout<<endl;
  }
}
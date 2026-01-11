#include<iostream>
#include<bits/stdc++.h>

using namespace std;
int maximum(int x, int y){
   if(x>y){
      return x;
   }
   else{
    return y;
   }

}

int maximumpoints(int* array, int n){
    int newarr[n+2];
    newarr[0]=1;
    newarr[n+1]=1;

    for(int i=0;i<n;i++){
          
          newarr[i]=array[i-1];
    }

    int dp[n+2][n+2];

    memset(dp,0,sizeof(dp));

    for(int length =1; length<=n;length++){
        for(int low =1;low<=n-length+1; low++){

            int high = low+length-1;
              
              for(int k=low;k<=high;k++)
              {
                dp[low][high] =maximum(dp[low][high],newarr[low-1]*newarr[k]*newarr[high+1]+dp[low][k+1]*dp[k+1][high]);
              }

            
        }
    }
    dp[1][n];

}

int main(){
 
 int n;
 cout<<"Enter n : ";
 cin>>n;

 int array[n];
 cout<<"Enter element of array : ";
      
      for(int i=0;i<n;i++){
          
          cin>>array[i];
      }

      int ans = maximumpoints(array, n);
      cout<<"Your profit : "<<ans<<endl;

}
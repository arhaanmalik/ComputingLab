#include<iostream>
#include<bits/stdc++.h>

using namespace std;


class job{
    public : 
    char id;
    int deadline;
    int prft;

};

int compare(const void*x ,const void* y){
    job*temp1=(job*)x;
    job*temp2=(job*)y;
    return(temp2->prft - temp1->prft);
}
int min(int x, int y){
   if(x<y){
      return x;
   }
   else{
    return y;
   }

}

void jobseq(job array[], int n){

    qsort(array,n,sizeof(job), compare);

   int res[n];
   int dummy[n];

   for(int i=0;i<n;i++){
     dummy[i]=0;
   }
 for(int i=0;i<n;i++){
    for(int j=min(n,array[i].deadline)-1;j>=0;j--){
        if(dummy[j]==0){
            res[j]=i;
            dummy[j]=1;
            break;
        }
    }
 }
        for(int i=0;i<n;i++){
            if(dummy[i]){
               // int x=res[i];
                cout<<array[res[i]].id<<" ";
            }
        }

}

int main(){
    int n;
    //cout<<"Enter the number of jobs : ";
   // cin>>n;

    job array[n]={ {'a',4,20},
    {'b',1,10},
    {'c',1,40},
    {'d',1,30}
    };

   // for(int i=0;i<n;i++){
     //   cin>>array[i].id;
    //    cin>>array[i].deadline;
  //      cin>>array[i].prft;
   // }

     int n = sizeof(array)/sizeof(array[0]);     
       cout<<"Sequences : ";
         jobseq(array,n);
    
}
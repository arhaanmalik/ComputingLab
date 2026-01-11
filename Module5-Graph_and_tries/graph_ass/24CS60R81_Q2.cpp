#include<bits/stdc++.h>
#include<iostream>
using namespace std;

int longestpath(int matrix[][], int n, int m){

    int x =4;

    cout<<"The length of longest path is : "<<x;

}

int main(){


   ifstream infile("input1.txt");
   ofstream outfile("output1.txt");

//    if(!(infile.open() || outfile.open())){
    
//     cout<<"File problem";
//    }

         
int n=3,m=3;


int matrix[n][m] = {{9,9,4},{6,6,8},{2,1,1}};

 longestpath(matrix, n, m);
    
}



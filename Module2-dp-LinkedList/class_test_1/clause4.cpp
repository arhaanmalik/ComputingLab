#include <iostream>
#include<bits/stdc++.h>
using namespace std;

struct Table {
    int weight;
    int value;
};

int maxx(int a, int b) {

    if(a>b){
        return a;
    }
    else {
        return b;
    }
  
}

int knpsck(Table tableData[], int n, int W) {
    int dp[n + 1][W + 1];

    
    for (int j = 0; j <= n; ++j) {
        for (int w = 0; w <= W; ++w) {
            dp[j][w] = 0;
        }
    }

    for (int j = 1; j <= n; ++j) {
        for (int w = 0; w <= W; ++w) {
            if (tableData[j - 1].weight <= w) 
                dp[j][w] = maxx(dp[j - 1][w], dp[j - 1][w - tableData[j - 1].weight] + tableData[j - 1].value);
            else 
                dp[j][w] = dp[j - 1][w];
            
        }
    }

    return dp[n][W];
}

int main() {
    int m;
    int W;
     cout<<"Enter your inputs : ";
    cin >> m;
    cin >> W;
    Table tableData[m];
   
    for (int i = 0; i < m; ++i) {
        cin >> tableData[i].weight;
        cin>> tableData[i].value;
    }


    cout << "Clause 4: ";
    cout<< knpsck(tableData, m, W);

   

    return 0;
}

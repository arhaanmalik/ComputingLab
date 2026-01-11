#include <iostream>
#include <bits/stdc++.h>

using namespace std;


int mps(int grid[][], int m, int n) {
  
    int dp[m][n];

    
    dp[0][0] = grid[0 * n + 0];









    return dp[m-1][n-1];
}


int main() {
    int row, col;
    cout << "Number of rows : ";
    cin >> row;
    cout << "Number of columns : ";
    cin >> col;

   int grid[row][col];

    cout << "Enter the grid elements (row by row):";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cin >> grid[i][j];
        }
    }

    int result = mps(grid, row, col);
    cout << "The minimum path sum is: " << result << endl;

    
    
    return 0;
}
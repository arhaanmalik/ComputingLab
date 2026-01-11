#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int count_0_1(const char* str, int c0, int c1) {
    
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '0') {
            c0++;
        } else if (str[i] == '1') {
            c1++;
        }
    }
    return c0,c1;

}


int fmf(char strs[][100], int nbs, int m, int n) {

  int dp[m+1][n+1];



    for (int i = 0; i < nbs; ++i) {
        int c0, c1 =0;
         c0,c1 = count_0_1(strs[i], c0, c1);

        // Update dp table in reverse to avoid overwriting results
        for (int j = m; j >= c0; --j) {
            for (int k = n; k >= c1; --k) {
              
            }
        }
    }





}

int main() {

    int nbs;
    cout << "Number of binary strings: ";
    cin >>  nbs;

    int m, n;
    
    cout << "Maximum number of 1's: ";
    cin >> n;
         cout << "Maximum number of 0's: ";
         cin >> m;
    

           // Dynamically allocate memory for an array of strings
    char strs[nbs][100];

    cout << "Enter the binary strings:\n";
    for (int i = 0; i < nbs; ++i) {
        cin >> strs[i];
    }

    int result = fmf(strs, nbs, m, n);
    cout << "The size of the largest subset is: " << result << endl;

    return 0;
}
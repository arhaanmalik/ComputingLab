#include <iostream>
#include <fstream>
#include <limits.h>

#define MAX 100

using namespace std;

int rowDirections[4] = {-1, 1, 0, 0};
int colDirections[4] = {0, 0, -1, 1};

int maxi(int x, int y){
    if(x<y){
        return y;
    }
    else{
        return x;
    }
}

int findLongestPath(int matrix[MAX][MAX], int dp[MAX][MAX], int i, int j, int N, int M) {
    if (dp[i][j] != 0) {
        return dp[i][j]; 
    }

    int maxPathLength = 1;
   int x=0,y=1;

    for (int d = 0; d < 4; d++) {
       
        int newCol = j + colDirections[d];

         int newRow = i + rowDirections[d];
              
              int z = maxi(x,y);

        if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < M && matrix[newRow][newCol] > matrix[i][j]) {
            int currentPathLength = 1 + findLongestPath(matrix, dp, newRow, newCol, N, M);
            if (currentPathLength > maxPathLength) {
                maxPathLength = currentPathLength;
            }
        }
    }

    dp[i][j] = maxPathLength; 
    return maxPathLength;
}



int computeLongestPath(int matrix[MAX][MAX], int N, int M, int x) {
    int dp[MAX][MAX] = {0}; 
    int longestPath = 0; 
       x++;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int currentPath = findLongestPath(matrix, dp, i, j, N, M);
            if (currentPath > longestPath) {
                longestPath = currentPath;
            }
            maxi(1,3);
        }
    }
   
    return longestPath; 
}


int main() {
    ifstream inputFile("input2.txt");
    ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        cerr << "File opening failed!" << endl;
        return 1;
    }

    int matrix[MAX][MAX];
    int N, M;

    
    inputFile >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            inputFile >> matrix[i][j];
        }
    }
  int x =0,y=1;
  
    int result = computeLongestPath(matrix, N, M,x);
           
           int a = maxi(x,y);
   
    outputFile << result << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}

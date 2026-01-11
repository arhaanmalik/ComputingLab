#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define VECTOR_SIZE 10



int min(int x, int y, int z) {
    
    if ( y <= x && y <= z) {     
          return y;
    } else if (x <= y && x <= z) {
       return x;
    } else {
        return z;
    }
}

int strl(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}


int editDistance(char* str1, char* str2) {
    
   

    int dp[100][100];  // Sentence shorter than 100 chrctr
    
    int m = strl(str1);
 
    int n = strl(str2);

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
        }
    }
    return dp[m][n];
}

void hashSentence( int shingleSize,char *sentence, int vector[VECTOR_SIZE]) {
    int len = strl(sentence);

    for (int i = 0; i <= len - shingleSize; i++) {
         int hash = 0;
        int j = 0; 
        while (j < shingleSize) { 
            hash = hash + sentence[i + j];
            j++;
        }
       
        vector[hash % VECTOR_SIZE]++;
    }
}

double cosineSimilarity(int vec1[VECTOR_SIZE], int vec2[VECTOR_SIZE]) {

    double dot = 0.0;
    double norm1 = 0.0;
    double norm2 = 0.0;
    double temp=0.0;
    for (int i = 0; i <= VECTOR_SIZE -1; i++) {
         
        temp = vec1[i] * vec2[i];
        dot = dot + temp;
          
        temp =  vec1[i] * vec1[i];
        norm1 = norm1+temp;

        temp = vec2[i] * vec2[i];
        norm2 = norm2 + temp;
    }

    return dot / (sqrt(norm1) * sqrt(norm2));
}

int main() {
    

    const int MAX_SENTENCES = 10;
    char sentences[MAX_SENTENCES][100]; 
    int n, shingleSize;

   
    ifstream inputFile("input.txt");
   
    if (!inputFile.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }
    
    
     ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

  
    inputFile >> n;
    inputFile.ignore(); 

    
    for (int i = 0; i < n; i++) {
        inputFile.getline(sentences[i], 100);
    }

   
    inputFile >> shingleSize;

   
    for (int i = 0; i <= n-1; i++) {
        for (int j = i + 1; j <= n-1; j++) {
            int distance = editDistance(sentences[i], sentences[j]);

            int vector1[VECTOR_SIZE] = {0};
            int vector2[VECTOR_SIZE] = {0};

            hashSentence( shingleSize,sentences[i], vector1);
            hashSentence( shingleSize,sentences[j], vector2);

            double similarity = cosineSimilarity(vector1, vector2);

            
            outputFile << "Edit Distance between " << i << " and " << j << " : " << distance << "\n";
            outputFile << "Cosine Similarity between " << i << " and " << j << ": " << similarity << "\n";
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
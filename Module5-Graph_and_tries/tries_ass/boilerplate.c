#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of words and maximum word length
#define MAX_WORDS 50000
#define MAX_WORD_LEN 100

// Structure for Trie node (Hint)
// struct TrieNode {
//     struct TrieNode *children[26]; // Each node can have 26 children (for each letter of the alphabet)
//     int isEndOfWord;               // Flag to indicate if the node represents the end of a word
// };

typedef struct TrieNode TrieNode; // Defining the TrieNode structure

// Function prototypes with descriptions
void Add(TrieNode *root, char *w);
// Adds the word `w` to the Trie and sets its initial rank to 1. 

void Delete(TrieNode *root, char *w);
// Deletes the word `w` from the Trie, ensuring the rank is removed appropriately.

int SpellCheck(TrieNode *root, char *w);
// Checks if the word `w` is spelled correctly in the Trie. Returns 1 if correct, otherwise 0.

void Autocomplete(TrieNode *root, char *prefix, FILE *outputFile);
// Finds and prints all words in the Trie that start with the prefix `prefix`, sorted by rank and lexicographically.

void Autocorrect(TrieNode *root, char *w, int maxCost, FILE *outputFile);
// Finds the closest word in the Trie to `w` using Levenshtein distance and updates the rank.

int CheckConcatenation(TrieNode *root, char *w, FILE *outputFile);
// Checks if `w` can be formed by concatenating two or more words in the Trie. Returns 1 if possible, otherwise 0.

int main(int argc, char *argv[]) {
    FILE *file = fopen("dict.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Could not open output file output.txt\n");
        return 1;
    }

    char word[MAX_WORD_LEN];

    // TODO : Replace NULL with actual Trie initialization code
    TrieNode *root = NULL; 
    while (fgets(word, MAX_WORD_LEN, file) != NULL) {
        word[strcspn(word, "\n")] = '\0';

        // Add word to Trie
        Add(root, word);
    }

    // now read the query file 
    file = fopen("input.txt", "r");
    
    int N, Q;
    
    fscanf(file, "%d %d", &N, &Q);
    
    // Reading the queries and processing them
    for (int i = 0; i < Q; i++) {
        int x;
        char w[MAX_WORD_LEN];
        fscanf(file, "%d %s", &x, w);

        switch (x) {
            case 1:
                // Add word w to the Trie with rank 1
                Add(root, w);
                printf("Add function called with word: %s\n", w);
                break;
            case 2:
                // Delete word w from the Trie
                Delete(root, w);
                printf("Delete function called with word: %s\n", w);
                break;
            case 3:
                // Check if the word w is spelled correctly
                if (SpellCheck(root, w)) {
                    fprintf(outputFile, "1\n");
                    printf("Spell-Check function: Word %s is correct\n", w);
                } else {
                    fprintf(outputFile, "0\n");
                    printf("Spell-Check function: Word %s is incorrect\n", w);
                }
                break;
            case 4:
                // Autocomplete based on prefix w
                Autocomplete(root, w, outputFile);
                printf("Autocomplete function called with prefix: %s\n", w);
                break;
            case 5:
                // Autocorrect word w to the closest word in the Trie
                Autocorrect(root, w, 3, outputFile);
                printf("Autocorrect function called with word: %s\n", w);
                break;
            case 6:
                // Check if the word w can be formed by concatenating two or more Trie words
                if (CheckConcatenation(root, w, outputFile)) {
                    fprintf(outputFile, "1\n");
                    printf("Check_Concatenation function: Word %s can be formed by concatenation\n", w);
                } else {
                    fprintf(outputFile, "0\n");
                    printf("Check_Concatenation function: Word %s cannot be formed by concatenation\n", w);
                }
                break;
            default:
                printf("Unknown operation: %d\n", x);
                break;
        }
    }
    fclose(file);
    fclose(outputFile);
    return 0;
}

// Function to add a word to the Trie with rank 1
void Add(TrieNode *root, char *w) {
    // Insert the word `w` into the Trie, creating nodes as necessary
    // Set the rank to 1 if this is the first time the word is added
}

// Function to delete a word from the Trie
void Delete(TrieNode *root, char *w) {
    // Remove the word `w` from the Trie, and adjust the rank and Trie structure
}

// Function to check if a word is spelled correctly
int SpellCheck(TrieNode *root, char *w) {
    // Traverse the Trie to see if the word `w` exists
    // Return 1 if it exists and is spelled correctly, otherwise return 0
    return 1;  // Placeholder return value for testing
}

// Function to autocomplete based on prefix w
void Autocomplete(TrieNode *root, char *prefix, FILE *outputFile) {
    // Traverse the Trie to find all words that start with `prefix`
    // Print top 5 in decreasing order of rank and lexicographical(when same rank) order to the output file
}

// Function to autocorrect word `w` to the closest word in the Trie
void Autocorrect(TrieNode *root, char *w, int maxCost, FILE *outputFile) {
    // 1. Initialize the first row of the dynamic programming matrix (currentRow) 
    //    to represent the distance between the empty prefix and each prefix of the target word `w`.

    // 2. Initialize a list or array to store the results (words within maxCost).

    // 3. Iterate over each child node of the root. For each child node:
    //    a. Call the recursive search helper function with the current node, 
    //       the corresponding letter, the target word, the initialized currentRow, 
    //       and the maximum allowed cost.

    // 4. The recursive helper function will:
    //    a. Create a new row in the dynamic programming matrix based on the previous row.
    //    b. For each letter in the target word, calculate the cost of inserting, deleting, 
    //       or replacing a character to match the current Trie path with the target word.
    //    c. If the final cost in the row is within maxCost and the current Trie node is 
    //       the end of a word, add the word to the results array.
    //    d. If further exploration is needed, recursively call the helper function for each 
    //       child node of the current node.
    
    // 5. After the search is complete, output the results (words within maxCost) to the output file.
}

// Function to check if word w can be formed by concatenating two or more Trie words
int CheckConcatenation(TrieNode *root, char *w, FILE *outputFile) {
    // Check if `w` can be formed by concatenating two or more words in the Trie
    // Return 1 if it can, otherwise return 0
    return 0;  // Placeholder return value
}

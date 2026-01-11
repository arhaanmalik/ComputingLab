#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

#define MAX_WORD_LENGTH 100
#define ALPHABET_SIZE 26

using namespace std;

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isWordEnd;
    int rank;

    TrieNode() {
        isWordEnd = false;
        rank = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    int stringLength(const char* word) {
        int length = 0;
        while (word[length] != '\0') {
            length++;
        }
        return length;
    }

    int getValidIndex(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';
        } else if (c >= 'A' && c <= 'Z') {
            return c - 'A';
        }
        return -1;
    }

    void copyString(char* destination, const char* source) {
        int i = 0;
        while (source[i] != '\0') {
            destination[i] = source[i];
            i++;
        }
        destination[i] = '\0';  // Null-terminate the destination string
    }

    void insertWord(char* word) {
        TrieNode* currentNode = root;
        for (int i = 0; word[i] != '\0'; i++) {
            int index = getValidIndex(word[i]);
            if (index == -1) {
                continue;
            }
            if (currentNode->children[index] == nullptr) {
                currentNode->children[index] = new TrieNode();
            }
            currentNode = currentNode->children[index];
        }
        currentNode->isWordEnd = true;
        if (currentNode->rank < 5) {
            currentNode->rank++;
        }
    }
// Counts the number of children of a given node
int countChildren(TrieNode* node) {
    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != nullptr) {
            count++;
        }
    }
    return count;
}

// Deletes the word from the trie and handles any potential branching issues
void deleteWordPath(TrieNode* node, const char* word, int startIndex) {
    for (int i = startIndex; word[i] != '\0'; i++) {
        int index = getValidIndex(word[i]);
        delete node->children[index];
        node->children[index] = nullptr;
        node = nullptr;  // Ensure node is not accessed after deletion
    }
}

// Searches for the word in the trie, and identifies the last branching point
TrieNode* searchWordAndIdentifyBranch(char* word, TrieNode*& lastNodeWithMultipleBranches, int& lastBranchingIndex) {
    TrieNode* currentNode = root;
    bool uniqueWordPath = true;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = getValidIndex(word[i]);
        if (index == -1 || currentNode->children[index] == nullptr) {
            return nullptr;  // Word not found or invalid character
        }

        if (countChildren(currentNode) > 1) {
            uniqueWordPath = false;
            lastNodeWithMultipleBranches = currentNode;
            lastBranchingIndex = i;
        }

        currentNode = currentNode->children[index];
    }

    return (uniqueWordPath) ? currentNode : nullptr;
}

// The main removeWord function
void removeWord(char* word) {
    TrieNode* lastNodeWithMultipleBranches = nullptr;
    int lastBranchingIndex = 0;

    TrieNode* endNode = searchWordAndIdentifyBranch(word, lastNodeWithMultipleBranches, lastBranchingIndex);

    if (endNode == nullptr || !endNode->isWordEnd) {
        return;  // Word not found
    }

    endNode->isWordEnd = false;
    endNode->rank = 0;

    if (lastNodeWithMultipleBranches != nullptr) {
        deleteWordPath(lastNodeWithMultipleBranches, word, lastBranchingIndex + 1);
    }
}

    int verifyWord(char* word) {
        TrieNode* currentNode = root;
        while (*word) {
            int index = getValidIndex(*word);
            if (index == -1 || currentNode->children[index] == nullptr) {
                return 0;  // Word not found or invalid character
            }
            currentNode = currentNode->children[index];
            word++;
        }
        if (currentNode->isWordEnd) {
            if (currentNode->rank < 5) {
                currentNode->rank++;
            }
            return 1;  // Word found
        }
        return 0;  // Word not found
    }

    void collectSuggestions(TrieNode* node, char* prefix, char output[][MAX_WORD_LENGTH], int& suggestionCount, int& highestRank) {
        if (node->isWordEnd) {
            if (node->rank > highestRank) {
                highestRank = node->rank;
                suggestionCount = 0;
            }
            if (node->rank == highestRank) {
                copyString(output[suggestionCount], prefix);  // Use copyString instead of strcpy
                suggestionCount++;
            }
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i] != nullptr) {
                char newPrefix[MAX_WORD_LENGTH];
                copyString(newPrefix, prefix);  // Use copyString instead of strcpy
                int length = stringLength(newPrefix);
                newPrefix[length] = i + 'a';
                newPrefix[length + 1] = '\0';
                collectSuggestions(node->children[i], newPrefix, output, suggestionCount, highestRank);
            }
        }
    }

  

int main() {
    ifstream inputFile("input.txt");
    ifstream dictionaryFile("dict.txt");
    ofstream outputFile("output.txt");

    if (!inputFile) {
        cout << "Input File opening failed!" << endl;
        return 1;
    }

    if (!outputFile) {
        cout << "Output File opening failed!" << endl;
        return 1;
    }

    if (!dictionaryFile) {
        cout << "Dictionary File opening failed!" << endl;
        return 1;
    }

    Trie trie;

    // Load dictionary into Trie
    char word[MAX_WORD_LENGTH];
    while (dictionaryFile >> word) {
        trie.insertWord(word);
    }

    int Q;
    inputFile >> Q;
    while (Q--) {
        int command;
        inputFile >> command >> word;
        cout << "Processing Command: " << command << " Word: " << word << endl;

        switch (command) {
            case 1:
                cout << "Inserting: " << word << endl;
                trie.insertWord(word);
                break;
            case 2:
                cout << "Removing: " << word << endl;
                trie.removeWord(word);
                cout<<word << "removed";
                break;
            case 3:
                cout << "Verifying: " << word << endl;
                outputFile << trie.verifyWord(word) << "\n";
                cout << trie.verifyWord(word) << endl;
                break;
            case 4:
                cout << "Autocomplete for: " << word << endl;
                trie.findAutocompleteSuggestions(word, outputFile);
                break;
            case 5:
                cout << "Autocorrect for: " << word << endl;
                trie.executeAutocorrect(word, outputFile);
                break;
            case 6:
                cout << "Concatenation Check for: " << word << endl;
                trie.verifyConcatenation(word, outputFile);
                break;
            default:
                cout << "Unknown command: " << command << endl;
                break;
        }

        // Flush the output to ensure it writes immediately
        outputFile.flush();

    }

    inputFile.close();
    dictionaryFile.close();
    outputFile.close();
    return 0;
}



















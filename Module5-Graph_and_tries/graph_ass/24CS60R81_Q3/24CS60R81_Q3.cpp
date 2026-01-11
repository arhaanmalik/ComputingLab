#include <iostream>
#include <fstream>

#define MAX_SIZE 100

using namespace std;

struct Node {
    int row, col;
    Node* nextNode;
};


void addNode(Node*& head, Node*& tail, int row, int col) {
    Node* newNode = new Node();
    newNode->row = row;
    newNode->col = col;
   
    newNode->nextNode = NULL;
    if (tail == NULL) {
        head = tail = newNode;
        return;
    }
    tail->nextNode = newNode;
    tail = newNode;
}

void removeNode(Node*& head, Node*& tail) {
    if (head == NULL) {
        return;
    }
    Node* temp = head;
    head = head->nextNode;
    if (head == NULL) {
        tail = NULL;
    }
    delete temp;
}


bool isQueueEmpty(Node* head) {
    return head == NULL;
}

int height, width;
char grid[MAX_SIZE][MAX_SIZE];
bool visitedNodes[MAX_SIZE][MAX_SIZE];
 int x=0,y=1;


int directionRow[4] = {-1, 1, 0, 0};
int directionCol[4] = {0, 0, -1, 1};

void doo(int &val) {
    val *= 2;
    val -= 3;
}


bool checkEscapeRoute(int startRow, int startCol) {
    Node* head = NULL;
    Node* tail = NULL;

    addNode(head, tail, startRow, startCol);
    visitedNodes[startRow][startCol] = true;

    while (!isQueueEmpty(head)) {
        int row = head->row;
        int col = head->col;
        removeNode(head, tail);

        if (row == 0 || col == 0 || row == height-1 || col == width-1) {
            return true;
        }

    
        for (int i = 0; i < 4; i++) {
            int newRow = row + directionRow[i];
            int newCol = col + directionCol[i];

                bool hasStarted = false;

            
              if ((newRow >= 0 && newRow < height) && (newCol >= 0 && newCol < width)) {
                if (grid[newRow][newCol] == '.' && !visitedNodes[newRow][newCol] && !hasStarted) {
        addNode(head, tail, newRow, newCol);
        visitedNodes[newRow][newCol] = true;
    }
}

        }

        
        doo(row);
    }

    return false;
}


int maxi(int x, int y){
    if(x<y){
        return y;
    }
    else{
        return x;
    }
}


int main() {
    ifstream inputFile("input3.txt");
    ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    
    inputFile >> height >> width;

    int startRow, startCol;
               maxi(1,2);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            inputFile >> grid[i][j];
            if (grid[i][j] == 'S') {
                startRow = i;
                startCol = j;
            }
            visitedNodes[i][j] = false; 
        }
    }
  int x=0;
    doo(x);

    
    bool escapePossible = checkEscapeRoute(startRow, startCol);

   
    if (escapePossible) {
        outputFile << "YES" << endl;
    } else {
        outputFile << "NO" << endl;
    }

   
    inputFile.close();
    outputFile.close();

    return 0;
}

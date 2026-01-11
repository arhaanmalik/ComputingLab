#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class Node {
   public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        this->data = val;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    }
};

int maxi(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

Node* rightrotate(Node* root) {
    Node* x = root->left;
    Node* y = x->right;

    x->right = root;
    root->left = y;

    
    root->height = 1 + maxi(height(root->left), height(root->right));
    x->height = maxi(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftrotate(Node* root) {
    Node* x = root->right;
    Node* y = x->left;

    x->left = root;
    root->right = y;
      root->height = 1 + maxi(height(root->left), height(root->right));
    x->height = maxi(height(x->left), height(x->right)) + 1;
   

    return x;
}

Node* buildAVL(Node* root, int data) {
    if (root == NULL) {
        root = new Node(data);
    }

    if (data < root->data) {
        root->left = buildAVL(root->left, data);
    }

     else if (data > root->data) {
        root->right = buildAVL(root->right, data);
    }

    root->height = maxi(height(root->left), height(root->right)) + 1;

    int lefth = height(root->left);
    int righth = height(root->right);
    int balancef = lefth - righth;

if (balancef > 1 && data < root->left->data) {
    // Left-Left case
    return rightrotate(root);
}

if (balancef > 1 && data > root->left->data) {
    // Left-Right case
    root->left = leftrotate(root->left);
    return rightrotate(root);
}

if (balancef < -1 && data > root->right->data) {
    // Right-Right case
    return leftrotate(root);
}

if (balancef < -1 && data < root->right->data) {
    // Right-Left case
    root->right = rightrotate(root->right);
    return leftrotate(root);
}
 

    return root;
}




bool checkCondition(Node* node) {
    
    if (node == nullptr) {
        return true;
    }
    if (node->left == nullptr && node->right == nullptr) {
        return true;
    }

    
    int leftVal;
    int rightVal;
    
    if (node->left != nullptr) {
        leftVal = node->left->data;
    } 

    else {
        leftVal = 0;
    }
    
    if (node->right != nullptr) {
        rightVal = node->right->data;
     } 
    else {
        rightVal = 0;
    }

   if (node->data * 2 == leftVal + rightVal)
         return checkCondition(node->left) && checkCondition(node->right); 
    else
        return false;
}


int main() {
    Node* root = NULL;

    ifstream ifile("input.txt");
    ofstream ofile("output.txt");

    if (!ifile.is_open()) {
        cout << "Input File not opening.";
    }

    if (!ofile.is_open()) {
        cout << "Output File not opening.";
    }

    cout << endl;

    int command, value;

    while (ifile >> command) {
        if (command == 1) {
            ifile >> value;
            root = buildAVL(root, value);
        } else if (command == 10) {
            if (checkCondition(root))
              ofile << "1\n";
             else
                ofile << "0\n";

              root = nullptr; // Reset tree for next set of inputs
             }
    }
    cout << endl;


    
    

    ifile.close();
    ofile.close();
}
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};



int maxi(int x, int y) {
    if (x < y) {
        return y;
    } else {
        return x;
    }
}


Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd) {
        return nullptr;
    }

    Node* root = new Node(preorder[*preIndex]);
    (*preIndex)++;

    if (inStart == inEnd) {
        return root;
    }

    int inIndex;
         int i = inStart;

    while(i<= inEnd){
      if (inorder[i] == root->data) {
            inIndex = i;
            break;
        }
        i++;
    }
    
    Node* lft = buildTree(inorder, preorder, inStart, inIndex - 1, preIndex);
    root->left = lft;

    Node* rght = buildTree(inorder, preorder, inIndex + 1, inEnd, preIndex);
    root->right = rght;

    return root;
}

 // Function to check if a given root is a valid BST
    bool isValidBST(Node* root, int minVal, int maxVal) {
        if (root == nullptr) return true;
        if (root->data >= maxVal || root->data <= minVal) return false;
         bool isLeftBST = isValidBST(root->left, minVal, root->data);
         bool isRightBST = isValidBST(root->right, root->data, maxVal);

    if (isLeftBST && isRightBST) {
        return true;
    } else {
        return false;
    }
    }
    
    // Function to count the number of  
    // nodes given the root of a subtree
    int countNodes(Node* root) {
        if (root == nullptr) return 0;

        int add = countNodes(root->left) + countNodes(root->right);
        return 1 + add;
    }


 // Function to find the size
    // of the largest BST subtree
    int largestBSTSubtree(Node* root) {
        if (root == nullptr) return 0;
        if (isValidBST(root, INT_MIN, INT_MAX)) {
            // If the current node is a valid BST,
            // return the size of the entire subtree
            return countNodes(root);
        } else {
            // If not, explore left and right subtrees
            int left = largestBSTSubtree(root->left);
            int right = largestBSTSubtree(root->right);
            return maxi(left, right);
        }
    }
    
   

int main() {

    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    int n;
    
    infile>> n;
    int inorder[n];

   // cout<<"Enter inorder : ";
    for (int i = 0; i < n; i++) {
         infile >> inorder[i];
    }
    // cout<<"Enter pre order : ";
    int preorder[n];
    for (int i = 0; i < n; i++) {
         infile >> preorder[i];
    }

    int preIndex = 0;
    Node* root = buildTree(inorder, preorder, 0, n - 1, &preIndex);
    int lBST = largestBSTSubtree(root);
    outfile << "The size of the largest BST is " << lBST << endl;
  infile.close();
  outfile.close();
    return 0;
}

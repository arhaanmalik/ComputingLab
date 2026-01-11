#include <iostream>
#include <fstream>

using namespace std;

// TreeNode structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x){
        this-> val = x;
        this->left = nullptr;
        this->right=nullptr;

    }
};

// Function to find index of a value in the inorder array
int search(int inorder[], int start, int end, int value) {
   

    int i = start;
    while(i<=end){
        if (inorder[i] == value)
            return i;
    
       i++;
      }
    return -1;
}

int maxi(int x, int y){
    if(x<y){
        return y;
    }
    else{
        return x;
    }
}
// Function to build the tree
TreeNode* buildTree(int inorder[], int preorder[], int inorderStart, int inorderEnd, int& preorderIndex) {
    
    if (inorderStart > inorderEnd) 
    return nullptr;

   
    TreeNode* root = new TreeNode(preorder[preorderIndex]);

   
    if (inorderStart == inorderEnd) {
        preorderIndex++;
        return root;
    }

   
    int inorderIndex = inorderStart;

    while (inorder[inorderIndex] != preorder[preorderIndex]) {
        inorderIndex++;
    }

   
    preorderIndex++;

   
    root->left = buildTree(inorder, preorder, inorderStart, inorderIndex - 1, preorderIndex);
    root->right = buildTree(inorder, preorder, inorderIndex + 1, inorderEnd, preorderIndex);

    return root;
}



void postorderTraversal(TreeNode* root, ofstream& outputFile) {
    if (root == NULL) {
        return;

    }
        postorderTraversal(root->left, outputFile);
        postorderTraversal(root->right, outputFile);
        outputFile << root->val << " ";
    
}


int findHeight(TreeNode* root) {

    if (root == nullptr)
     {
          return 0;
    }

    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    return 1 + maxi(leftHeight , rightHeight);
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");


    if (!outputFile.is_open()) {
        cout<< "Error opening file!" << endl;
        return 1;
    }


       
    if (!inputFile.is_open()) {
        cout<< "Error opening file!" << endl;
        return 1;
    }

    int n;
    inputFile >> n;  
    
    int inorder[100];  
    int preorder[100];  
    
    
    int i =0;
   while(i<n){
    inputFile >> inorder[i];
    i++;
   }
      int j=0;
   while(j<n){
     inputFile >> preorder[j];
    }
    j++;
   
       

    int preorderIndex = 0;
    TreeNode* root = buildTree(inorder, preorder, 0, n - 1, preorderIndex);

    outputFile << "Postorder: ";
    postorderTraversal(root, outputFile);
    outputFile << endl;

    
    int height = findHeight(root);
    outputFile << "Height: " << height << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}

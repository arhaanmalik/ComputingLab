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

    x->height = maxi(height(x->left), height(x->right)) + 1;
    root->height = 1 + maxi(height(root->left), height(root->right));

    return x;
}

Node* leftrotate(Node* root) {
    Node* x = root->right;
    Node* y = x->left;

    x->left = root;
    root->right = y;

    x->height = maxi(height(x->left), height(x->right)) + 1;
    root->height = 1 + maxi(height(root->left), height(root->right));

    return x;
}

Node* buildAVL(Node* root, int data) {
    if (root == NULL) {
        root = new Node(data);
    }

    if (data < root->data) {
        root->left = buildAVL(root->left, data);
    }

    if (data > root->data) {
        root->right = buildAVL(root->right, data);
    }

    root->height = maxi(height(root->left), height(root->right)) + 1;

    int lefth = height(root->left);
    int righth = height(root->right);
    int balancef = lefth - righth;

    if (balancef > 1 && root->left->data > data) {
        return rightrotate(root);
    }

    if (balancef > 1 && root->left->data < data) {
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }
    if (balancef < -1 && root->right->data < data) {
        return leftrotate(root);
    }
    if (balancef < -1 && root->right->data > data) {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root->data;
    }

    if (data < root->data) {
        return search(root->left, data);
    }
    if (data > root->data) {
        return search(root->right, data);
    }
}

Node* deleteNode(Node* root, int data) {
    // if (root == NULL) {
    //     return;
    // }

    cout << "this function is not working properly";
}

void preorder(Node* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

Node* levelorder(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (temp == NULL) {
            // cout << endl;
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left) {
                levelorder(temp->left);
            }

            if (temp->right) {
                levelorder(temp->right);
            }
        }
    }
}

void postorder(Node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

Node* zigzag(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (temp == NULL) {
            //  cout << endl;
            if (!q.empty()) {
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";

            if (temp->right) {
                zigzag(temp->right);
            }

            if (temp->left) {
                zigzag(temp->left);
            }
        }
    }
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
    cout << endl;

    while (1) {
        cout << "1. Insert new node : " << endl;
        cout << "2. Search a node : " << endl;
        cout << "3. Delete a node : " << endl;
        cout << "4. Find_height of the tree : " << endl;
        cout << "5. Print the Preorder of the tree : " << endl;
        cout << "6. Print the Postorder of the tree : " << endl;
        cout << "7. Print the inorder of the tree : " << endl;
        cout << "8. Level order : " << endl;
        cout << "9. zigzag order : " << endl;
        int choice;
        cout << "Enter your choice : ";
        cin >> choice;
        int hght;
        int value;
        int srch;
        int del;
        cout << endl;
        switch (choice) {
            case 1:
                cout << "Enter data to insert in BST (-1 to stop): ";
                int data;
                cin >> data;
                root = buildAVL(root, data);

                break;

            case 2:
                cout << "Enter data you want to search : ";
                cin >> value;
                srch = search(root, value);

                if (srch == NULL) {
                    cout << "Not found";
                } else {
                    cout << "found";
                }

                cout << endl;
                break;

            case 3:
                // delete a node
                cout << "Enter node which you want to delete : ";
                cin >> del;
                deleteNode(root, del);

                break;

            case 4:
                hght = height(root);
                cout << "The height of the tree is : " << hght << endl;
                break;

            case 5:
                cout << " pre order : ";
                preorder(root);
                cout << endl;
                break;

            case 6:
                cout << " post order : ";
                postorder(root);
                cout << endl;
                break;

            case 7:
                cout << " In order : ";
                inorder(root);
                cout << endl;
                break;

            case 8:
                cout << " Level order : ";
                levelorder(root);
                cout << endl;

                break;

            case 9:
                cout << "ZiG Zag order : ";

                zigzag(root);
                cout << endl;

                break;

            default:
                cout << "Invalid choice";
                cout << endl;
                exit(0);
        }
    }

    ifile.close();
    ofile.close();
}
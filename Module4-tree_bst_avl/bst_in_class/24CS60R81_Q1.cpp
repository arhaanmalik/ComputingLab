#include <bits/stdc++.h>

#include <iostream>

using namespace std;

class Node {
   public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        this->data = val;
        this->left = NULL;
        this->right = NULL;
    }
};

int maxi(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}
void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
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
            if (temp->left) {
                zigzag(temp->left);
            }

            if (temp->right) {
                zigzag(temp->right);
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

int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int lfth = height(root->left);
    int rghth = height(root->right);
    return 1 + maxi(lfth, rghth);
}

int search(Node* root, int data) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == data) {
        return root->data;
    }

    return search(root->left, data);
    return search(root->right, data);
}

Node* buildBST(Node* root, int data) {
    if (root == NULL) {
        root = new Node(data);
    }

    if (data < root->data) {
        root->left = buildBST(root->left, data);
    }

    if (data > root->data) {
        root->right = buildBST(root->right, data);
    }
    return root;
}

Node* deleteNode(Node* root, int data) {
    // if (root == NULL) {
    //     return;
    // }

    cout << "this function is not working properly";
}

int main() {
    Node* root = NULL;

    // Boiler code was provided only for c so, i couldn't do file handling for cpp.

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
                while (true) {
                    cin >> data;
                    if (data == -1) {
                        break;
                    }
                    root = buildBST(root, data);
                }
                break;

            case 2:
                cout << "Enter data you want to search : ";
                cin >> value;
                srch = search(root, value);

                if (srch == NULL) {
                    cout << "Key Not found";
                } else {
                    cout << "Key found";
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
                cout << "Height : " << hght << endl;
                break;

            case 5:
                cout << " preorder : ";
                preorder(root);
                cout << endl;
                break;

            case 6:
                cout << " postorder : ";
                postorder(root);
                cout << endl;
                break;

            case 7:
                cout << " Inorder : ";
                inorder(root);
                cout << endl;
                break;

            case 8:
                cout << " Levelorder : ";
                levelorder(root);
                cout << endl;

                break;

            case 9:
                cout << "ZiGZag order : ";

                zigzag(root);
                cout << endl;

                break;

            default:
                cout << "Invalid choice";
                cout << endl;
                exit(0);
        }
    }
}
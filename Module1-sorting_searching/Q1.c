#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int num;
    struct node * next;
}Node;

Node * createNode(int n) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->num = n;
    newNode->next = NULL;
    return newNode;
}

Node * createList(int n) {
    Node *h = createNode(1);
    Node *rear = NULL;
    Node *new = NULL;
    for(int i = 2; i <= n; i++) {
        new = createNode(i);
        if(i == 2) {
            h->next = new;
            rear = new;
        }
        rear->next = new;
        rear = new;
    }
    rear->next = h;
    return h;
}

void printL(Node *h) {
    Node *k = h;
    if(k) {
        printf("%d ", k->num);
    }
    k = k->next;
    while(k != h && k) {
        printf("%d ", k->num);
        k = k->next;
    }
    printf("\n");
}

void nodeKill(Node *h, int n, int k) {
    Node* currentNode = h;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < (k - 2); j++) {
            currentNode = currentNode->next;
        }
        Node *l = currentNode->next;
        currentNode->next = l->next;
        currentNode = currentNode->next;
        free(l);
    }
    printf("\nSurviving Member is : ");
    printL(currentNode);
}

int main() {
    int n, k;
    printf("\nEnter N: ");
    scanf("%d", &n);
    printf("\nEnter k: ");
    scanf("%d", &k);
    Node *h = createList(n);
    nodeKill(h, n, k);
    return 0;
}


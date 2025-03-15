#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef int Data;

typedef struct node {
    Data data;
    struct node *left;
    struct node *right;
} Node;

Node *find(Node *root, Data data);

int getHeight(Node *root);

int getNodeCount(Node *root);

int isBST(Node *root);

Node *createNode(Data data);

void insert(Node **root, Data data);

void inOrder(Node *root);

void preOrder(Node *root);

void postOrder(Node *root);

void levelOrder(Node *root);

void destroy(Node *root);

void destroyNode(Node *node);

void showTree(Node *root, int level);

#endif //BINARYTREE_H

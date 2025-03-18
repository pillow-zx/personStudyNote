#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"



Node *createNode(Data data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *find(Node *root, Data data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return find(root->left, data);
    } else {
        return find(root->right, data);
    }
}

int getHeight(Node  *root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int getNodeCount(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return getNodeCount(root->left) + getNodeCount(root->right) + 1;
}

int isBST(Node *root) {
    static Node *prev = NULL;

    if (root != NULL) {
        if (!isBST(root->left)) {
            return 0;
        }
        if (prev != NULL && root->data <= prev->data) {
            return 0;
        }
        prev = root;
        return isBST(root->right);
    }

    return 1;
}

void insert(Node **root, Data data) {
    if (*root == NULL) {
        *root = createNode(data);
    } else {
        if (data < (*root)->data) {
            insert(&(*root)->left, data);
        } else {
            insert(&(*root)->right, data);
        }
    }
}

void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}


void preOrder(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}


void levelOrder(Node *root) {
    if (root == NULL) {
        return;
    }
    Node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        Node *temp = queue[front++];
        printf("%d ", temp->data);
        if (temp->left != NULL) {
            queue[rear++] = temp->left;
        }
        if (temp->right != NULL) {
            queue[rear++] = temp->right;
        }
    }
}


void destroy(Node *root) {
    if (root != NULL) {
        destroy(root->left);
        destroy(root->right);
        free(root);
    }
}

void destroyNode(Node *node) {
    free(node);
}

void showTree(Node *root, int level) {
    if (root != NULL) {
        showTree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("%d\n", root->data);
        showTree(root->left, level + 1);
    }
}

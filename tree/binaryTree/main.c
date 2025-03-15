#include <stdio.h>
#include "binaryTree.h"

int main(void) {
    printf("Creating a tree manually:\n");
    Node *n1 = createNode(10);
    Node *n2 = createNode(5);
    Node *n3 = createNode(15);
    Node *n4 = createNode(2);
    Node *n5 = createNode(7);

    // Build connections between nodes
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;

    printf("\nTree visualization:\n");
    showTree(n1, 0);

    printf("\nTraversal methods:\n");
    printf("Pre-order: ");
    preOrder(n1);
    printf("\nIn-order: ");
    inOrder(n1);
    printf("\nPost-order: ");
    postOrder(n1);
    printf("\nLevel-order: ");
    levelOrder(n1);

    printf("\n\nTree properties:\n");
    printf("Height: %d\n", getHeight(n1));
    printf("Node count: %d\n", getNodeCount(n1));
    printf("Is BST: %s\n", isBST(n1) ? "Yes" : "No");

    printf("\n\nCreating a BST using insert method:\n");
    Node* bst = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < numValues; i++) {
        insert(&bst, values[i]);
    }

    printf("\nBST visualization:\n");
    showTree(bst, 0);

    printf("\nBST traversals:\n");
    printf("In-order: ");
    inOrder(bst);
    printf("\n");

    // Search for a value
    int searchValue = 40;
    Node* found = find(bst, searchValue);
    printf("\nSearching for %d: %s\n", searchValue, found ? "Found" : "Not found");

    // Clean up
    destroy(n1);
    destroy(bst);

    return 0;
}
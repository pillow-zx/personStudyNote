#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef int Data;

typedef struct binaryTree {
    Data data;
    struct binaryTree *left;
    struct binaryTree *right;
} tree;


#endif

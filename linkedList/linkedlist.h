#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef int Data;

typedef struct Node {
    Data data;
    struct Node *next;
} Node;

Node *creatList();

Node *createNode(Data value);

void insertNodeHead(Node *list, Data value);

void insertNodeEnd(Node *list, Data value);

void insertNodePos(Node *list, Data value, int pos);

void insertNodeItem(Node *list, Node *item, Data value);

void deleteNodeHead(Node *list);

void deleteNodeEnd(Node *list);

void deleteNodePos(Node *list, int pos);

void deleteNodeItem(Node *list, Node *item);

void deleteNode(Node *list);

void sortList(Node *list);

void reverseList(Node *list);

void showList(Node *list);

#endif
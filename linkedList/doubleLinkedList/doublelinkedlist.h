#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

typedef int Data;

typedef struct node {
    Data data;
    struct node *left;
    struct node *right;
} node;

typedef struct list {
    int size;
    struct node *head;
    struct node *tail;
} list;

node *createNode(Data data);

list *createList();

void insertNodeHead(list *list, Data data);

void insertNodeTail(list *list, Data data);

void insertNodeAtIndex(list *list, int index, Data data);

void insertNodeAtNode(list *list, node *node, Data data);

void deleteNodeHead(list *list);

void deleteNodeTail(list *list);

void deleteNodeAtIndex(list *list, int index);

void deleteNodeAtNode(list *list, node *node);

void deleteList(list *list);

void showList(list *list);

#endif //DOUBLELINKEDLIST_H

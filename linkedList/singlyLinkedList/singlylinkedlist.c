#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "singlylinkedlist.h"

Node *creatList() {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation failed\n");
        return NULL;
    }
    memset(newNode, 0, sizeof(Node));
    newNode->data = 0;
    newNode->next = NULL;
    return newNode;
}

Node *createNode(Data value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation failed\n");
        return NULL;
    }
    memset(newNode, 0, sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node *findItem(Node *list, Node *item) {
    if (list == NULL || item == NULL) {
        perror("List or item is NULL\n");
        return NULL;
    }
    Node *temp = list;
    while (temp != NULL) {
        if (temp == item) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Node *findPos(Node *list, int pos) {
    if (list == NULL) {
        perror("List is NULL\n");
        return NULL;
    }
    Node *temp = list;
    for (int i = 0; i < pos && temp->next; i++) {
        temp = temp->next;
    }
    return temp;
}

Node *lastList(Node *list) {
    if (list == NULL) {
        perror("List is NULL\n");
        return NULL;
    }
    Node *lastNode = list;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    return lastNode;
}

void insertNodeHead(Node *list, Data value) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }
    Node *newNode = createNode(value);
    newNode->next = list->next;
    list->next = newNode;
}

void insertNodeEnd(Node *list, Data value) {
    Node *lastNode = lastList(list);
    Node *newNode = createNode(value);
    lastNode->next = newNode;
}

void insertNodePos(Node *list, int pos, Data value) {
    Node *poseNode = findPos(list, pos);
    Node *newNode = createNode(value);
    newNode->next = poseNode->next;
    poseNode->next = newNode;
}

void insertNodeItem(Node *list, Node *item, Data value) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }
    Node *newNode = createNode(value);
    Node *posNode = findItem(list, item);
    if (posNode == NULL) {
        perror("Item not found\n");
        return;
    }
    newNode->next = posNode->next;
    posNode->next = newNode;
}

void deleteNodeHead(Node *list) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }
    Node *temp = list->next;
    list->next = temp->next;
    free(temp);
}

void deleteNodeEnd(Node *list) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }
    Node *NlastNode = list;
    while (NlastNode->next->next != NULL) {
        NlastNode = NlastNode->next;
    }
    free(NlastNode->next);
    NlastNode->next = NULL;
}

void deleteNodePos(Node *list, int pos) {
    Node *temp = findPos(list, pos - 1);
    Node *delNode = temp->next;
    temp->next = delNode->next;
    free(delNode);
}

void deleteNodeItem(Node *list, Node *item) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }
    Node *temp = list;
    while (temp->next != item) {
        temp = temp->next;
    }
    temp->next = item->next;
    free(item);
}

void deleteNode(Node *list) {
    while (list != NULL) {
        Node *temp = list;
        list = list->next;
        free(temp);
    }
}

void sortList(Node *list) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }

    for (Node *i = list->next; i->next != NULL; i = i->next) {
        for (Node *j = list->next; j->next != NULL; j = j->next) {
            if (j->data > i->data) {
                Data temp = j->data;
                j->data = i->data;
                i->data = temp;
            }
        }
    }
}

void reverseList(Node *list) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }

    //sortList(list);

    Node *prev = NULL;
    Node *current = list->next;
    Node *temp = NULL;

    while (current != NULL) {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    list->next = prev;
}

void showList(Node *list) {
    if (list == NULL) {
        perror("List is NULL\n");
        return;
    }
    for (Node *node = list->next; node != NULL; node = node->next) {
        printf("%d", node->data);
        if (node->next != NULL) {
            printf(" --> ");
        }
    }
}

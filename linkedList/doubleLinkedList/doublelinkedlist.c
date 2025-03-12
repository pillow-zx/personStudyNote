#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublelinkedlist.h"


list *createList() {
    list *newList = (list *) malloc(sizeof(list));
    if (newList == NULL) {
        return NULL;
    }
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

node *createNode(Data data) {
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        perror("Error: ");
        return NULL;
    }
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;
    return newNode;
}

void insertNodeHead(list *list, Data data) {
    node *newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->right = list->head;
        list->head->left = newNode;
        list->head = newNode;
    }
    list->size++;
}

void insertNodeTail(list *list, Data data) {
    node *newNode = createNode(data);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->left = list->tail;
        list->tail->right = newNode;
        list->tail = newNode;
    }
    list->size++;
}

void insertNodeAtIndex(list *list, int index, Data data) {
    if (index < 0 || index < 0 || index > list->size) {
        return;
    }
    if (index == 0) {
        insertNodeHead(list, data);
    } else if (index == list->size) {
        insertNodeTail(list, data);
    } else {
        node *temp = list->head;
        for (int i = 0; i < index; i++) {
            temp = temp->right;
        }
        node *newNode = createNode(data);
        temp->left->right = newNode;
        newNode->left = temp->left;
        newNode->right = temp;
        temp->left = newNode;
    }
    list->size++;
}

void insertNodeAtNode(list *list, node *goal, Data data) {
    if (list->size <= 0 || goal == NULL) {
        printf("List is empty or goal is not avaiable\n");
        return;
    }
    node *temp = list->head;
    while (temp != NULL) {
        if (temp == goal) {
            break;
        }
        temp = temp->right;
    }
    if (temp == NULL) {
        printf("Goal is not avaiable\n");
        return;
    }
    node *newNode = createNode(data);
    newNode->right = temp->right;
    newNode->left = temp->left;
    temp->right->left = newNode;
    temp->left->right = newNode;
    list->size++;
}

void deleteNodeHead(list *list) {
    if (list->size <= 0) {
        printf("List is empty\n");
        return;
    }
    node *temp = list->head;
    list->head = list->head->right;
    list->head->left = NULL;
    free(temp);
    list->size--;
}

void deleteNodeTail(list *list) {
    if (list->size <= 0) {
        printf("List is empty\n");
        return;
    }
    node *temp = list->tail;
    list->tail = list->tail->left;
    list->tail->right = NULL;
    free(temp);
    list->size--;
}

void deleteNodeAtIndex(list *list, int index) {
    if (list->size <= 0 || index < 0 || index >= list->size) {
        printf("List is empty or index is not avaiable\n");
        return;
    }
    if (index == 0) {
        deleteNodeHead(list);
    } else if (index == list->size - 1) {
        deleteNodeTail(list);
    } else {
        node *current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->right;
        }
        node *temp = current->right;
        current->right = temp->right;
        temp->right->left = current;
        free(temp);
    }
    list->size--;
}

void deleteNodeAtNode(list *list, node *goal) {
    if (list->size <= 0 || goal == NULL) {
        printf("List is empty or goal is not avaiable\n");
        return;
    }
    node *temp = list->head;
    while (temp != NULL) {
        if (temp == goal) {
            break;
        }
        temp = temp->right;
    }
    if (temp == NULL) {
        printf("Goal is not avaiable\n");
        return;
    }
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    list->size--;
}

void deleteList(list *list) {
    if (list->size <= 0) {
        printf("List is empty\n");
        return;
    }
    node *current = list->head;
    while (current != NULL) {
        node *temp = current;
        current = current->right;
        free(temp);
    }
    free(list);
    list->size = 0;
}

void showList(list *list) {
    node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}
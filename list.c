#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc (sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    list->current = list->head;
    if(list->current) return list->current->data;
    return NULL;

}

void * nextList(List * list) {
    if(list->current != NULL) list->current = list->current->next;
    if(list->current != NULL) return list->current->data;
    return NULL;
}

void * lastList(List * list) {
    list->current = list->tail;
    if(list->current) return list->current->data;
    return NULL;
}

void * prevList(List * list) {
    if(list->current != NULL || list->current->prev != NULL) list->current = list->current->prev;
    return list->current->data;
    return NULL;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    if(list->head) list->head->prev = newNode;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newNode = createNode(data);
    newNode->prev = list->current;
    newNode->next = list->current->next;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void* data1 = list->current->data;
    Node* izq = list->current->prev;
    Node* der = list->current->next;
    izq->next = der;
    der->prev = izq;
    return data1;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
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
    if(list == NULL) return NULL;
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
    if(list->current != NULL) list->current = list->current->prev;
    if(list->current) return list->current->data;
    return NULL;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);
    if(list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
    }
    newNode->next = list->head;
    list->head->prev = newNode;
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
    if(list->current->next != NULL) {
        list->current->next->prev = newNode;
    }
    else {
        list->tail = newNode;
    }
    list->current->next = newNode;
    list->current = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void* popCurrent(List* list) {
    if (list == NULL || list->current == NULL) {
        return NULL;
    }
    void* dato1 = list->current->data;
    Node* izq = list->current->prev;
    Node* der = list->current->next;
    if (izq != NULL) {
        izq->next = der;
    } 
    else {
        list->head = der;
    }
    if (der != NULL) {
        der->prev = izq;
        list->current = der;
    }
    else {
        list->tail = izq;
        list->current = list->tail;
    }
    if(list->head == NULL) {
        list->tail = NULL;
        list->current = NULL;
    }
    free(list->current);
    return dato1;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
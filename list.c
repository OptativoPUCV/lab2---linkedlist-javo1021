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

  if(!list->head) return NULL;
  list->current = list->head;
  return (list->head->data);
}

void * nextList(List * list) {
  if(list->current == NULL){
    return NULL;
  }
  if(list->current->next != NULL){
    list->current = list->current->next;
    return (list->current->data);
  }
  return NULL;
}

void * lastList(List * list) {
  if (list->tail == NULL){
    return NULL;
  }

  list->current = list->tail;
  
  return (list->current->data);
}

void * prevList(List * list) {
  if(list->current == NULL){
    return NULL;
  }

  if(list->current->prev != NULL){
    list->current = list->current->prev;
    return(list->current->data);
  }
  return NULL;
}

void pushFront(List * list, void * data) {
  Node* nuevoNodo = createNode(data);
  
  if(list->head == NULL){
    list->head = nuevoNodo;
    list->tail = nuevoNodo;  
  } else {
    
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
    
}

void pushBack(List * list, void * data) {
  Node* nuevoNodo = createNode(data);

  if(list->tail == NULL){
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  } else {
    
    nuevoNodo->prev = list->tail;
    list->tail->next = nuevoNodo;
    list->tail = nuevoNodo;
  }
  
}

void pushCurrent(List * list, void * data) {

  if(list->current == NULL){
    return;
  }
  
  Node* nuevoNodo = createNode(data);
  nuevoNodo->next = list->current->next;
  nuevoNodo->prev = list->current;

  if(list->current->next != NULL){
    list->current->next->prev = nuevoNodo;
  }

  list->current->next = nuevoNodo;
  if(list->tail == list->current) list->tail = nuevoNodo;
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
    if (list->current == NULL) return NULL;
  Node* actual = list->current;
  void * dato = actual->data;

  if(actual->prev != NULL){
    actual->prev->next = actual->next;
  } else {
    list->head = actual->next;
  }
  
  if(actual->next != NULL){
    actual->next->prev = actual->prev;
  } else{
    list->tail = actual->prev;
  }

  if(list->current == actual){
    list->current = actual->next;
  }
  free(actual);

return dato;
  
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
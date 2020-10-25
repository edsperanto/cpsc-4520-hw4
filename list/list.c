#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"

void list_append(struct list *list, void *data) {
  if (list == NULL || data == NULL) return;

  struct list_node *node = malloc(sizeof *node);
  if (node == NULL) return;

  node->data = data;
  node->next = NULL;
  if (list->head != NULL) {
    node->prev = list->tail;
    list->tail = node;
  } else {
    node->prev = NULL;
    list->head = node;
    list->tail = node;
  }
}

void list_prepend(struct list *list, void *data) {
  if (list == NULL || data == NULL) return;

  struct list_node *node = malloc(sizeof *node);
  if (node == NULL) return;

  node->data = data;
  node->prev = NULL;
  if (list->tail != NULL) {
    node->next = list->head;
    list->head = node;
  } else {
    node->next = NULL;
    list->head = node;
    list->tail = node;
  }
}

struct list_node *list_pop_head(struct list *list) {
  if (list == NULL || list->head == NULL) return NULL;
  
  struct list_node *node = list->head;
  list->head = node->next;
  node->next->prev = NULL;
  node->next = NULL;
  return node;
}

struct list_node *list_pop_tail(struct list *list) {
  if (list == NULL || list->head == NULL) return NULL;
  
  struct list_node *node = list->tail;
  list->tail = node->prev;
  node->prev->next = NULL;
  node->prev = NULL;
  return node;
}

void list_dealloc(struct list *list, void *data_dealloc(void *), bool container_dealloc) {
  if (list == NULL) return;
  if (list->head == NULL && container_dealloc == false) return;
  
  struct list_node *trav = list->head,
                   *del = NULL;
  
  while (trav != NULL) {
    del = trav;
    trav = trav->next;
    
    if (data_dealloc != NULL) {
      (*data_dealloc)(del->data);
    }
    free(del);
  }
  if (container_dealloc == false) {
    list->head = NULL;
    list->tail = NULL;
  }
  else {
    free(list);
  }
}

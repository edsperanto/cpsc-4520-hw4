#ifndef __LIST_H_
#define __LIST_H_

#include <stdbool.h>

struct list {
  struct list_node *head,
                   *tail;
};

struct list_node {
  struct list_node *next,
                   *prev;
  void *data;
};

void list_dealloc(struct list *list, void *data_dealloc(void *), bool container_dealloc);
struct list_node *list_pop_head(struct list *list);
struct list_node *list_pop_tail(struct list *list);
void list_append(struct list *list, void *data);
void list_prepend(struct list *list, void *data);

#endif // __LIST_H_

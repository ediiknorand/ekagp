#ifndef H_LIST_H
#define H_LIST_H

typedef struct ____Node {
  void *obj;
  void (*rmfunct)(void*);
  struct ____Node *next;
  struct ____Node *prev;
} List_node;

typedef struct {
  List_node *first;
  List_node *last;
  int count;
} List;

List *list_create();
void list_destroy(List *l);
void list_free(void *l); //not implemented

void list_enqueue(List *l, void *obj, void (*rmfunct)(void*));
void list_push(List *l, void *obj, void (*rmfunct)(void*));

void *list_dequeue(List *l);
void *list_pop(List *l);

#endif

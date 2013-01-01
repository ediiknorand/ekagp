#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List *list_create()
{
  List *l = malloc(sizeof(List));
  if(!l)
  {
    perror("ERRO");
    exit(1);
  }
  l->first = NULL;
  l->last = NULL;
  l->count = 0;

  return l;
}


void list_destroy(List *l)
{
  List_node *n;
  List_node *aux = NULL;

  if(!l) return;

  for(n = l->first; n; n = n->next)
  {
    if(aux) 
    {
      free(aux);
      aux = NULL;
    }
    if(n->rmfunct)
    {
      n->rmfunct(n->obj);
    }
      aux = n;
  }
  if(aux)
  {
    free(aux);
  }
  free(l);
}


void list_enqueue(List *l, void *obj, void (*rmfunct)(void*))
{
  List_node *n;

  if(!l) return;
    
  n = malloc(sizeof(List_node));
  if (!n)
  {
    perror("ERROR");
    exit(1);
  }

  n->next = NULL;
  n->prev = l->last;
  if (!(l->last))
  {
    l->first = n;
  }
  else
  {
    l->last->next = n;
  }
  l->last = n;

  n->obj = obj;
  n->rmfunct = rmfunct;

  l->count++;
}


void list_push(List *l, void *obj, void (*rmfunct)(void*))
{
  List_node *n;

  if(!l) return;
    
  n = malloc(sizeof(List_node));
  if (!n)
  {
    perror("ERRO");
    exit(1);
  }

  n->next = l->first;
  n->prev = NULL;
  if (!(l->first))
  {
    l->last = n;
  }
  else
  {
    l->first->prev = n;
  }
  l->first = n;

  n->obj = obj;
  n->rmfunct = rmfunct;
    
  l->count++;
}


void *list_dequeue(List *l) 
{
  List_node *n;
  void *obj;

  if (!(l && l->first)) return NULL;

  n = l->first;
  obj = n->obj;
  if (!(n->next))
  {
    l->first = NULL;
    l->last = NULL;
    free(n);
    return obj;
  }
  n->next->prev = NULL;
  l->first = n->next;

  l->count--;

  free(n);
  return obj;
}


void *list_pop(List *l)
{
  return list_dequeue(l);
}


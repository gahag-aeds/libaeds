#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>

#include <libaeds/memory.h>


typedef struct listnode {
  struct listnode* next;
  void* data;
} listnode;

typedef struct linkedlist {
  allocator allocator;
  
  listnode* head;
  listnode* tail;
} linkedlist;


#define node_data(node, type) ((type*) (node)->data)

extern linkedlist new_llist(allocator);
extern void delete_llist(linkedlist*, void (*delete)(allocator, void*), allocator);

extern bool llist_empty(linkedlist);

extern void llist_push_head(linkedlist*, const void*);  // Insert at the head.
extern void llist_push_tail(linkedlist*, const void*);  // Insert at the tail.
extern void* llist_pop_head(linkedlist*); // Pop from the head.


#endif /* __LINKED_LIST_H__ */

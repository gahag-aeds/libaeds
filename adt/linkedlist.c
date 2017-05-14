#include "linkedlist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


// O(1)
linkedlist new_llist(allocator allocator) {
  return (linkedlist) {
    .allocator = allocator,
    .head = NULL,
    .tail = NULL
  };
}

// O(n)
void delete_llist(
  linkedlist* list,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(list != NULL);
  
  for (listnode* next, *node = list->head; node != NULL; node = next) { // O(n)
    next = node->next;
    
    if (delete != NULL)
      delete(allocator, node->data);  // O(1)
    
    al_dealloc(list->allocator, node);  // O(1)
  }
  
  *list = (linkedlist) {
    .allocator = null_allocator(),  // O(1)
    .head = NULL,
    .tail = NULL
  };
}


// O(1)
bool llist_empty(linkedlist list) {
  return list.head == NULL;
}


// O(1)
void llist_push_head(linkedlist* list, const void* obj) {  // Insert at the head.
  assert(list != NULL);
  
  if (obj == NULL)
    return;

  listnode* node = al_alloc(list->allocator, 1, sizeof(*node)); // O(1)
  *node = (listnode) {
    .next = list->head,
    .data = (void*) obj
  };
  
  if (llist_empty(*list)) // O(1)
    list->tail = node;
  
  list->head = node;
}

// O(1)
void llist_push_tail(linkedlist* list, const void* obj) {  // Insert at the tail.
  assert(list != NULL);
  
  if (obj == NULL)
    return;
  
  listnode* node = al_alloc(list->allocator, 1, sizeof(*node)); // O(1)
  *node = (listnode) {
    .next = NULL,
    .data = (void*) obj
  };
  
  if (llist_empty(*list)) // O(1)
    list->head = list->tail = node;
  else
    list->tail = list->tail->next = node;
}


// O(1)
void* llist_pop_head(linkedlist* list) {  // Pop from the head.
  assert(list != NULL);
  
  if (llist_empty(*list)) // O(1)
    return NULL;
  
  listnode* node = list->head;
  void* obj = node->data;
  
  list->head = list->head->next;
  if (list->tail == node)
    list->tail = NULL;
  
  al_dealloc(list->allocator, node);  // O(1)
  
  return obj;
}

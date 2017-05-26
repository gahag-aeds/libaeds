#include "linkedlist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


// O(1)
LinkedList new_llist(Allocator allocator) {
  return (LinkedList) {
    .allocator = allocator,
    .head = NULL,
    .tail = NULL
  };
}

// O(n)
void delete_llist(
  LinkedList* list,
  void (*delete)(Allocator, void*),
  Allocator allocator
) {
  assert(list != NULL);
  
  for (ListNode* next, *node = list->head; node != NULL; node = next) { // O(n)
    next = node->next;
    
    if (delete != NULL)
      delete(allocator, node->data);  // O(1)
    
    al_dealloc(list->allocator, node);  // O(1)
  }
  
  *list = (LinkedList) {
    .allocator = null_allocator(),  // O(1)
    .head = NULL,
    .tail = NULL
  };
}


// O(1)
bool llist_empty(LinkedList list) {
  return list.head == NULL;
}


// O(1)
void llist_push_head(LinkedList* list, const void* obj) {  // Insert at the head.
  assert(list != NULL);
  
  if (obj == NULL)
    return;

  ListNode* node = al_alloc(list->allocator, 1, sizeof(*node)); // O(1)
  *node = (ListNode) {
    .next = list->head,
    .data = (void*) obj
  };
  
  if (llist_empty(*list)) // O(1)
    list->tail = node;
  
  list->head = node;
}

// O(1)
void llist_push_tail(LinkedList* list, const void* obj) {  // Insert at the tail.
  assert(list != NULL);
  
  if (obj == NULL)
    return;
  
  ListNode* node = al_alloc(list->allocator, 1, sizeof(*node)); // O(1)
  *node = (ListNode) {
    .next = NULL,
    .data = (void*) obj
  };
  
  if (llist_empty(*list)) // O(1)
    list->head = list->tail = node;
  else
    list->tail = list->tail->next = node;
}


// O(1)
void* llist_pop_head(LinkedList* list) {  // Pop from the head.
  assert(list != NULL);
  
  if (llist_empty(*list)) // O(1)
    return NULL;
  
  ListNode* node = list->head;
  void* obj = node->data;
  
  list->head = list->head->next;
  if (list->tail == node)
    list->tail = NULL;
  
  al_dealloc(list->allocator, node);  // O(1)
  
  return obj;
}

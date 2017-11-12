#include "linkedlist.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>


// A LinkedNode is a node of a LinkedList.
struct LinkedNode {
  LinkedNode* next;  // Pointer to the next node.
  void* data; // Pointer to the data.
};

// A LinkedList is a list that uses linked nodes as storage.
struct LinkedList {
  const Allocator* allocator; // The allocator used to allocate this struct.
  const Allocator* node_allocator; // The allocator used to allocate nodes.
  
  size_t size;  // The number of elements in the list.
  
  LinkedNode* head; // The pointer to the head element of the list.
  LinkedNode* tail; // The pointer to the tail element of the list.
};


const size_t sizeof_lnode = sizeof(LinkedNode);


// O(1)
void* lnode_data(const LinkedNode* node) {
  assert(node != NULL);
  return node->data;
}


// O(1)
LinkedList* new_llist(const Allocator* allocator, const Allocator* node_allocator) {
  assert(allocator != NULL);
  assert(node_allocator != NULL);
  
  LinkedList* list = al_alloc(allocator, 1, sizeof(LinkedList));
  *list = (LinkedList) {
    .allocator = allocator,
    .node_allocator = node_allocator,
    
    .size = 0,
    
    .head = NULL,
    .tail = NULL
  };
  
  return list;
}

// O(n)
void delete_llist(
  LinkedList** _list,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(_list != NULL);
  
  if (_list == NULL)
    return;
  
  LinkedList* list = *_list;
  
  for (LinkedNode *next, *node = list->head; node != NULL; node = next) { // O(n)
    next = node->next;
    
    if (delete != NULL)
      delete(allocator, node->data);  // O(1)
    
    al_dealloc(list->node_allocator, node);  // O(1)
  }
  
  al_dealloc(list->allocator, list);
  
  *_list = NULL;
}


// O(1)
size_t llist_size(const LinkedList* list) {
  assert(list != NULL);
  return list->size;
}

// O(1)
bool llist_empty(const LinkedList* list) {
  assert(list != NULL);
  return list->size == 0;
}


// O(1)
void llist_push_head(LinkedList* list, const void* obj) {  // Insert at the head.
  assert(list != NULL);
  
  if (obj == NULL)
    return;

  LinkedNode* node = al_alloc(list->node_allocator, 1, sizeof(LinkedNode)); // O(1)
  *node = (LinkedNode) {
    .next = list->head,
    .data = (void*) obj
  };
  
  if (llist_empty(list)) // O(1)
    list->tail = node;
  
  list->head = node;
  
  list->size++;
}

// O(1)
void llist_push_tail(LinkedList* list, const void* obj) {  // Insert at the tail.
  assert(list != NULL);
  
  if (obj == NULL)
    return;
  
  LinkedNode* node = al_alloc(list->node_allocator, 1, sizeof(LinkedNode)); // O(1)
  *node = (LinkedNode) {
    .next = NULL,
    .data = (void*) obj
  };
  
  if (llist_empty(list)) // O(1)
    list->head = list->tail = node;
  else
    list->tail = list->tail->next = node;
  
  list->size++;
}


// O(1)
void* llist_pop_head(LinkedList* list) {  // Pop from the head.
  assert(list != NULL);
  
  if (llist_empty(list)) // O(1)
    return NULL;
  
  LinkedNode* node = list->head;
  void* obj = lnode_data(node);
  
  list->head = list->head->next;
  if (list->tail == node)
    list->tail = NULL;
  
  list->size--;
  
  al_dealloc(list->node_allocator, node);  // O(1)
  
  return obj;
}

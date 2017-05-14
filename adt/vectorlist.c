#include "vectorlist.h"

#include <assert.h>
#include <stddef.h>


// O(1)
void** vlist_advance(vectorlist list, void** ptr) {
  return ptr + 1 >= (list.data + list.capacity) ? list.data
                                                : ptr + 1;
}

// O(1)
void** vlist_retreat(vectorlist list, void** ptr) {
  return ptr <= list.data ? list.data + list.capacity - 1
                          : ptr - 1;
}



// O(1)
vectorlist new_vlist(allocator allocator, size_t capacity) {
  return (vectorlist) {
    .allocator = allocator,
    
    .capacity = capacity,
    .data = capacity == 0 ? NULL
                          : al_alloc(allocator, capacity, sizeof(void*)),
    
    .head = NULL,
    .tail = NULL
  };
}

// O(n) when delete is not NULL. O(1) otherwise.
void delete_vlist(
  vectorlist* list,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(list != NULL);
  
  if (list->head != NULL && delete != NULL) {
    for (void** ptr = list->head; ptr != list->tail; ptr = vlist_advance(*list, ptr)) // O(n)
      delete(allocator, *ptr);  // O(1)
    
    delete(allocator, *list->tail); // O(1)
  }
  
  al_dealloc(list->allocator, list->data);
  
  *list = (vectorlist) {
    .allocator = null_allocator(),
    
    .capacity = 0,
    .data = NULL,
    .head = NULL,
    .tail = NULL
  };
}



// O(1)
bool vlist_initialized(vectorlist list) {
  return list.data != NULL;
}

// O(1)
bool vlist_empty(vectorlist list) {
  return list.head == NULL;
}

// O(1)
bool vlist_full(vectorlist list) {
  return !vlist_empty(list)
      && list.tail != NULL
      && list.head == vlist_advance(list, list.tail); // O(1)
}



// O(1)
bool vlist_push_head(vectorlist* list, const void* obj) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || obj == NULL || vlist_full(*list)) // O(1)
    return false;
  
  if (vlist_empty(*list)) // O(1)
    list->head = list->tail = list->data;
  else
    list->head = vlist_retreat(*list, list->head); // O(1)
  
  *list->head = (void*) obj;
  
  return true;
}

// O(1)
bool vlist_push_tail(vectorlist* list, const void* obj) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || obj == NULL || vlist_full(*list))  // O(1)
    return false;
  
  if (vlist_empty(*list)) // O(1)
    list->tail = list->head = list->data;
  else
    list->tail = vlist_advance(*list, list->tail);  // O(1)
  
  *list->tail = (void*) obj;
  
  return true;
}


// O(1)
void* vlist_pop_head(vectorlist* list) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || vlist_empty(*list))  // O(1)
    return NULL;
  
  void* obj = *list->head;
  
  if (list->head == list->tail)
    list->head = list->tail = NULL;
  else
    list->head = vlist_advance(*list, list->head);  // O(1)
  
  return obj;
}

// O(1)
void* vlist_pop_tail(vectorlist* list) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || vlist_empty(*list))  // O(1)
    return NULL;
  
  void* obj = *list->tail;
  
  if (list->head == list->tail)
    list->tail = list->head = NULL;
  else
    list->tail = vlist_retreat(*list, list->tail);  // O(1)
  
  return obj;
}

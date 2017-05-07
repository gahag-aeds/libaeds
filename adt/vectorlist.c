#include "vectorlist.h"

#include <assert.h>
#include <stddef.h>


void** vlist_advance(vectorlist list, void** ptr) {
  return ptr + 1 >= (list.data + list.capacity) ? list.data
                                                : ptr + 1;
}

void** vlist_retreat(vectorlist list, void** ptr) {
  return ptr <= list.data ? list.data + list.capacity - 1
                          : ptr - 1;
}



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

void delete_vlist(
  vectorlist* list,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(list != NULL);
  
  if (list->head != NULL && delete != NULL) {
    for (void** ptr = list->head; ptr != list->tail; ptr = vlist_advance(*list, ptr))
      delete(allocator, *ptr);
    
    delete(allocator, *list->tail);
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



bool vlist_initialized(vectorlist list) {
  return list.data != NULL;
}

bool vlist_empty(vectorlist list) {
  return list.head == NULL;
}

bool vlist_full(vectorlist list) {
  return !vlist_empty(list)
      && list.tail != NULL
      && list.head == vlist_advance(list, list.tail);
}



bool vlist_push_head(vectorlist* list, const void* obj) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || obj == NULL || vlist_full(*list))
    return false;
  
  if (vlist_empty(*list))
    list->head = list->tail = list->data;
  else
    list->head = vlist_retreat(*list, list->head);
  
  *list->head = (void*) obj;
  
  return true;
}

bool vlist_push_tail(vectorlist* list, const void* obj) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || obj == NULL || vlist_full(*list))
    return false;
  
  if (vlist_empty(*list))
    list->tail = list->head = list->data;
  else
    list->tail = vlist_advance(*list, list->tail);
  
  *list->tail = (void*) obj;
  
  return true;
}


void* vlist_pop_head(vectorlist* list) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || vlist_empty(*list))
    return NULL;
  
  void* obj = *list->head;
  
  if (list->head == list->tail)
    list->head = list->tail = NULL;
  else
    list->head = vlist_advance(*list, list->head);
  
  return obj;
}


void* vlist_pop_tail(vectorlist* list) {
  assert(list != NULL);
  
  if (!vlist_initialized(*list) || vlist_empty(*list))
    return NULL;
  
  void* obj = *list->tail;
  
  if (list->head == list->tail)
    list->tail = list->head = NULL;
  else
    list->tail = vlist_retreat(*list, list->tail);
  
  return obj;
}

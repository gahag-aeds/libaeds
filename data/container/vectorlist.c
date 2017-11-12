#include "vectorlist.h"

#include <assert.h>
#include <stddef.h>


struct VectorList {
  const Allocator* allocator;  // The allocator used for memory
                               // operations performed by the vlist functions.
  size_t capacity;  // The capacity of the data array.
  size_t size;
  
  void** head;  // The pointer to the head element of the list.
  void** tail;  // The pointer to the tail element of the list.
  
  void* data[];  // The array used for storing the elements.
};


// O(1)
void** vlist_advance(const VectorList* list, void** ptr) {
  return ptr + 1 < (list->data + list->capacity) ? ptr + 1
                                                 : (void**) list->data;
}

// O(1)
void** vlist_retreat(const VectorList* list, void** ptr) {
  return ptr > list->data ? ptr - 1
                          : (void**) list->data + list->capacity - 1;
}



// O(1)
VectorList* new_vlist(const Allocator* allocator, size_t capacity) {
  assert(allocator != NULL);
  
  VectorList* list = al_alloc_fma(allocator, sizeof(VectorList), capacity, sizeof(void*));
  
  *list = (VectorList) {
    .allocator = allocator,
    
    .capacity = capacity,
    .size = 0,
    
    .head = NULL,
    .tail = NULL
  };
  
  return list;
}

// O(n) when delete is not NULL. O(1) otherwise.
void delete_vlist(
  VectorList** _list,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(_list != NULL);
  
  if (*_list == NULL)
    return;
  
  VectorList* list = *_list;
  
  if (list->head != NULL && delete != NULL) {
    for (void** ptr = list->head; ptr != list->tail; ptr = vlist_advance(list, ptr)) // O(n)
      delete(allocator, *ptr);  // O(1)
    
    delete(allocator, *list->tail); // O(1)
  }
  
  al_dealloc(list->allocator, list);
  
  *_list = NULL;
}



// O(1)
size_t vlist_size(const VectorList* list) {
  assert(list != NULL);
  return list->size;
}

// O(1)
bool vlist_empty(const VectorList* list) {
  assert(list != NULL);
  return list->size == 0;
}

// O(1)
bool vlist_full(const VectorList* list) {
  assert(list != NULL);
  return list->size == list->capacity;
}



// O(1)
bool vlist_push_head(VectorList* list, const void* obj) {
  assert(list != NULL);
  
  if (obj == NULL || vlist_full(list)) // O(1)
    return false;
  
  if (vlist_empty(list)) // O(1)
    list->head = list->tail = list->data;
  else
    list->head = vlist_retreat(list, list->head); // O(1)
  
  *list->head = (void*) obj;
  
  list->size++;
  
  return true;
}

// O(1)
bool vlist_push_tail(VectorList* list, const void* obj) {
  assert(list != NULL);
  
  if (obj == NULL || vlist_full(list))  // O(1)
    return false;
  
  if (vlist_empty(list)) // O(1)
    list->tail = list->head = list->data;
  else
    list->tail = vlist_advance(list, list->tail);  // O(1)
  
  *list->tail = (void*) obj;
  
  list->size++;
  
  return true;
}


// O(1)
void* vlist_pop_head(VectorList* list) {
  assert(list != NULL);
  
  if (vlist_empty(list))  // O(1)
    return NULL;
  
  void* obj = *(list->head);
  
  if (list->head == list->tail)
    list->head = list->tail = NULL;
  else
    list->head = vlist_advance(list, list->head);  // O(1)
  
  list->size--;
  
  return obj;
}

// O(1)
void* vlist_pop_tail(VectorList* list) {
  assert(list != NULL);
  
  if (vlist_empty(list))  // O(1)
    return NULL;
  
  void* obj = *(list->tail);
  
  if (list->head == list->tail)
    list->tail = list->head = NULL;
  else
    list->tail = vlist_retreat(list, list->tail);  // O(1)
  
  list->size--;
  
  return obj;
}



static void* vlist_it_get(Iterator* it) {
  assert(it != NULL);
  
  void** data = it->data;
  
  return data == NULL ? NULL
                      : *data;
}

static void vlist_it_advance(Iterator* it) {
  assert(it != NULL);
  assert(it->container != NULL);
  
  const VectorList* list = it->container;
  
  it->data = it->data == list->tail ? NULL
                                    : vlist_advance(list, it->data);
}

Iterator vlist_begin(const VectorList* list) {
  assert(list != NULL);
  return (Iterator) {
    .container = list,
    .data = list->head,
    
    .get = vlist_it_get,
    .advance = vlist_it_advance
  };
}

#ifndef __VECTOR_LIST_H__
#define __VECTOR_LIST_H__

#include <stdbool.h>
#include <stdlib.h>

#include <libaeds/memory.h>


typedef struct vectorlist {
  allocator allocator;
  
  size_t capacity;
  void** data;
  
  void** head;
  void** tail;
} vectorlist;


// Advance a pointer in a vector list:
void** vlist_advance(vectorlist, void**);
void** vlist_retreat(vectorlist, void**);

extern vectorlist new_vlist(allocator, size_t);
extern void delete_vlist(vectorlist*, void (*delete)(allocator, void*), allocator);

extern bool vlist_initialized(vectorlist);
extern bool vlist_empty(vectorlist);
extern bool vlist_full(vectorlist);

extern bool vlist_push_head(vectorlist*, const void*);  // Insert at the head.
extern bool vlist_push_tail(vectorlist*, const void*);  // Insert at the tail.
extern void* vlist_pop_head(vectorlist*); // Pop from the head.
extern void* vlist_pop_tail(vectorlist*); // Pop from the tail.


#endif /* __VECTOR_LIST_H__ */

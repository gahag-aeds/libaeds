#include "../queue.h"

#include <assert.h>

#include <libaeds/data/container/vectorlist.h>


// O(1)
static bool vqueue_empty(Queue q) {
  assert(q.data != NULL);
  return vlist_empty(q.data);
}

// O(1)
static bool vqueue_push(Queue q, const void* obj) {
  assert(q.data != NULL);
  return vlist_push_tail(q.data, obj);
}

// O(1)
static void* vqueue_pop(Queue q) {
  assert(q.data != NULL);
  return vlist_pop_head(q.data);
}


// O(n) when delete is not NULL. O(1) otherwise.
static void delete_vqueue(
  Queue* q,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(q != NULL);
  delete_vlist((VectorList**) &q->data, delete, allocator); // O(n) when delete is not NULL.
                                                            // O(1) otherwise
}

// O(1)
Queue new_vqueue(const Allocator* allocator, size_t size) {
  assert(allocator != NULL);
  
  return (Queue) {
    .data = new_vlist(allocator, size),
    
    .delete  = delete_vqueue,
    .empty   = vqueue_empty,
    .enqueue = vqueue_push,
    .dequeue = vqueue_pop
  };
}

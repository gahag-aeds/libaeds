#include "../queue.h"

#include <assert.h>

#include <libaeds/data/container/linkedlist.h>


// O(1)
static bool lqueue_empty(Queue q) {
  assert(q.data != NULL);
  return llist_empty(q.data);
}

// O(1)
static bool lqueue_push(Queue q, const void* obj) {
  assert(q.data != NULL);
  llist_push_tail(q.data, obj);
  return true;
}

// O(1)
static void* lqueue_pop(Queue q) {
  assert(q.data != NULL);
  return llist_pop_head(q.data);
}


// O(1)
static Iterator lqueue_begin(Queue q) {
  assert(q.data != NULL);
  return llist_begin(q.data);
}


// O(n)
static void delete_lqueue(
  Queue* q,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(q != NULL);
  delete_llist((LinkedList**) &q->data, delete, allocator);
}

// O(1)
Queue new_lqueue(const Allocator* allocator, const Allocator* node_allocator) {
  assert(allocator != NULL);
  
  return (Queue) {
    .data = new_llist(allocator, node_allocator),
    
    .delete  = delete_lqueue,
    .empty   = lqueue_empty,
    .enqueue = lqueue_push,
    .dequeue = lqueue_pop,
    .begin   = lqueue_begin
  };
}

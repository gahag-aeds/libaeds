#include "../queue.h"

#include <assert.h>
#include <stddef.h>


// On a lqueue: O(n)
// On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
void delete_queue(
  Queue* q,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(q != NULL);
  
  if (q->data == NULL)
    return;
  
  assert(q->delete != NULL);
  
  q->delete(q, delete, allocator);
  
  *q = (Queue) {
    .data = NULL,
    
    .delete  = NULL,
    .empty   = NULL,
    .enqueue = NULL,
    .dequeue = NULL
  };
}


// O(1)
bool queue_empty(Queue q) {
  assert(q.empty != NULL);
  return q.empty(q);
}


// O(1)
bool enqueue(Queue q, const void* obj) {
  assert(q.enqueue != NULL);
  return q.enqueue(q, obj);
}

// O(1)
void* dequeue(Queue q) {
  assert(q.dequeue != NULL);
  return q.dequeue(q);
}

#include "queue.h"

#include <assert.h>


static bool  vqueue_empty(queue);
static bool  vqueue_push(queue*, const void*);
static void* vqueue_pop(queue*);

static bool  lqueue_empty(queue);
static bool  lqueue_push(queue*, const void*);
static void* lqueue_pop(queue*);


// O(n)
static void delete_lqueue(
  queue* q,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(q != NULL);
  
  delete_llist(&q->data.llist, delete, allocator);
  
  *q = (queue) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .enqueue = NULL,
    .dequeue = NULL
  };
}

// O(n) when delete is not NULL. O(1) otherwise.
static void delete_vqueue(
  queue* q,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(q != NULL);
  
  delete_vlist(&q->data.vlist, delete, allocator); // O(n) when delete is not NULL.
                                                   // O(1) otherwise
  
  *q = (queue) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .enqueue = NULL,
    .dequeue = NULL
  };
}


// O(1)
queue new_lqueue(allocator allocator) {
  return (queue) {
    .type = LinkedList,
    .data.llist = new_llist(allocator),
    
    .delete = delete_lqueue,
    
    .empty = lqueue_empty,
    
    .enqueue = lqueue_push,
    .dequeue = lqueue_pop
  };
}

// O(1)
queue new_vqueue(allocator allocator, size_t size) {
  return (queue) {
    .type = VectorList,
    .data.vlist = new_vlist(allocator, size),
    
    .delete = delete_vqueue,
    
    .empty = vqueue_empty,
    
    .enqueue = vqueue_push,
    .dequeue = vqueue_pop
  };
}


// On a lqueue: O(n)
// On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
void delete_queue(queue* q, void (*delete)(allocator, void*), allocator allocator) {
  assert(q != NULL && q->delete != NULL);
  
  return q->delete(q, delete, allocator);
}


// O(1)
bool queue_empty(queue q) {
  assert(q.empty != NULL);
  
  return q.empty(q);
}


// O(1)
bool enqueue(queue* q, const void* obj) {
  assert(q != NULL && q->enqueue != NULL);
  
  return q->enqueue(q, obj);
}

// O(1)
void* dequeue(queue* q) {
  assert(q != NULL && q->dequeue != NULL);
  
  return q->dequeue(q);
}



// O(1)
static bool vqueue_empty(queue q) {
  return vlist_empty(q.data.vlist);
}

// O(1)
static bool vqueue_push(queue* q, const void* obj) {
  assert(q != NULL);
  
  return vlist_push_tail(&q->data.vlist, obj);
}

// O(1)
static void* vqueue_pop(queue* q) {
  assert(q != NULL);
  
  return vlist_pop_head(&q->data.vlist);
}


// O(1)
static bool lqueue_empty(queue q) {
  return llist_empty(q.data.llist);
}

// O(1)
static bool lqueue_push(queue* q, const void* obj) {
  assert(q != NULL);
  
  llist_push_tail(&q->data.llist, obj);
  return true;
}

// O(1)
static void* lqueue_pop(queue* q) {
  assert(q != NULL);
  
  return llist_pop_head(&q->data.llist);
}

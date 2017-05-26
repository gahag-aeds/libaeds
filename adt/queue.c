#include "queue.h"

#include <assert.h>


static bool  vqueue_empty(Queue);
static bool  vqueue_push(Queue*, const void*);
static void* vqueue_pop(Queue*);

static bool  lqueue_empty(Queue);
static bool  lqueue_push(Queue*, const void*);
static void* lqueue_pop(Queue*);


// O(n)
static void delete_lqueue(
  Queue* q,
  void (*delete)(Allocator, void*),
  Allocator allocator
) {
  assert(q != NULL);
  
  delete_llist(&q->data.llist, delete, allocator);
  
  *q = (Queue) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .enqueue = NULL,
    .dequeue = NULL
  };
}

// O(n) when delete is not NULL. O(1) otherwise.
static void delete_vqueue(
  Queue* q,
  void (*delete)(Allocator, void*),
  Allocator allocator
) {
  assert(q != NULL);
  
  delete_vlist(&q->data.vlist, delete, allocator); // O(n) when delete is not NULL.
                                                   // O(1) otherwise
  
  *q = (Queue) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .enqueue = NULL,
    .dequeue = NULL
  };
}


// O(1)
Queue new_lqueue(Allocator allocator) {
  return (Queue) {
    .type = Linked_List,
    .data.llist = new_llist(allocator),
    
    .delete = delete_lqueue,
    
    .empty = lqueue_empty,
    
    .enqueue = lqueue_push,
    .dequeue = lqueue_pop
  };
}

// O(1)
Queue new_vqueue(Allocator allocator, size_t size) {
  return (Queue) {
    .type = Vector_List,
    .data.vlist = new_vlist(allocator, size),
    
    .delete = delete_vqueue,
    
    .empty = vqueue_empty,
    
    .enqueue = vqueue_push,
    .dequeue = vqueue_pop
  };
}


// On a lqueue: O(n)
// On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
void delete_queue(Queue* q, void (*delete)(Allocator, void*), Allocator allocator) {
  assert(q != NULL && q->delete != NULL);
  
  q->delete(q, delete, allocator);
}


// O(1)
bool queue_empty(Queue q) {
  assert(q.empty != NULL);
  
  return q.empty(q);
}


// O(1)
bool enqueue(Queue* q, const void* obj) {
  assert(q != NULL && q->enqueue != NULL);
  
  return q->enqueue(q, obj);
}

// O(1)
void* dequeue(Queue* q) {
  assert(q != NULL && q->dequeue != NULL);
  
  return q->dequeue(q);
}



// O(1)
static bool vqueue_empty(Queue q) {
  return vlist_empty(q.data.vlist);
}

// O(1)
static bool vqueue_push(Queue* q, const void* obj) {
  assert(q != NULL);
  
  return vlist_push_tail(&q->data.vlist, obj);
}

// O(1)
static void* vqueue_pop(Queue* q) {
  assert(q != NULL);
  
  return vlist_pop_head(&q->data.vlist);
}


// O(1)
static bool lqueue_empty(Queue q) {
  return llist_empty(q.data.llist);
}

// O(1)
static bool lqueue_push(Queue* q, const void* obj) {
  assert(q != NULL);
  
  llist_push_tail(&q->data.llist, obj);
  return true;
}

// O(1)
static void* lqueue_pop(Queue* q) {
  assert(q != NULL);
  
  return llist_pop_head(&q->data.llist);
}

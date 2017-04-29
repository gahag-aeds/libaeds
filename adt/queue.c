#include "queue.h"


bool  vqueue_empty(queue);
bool  vqueue_push(queue*, const void*);
void* vqueue_pop(queue*);

bool  lqueue_empty(queue);
bool  lqueue_push(queue*, const void*);
void* lqueue_pop(queue*);


void delete_lqueue(queue* s, void (*delete)(allocator, void*), allocator allocator) {
  if (s == NULL)
    return;
  
  delete_llist(&s->data.llist, delete, allocator);
  
  *s = (queue) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .enqueue = NULL,
    .dequeue = NULL
  };
}

void delete_vqueue(queue* s, void (*delete)(allocator, void*), allocator allocator) {
  if (s == NULL)
    return;
  
  delete_vlist(&s->data.vlist, delete, allocator);
  
  *s = (queue) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .enqueue = NULL,
    .dequeue = NULL
  };
}


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


void delete_queue(queue* s, void (*delete)(allocator, void*), allocator allocator) {
  if (s == NULL)
    return;
  
  return s->delete(s, delete, allocator);
}


bool queue_empty(queue s) {
  return s.empty(s);
}


bool enqueue(queue* s, const void* obj) {
  if (s == NULL)
    return false;
  
  return s->enqueue(s, obj);
}

void* dequeue(queue* s) {
  return s->dequeue(s);
}



bool vqueue_empty(queue s) {
  return vlist_empty(s.data.vlist);
}

bool vqueue_push(queue* s, const void* obj) {
  return vlist_push_tail(&s->data.vlist, obj);
}

void* vqueue_pop(queue* s) {
  return vlist_pop_head(&s->data.vlist);
}


bool lqueue_empty(queue s) {
  return llist_empty(s.data.llist);
}

bool lqueue_push(queue* s, const void* obj) {
  llist_push_tail(&s->data.llist, obj);
  return true;
}

void* lqueue_pop(queue* s) {
  return llist_pop_head(&s->data.llist);
}

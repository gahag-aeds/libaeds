#include "stack.h"

#include <assert.h>


static bool  vstack_empty(stack);
static bool  vstack_push(stack*, const void*);
static void* vstack_pop(stack*);

static bool  lstack_empty(stack);
static bool  lstack_push(stack*, const void*);
static void* lstack_pop(stack*);


static void delete_lstack(
  stack* s,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(s != NULL);
  
  delete_llist(&s->data.llist, delete, allocator);
  
  *s = (stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}

static void delete_vstack(
  stack* s,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(s != NULL);
  
  delete_vlist(&s->data.vlist, delete, allocator);
  
  *s = (stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}


stack new_lstack(allocator allocator) {
  return (stack) {
    .type = LinkedList,
    .data.llist = new_llist(allocator),
    
    .delete = delete_lstack,
    
    .empty = lstack_empty,
    
    .push = lstack_push,
    .pop  = lstack_pop
  };
}

stack new_vstack(allocator allocator, size_t size) {
  return (stack) {
    .type = VectorList,
    .data.vlist = new_vlist(allocator, size),
    
    .delete = delete_vstack,
    
    .empty = vstack_empty,
    
    .push  = vstack_push,
    .pop   = vstack_pop
  };
}


void delete_stack(stack* s, void (*delete)(allocator, void*), allocator allocator) {
  assert(s != NULL && s->delete != NULL);
  
  return s->delete(s, delete, allocator);
}


bool stack_empty(stack s) {
  assert(s.empty != NULL);
  
  return s.empty(s);
}


bool stack_push(stack* s, const void* obj) {
  assert(s != NULL && s->push != NULL);
  
  return s->push(s, obj);
}

void* stack_pop(stack* s) {
  assert(s != NULL && s->pop != NULL);
  
  return s->pop(s);
}



static bool vstack_empty(stack s) {
  return vlist_empty(s.data.vlist);
}

static bool vstack_push(stack* s, const void* obj) {
  assert(s != NULL);
  
  return vlist_push_head(&s->data.vlist, obj);
}

static void* vstack_pop(stack* s) {
  assert(s != NULL);
  
  return vlist_pop_head(&s->data.vlist);
}


static bool lstack_empty(stack s) {
  return llist_empty(s.data.llist);
}

static bool lstack_push(stack* s, const void* obj) {
  assert(s != NULL);
  
  llist_push_head(&s->data.llist, obj);
  return true;
}

static void* lstack_pop(stack* s) {
  assert(s != NULL);
  
  return llist_pop_head(&s->data.llist);
}

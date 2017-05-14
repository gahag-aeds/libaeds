#include "stack.h"

#include <assert.h>


static bool  vstack_empty(stack);
static bool  vstack_push(stack*, const void*);
static void* vstack_pop(stack*);

static bool  lstack_empty(stack);
static bool  lstack_push(stack*, const void*);
static void* lstack_pop(stack*);


// O(n)
static void delete_lstack(
  stack* s,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(s != NULL);
  
  delete_llist(&s->data.llist, delete, allocator); // O(n)
  
  *s = (stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}

// O(n) when delete is not NULL. O(1) otherwise.
static void delete_vstack(
  stack* s,
  void (*delete)(allocator, void*),
  allocator allocator
) {
  assert(s != NULL);
  
  delete_vlist(&s->data.vlist, delete, allocator); // O(n)
  
  *s = (stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}


// O(1)
stack new_lstack(allocator allocator) {
  return (stack) {
    .type = LinkedList,
    .data.llist = new_llist(allocator), // O(1)
    
    .delete = delete_lstack,
    
    .empty = lstack_empty,
    
    .push = lstack_push,
    .pop  = lstack_pop
  };
}

// O(1)
stack new_vstack(allocator allocator, size_t size) {
  return (stack) {
    .type = VectorList,
    .data.vlist = new_vlist(allocator, size), // O(1)
    
    .delete = delete_vstack,
    
    .empty = vstack_empty,
    
    .push  = vstack_push,
    .pop   = vstack_pop
  };
}


// On a lstack: O(n)
// On a vstack: O(n) when delete is not NULL. O(1) otherwise.
void delete_stack(stack* s, void (*delete)(allocator, void*), allocator allocator) {
  assert(s != NULL && s->delete != NULL);
  
  return s->delete(s, delete, allocator); // O(n)
}


// O(1)
bool stack_empty(stack s) {
  assert(s.empty != NULL);
  
  return s.empty(s);  // O(1)
}


// O(1)
bool stack_push(stack* s, const void* obj) {
  assert(s != NULL && s->push != NULL);
  
  return s->push(s, obj); // O(1)
}

// O(1)
void* stack_pop(stack* s) {
  assert(s != NULL && s->pop != NULL);
  
  return s->pop(s); // O(1)
}



// O(1)
static bool vstack_empty(stack s) {
  return vlist_empty(s.data.vlist); // O(1)
}

// O(1)
static bool vstack_push(stack* s, const void* obj) {
  assert(s != NULL);
  
  return vlist_push_head(&s->data.vlist, obj); // O(1)
}

// O(1)
static void* vstack_pop(stack* s) {
  assert(s != NULL);
  
  return vlist_pop_head(&s->data.vlist); // O(1)
}


// O(1)
static bool lstack_empty(stack s) {
  return llist_empty(s.data.llist); // O(1)
}

// O(1)
static bool lstack_push(stack* s, const void* obj) {
  assert(s != NULL);
  
  llist_push_head(&s->data.llist, obj); // O(1)
  return true;
}

// O(1)
static void* lstack_pop(stack* s) {
  assert(s != NULL);
  
  return llist_pop_head(&s->data.llist); // O(1)
}

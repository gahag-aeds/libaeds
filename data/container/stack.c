#include "stack.h"

#include <assert.h>


static bool  vstack_empty(Stack);
static bool  vstack_push(Stack*, const void*);
static void* vstack_pop(Stack*);

static bool  lstack_empty(Stack);
static bool  lstack_push(Stack*, const void*);
static void* lstack_pop(Stack*);


// O(n)
static void delete_lstack(
  Stack* s,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(s != NULL);
  
  delete_llist(&s->data.llist, delete, allocator); // O(n)
  
  *s = (Stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}

// O(n) when delete is not NULL. O(1) otherwise.
static void delete_vstack(
  Stack* s,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(s != NULL);
  
  delete_vlist(&s->data.vlist, delete, allocator); // O(n)
  
  *s = (Stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}


// O(1)
Stack new_lstack(const Allocator* allocator) {
  assert(allocator != NULL);
  
  return (Stack) {
    .type = Linked_List,
    .data.llist = new_llist(allocator), // O(1)
    
    .delete = delete_lstack,
    
    .empty = lstack_empty,
    
    .push = lstack_push,
    .pop  = lstack_pop
  };
}

// O(1)
Stack new_vstack(const Allocator* allocator, size_t size) {
  assert(allocator != NULL);
  
  return (Stack) {
    .type = Vector_List,
    .data.vlist = new_vlist(allocator, size), // O(1)
    
    .delete = delete_vstack,
    
    .empty = vstack_empty,
    
    .push  = vstack_push,
    .pop   = vstack_pop
  };
}


// On a lstack: O(n)
// On a vstack: O(n) when delete is not NULL. O(1) otherwise.
void delete_stack(
  Stack* s,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(s != NULL && s->delete != NULL);
  
  s->delete(s, delete, allocator); // O(n)
}


// O(1)
bool stack_empty(Stack s) {
  assert(s.empty != NULL);
  
  return s.empty(s);  // O(1)
}


// O(1)
bool stack_push(Stack* s, const void* obj) {
  assert(s != NULL && s->push != NULL);
  
  return s->push(s, obj); // O(1)
}

// O(1)
void* stack_pop(Stack* s) {
  assert(s != NULL && s->pop != NULL);
  
  return s->pop(s); // O(1)
}



// O(1)
static bool vstack_empty(Stack s) {
  return vlist_empty(s.data.vlist); // O(1)
}

// O(1)
static bool vstack_push(Stack* s, const void* obj) {
  assert(s != NULL);
  
  return vlist_push_head(&s->data.vlist, obj); // O(1)
}

// O(1)
static void* vstack_pop(Stack* s) {
  assert(s != NULL);
  
  return vlist_pop_head(&s->data.vlist); // O(1)
}


// O(1)
static bool lstack_empty(Stack s) {
  return llist_empty(s.data.llist); // O(1)
}

// O(1)
static bool lstack_push(Stack* s, const void* obj) {
  assert(s != NULL);
  
  llist_push_head(&s->data.llist, obj); // O(1)
  return true;
}

// O(1)
static void* lstack_pop(Stack* s) {
  assert(s != NULL);
  
  return llist_pop_head(&s->data.llist); // O(1)
}
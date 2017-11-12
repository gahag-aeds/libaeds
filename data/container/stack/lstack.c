#include "../stack.h"

#include <assert.h>

#include <libaeds/data/container/linkedlist.h>


// O(1)
static bool lstack_empty(Stack s) {
  assert(s.data != NULL);
  return llist_empty(s.data); // O(1)
}

// O(1)
static bool lstack_push(Stack s, const void* obj) {
  assert(s.data != NULL);
  llist_push_head(s.data, obj); // O(1)
  return true;
}

// O(1)
static void* lstack_pop(Stack s) {
  assert(s.data != NULL);
  return llist_pop_head(s.data); // O(1)
}


// O(n)
static void delete_lstack(
  Stack* s,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(s != NULL);
  delete_llist((LinkedList**) &s->data, delete, allocator); // O(n)
}

// O(1)
Stack new_lstack(const Allocator* allocator, const Allocator* node_allocator) {
  assert(allocator != NULL);
  
  return (Stack) {
    .data = new_llist(allocator, node_allocator), // O(1)
    
    .delete = delete_lstack,
    .empty  = lstack_empty,
    .push   = lstack_push,
    .pop    = lstack_pop
  };
}

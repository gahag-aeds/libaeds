#include "../stack.h"

#include <assert.h>

#include <libaeds/data/container/vectorlist.h>


// O(1)
static bool vstack_empty(Stack s) {
  assert(s.data != NULL);
  return vlist_empty(s.data); // O(1)
}

// O(1)
static bool vstack_push(Stack s, const void* obj) {
  assert(s.data != NULL);
  return vlist_push_head(s.data, obj); // O(1)
}

// O(1)
static void* vstack_pop(Stack s) {
  assert(s.data != NULL);
  return vlist_pop_head(s.data); // O(1)
}


// O(n) when delete is not NULL. O(1) otherwise.
static void delete_vstack(
  Stack* s,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(s != NULL);
  delete_vlist((VectorList**) &s->data, delete, allocator); // O(n)
}

// O(1)
Stack new_vstack(const Allocator* allocator, size_t size) {
  assert(allocator != NULL);
  
  return (Stack) {
    .data = new_vlist(allocator, size), // O(1)
    
    .delete = delete_vstack,
    .empty  = vstack_empty,
    .push   = vstack_push,
    .pop    = vstack_pop
  };
}

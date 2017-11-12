#include "../stack.h"

#include <assert.h>


// On a lstack: O(n)
// On a vstack: O(n) when delete is not NULL. O(1) otherwise.
void delete_stack(
  Stack* s,
  void (*delete)(const Allocator*, void*),
  const Allocator* allocator
) {
  assert(s != NULL);
  
  if (s->data == NULL)
    return;
  
  assert(s->delete != NULL);
  
  s->delete(s, delete, allocator); // O(n)
  
  *s = (Stack) {
    .data = NULL,
    
    .delete = NULL,
    .empty  = NULL,
    .push   = NULL,
    .pop    = NULL
  };
}


// O(1)
bool stack_empty(Stack s) {
  assert(s.empty != NULL);
  return s.empty(s);  // O(1)
}


// O(1)
bool stack_push(Stack s, const void* obj) {
  assert(s.push != NULL);
  return s.push(s, obj); // O(1)
}

// O(1)
void* stack_pop(Stack s) {
  assert(s.pop != NULL);
  return s.pop(s); // O(1)
}

#ifndef __LIBAEDS_DATA_CONTAINER_STACK_H__
#define __LIBAEDS_DATA_CONTAINER_STACK_H__

#include <stdbool.h>

#include <libaeds/memory/allocator.h>


typedef struct Stack {
  void* data; // The data structure used for storage.
  
  // Delete a stack, deallocating the memory used by the stack,
  // via the allocator specified in new_*stack.
  // The delete function is called with the supplyed allocator for each contained element,
  // unless NULL is supplyed as the delete function.
  // Complexity:
  // On a lstack: O(n)
  // On a vstack: O(n) when delete is not NULL. O(1) otherwise.
  void (*delete)(struct Stack*, void (*delete)(const Allocator*, void*), const Allocator*);
  
  // Returns wether a stack contains no elements or not.
  // Complexity: O(1)
  bool (*empty)(struct Stack);
  
  // Pushes an element to a stack.
  // Returns wether the operation succeeded.
  // This operation fails if a VectorList is used as storage, and the list is full.
  // Complexity: O(1)
  bool (*push)(struct Stack, const void*);
  // Pops an element from a stack.
  // Returns NULL if the operation fails.
  // This operation fails if the stack is empty.
  // Complexity: O(1)
  void* (*pop)(struct Stack);
} Stack;


// Creates a stack that uses a LinkedList as storage.
// The LinkedList will use the specified allocator once to allocate the LinkedList struct,
// and the node_allocator for each node allocation.
// The list only allocates nodes one at a time. Therefore, it supports any node_allocator
// that provides `al_alloc(allocator, 1, sizeof_lnode)` and the correspondent al_dealloc.
// Complexity: O(1)
Stack new_lstack(const Allocator*, const Allocator* node_allocator);
// Creates a stack that uses a VectorList of the specified size as storage.
// The VectorList will use the supplyed allocator for memory operations.
// Complexity: O(1)
Stack new_vstack(const Allocator*, size_t);

// Delete a stack, deallocating the memory used by the stack
// via the allocator specified in new_*stack.
// The delete function is called for each contained element and the supplyed allocator,
// unless NULL is supplyed as the delete function.
// Complexity:
// On a lstack: O(n)
// On a vstack: O(n) when delete is not NULL. O(1) otherwise.
void delete_stack(Stack*, void (*delete)(const Allocator*, void*), const Allocator*);

// Returns wether a stack contains no elements or not.
// Complexity: O(1)
bool stack_empty(Stack);

// Pushes an element to a stack.
// Returns wether the operation succeeded.
// This operation fails if a VectorList is used as storage, and the list is full.
// Complexity: O(1)
bool stack_push(Stack, const void*);
// Pops an element from a stack.
// Returns NULL if the operation fails.
// This operation fails if the stack is empty.
// Complexity: O(1)
void* stack_pop(Stack);


#endif /* __LIBAEDS_DATA_CONTAINER_STACK_H__ */

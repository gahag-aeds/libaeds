#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/adt/storagetype.h>
#include <libaeds/adt/linkedlist.h>
#include <libaeds/adt/vectorlist.h>


typedef struct Stack {
  StorageType type; // Indicates the type of the data structure used for storage.
  
  union {
    LinkedList llist;
    VectorList vlist;
  } data; // The data structure used for storage.
  
  
  // Delete a stack, deallocating the memory used by the stack,
  // via the allocator specified in new_*stack.
  // The delete function is called with the supplyed allocator for each contained element,
  // unless NULL is supplyed as the delete function.
  // Complexity:
  // On a lstack: O(n)
  // On a vstack: O(n) when delete is not NULL. O(1) otherwise.
  void (*delete)(struct Stack*, void (*delete)(Allocator, void*), Allocator);
  
  // Returns wether a stack contains no elements or not.
  // Complexity: O(1)
  bool (*empty)(struct Stack);
  
  // Pushes an element to a stack.
  // Returns wether the operation succeeded.
  // This operation fails if a vector list is used as storage, and the list is full.
  // Complexity: O(1)
  bool (*push)(struct Stack*, const void*);
  // Pops an element from a stack.
  // Returns NULL if the operation fails.
  // This operation fails if the stack is empty.
  // Complexity: O(1)
  void* (*pop)(struct Stack*);
} Stack;


// Creates a stack that uses a linked list as storage.
// The linked list will use the supplyed allocator for memory operations.
// The list only uses the allocator for allocating a listnodes one at a time.
// Therefore, it supports any allocator that
// provides `al_alloc(allocator, 1, sizeof(*node))` and the correspondent al_dealloc.
// Complexity: O(1)
Stack new_lstack(Allocator);
// Creates a stack that uses a vector list of the specified size as storage.
// The vector list will use the supplyed allocator for memory operations.
// Complexity: O(1)
Stack new_vstack(Allocator, size_t);

// Delete a stack, deallocating the memory used by the stack
// via the allocator specified in new_*stack.
// The delete function is called for each contained element and the supplyed allocator,
// unless NULL is supplyed as the delete function.
// Complexity:
// On a lstack: O(n)
// On a vstack: O(n) when delete is not NULL. O(1) otherwise.
void delete_stack(Stack*, void (*delete)(Allocator, void*), Allocator);

// Returns wether a stack contains no elements or not.
// Complexity: O(1)
bool stack_empty(Stack);

// Pushes an element to a stack.
// Returns wether the operation succeeded.
// This operation fails if a vector list is used as storage, and the list is full.
// Complexity: O(1)
bool stack_push(Stack*, const void*);
// Pops an element from a stack.
// Returns NULL if the operation fails.
// This operation fails if the stack is empty.
// Complexity: O(1)
void* stack_pop(Stack*);


#endif /* __STACK_H__ */

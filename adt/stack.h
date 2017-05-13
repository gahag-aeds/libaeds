#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/adt/storagetype.h>
#include <libaeds/adt/linkedlist.h>
#include <libaeds/adt/vectorlist.h>


typedef struct stack {
  storagetype type; // Indicates the type of the data structure used for storage.
  
  union {
    linkedlist llist;
    vectorlist vlist;
  } data; // The data structure used for storage.
  
  
  // Delete a stack, deallocating the memory used by the stack,
  // via the allocator specified in new_*stack.
  // The delete function is called with the supplyed allocator for each contained element,
  // unless NULL is supplyed as the delete function.
  void (*delete)(struct stack*, void (*delete)(allocator, void*), allocator);
  
  // Returns wether a stack contains no elements or not.
  bool (*empty)(struct stack);
  
  // Pushes an element to a stack.
  // Returns wether the operation succeeded.
  // This operation fails if a vector list is used as storage, and the list is full.
  bool (*push)(struct stack*, const void*);
  // Pops an element from a stack.
  // Returns NULL if the operation fails.
  // This operation fails if the stack is empty.
  void* (*pop)(struct stack*);
} stack;


// Creates a stack that uses a linked list as storage.
// The linked list will use the supplyed allocator for memory operations.
// The list only uses the allocator for allocating a listnodes one at a time.
// Therefore, it supports any allocator that
// provides `al_alloc(allocator, 1, sizeof(*node))` and the correspondent al_dealloc.
stack new_lstack(allocator);
// Creates a stack that uses a vector list of the specified size as storage.
// The vector list will use the supplyed allocator for memory operations.
stack new_vstack(allocator, size_t);

// Delete a stack, deallocating the memory used by the stack
// via the allocator specified in new_*stack.
// The delete function is called for each contained element and the supplyed allocator,
// unless NULL is supplyed as the delete function.
void delete_stack(stack*, void (*delete)(allocator, void*), allocator);

// Returns wether a stack contains no elements or not.
bool stack_empty(stack);

// Pushes an element to a stack.
// Returns wether the operation succeeded.
// This operation fails if a vector list is used as storage, and the list is full.
bool stack_push(stack*, const void*);
// Pops an element from a stack.
// Returns NULL if the operation fails.
// This operation fails if the stack is empty.
void* stack_pop(stack*);


#endif /* __STACK_H__ */

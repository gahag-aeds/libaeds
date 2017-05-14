#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/memory/allocator.h>
#include <libaeds/adt/storagetype.h>
#include <libaeds/adt/linkedlist.h>
#include <libaeds/adt/vectorlist.h>


typedef struct queue {
  storagetype type; // Indicates the type of the data structure used for storage.
  
  union {
    linkedlist llist;
    vectorlist vlist;
  } data; // The data structure used for storage.
  
  
  // Delete a queue, deallocating the memory used by the queue
  // via the allocator specified in new_*queue.
  // The delete function is called with the supplyed allocator for each contained element,
  // unless NULL is supplyed as the delete function.
  // Complexity:
  // On a lqueue: O(n)
  // On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
  void (*delete)(struct queue*, void (*delete)(allocator, void*), allocator);
  
  // Returns wether a queue contains no elements or not.
  // Complexity: O(1)
  bool (*empty)(struct queue);
  
  // Pushes an element to a queue.
  // Returns wether the operation succeeded.
  // This operation fails if a vector list is used as storage, and the list is full.
  // Complexity: O(1)
  bool (*enqueue)(struct queue*, const void*);
  // Pops an element from a queue.
  // Returns NULL if the operation fails.
  // This operation fails if the queue is empty.
  // Complexity: O(1)
  void* (*dequeue)(struct queue*);
} queue;


// Creates a queue that uses a linked list as storage.
// The linked list will use the supplyed allocator for memory operations.
// The list only uses the allocator for allocating a listnodes one at a time.
// Therefore, it supports any allocator that
// provides `al_alloc(allocator, 1, sizeof(listnode))` and the correspondent al_dealloc.
// Complexity: O(1)
queue new_lqueue(allocator);
// Creates a queue that uses a vector list of the specified size as storage.
// The vector list will use the supplyed allocator for memory operations.
// Complexity: O(1)
queue new_vqueue(allocator, size_t);

// Delete a queue, deallocating the memory used by the queue
// via the allocator specified in new_*queue.
// The delete function is called for each contained element and the supplyed allocator,
// unless NULL is supplyed as the delete function.
// Complexity:
// On a lqueue: O(n)
// On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
void delete_queue(queue*, void (*delete)(allocator, void*), allocator);

// Returns wether a queue contains no elements or not.
// Complexity: O(1)
bool queue_empty(queue);

// Pushes an element to a queue.
// Returns wether the operation succeeded.
// This operation fails if a vector list is used as storage, and the list is full.
// Complexity: O(1)
bool enqueue(queue*, const void*);
// Pops an element from a queue.
// Returns NULL if the operation fails.
// This operation fails if the queue is empty.
// Complexity: O(1)
void* dequeue(queue*);


#endif /* __QUEUE_H__ */

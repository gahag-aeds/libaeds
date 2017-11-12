#ifndef __LIBAEDS_DATA_CONTAINER_QUEUE_H__
#define __LIBAEDS_DATA_CONTAINER_QUEUE_H__

#include <stdbool.h>

#include <libaeds/memory/allocator.h>


typedef struct Queue {
  void* data; // The data structure used for storage.
  
  // Delete a queue, deallocating the memory used by the queue
  // via the allocator specified in new_*queue.
  // The delete function is called with the supplyed allocator for each contained element,
  // unless NULL is supplyed as the delete function.
  // Complexity:
  // On a lqueue: O(n)
  // On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
  void (*delete)(struct Queue*, void (*delete)(const Allocator*, void*), const Allocator*);
  
  // Returns wether a queue contains no elements or not.
  // Complexity: O(1)
  bool (*empty)(struct Queue);
  
  // Pushes an element to a queue.
  // Returns wether the operation succeeded.
  // This operation fails if a VectorList is used as storage, and the list is full.
  // Complexity: O(1)
  bool (*enqueue)(struct Queue, const void*);
  // Pops an element from a queue.
  // Returns NULL if the operation fails.
  // This operation fails if the queue is empty.
  // Complexity: O(1)
  void* (*dequeue)(struct Queue);
} Queue;


// Creates a queue that uses a LinkedList as storage.
// The LinkedList will use the specified allocator once to allocate the LinkedList struct,
// and the node_allocator for each node allocation.
// The list only allocates nodes one at a time. Therefore, it supports any node_allocator
// that provides `al_alloc(allocator, 1, sizeof_lnode)` and the correspondent al_dealloc.
// Complexity: O(1)
Queue new_lqueue(const Allocator*, const Allocator* node_allocator);

// Creates a queue that uses a VectorList of the specified size as storage.
// The VectorList will use the supplyed allocator for memory operations.
// Complexity: O(1)
Queue new_vqueue(const Allocator*, size_t);

// Delete a queue, deallocating the memory used by the queue
// via the allocator specified in new_*queue.
// The delete function is called for each contained element and the supplyed allocator,
// unless NULL is supplyed as the delete function.
// Complexity:
// On a lqueue: O(n)
// On a vqueue: O(n) when delete is not NULL. O(1) otherwise.
void delete_queue(Queue*, void (*delete)(const Allocator*, void*), const Allocator*);

// Returns wether a queue contains no elements or not.
// Complexity: O(1)
bool queue_empty(Queue);

// Pushes an element to a queue.
// Returns wether the operation succeeded.
// This operation fails if a VectorList is used as storage, and the list is full.
// Complexity: O(1)
bool enqueue(Queue, const void*);
// Pops an element from a queue.
// Returns NULL if the operation fails.
// This operation fails if the queue is empty.
// Complexity: O(1)
void* dequeue(Queue);


#endif /* __LIBAEDS_DATA_CONTAINER_QUEUE_H__ */

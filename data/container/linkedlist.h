#ifndef __LIBAEDS_DATA_CONTAINER_LINKEDLIST_H__
#define __LIBAEDS_DATA_CONTAINER_LINKEDLIST_H__

#include <stdbool.h>

#include <libaeds/memory/allocator.h>


// A LinkedNode is a node of a linked list.
typedef struct LinkedNode LinkedNode;

// A linked list is a list that uses linked nodes as storage.
typedef struct LinkedList LinkedList;


extern const size_t sizeof_lnode;

// Returns the data pointer contained in the node.
// Complexity: O(1)
void* lnode_data(const LinkedNode*);

// The data referenced by a LinkedNode is the contained pointer casted to the original type.
#define lnode_tdata(node, type) ((type*) lnode_data(node))


// Creates a linked list that will use the specified allocator once to allocate the
// LinkedList struct, and the node_allocator for each node allocation.
// The list only allocates nodes one at a time. Therefore, it supports any node_allocator
// that provides `al_alloc(allocator, 1, sizeof_lnode)` and the correspondent al_dealloc.
// Complexity: O(1)
LinkedList* new_llist(const Allocator* allocator, const Allocator* node_allocator);
// Delete a linked list, deallocating the memory used by the list and nodes via the
// allocators specified in new_llist.
// The delete function is called with the supplyed allocator for each contained element,
// unless NULL is supplyed as the delete function.
// Complexity: O(n) where n is the number of elements in the list.
void delete_llist(LinkedList**, void (*delete)(const Allocator*, void*), const Allocator*);

// Returns the number of elements in the list.
// Complexity: O(1)
size_t llist_size(const LinkedList*);
// Returns wether a linked list contains no elements or not.
// Complexity: O(1)
bool llist_empty(const LinkedList*);

// Pushes an element to the head of a linked list.
// Complexity: O(1)
void llist_push_head(LinkedList*, const void*);
// Pushes an element to the tail of a linked list.
// Complexity: O(1)
void llist_push_tail(LinkedList*, const void*);
// Pops an element from the head of a linked list.
// Returns NULL if the operation fails.
// This operation fails if the linked list is empty.
// Complexity: O(1)
void* llist_pop_head(LinkedList*); // Pop from the head.


#endif /* __LIBAEDS_DATA_CONTAINER_LINKEDLIST_H__ */

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>

#include <libaeds/memory/allocator.h>


// A listnode is a node of a linked list.
typedef struct listnode {
  struct listnode* next;  // Pointer to the next node.
  void* data; // Pointer to the data.
} listnode;

// A linked list is a list that uses linked nodes as storage.
typedef struct linkedlist {
  allocator allocator;  // The allocator used for memory
                        // operations performed by the llist functions.
  listnode* head; // The pointer to the head element of the list.
  listnode* tail; // The pointer to the tail element of the list.
} linkedlist;


// The data referenced by a list node is the data pointer casted to a data type pointer.
#define node_data(node, type) ((type*) (node)->data)

// Creates a linked list that will use the specified allocator for memory allocations.
// The list only uses the allocator for allocating a listnodes one at a time.
// Therefore, it supports any allocator that
// provides `al_alloc(allocator, 1, sizeof(listnode))` and the correspondent al_dealloc.
// Complexity: O(1)
extern linkedlist new_llist(allocator);
// Delete a linked list, deallocating the memory used by the list
// via the allocator specified in new_llist.
// The delete function is called with the supplyed allocator for each contained element,
// unless NULL is supplyed as the delete function.
// Complexity: O(n) where n is the number of elements in the list.
extern void delete_llist(linkedlist*, void (*delete)(allocator, void*), allocator);

// Returns wether a linked list contains no elements or not.
// Complexity: O(1)
extern bool llist_empty(linkedlist);

// Pushes an element to the head of a linked list.
// Complexity: O(1)
extern void llist_push_head(linkedlist*, const void*);
// Pushes an element to the tail of a linked list.
// Complexity: O(1)
extern void llist_push_tail(linkedlist*, const void*);
// Pops an element from the head of a linked list.
// Returns NULL if the operation fails.
// This operation fails if the linked list is empty.
// Complexity: O(1)
extern void* llist_pop_head(linkedlist*); // Pop from the head.


#endif /* __LINKED_LIST_H__ */

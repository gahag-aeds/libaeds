#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdbool.h>

#include <libaeds/memory/allocator.h>


// A ListNode is a node of a linked list.
typedef struct ListNode {
  struct ListNode* next;  // Pointer to the next node.
  void* data; // Pointer to the data.
} ListNode;

// A linked list is a list that uses linked nodes as storage.
typedef struct LinkedList {
  Allocator allocator;  // The allocator used for memory
                        // operations performed by the llist functions.
  ListNode* head; // The pointer to the head element of the list.
  ListNode* tail; // The pointer to the tail element of the list.
} LinkedList;


// The data referenced by a list node is the data pointer casted to a data type pointer.
#define node_data(node, type) ((type*) (node)->data)

// Creates a linked list that will use the specified allocator for memory allocations.
// The list only uses the allocator for allocating a ListNodes one at a time.
// Therefore, it supports any allocator that
// provides `al_alloc(allocator, 1, sizeof(ListNode))` and the correspondent al_dealloc.
// Complexity: O(1)
extern LinkedList new_llist(Allocator);
// Delete a linked list, deallocating the memory used by the list
// via the allocator specified in new_llist.
// The delete function is called with the supplyed allocator for each contained element,
// unless NULL is supplyed as the delete function.
// Complexity: O(n) where n is the number of elements in the list.
extern void delete_llist(LinkedList*, void (*delete)(Allocator, void*), Allocator);

// Returns wether a linked list contains no elements or not.
// Complexity: O(1)
extern bool llist_empty(LinkedList);

// Pushes an element to the head of a linked list.
// Complexity: O(1)
extern void llist_push_head(LinkedList*, const void*);
// Pushes an element to the tail of a linked list.
// Complexity: O(1)
extern void llist_push_tail(LinkedList*, const void*);
// Pops an element from the head of a linked list.
// Returns NULL if the operation fails.
// This operation fails if the linked list is empty.
// Complexity: O(1)
extern void* llist_pop_head(LinkedList*); // Pop from the head.


#endif /* __LINKED_LIST_H__ */

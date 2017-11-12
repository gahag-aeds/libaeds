#ifndef __LIBAEDS_DATA_CONTAINER_VECTORLIST_H__
#define __LIBAEDS_DATA_CONTAINER_VECTORLIST_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/memory/allocator.h>


// A vector list is a list that uses an array as storage.
typedef struct VectorList VectorList;


// Advance a pointer of an element in a vector list.
// Complexity: O(1)
void** vlist_advance(const VectorList*, void**);
// Retreat a pointer of an element in a vector list.
// Complexity: O(1)
void** vlist_retreat(const VectorList*, void**);

// Creates a vector list of the specified size,
// that will use the specified allocator for memory allocations.
// Complexity: O(1)
VectorList* new_vlist(const Allocator*, size_t);
// Delete a vector list, deallocating the memory used by the list
// via the allocator specified in new_vlist.
// The delete function is called with the supplyed allocator for each contained element,
// unless NULL is supplyed as the delete function.
// Complexity:
// If delete is not NULL, O(n) where n is the number of elements in the list.
// Otherwise, O(1).
void delete_vlist(VectorList**, void (*delete)(const Allocator*, void*), const Allocator*);

// Returns the number of elements in the vector list.
// Complexity: O(1)
size_t vlist_size(const VectorList*);
// Returns wether a vector list contains no elements or not.
// Complexity: O(1)
bool vlist_empty(const VectorList*);
// Returns wheter a vector list reached its capacity.
// Complexity: O(1)
bool vlist_full(const VectorList*);

// Pushes an element to the head of a vector list.
// Returns wether the operation succeeded.
// This operation fails if the vector list is full.
// Complexity: O(1)
bool vlist_push_head(VectorList*, const void*);
// Pushes an element to the tail of a vector list.
// Returns wether the operation succeeded.
// This operation fails if the vector list is full.
// Complexity: O(1)
bool vlist_push_tail(VectorList*, const void*);
// Pops an element from the head of a vector list.
// Returns NULL if the operation fails.
// This operation fails if the vector list is empty.
// Complexity: O(1)
void* vlist_pop_head(VectorList*);
// Pops an element from the tail of a vector list.
// Returns NULL if the operation fails.
// This operation fails if the vector list is empty.
// Complexity: O(1)
void* vlist_pop_tail(VectorList*);



#endif /* __LIBAEDS_DATA_CONTAINER_VECTORLIST_H__ */

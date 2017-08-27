#ifndef __LIBAEDS_DATA_CONTAINER_SEGTREE_H__
#define __LIBAEDS_DATA_CONTAINER_SEGTREE_H__

#include <libaeds/class/monoid.h>
#include <libaeds/data/array.h>
#include <libaeds/data/ix/range.h>
#include <libaeds/memory/allocator.h>


// An segment tree is a binary tree used to store information about elements of a
// collection with respect to their ordering. The tree offers the capability of fast
// update and query information about a given range inside the collection.
typedef struct SegTree {
  const Allocator* allocator;
  
  size_t source_size; // Size of the source array, a.k.a. the number of leaves in the tree.
  
  Monoid monoid;  // The monoid for the tree elements.
  Array nodes;    // Array of data members: all nodes and leaves.
                  // Size: source_size * 2 - 1.
  
  // Array of pointers to represent the tree structure.
  // Size: 2 * 2^[ceil(log_2(source_size))] - 1.
  void** tree;
  size_t tree_size;
} SegTree;


// Creates a segtree from the given array.
// 
// Parameters:
// 
// data_size: The size (bytes) of the data type to contain the
//            information for any given range in the source array.
// 
// data_init: A function to instantiate a leaf of the tree,
//            from the correspondent element in the source array.
// 
// monoid: A monoid for the range information data type.
//         All nodes except the leaves are generated via
//         the monoid associative operation on its child.
// 
// Complexity: O(n) where n is the source array size.
SegTree new_segtree(
  const Allocator*,
  Array,
  size_t data_size,
  void (*data_init)(void* array_elem, void* data),
  Monoid monoid
);

// Delete a segtree, deallocating the memory used.
// Complexity: O(1)
void delete_segtree(SegTree*);


// Update the leaves of a segtree in the given range via the supplyed the function.
// The tree is updated to incorporate the changes.
// Complexity: O(log n) where n is the width of the range.
void segtree_update(SegTree, IxRange, void (*update)(void*));

// Query the information of the given range in the segtree.
// The result is stored in the out parameter, which must be
// a pointer to a value of the range information data type.
// Complexity: O(log n) where n is the width of the query range.
void segtree_query(SegTree, IxRange, void* out);


#endif /* __LIBAEDS_DATA_CONTAINER_SEGTREE_H__ */

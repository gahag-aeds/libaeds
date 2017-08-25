#ifndef __LIBAEDS_DATA_CONTAINER_SEGTREE_H__
#define __LIBAEDS_DATA_CONTAINER_SEGTREE_H__

#include <libaeds/class/monoid.h>
#include <libaeds/data/array.h>
#include <libaeds/data/ix/range.h>
#include <libaeds/memory/allocator.h>


typedef struct SegTree {
  const Allocator* allocator;
  
  size_t source_size; // Size of the source array.
  
  Monoid monoid;  // The monoid for the tree elements.
  Array nodes;    // Array of data members: all nodes and leaves. Size: source_size * 2 - 1.
  
  // Array of pointers to represent the tree structure.
  // Size: 2 * 2^[ceil(log_2(source_size))] - 1
  void** tree;
  size_t tree_size;
} SegTree;


SegTree new_segtree(
  const Allocator*,
  Array,
  size_t data_size,
  void (*data_init)(void* array_elem, void* data),
  Monoid
);
void delete_segtree(SegTree*);

void segtree_update(SegTree, IxRange ix, void (*update)(void*));
void segtree_query(SegTree, IxRange ix, void* out);


#endif /* __LIBAEDS_DATA_CONTAINER_SEGTREE_H__ */

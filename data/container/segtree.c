#include "segtree.h"

#include <assert.h>
#include <math.h>


struct SegTree {
  const Allocator* allocator;
  
  Monoid monoid;
  size_t source_size;
  
  // Array of data members: all nodes and leaves. Size: source_size * 2 - 1.
  void* data;
  
  // Array of pointers to represent the tree structure.
  // Size: 2 * 2^[ceil(log_2(source_size))] - 1
  void** tree;
};

static void* segtree_left(SegTree tree, void** parent) {
  return NULL;  // TODO
}
static void* segtree_right(SegTree tree, void** parent) {
  return NULL;  // TODO
}


SegTree new_segtree(
  const Allocator* allocator,
  void* array, size_t elem_size, size_t size,
  Monoid m
) {
  size_t tree_size = 2 * exp2(ceil(log2(size))) - 1;
  
  SegTree tree = {
    .allocator = allocator,
    .monoid = m,
    .data = al_alloc(allocator, size * 2 - 1, elem_size),
    .tree = al_alloc(allocator, tree_size, sizeof(void*))
  };
  
  // TODO update tree
}

void delete_segtree(SegTree* tree) {
  assert(tree != NULL);
  
  al_dealloc(tree->allocator, tree->data);
  
  *tree = (SegTree) {
    .allocator = NULL,
    
    .monoid = (Monoid) {
      .clear = NULL,
      .append = NULL
    },
    
    .source_size = 0,
    .data = NULL
  };
}


void segtree_update(SegTree tree, void (*fn)(void*), IxRange ix) {
  
}

void* segtree_query(SegTree tree, IxRange ix) {
  // merge
}

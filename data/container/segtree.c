#include "segtree.h"

#include <assert.h>
#include <math.h>


struct DataInit {
  size_t bank_ix;
  void (*data_init)(void*, void*);
};



static size_t segtree_ix(SegTree tree, void** element) {
  return element - tree.tree;
}

static void** segtree_left(SegTree tree, void** parent) {
  size_t ix = 2 * segtree_ix(tree, parent) + 1;
  
  return ix >= tree.tree_size ? NULL
                              : &tree.tree[ix];
}

static void** segtree_right(SegTree tree, void** parent) {
  size_t ix = 2 * segtree_ix(tree, parent) + 2;
  
  return ix >= tree.tree_size ? NULL
                              : &tree.tree[ix];
}



static void segtree_init(
  SegTree tree,
  Array array,
  struct DataInit* di,
  void** node,
  IxRange node_range
) {
  *node = array_get(tree.nodes, di->bank_ix);
  di->bank_ix++;
  
  void** left_child = segtree_left(tree, node);
  void** right_child = segtree_right(tree, node);
  
  if (node_range.begin == node_range.end) {
    di->data_init(array_get(array, node_range.begin), *node);
    
    if (left_child != NULL) {
      *segtree_left(tree, node) = NULL;
      *segtree_right(tree, node) = NULL;
    }
    
    return;
  }
  
  IxRange left_range = ixrange_split(&node_range); // node_range is now right_range.
  
  segtree_init(tree, array, di, left_child, left_range);
  segtree_init(tree, array, di, right_child, node_range);
  
  tree.monoid.clear(*node);
  tree.monoid.append(*node, *left_child);
  tree.monoid.append(*node, *right_child);
}

SegTree new_segtree(
  const Allocator* allocator,
  Array array,
  size_t elem_size,
  void (*data_init)(void*, void*),
  Monoid m
) {
  assert(allocator != NULL);
  assert(array.data != NULL);
  assert(elem_size != 0);
  assert(data_init  != NULL);
  assert(m.append != NULL && m.clear != NULL);
  
  size_t data_size = array.size * 2 - 1;
  size_t tree_size = 2 * exp2(ceil(log2(array.size))) - 1;
  
  SegTree tree = {
    .allocator = allocator,
    
    .source_size = array.size,
    
    .monoid = m,
    .nodes = (Array) {
      .data = al_alloc(allocator, data_size, elem_size),
      .size = data_size,
      .elem_size = elem_size
    },
    
    .tree = al_alloc(allocator, tree_size, sizeof(void*)),
    .tree_size = tree_size
  };
  
  struct DataInit di = {
    .bank_ix = 0,
    .data_init = data_init
  };
  segtree_init(tree, array, &di, tree.tree, ixrange(0, tree.source_size - 1));
  
  return tree;
}

void delete_segtree(SegTree* tree) {
  assert(tree != NULL);
  
  al_dealloc(tree->allocator, tree->nodes.data);
  al_dealloc(tree->allocator, tree->tree);
  
  *tree = (SegTree) {
    .allocator = NULL,
    
    .source_size = 0,
    
    .monoid = (Monoid) {
      .clear = NULL,
      .append = NULL
    },
    .nodes = (Array) {
      .data = NULL,
      .size = 0,
      .elem_size = 0
    },
    
    .tree = NULL,
    .tree_size = 0
  };
}



static void segtree_update_(
  SegTree tree,
  IxRange range,
  void (*update)(void*),
  void** node,
  IxRange node_range
) {
  IxRange intersection;
  bool intersects = ixrange_intersect(node_range, range, &intersection);
  
  if (!intersects)
    return;
  
  if (node_range.begin == node_range.end) {
    update(*node);
    return;
  }
  
  void** left_child = segtree_left(tree, node);
  void** right_child = segtree_right(tree, node);
  
  IxRange left_range = ixrange_split(&node_range); // node_range is now right_range.
  
  segtree_update_(tree, range, update, left_child, left_range);
  segtree_update_(tree, range, update, right_child, node_range);
  
  tree.monoid.clear(*node);
  tree.monoid.append(*node, *left_child);
  tree.monoid.append(*node, *right_child);
}

void segtree_update(SegTree tree, IxRange range, void (*update)(void*)) {
  IxRange tree_range = ixrange(0, tree.source_size - 1);
  
  assert(tree.tree != NULL);
  assert(ixrange_intersect(tree_range, range, NULL));
  assert(update != NULL);
  
  segtree_update_(tree, range, update, tree.tree, tree_range);
}



static void segtree_query_(
  SegTree tree,
  void** node, IxRange node_range,
  IxRange query, void* out
) {
  if (*node == NULL)
    return;
  
  IxRange intersection;
  bool intersects = ixrange_intersect(node_range, query, &intersection);
  
  if (!intersects)
    return;
  
  if (ixrange_within(node_range, query))
    tree.monoid.append(out, *node);
  else {
    IxRange left_range = ixrange_split(&node_range);
    
    segtree_query_(tree, segtree_left(tree, node), left_range, query, out);
    segtree_query_(tree, segtree_right(tree, node), node_range, query, out);
  }
}

void segtree_query(SegTree tree, IxRange query, void* out) {
  IxRange tree_range = ixrange(0, tree.source_size - 1);
  
  assert(tree.tree != NULL);
  assert(ixrange_intersect(tree_range, query, NULL));
  assert(out != NULL);
  
  tree.monoid.clear(out);
  
  segtree_query_(tree, tree.tree, tree_range, query, out);
}

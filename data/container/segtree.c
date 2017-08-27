#include "segtree.h"

#include <assert.h>
#include <math.h>


// Internal helper functions -------------------------------------------------------------

// Index of a given element in the tree array.
static size_t segtree_ix(SegTree tree, void** element) {
  return element - tree.tree;
}

// Get the left child of a given node.
// If the node is at the bottom of the tree, returns NULL.
static void** segtree_left(SegTree tree, void** parent) {
  size_t ix = 2 * segtree_ix(tree, parent) + 1;
  
  return ix >= tree.tree_size ? NULL
                              : &tree.tree[ix];
}

// Get the right child of a given node.
// If the node is at the bottom of the tree, returns NULL.
static void** segtree_right(SegTree tree, void** parent) {
  size_t ix = 2 * segtree_ix(tree, parent) + 2;
  
  return ix >= tree.tree_size ? NULL
                              : &tree.tree[ix];
}
// ---------------------------------------------------------------------------------------



// new_segtree ---------------------------------------------------------------------------
struct DataInit { // Struct to hold the data necessary to init a whole tree.
  size_t nodes_ix;
  void (*data_init)(void*, void*);
};

// O(n)
static void segtree_init(
  SegTree tree,
  Array array,
  struct DataInit* di,
  void** node,
  IxRange node_range
) {
  // Set the current node as the next unused node in tree.nodes:
  *node = array_get(tree.nodes, di->nodes_ix); 
  di->nodes_ix++; // Advance the unused node index.
  
  void** left_child = segtree_left(tree, node);
  void** right_child = segtree_right(tree, node);
  
  if (node_range.begin == node_range.end) { // The node is a leaf.
    di->data_init(array_get(array, node_range.begin), *node);
    
    if (left_child != NULL) { // If the leaf is not at the bottom of the tree:
      // Set its childs to NULL.
      *segtree_left(tree, node) = NULL;
      *segtree_right(tree, node) = NULL;
    }
    
    return;
  }
  
  // The node is not a leaf:
  
  // Split the node's range for its children:
  IxRange left_range = ixrange_split(&node_range); // node_range is now right_range.
  
  segtree_init(tree, array, di, left_child, left_range);  // Recurse in the left child.
  segtree_init(tree, array, di, right_child, node_range); // Recurse in the right child.
  
  // Right and left childs are now initiated,
  // so init this node with the associative operation of the monoid:
  monoid_clear(tree.monoid, *node);
  monoid_append(tree.monoid, *node, *left_child);
  monoid_append(tree.monoid, *node, *right_child);
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
  
  // To hold n leaves, it is necessary (2n - 1) nodes (considering leaves are nodes).
  // The data array contains all nodes and leaves, so 2n -1 is its size.
  size_t nodes_size = array.size * 2 - 1;
  // The tree is structured in an array. To do so, the tree is considered complete.
  // The size of the array must then be 2n' - 1,
  // where n' is the closest power of 2 that is bigger than n.
  size_t tree_size = 2 * exp2(ceil(log2(array.size))) - 1;
  
  SegTree tree = {
    .allocator = allocator,
    
    .source_size = array.size,
    
    .monoid = m,
    .nodes = (Array) {
      .data = al_alloc(allocator, nodes_size, elem_size),
      .size = nodes_size,
      .elem_size = elem_size
    },
    
    .tree = al_alloc(allocator, tree_size, sizeof(void*)),
    .tree_size = tree_size
  };
  
  segtree_init(
    tree,
    array,
    &(struct DataInit) {
      .nodes_ix = 0,
      .data_init = data_init
    },
    tree.tree,
    ixrange(0, tree.source_size - 1)
  );
  
  return tree;
}
// ---------------------------------------------------------------------------------------


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


// segtree_update ------------------------------------------------------------------------
// O(log n)
static void segtree_update_(
  SegTree tree,
  IxRange range,
  void (*update)(void*),
  void** node,
  IxRange node_range
) {
  IxRange intersection;
  bool intersects = ixrange_intersect(node_range, range, &intersection);
  
  if (!intersects)  // If there is no intersection,
    return;         // the node's range is out of the target range.
  
  if (node_range.begin == node_range.end) { // If the node is a leaf, just update it.
    update(*node);
    return;
  }
  
  // The node is not a leaf and it's part of the target range:
  
  void** left_child = segtree_left(tree, node);
  void** right_child = segtree_right(tree, node);
  
  // Split the node's range for its children:
  IxRange left_range = ixrange_split(&node_range); // node_range is now right_range.
  
  // Recurse in both childs:
  segtree_update_(tree, range, update, left_child, left_range);
  segtree_update_(tree, range, update, right_child, node_range);
  
  // Both children are updated now,
  // so update this node with the associative operation of the monoid:
  monoid_clear(tree.monoid, *node);
  monoid_append(tree.monoid, *node, *left_child);
  monoid_append(tree.monoid, *node, *right_child);
}

// O(log n)
void segtree_update(SegTree tree, IxRange range, void (*update)(void*)) {
  IxRange tree_range = ixrange(0, tree.source_size - 1);
  
  assert(tree.tree != NULL);
  assert(ixrange_within(range, tree_range));
  assert(update != NULL);
  
  segtree_update_(tree, range, update, tree.tree, tree_range);
}
// ---------------------------------------------------------------------------------------


// segtree_query -------------------------------------------------------------------------
// O(log n)
static void segtree_query_(
  SegTree tree,
  void** node, IxRange node_range,
  IxRange query, void* out
) {
  IxRange intersection;
  bool intersects = ixrange_intersect(node_range, query, &intersection);
  
  if (!intersects)  // If there is no intersection,
    return;         // the node's range is out of the target range.
  
  if (ixrange_within(node_range, query)) {  // If the node's range is completely inside
    monoid_append(tree.monoid, out, *node); // the query range, then just associate it
    return;                                 // to the output value.
  }
  
  // The node's range is partially within the query range:
  
  // Split the node's range for its children:
  IxRange left_range = ixrange_split(&node_range); // node_range is now right_range.
  
  // Recurse for both children:
  segtree_query_(tree, segtree_left(tree, node), left_range, query, out);
  segtree_query_(tree, segtree_right(tree, node), node_range, query, out);
}

// O(log n)
void segtree_query(SegTree tree, IxRange query, void* out) {
  IxRange tree_range = ixrange(0, tree.source_size - 1);
  
  assert(tree.tree != NULL);
  assert(ixrange_within(query, tree_range));
  assert(out != NULL);
  
  monoid_clear(tree.monoid, out);
  
  segtree_query_(tree, tree.tree, tree_range, query, out);
}
// ---------------------------------------------------------------------------------------

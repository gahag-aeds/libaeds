#ifndef __LIBAEDS_DATA_CONTAINER_SEGTREE_H__
#define __LIBAEDS_DATA_CONTAINER_SEGTREE_H__

#include <libaeds/class/monoid.h>
#include <libaeds/data/ix/range.h>
#include <libaeds/memory/allocator.h>


typedef struct SegTree SegTree;


SegTree new_segtree(const Allocator*, void* array, size_t elem_size, size_t size, Monoid);
void delete_segtree(SegTree*);

void segtree_update(SegTree, void (*fn)(void*), IxRange ix);
void* segtree_query(SegTree, IxRange ix);


#endif /* __LIBAEDS_DATA_CONTAINER_SEGTREE_H__ */

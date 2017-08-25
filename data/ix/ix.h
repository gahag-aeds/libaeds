#ifndef __LIBAEDS_DATA_IX_IX_H__
#define __LIBAEDS_DATA_IX_IX_H__


// Short macro for writing for loops iterating an index.
// `var` must be a valid unused variable name in the context of the calling site.
// `from` must be an expression of type size_t. It is evaluated only once.
// `size` must be an expression of type size_t. It is evaluated once for each iterarion.
// Complexity: O(n) where n is the size.
#define foreach_ix(var, from, size) for (size_t var = (from); var < (size); var++)


#endif /* __LIBAEDS_DATA_IX_IX_H__ */

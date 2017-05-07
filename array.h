#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>


// Short macro for writing for loops iterating over an array.
// `var` must be a valid unused variable name in the context of the calling site.
// `from` must be an expression of type size_t. It is evaluated only once.
// `size` must be an expression of type size_t. It is evaluated once for each iterarion.
#define foreach(var, from, size) for (size_t var = (from); var < (size); var++)

// Fill an array of pointers with the given value. O(size) complexity.
// A for loop with a assignment is used. This guarantees the correct pointer
// representation is assigned, opposed to using memset.
extern void array_fill(size_t size, void* array[static size], void* value);


#endif /* __ARRAY_H__ */

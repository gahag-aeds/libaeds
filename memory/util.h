#ifndef __LIBAEDS_MEMORY_UTIL_H__
#define __LIBAEDS_MEMORY_UTIL_H__

#include <stdlib.h>


// Swap two portions of memory of given size.
// Complexity: O(n) where `n` is the given size.
void mem_swap(void*, void*, size_t);


#endif /* __LIBAEDS_MEMORY_UTIL_H__ */

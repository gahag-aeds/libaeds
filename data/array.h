#ifndef __LIBAEDS_DATA_ARRAY_H__
#define __LIBAEDS_DATA_ARRAY_H__

#include <stddef.h>

#include <libaeds/data/ix/range.h>


typedef struct Array {
  void* data;
  size_t size;
  size_t elem_size;
} Array;


// Indexing for void* arrays.
// array_get(a, elem_size, index) is equivalent to `a + (elem_size * index)`.
void* array_get(Array, size_t index);


// Fill an array of pointers with the given value. O(size) complexity.
// A for loop with a assignment is used. This guarantees the correct pointer
// representation is assigned, opposed to using memset.
// Complexity: O(n) where n is the size of the supplied array.
void array_fill(void** restrict array, size_t size, void* value);


void array_fmap(Array, void (*fn)(void*));

void array_fmap_range(Array, IxRange, void (*fn)(void*));


// Count occurrences of an element in an array.
// The `keys_counting` parameter is an array to hold how many times each key occurred.
// The `key` parameter is a function that transforms an element in a key.
// Elements which are considered equal must evaluate to the same key.
// The keys are used to index the `keys_counting` array.
// Therefore, every possible key must be in the bounds of `keys_counting`.
// Complexity: O(n) where n is the size of the array.
void count_occurrences(
  Array,
  unsigned long (*key)(void*),
  unsigned long* restrict keys_counting
);


#endif /* __LIBAEDS_DATA_ARRAY_H__ */

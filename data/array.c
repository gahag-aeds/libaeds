#include "array.h"

#include <assert.h>
#include <stddef.h>


void* array_get(void* _array, size_t elem_size, size_t index) {
  assert(_array != NULL);
  assert(elem_size != 0);
  
  char* array = _array;
  
  return array + (index * elem_size);
}


// O(n)
void array_fill(void** restrict  array, size_t size, void* value) {
  assert(array != NULL);
  
  for (size_t i = 0; i < size; i++) // O(n)
    array[i] = value; // O(1)
}


void array_fmap(void* array, size_t elem_size, size_t size, void (*fn)(void*)) {
  assert(array != NULL);
  assert(elem_size != 0);
  assert(fn != NULL);
  
  for (size_t i = 0; i < size; i++)
    fn(array_get(array, elem_size, i));
}

void array_fmap_range(void* array, size_t elem_size, IxRange range, void (*fn)(void*)) {
  assert(array != NULL);
  assert(elem_size != 0);
  assert(fn != NULL);
  
  if (range.begin < range.end)
    array_fmap(
      array_get(array, elem_size, range.begin),
      elem_size,
      range.begin - range.end + 1,
      fn
    );
  else
    for (size_t i = range.begin; i >= range.end; i--)
      fn(array_get(array, elem_size, i));
}


// O(n)
void count_occurrences(
  void* restrict array,
  size_t size,
  size_t elem_size,
  unsigned long (*key)(void*),
  unsigned long* restrict keys_counting
) {
  assert(array != NULL);
  assert(elem_size != 0);
  assert(key != NULL);
  assert(keys_counting != NULL);
  
  foreach_ix (i, 0, size) // O(n)
    keys_counting[key(array_get(array, elem_size, i))]++; // O(1)
}

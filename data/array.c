#include "array.h"

#include <assert.h>
#include <stddef.h>

#include <libaeds/data/ix/ix.h>


void* array_get(Array array, size_t index) {
  assert(array.data != NULL);
  assert(array.elem_size != 0);
  assert(index < array.size);
  
  char* data = array.data;
  
  return data + (index * array.elem_size);
}


// O(n)
void array_fill(void** restrict  array, size_t size, void* value) {
  assert(array != NULL);
  
  for (size_t i = 0; i < size; i++) // O(n)
    array[i] = value; // O(1)
}


void array_fmap(Array array, void (*fn)(void*)) {
  assert(array.data != NULL);
  assert(array.elem_size != 0);
  assert(fn != NULL);
  
  for (size_t i = 0; i < array.size; i++)
    fn(array_get(array, i));
}

void array_fmap_range(Array array, IxRange range, void (*fn)(void*)) {
  assert(array.data != NULL);
  assert(array.elem_size != 0);
  assert(fn != NULL);
  
  if (range.begin < range.end) {
    assert(range.end < array.size);
    
    array_fmap(
      (Array) {
        .data = array_get(array, range.begin),
        .size = range.end - range.begin + 1,
        .elem_size = array.elem_size
      },
      fn
    );
  }
  else {
    assert(range.begin < array.size);
    
    for (size_t i = range.begin; i >= range.end; i--)
      fn(array_get(array, i));
  }
}


// O(n)
void count_occurrences(
  Array array,
  unsigned long (*key)(void*),
  unsigned long* restrict keys_counting
) {
  assert(array.data != NULL);
  assert(array.elem_size != 0);
  assert(key != NULL);
  assert(keys_counting != NULL);
  
  foreach_ix (i, 0, array.size) // O(n)
    keys_counting[key(array_get(array, i))]++; // O(1)
}

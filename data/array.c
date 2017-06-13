#include "array.h"

#include <assert.h>
#include <stddef.h>


void* array_get(void* array, size_t elem_size, size_t index) {
  assert(array != NULL);
  assert(elem_size != 0);
  
  return array + (index * elem_size);
}


// O(n)
void array_fill(size_t size, void* array[static size], void* value) {
  assert(array != NULL);
  
  for (size_t i = 0; i < size; i++) // O(n)
    array[i] = value; // O(1)
}

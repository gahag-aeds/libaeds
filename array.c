#include "array.h"

#include <assert.h>


// O(n)
void array_fill(size_t size, void* array[static size], void* value) {
  assert(array != NULL);
  
  for (size_t i = 0; i < size; i++) // O(n)
    array[i] = value; // O(1)
}

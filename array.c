#include "array.h"

#include <assert.h>


void array_fill(size_t size, void* array[size], void* value) {
  assert(array != NULL);
  
  for (size_t i = 0; i < size; i++)
    array[i] = value;
}

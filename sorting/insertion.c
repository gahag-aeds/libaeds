#include "../sorting.h"

#include <assert.h>
#include <string.h>

#include <libaeds/array.h>


void array_insertion_sort(
  void* restrict array,
  size_t length,
  size_t elem_size,
  compare_fn* compare
) {
  assert(array != NULL);
  assert(compare != NULL);
  
  char elem[elem_size]; // VLA for temporary element.
  
	for (size_t i = 1; i < length; i++) {
		memcpy(
      elem,
      array_get(array, elem_size, i),
      elem_size
    );
    
		size_t j = i; //i - 1;
    
		while (j > 0 && compare(elem, array_get(array, elem_size, j - 1)) < 0) {
			memcpy(
        array_get(array, elem_size, j),
        array_get(array, elem_size, j - 1),
        elem_size
      );
      
			j--;
		}
    
		memcpy(
      array_get(array, elem_size, j),
      elem,
      elem_size
    );
	}
}

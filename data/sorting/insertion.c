#include "../sorting.h"

#include <assert.h>
#include <string.h>

#include <libaeds/data/array.h>


// O(n^2)
void array_insertion_sort(Array array, compare_fn* compare) {
  assert(array.data != NULL);
  assert(compare != NULL);
  
  char elem[array.elem_size]; // VLA for temporary element.
  
	for (size_t i = 1; i < array.size; i++) {
		memcpy(
      elem,
      array_get(array, i),
      array.elem_size
    );
    
		size_t j = i;
    
		while (j > 0 && compare(elem, array_get(array, j - 1)) < 0) {
			memcpy(
        array_get(array, j),
        array_get(array, j - 1),
        array.elem_size
      );
      
			j--;
		}
    
		memcpy(
      array_get(array, j),
      elem,
      array.elem_size
    );
	}
}

#include "../sorting.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include <libaeds/data/array.h>
#include <libaeds/data/ordering.h>
#include <libaeds/memory/util.h>


// Heapsort:
static size_t _heap_max(
  void* array,
  size_t elem_size,
  size_t length,
  size_t i,
  size_t j,
  size_t k,
  compare_fn* compare
) {
  size_t max = i;
  
  void* array_j = array_get(array, elem_size, j);
  void* array_k = array_get(array, elem_size, k);
  
  if (j < length && compare(array_j, array_get(array, elem_size, max)) > 0)
    max = j;
  
  if (k < length && compare(array_k, array_get(array, elem_size, max)) > 0)
    max = k;
  
  return max;
}

static void _heap_down(
  void* array,
  size_t elem_size,
  size_t length,
  size_t i,
  compare_fn* compare
) {
  while (true) {
    size_t j = _heap_max(
      array,
      elem_size,
      length,
      i,
      2 * i + 1,
      2 * i + 2,
      compare
    );
    
    if (j == i)
      break;
    
    mem_swap(
      array_get(array, elem_size, i),
      array_get(array, elem_size, j),
      elem_size
    );
    
    i = j;
  }
}

static void _array_heap_sort(
  void* array,
  size_t length,
  size_t elem_size,
  compare_fn* compare
) {
  for (size_t i = (length - 2) / 2 + 1; i > 0; i--)
    _heap_down(array, elem_size, length, i - 1, compare);
  
  for (size_t i = 0; i < length; i++) {
    mem_swap(
      array_get(array, elem_size, length - i - 1),
      array_get(array, elem_size, 0),
      elem_size
    );
    
    _heap_down(array, elem_size, length - i - 1, 0, compare);
  }
}


// Introsort:
static size_t _array_partition( // Hoare's partition scheme:
  void* array,
  size_t length,
  size_t elem_size,
  compare_fn* compare
) {
  void* const elem = array;
  
  size_t left = 0, right = length;
  
  while (true) {
    do right--;
    while (compare(array_get(array, elem_size, right), elem) > 0);
    
    while (compare(array_get(array, elem_size, left), elem) < 0)
     left++;
    
    if (left < right) 
      mem_swap(
        array_get(array, elem_size, left),
        array_get(array, elem_size, right),
        elem_size
      );
    else
      return right + 1;
  }
}

static void _array_intro_sort(
  void* array,
  size_t length,
  size_t elem_size,
  compare_fn* compare,
  size_t max_depth
) {
  if (length <= 16) { // Use insertion sort on small arrays.
    array_insertion_sort(array, length, elem_size, compare);
    return;
  }
  
  if (max_depth == 0) { // Switch to heapsort on a bad case.
    _array_heap_sort(array, length, elem_size, compare);
    return;
  }
  
  size_t pivot = _array_partition(array, length, elem_size, compare);
  
  _array_intro_sort(array, pivot, elem_size, compare, max_depth - 1);
  
  _array_intro_sort(
    array_get(array, elem_size, pivot),
    length - pivot,
    elem_size,
    compare,
    max_depth - 1
  );
}

void array_intro_sort(
  void* array,
  size_t length,
  size_t elem_size,
  compare_fn* compare
) {
  assert(array != NULL);
  assert(compare != NULL);
  
  size_t max_depth = log2(length);
  
  _array_intro_sort(array, length, elem_size, compare, max_depth * 2);
}

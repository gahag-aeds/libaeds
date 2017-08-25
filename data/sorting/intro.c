#include "../sorting.h"

#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include <libaeds/data/array.h>
#include <libaeds/data/ordering.h>
#include <libaeds/memory/util.h>


// Heapsort:
static size_t _heap_max(Array array, size_t i, size_t j, size_t k, compare_fn* compare) {
  size_t max = i;
  
  void* array_j = array_get(array, j);
  void* array_k = array_get(array, k);
  
  if (j < array.size && compare(array_j, array_get(array, max)) > 0)
    max = j;
  
  if (k < array.size && compare(array_k, array_get(array, max)) > 0)
    max = k;
  
  return max;
}

static void _heap_down(Array array, size_t i, compare_fn* compare) {
  while (true) {
    size_t j = _heap_max(
      array,
      i,
      2 * i + 1,
      2 * i + 2,
      compare
    );
    
    if (j == i)
      break;
    
    mem_swap(
      array_get(array, i),
      array_get(array, j),
      array.elem_size
    );
    
    i = j;
  }
}

static void _array_heap_sort(Array array, compare_fn* compare) {
  for (size_t i = (array.size - 2) / 2 + 1; i > 0; i--)
    _heap_down(array, i - 1, compare);
  
  for (size_t i = 0; i < array.size; i++) {
    mem_swap(
      array_get(array, array.size - i - 1),
      array_get(array, 0),
      array.elem_size
    );
    
    _heap_down(
      (Array) {
        .data = array.data,
        .size = array.size - i - 1,
        .elem_size = array.elem_size
      },
      0,
      compare
    );
  }
}


// Introsort:
static size_t _array_partition(Array array, compare_fn* compare) { // Hoare's partition:
  void* const elem = array.data;
  
  size_t left = -1, right = array.size;
  
  while (true) {
    do right--;
    while (compare(array_get(array, right), elem) > 0);
    
    do left++;
    while (compare(array_get(array, left), elem) < 0);
    
    if (left < right) 
      mem_swap(
        array_get(array, left),
        array_get(array, right),
        array.elem_size
      );
    else
      return right + 1;
  }
}

static void _array_intro_sort(Array array, compare_fn* compare, size_t max_depth) {
  if (array.size <= 16) { // Use insertion sort on small arrays.
    array_insertion_sort(array, compare);
    return;
  }
  
  if (max_depth == 0) { // Switch to heapsort on a bad case.
    _array_heap_sort(array, compare);
    return;
  }
  
  size_t pivot = _array_partition(array, compare);
  
  _array_intro_sort(
    (Array) {
      .data = array.data,
      .size = pivot,
      .elem_size = array.elem_size
    },
    compare,
    max_depth - 1
  );
  
  _array_intro_sort(
    (Array) {
      .data = array_get(array, pivot),
      .size = array.size - pivot,
      .elem_size = array.elem_size
    },
    compare,
    max_depth - 1
  );
}

void array_intro_sort(Array array, compare_fn* compare) {
  assert(array.data != NULL);
  assert(compare != NULL);
  
  size_t max_depth = log2(array.size);
  
  _array_intro_sort(array, compare, max_depth * 2);
}

#ifndef __LIBAEDS_SORTING_H__
#define __LIBAEDS_SORTING_H__

#include <stddef.h>

#include <libaeds/ordering.h>


// Sort an array using insertion sort. Usefull for very small arrays.
// Stable.
// Complexity: O(n^2)
void array_insertion_sort(void* array, size_t length, size_t elem_size, compare_fn*);

// Sort an array using intro sort. Usefull for most types of arrays.
// Intro sort is a modified quicksort:
// It switches to insertion sort on small partition sizes.
// It switches to heap sort when a high recurrence depth is identified.
// This amortizes the worst case complexity to heap sort's worst case: O(n log n).
// Unstable.
// Complexity: O(n log n)
void array_intro_sort(void* array, size_t length, size_t elem_size, compare_fn*);


#endif /* __LIBAEDS_SORTING_H__ */

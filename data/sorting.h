#ifndef __LIBAEDS_DATA_SORTING_H__
#define __LIBAEDS_DATA_SORTING_H__

#include <stddef.h>

#include <libaeds/data/array.h>
#include <libaeds/data/ordering.h>


// Sort an array using insertion sort. Usefull for very small arrays.
// Stable.
// Complexity: O(n^2)
void array_insertion_sort(Array, compare_fn*);

// Sort an array using intro sort. Usefull for most types of arrays.
// Intro sort is a modified quicksort:
// It switches to insertion sort on small partition sizes.
// It switches to heap sort when a high recurrence depth is identified.
// This amortizes the worst case complexity to heap sort's worst case: O(n log n).
// Unstable.
// Complexity: O(n log n)
void array_intro_sort(Array, compare_fn*);


#endif /* __LIBAEDS_DATA_SORTING_H__ */

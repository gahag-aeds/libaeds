#ifndef __LIBAEDS_DATA_IX_RANGE_H__
#define __LIBAEDS_DATA_IX_RANGE_H__

#include <stdbool.h>
#include <stddef.h>


// Range of indexes. begin <= end.
typedef struct IxRange {
  size_t begin, end;
} IxRange;


// Utility to create an IxRange.
IxRange ixrange(size_t begin, size_t end);


// The size (width) of a given range.
size_t ixrange_size(IxRange);


// Split a range in half.
// The left part is returned, the right part is written to the parameter.
// If the range size is even, the biggest half is always the right one.
IxRange ixrange_split(IxRange*);

// Range intersection.
// Returns wether two ranges intersect.
// If the intersection parameter is not NULL, the intersection range is written to it.
bool ixrange_intersect(IxRange, IxRange, IxRange* intersection);

// Checks whether the range `r1` is completely within `r2`.
bool ixrange_within(IxRange r1, IxRange r2);


#endif /* __LIBAEDS_DATA_IX_RANGE_H__ */

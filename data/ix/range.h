#ifndef __LIBAEDS_DATA_IX_RANGE_H__
#define __LIBAEDS_DATA_IX_RANGE_H__

#include <stdbool.h>
#include <stddef.h>


typedef struct IxRange {  // Range of indexes. begin <= end.
  size_t begin, end;
} IxRange;


IxRange ixrange(size_t begin, size_t end);

IxRange ixrange_split(IxRange*);
bool ixrange_intersect(IxRange, IxRange, IxRange* intersection);
bool ixrange_within(IxRange r1, IxRange r2); // r1 within r2.


#endif /* __LIBAEDS_DATA_IX_RANGE_H__ */

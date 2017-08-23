#ifndef __LIBAEDS_DATA_IX_RANGE_H__
#define __LIBAEDS_DATA_IX_RANGE_H__

#include <stddef.h>


typedef struct IxRange {  // Range of indexes.
  size_t begin, end;
} IxRange;


IxRange ixrange_split(IxRange*);

IxRange ixrange_intersect(IxRange, IxRange);


#endif /* __LIBAEDS_DATA_IX_RANGE_H__ */

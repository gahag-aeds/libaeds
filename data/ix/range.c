#include "range.h"

#include <assert.h>


IxRange ixrange_split(IxRange* r) {
  assert(r != NULL);
  
  size_t half_length = (r->begin < r->end ? r->end - r->begin
                                          : r->begin - r->end) / 2;
  
  IxRange left = {
    .begin = r->begin,
    .end = half_length - 1
  };
  
  r->begin = half_length;
  
  return left;
}

IxRange ixrange_intersect(IxRange r1, IxRange r2) {
  // TODO
}

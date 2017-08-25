#include "range.h"

#include <assert.h>


IxRange ixrange(size_t begin, size_t end) {
  assert(begin <= end);
  
  return (IxRange) {
    .begin = begin,
    .end = end
  };
}


IxRange ixrange_split(IxRange* r) {
  assert(r != NULL);
  assert(r->begin <= r->end);
  
  size_t half_length = (r->end - r->begin + 1) / 2;
  
  IxRange left = {
    .begin = r->begin,
    .end = r->begin + half_length - 1
  };
  
  r->begin += half_length;
  
  return left;
}

bool ixrange_intersect(IxRange r1, IxRange r2, IxRange* out) {
  assert(r1.begin <= r1.end);
  assert(r2.begin <= r2.end);
  
  IxRange isect = {
    .begin = r1.begin > r2.begin ? r1.begin
                                 : r2.begin,
    
    .end = r1.end < r2.end ? r1.end
                           : r2.end
  };
  
  if (isect.begin > isect.end)
    return false;
  
  if (out != NULL)
    *out = isect;  
  
  return true;
}

bool ixrange_within(IxRange r1, IxRange r2) {
  return r2.begin <= r1.begin && r2.end >= r1.end;
}

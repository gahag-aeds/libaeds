#include "memory.h"

#include <assert.h>


ResourceDisposer rs_disposer_al(Allocator* al) {
  assert(al != NULL);
  
  return rs_disposer_d(al, al_dealloc_void);
}

void al_dealloc_void(void* al, void* ptr) {
  assert(al != NULL);
  
  al_dealloc((Allocator*) al, ptr);
}

#include "memory.h"

#include <assert.h>


void* rs_register_alloc(
  Allocator allocator,
  size_t count,
  size_t size,
  ResourceDisposer disposer,
  Resources* rss
) {
  assert(rss != NULL);
  
  void* ptr = al_alloc(&allocator, count, size);
  
  return rs_register(ptr, disposer, rss) ? ptr
                                         : NULL;
}

ResourceDisposer rs_disposer_al(const Allocator* al) {
  assert(al != NULL);
  
  return rs_disposer_d((void*) al, al_dealloc_void);
}

void al_dealloc_void(void* al, void* ptr) {
  assert(al != NULL);
  
  al_dealloc((const Allocator*) al, ptr);
}

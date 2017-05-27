#include "memory.h"


ResourceDisposer rs_disposer_al(Allocator* al) {
  return rs_disposer_d(al, al_dealloc_void);
}

void al_dealloc_void(void* al, void* ptr) {
  Allocator* allocator = al;
  al_dealloc(*allocator, ptr);
}

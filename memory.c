#include <stdlib.h>

#include "memory.h"


void* alloc(allocator allocator, size_t size) {
  void* ptr = allocator.allocate(size);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
      allocator.mem_error();
  
  return ptr;
}

void dealloc(allocator allocator, void* ptr) {
  allocator.deallocate(ptr);
}


allocator std_allocator(void (*mem_error)(void)) {
  return (allocator) {
    .allocate   = malloc,
    .deallocate = free,
    .mem_error  = mem_error
  };
}

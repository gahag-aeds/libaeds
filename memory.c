#include <stdlib.h>

#include "memory.h"


void* alloc(allocator allocator, size_t size) {
  void* ptr = allocator.allocate(size);
  
  if (ptr == NULL)
    allocator.mem_error();
  
  return ptr;
}

void dealloc(allocator allocator, void* ptr) {
  allocator.deallocate(ptr);
}


allocator mallocator(void (*mem_error)(void)) {
  return (allocator) {
    .allocate   = malloc,
    .deallocate = free,
    .mem_error  = mem_error
  };
}

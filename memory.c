#include "memory.h"

#include <stdlib.h>


void* al_alloc(allocator allocator, size_t num, size_t size) {
  void* ptr = allocator.allocate(num, size);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
      allocator.mem_error();
  
  return ptr;
}

void* al_alloc_clear(allocator allocator, size_t num, size_t size) {
  void* ptr = allocator.allocate_clear(num, size);
  
  // A call to allocate_clear with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
      allocator.mem_error();
  
  return ptr;
}

void* al_realloc(allocator allocator, void* ptr, size_t num, size_t size) {
  ptr = allocator.reallocate(ptr, num, size);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
      allocator.mem_error();
  
  return ptr;
}

void al_dealloc(allocator allocator, void* ptr) {
  allocator.deallocate(ptr);
}


static void* checked_malloc(size_t num, size_t size) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : malloc(total_size);
}

static void* checked_realloc(void* ptr, size_t num, size_t size) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : realloc(ptr, total_size);
}


allocator std_allocator(void (*mem_error)(void)) {
  return (allocator) {
    .allocate       = checked_malloc,
    .allocate_clear = calloc,
    .reallocate     = checked_realloc,
    .deallocate     = free,
    .mem_error      = mem_error
  };
}

allocator null_allocator(void) {
  return (allocator) {
    .allocate       = NULL,
    .allocate_clear = NULL,
    .reallocate     = NULL,
    .deallocate     = NULL,
    .mem_error      = NULL
  };
}

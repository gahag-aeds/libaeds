#include "allocator.h"

#include <assert.h>
#include <stdlib.h>


// O(1)
void* al_alloc(allocator allocator, size_t num, size_t size) {
  assert(allocator.allocate != NULL);
  
  void* ptr = allocator.allocate(num, size, allocator.data);  // O(1)
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
    allocator.mem_error();  // O(1)
  
  return ptr;
}

// O(1)
void* al_alloc_clear(allocator allocator, size_t num, size_t size) {
  assert(allocator.allocate_clear != NULL);
  
  void* ptr = allocator.allocate_clear(num, size, allocator.data);  // O(1)
  
  // A call to allocate_clear with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
    allocator.mem_error();  // O(1)
  
  return ptr;
}

// O(1)
void* al_realloc(allocator allocator, void* ptr, size_t num, size_t size) {
  assert(allocator.reallocate != NULL);
  
  ptr = allocator.reallocate(ptr, num, size, allocator.data); // O(1)
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator.mem_error != NULL)
      allocator.mem_error();
  
  return ptr;
}

// O(1)
void al_dealloc(allocator allocator, void* ptr) {
  assert(allocator.deallocate != NULL);
  
  allocator.deallocate(ptr, allocator.data); // O(1)
}



// O(1)
static void* std_malloc(size_t num, size_t size, __attribute__((unused)) void* _) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : malloc(total_size); // O(1)
}

static void* std_calloc(size_t num, size_t size, __attribute__((unused)) void* _) {
  return calloc(num, size);
}

// O(1)
static void* std_realloc(
  void* ptr,
  size_t num,
  size_t size,
  __attribute__((unused)) void* data
) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : realloc(ptr, total_size); // O(1)
}

static void std_free(void* ptr, __attribute__((unused)) void* data) {
  free(ptr);
}


// O(1)
allocator std_allocator(void (*mem_error)(void)) {
  return (allocator) {
    .data = NULL,
    .allocate       = std_malloc,
    .allocate_clear = std_calloc,
    .reallocate     = std_realloc,
    .deallocate     = std_free,
    .mem_error      = mem_error
  };
}

// O(1)
allocator null_allocator(void) {
  return (allocator) {
    .data = NULL,
    .allocate       = NULL,
    .allocate_clear = NULL,
    .reallocate     = NULL,
    .deallocate     = NULL,
    .mem_error      = NULL
  };
}

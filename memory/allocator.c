#include "allocator.h"

#include <assert.h>
#include <stdlib.h>


void* al_alloc(const Allocator* allocator, size_t num, size_t size) {
  assert(allocator != NULL);
  assert(allocator->allocate != NULL);
  
  void* ptr = allocator->allocate(num, size, allocator->data);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator->mem_error != NULL)
    allocator->mem_error();
  
  return ptr;
}

void* al_alloc_clear(const Allocator* allocator, size_t num, size_t size) {
  assert(allocator != NULL);
  assert(allocator->allocate_clear != NULL);
  
  void* ptr = allocator->allocate_clear(num, size, allocator->data);
  
  // A call to allocate_clear with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator->mem_error != NULL)
    allocator->mem_error();
  
  return ptr;
}

void* al_realloc(const Allocator* allocator, void* ptr, size_t num, size_t size) {
  assert(allocator != NULL);
  assert(allocator->reallocate != NULL);
  
  ptr = allocator->reallocate(ptr, num, size, allocator->data);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  if (ptr == NULL && size != 0 && allocator->mem_error != NULL)
      allocator->mem_error();
  
  return ptr;
}

void al_dealloc(const Allocator* allocator, void* ptr) {
  assert(allocator != NULL);
  
  allocator->deallocate(ptr, allocator->data);
}



static void* std_malloc(size_t num, size_t size, __attribute__((unused)) void* _) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : malloc(total_size);
}

static void* std_calloc(size_t num, size_t size, __attribute__((unused)) void* _) {
  return calloc(num, size);
}

static void* std_realloc(
  void* ptr,
  size_t num,
  size_t size,
  __attribute__((unused)) void* _
) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : realloc(ptr, total_size);
}

static void std_free(void* ptr, __attribute__((unused)) void* _) {
  free(ptr);
}


Allocator std_allocator(void (*mem_error)(void)) {
  return (Allocator) {
    .data = NULL,
    .allocate       = std_malloc,
    .allocate_clear = std_calloc,
    .reallocate     = std_realloc,
    .deallocate     = std_free,
    .mem_error      = mem_error
  };
}

#include "allocator.h"

#include <assert.h>
#include <stdbool.h>


// al_alloc
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

void* al_alloc_fma(
  const Allocator* allocator,
  size_t size,
  size_t fma_num,
  size_t fma_size
) {
  assert(allocator != NULL);
  assert(allocator->allocate_fma != NULL);
  
  void* ptr = allocator->allocate_fma(size, fma_num, fma_size, allocator->data);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  const bool size0 = (size == 0) && (fma_num == 0 || fma_size == 0);
  if (ptr == NULL && !size0 && allocator->mem_error != NULL)
    allocator->mem_error();
  
  return ptr;
}


// al_alloc_clear
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

void* al_alloc_clear_fma(
  const Allocator* allocator,
  size_t size,
  size_t fma_num,
  size_t fma_size
) {
  assert(allocator != NULL);
  assert(allocator->allocate_clear_fma != NULL);
  
  void* ptr = allocator->allocate_clear_fma(size, fma_num, fma_size, allocator->data);
  
  // A call to allocate_clear with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  const bool size0 = (size == 0) && (fma_num == 0 || fma_size == 0);
  if (ptr == NULL && !size0 && allocator->mem_error != NULL)
    allocator->mem_error();
  
  return ptr;
}


// al_realloc
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

void* al_realloc_fma(
  const Allocator* allocator,
  void* ptr,
  size_t size,
  size_t fma_num,
  size_t fma_size
) {
  assert(allocator != NULL);
  assert(allocator->reallocate_fma != NULL);
  
  ptr = allocator->reallocate_fma(ptr, size, fma_num, fma_size, allocator->data);
  
  // A call to allocate with 0 as size, will return NULL.
  // According to the standard, that is a valid allocation.
  const bool size0 = (size == 0) && (fma_num == 0 || fma_size == 0);
  if (ptr == NULL && !size0 && allocator->mem_error != NULL)
    allocator->mem_error();
  
  return ptr;
}


void al_dealloc(const Allocator* allocator, void* ptr) {
  assert(allocator != NULL);
  
  allocator->deallocate(ptr, allocator->data);
}

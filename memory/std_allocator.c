#include "allocator.h"

#include <assert.h>
#include <stdlib.h>


// malloc
static void* std_malloc(size_t num, size_t size, __attribute__((unused)) void* _) {
  size_t total_size;
  
  return __builtin_mul_overflow(num, size, &total_size) ? NULL
                                                        : malloc(total_size);
}

static void* std_malloc_fma(
  size_t size,
  size_t fma_num,
  size_t fma_size,
  __attribute__((unused)) void* _
) {
  size_t total_size;
  
  if (__builtin_mul_overflow(fma_num, fma_size, &total_size))
    return NULL;
  
  if (__builtin_add_overflow(size, total_size, &total_size))
    return NULL;
  
  return malloc(total_size);
}


// calloc
static void* std_calloc(size_t num, size_t size, __attribute__((unused)) void* _) {
  return calloc(num, size);
}

static void* std_calloc_fma(
  size_t size,
  size_t fma_num,
  size_t fma_size,
  __attribute__((unused)) void* _
) {
  size_t total_size;
  
  if (__builtin_mul_overflow(fma_num, fma_size, &total_size))
    return NULL;
  
  if (__builtin_add_overflow(size, total_size, &total_size))
    return NULL;
  
  return calloc(1, total_size);
}


// realloc
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

static void* std_realloc_fma(
  void* ptr,
  size_t size,
  size_t fma_num,
  size_t fma_size, __attribute__((unused)) void* _
) {
  size_t total_size;
  
  if (__builtin_mul_overflow(fma_num, fma_size, &total_size))
    return NULL;
  
  if (__builtin_add_overflow(size, total_size, &total_size))
    return NULL;
  
  return realloc(ptr, total_size);
}


// free
static void std_free(void* ptr, __attribute__((unused)) void* _) {
  free(ptr);
}


// allocator
Allocator std_allocator(void (*mem_error)(void)) {
  return (Allocator) {
    .data = NULL,
    
    .allocate     = std_malloc,
    .allocate_fma = std_malloc_fma,
    
    .allocate_clear     = std_calloc,
    .allocate_clear_fma = std_calloc_fma,
    
    .reallocate     = std_realloc,
    .reallocate_fma = std_realloc_fma,
    
    .deallocate = std_free,
    
    .mem_error = mem_error
  };
}

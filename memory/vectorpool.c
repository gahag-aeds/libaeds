#include "vectorpool.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libaeds/adt/stack.h>
#include <libaeds/array.h>


typedef struct vpooldata {
  allocator allocator;
  
  size_t elem_size
       , size;
  
  void* vector;
  stack free_elements;
} vpooldata;


static void* vpool_allocate(size_t, size_t, void*);
static void* vpool_allocate_clear(size_t, size_t, void*);
static void vpool_deallocate(void*, void*);


// O(n)
allocator new_vpool(allocator al, size_t size, size_t elem_size, void (*mem_error)(void)) {
  assert(elem_size > 0 && size > 0);
  
  vpooldata* data = al_alloc(al, 1, sizeof(vpooldata));
  
  *data = (vpooldata) {
    .allocator = al,
    
    .elem_size = elem_size,
    .size      = size,
    
    .vector = al_alloc(al, size, elem_size),
    .free_elements = new_vstack(al, size)
  };
  
  foreach_ix (i, 0, size) // O(n)
    if (!stack_push(&data->free_elements, data->vector + (i * data->elem_size))) // O(1)
      assert(false);
  
  return (allocator) {
    .data = data,
    
    .allocate       = vpool_allocate,
    .allocate_clear = vpool_allocate_clear,
    .reallocate     = NULL,
    .deallocate     = vpool_deallocate,
    .mem_error      = mem_error
  };
}

// O(1)
void delete_vpool(allocator* vpool) {
  assert(vpool != NULL);
  
  vpooldata* data = (vpooldata*) vpool->data;
  
  assert(data != NULL);
  
  allocator al = data->allocator;
  
  al_dealloc(al, data->vector);
  delete_stack(&data->free_elements, NULL, null_allocator()); // O(1)
  al_dealloc(al, data);
  
  *vpool = null_allocator();
}


// O(1)
static void* vpool_allocate(size_t num, size_t size, void* _data) {
  assert(_data != NULL);
  assert(num == 1 && size == ((vpooldata*) _data)->elem_size);
  
  vpooldata* data = _data;
  
  if (num != 1 || size != data->elem_size)
    return NULL;
  
  return stack_pop(&data->free_elements); // O(1)
}

// Worst O(n)
static void* vpool_allocate_clear(size_t num, size_t size, void* _data) {
  assert(_data != NULL);
  assert(num == 1 && size == ((vpooldata*) _data)->elem_size);
  
  vpooldata* data = _data;
  
  if (num != 1 || size != data->elem_size)
    return NULL;
  
  void* ptr = stack_pop(&data->free_elements); // O(1)
  
  return ptr == NULL ? NULL
                     : memset(ptr, 0, data->elem_size); // Worst O(n)
}

// O(1)
static void vpool_deallocate(void* ptr, void* _data) {
  if (ptr == NULL)
    return;
  
  vpooldata* data = _data;
  
  assert(_data != NULL);
  assert(ptr >= data->vector &&
         ptr <= data->vector + ((data->size - 1) * data->elem_size));
  
  if (!stack_push(&data->free_elements, ptr)) // O(1)
    assert(false);
}

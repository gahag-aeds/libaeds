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


allocator new_vpool(allocator al, size_t size, size_t elem_size, void (*mem_error)(void)) {
  assert(al.allocate != NULL && al.deallocate != NULL);
  assert(elem_size > 0 && size > 0);
  
  vpooldata* data = al_alloc(al, 1, sizeof(vpooldata));
  
  *data = (vpooldata) {
    .allocator = al,
    
    .elem_size = elem_size,
    .size      = size,
    
    .vector = al_alloc(al, size, elem_size),
    .free_elements = new_vstack(al, size)
  };
  
  foreach (i, 0, size)
    if (!stack_push(&data->free_elements, data->vector + (i * data->elem_size)))
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

void delete_vpool(allocator* vpool) {
  assert(vpool != NULL);
  
  vpooldata* data = (vpooldata*) vpool->data;
  allocator al = data->allocator;
  
  al_dealloc(al, data->vector);
  delete_stack(&data->free_elements, NULL, null_allocator());
  al_dealloc(al, data);
  
  *vpool = null_allocator();
}


static void* vpool_allocate(size_t num, size_t size, void* _data) {
  assert(_data != NULL);
  assert(num == 1 && size == ((vpooldata*) _data)->elem_size);
  
  vpooldata* data = _data;
  
  if (num != 1 || size != data->elem_size)
    return NULL;
  
  return stack_pop(&data->free_elements);
}

static void* vpool_allocate_clear(size_t num, size_t size, void* _data) {
  assert(_data != NULL);
  assert(num == 1 && size == ((vpooldata*) _data)->elem_size);
  
  vpooldata* data = _data;
  
  if (num != 1 || size != data->elem_size)
    return NULL;
  
  void* ptr = stack_pop(&data->free_elements);
  
  return ptr == NULL ? NULL
                     : memset(ptr, 0, data->elem_size);
}

static void vpool_deallocate(void* ptr, void* _data) {
  vpooldata* data = _data;
  
  assert(_data != NULL);
  assert(ptr >= data->vector && ptr <= data->vector + ((data->size - 1) * data->elem_size));
  
  if (!stack_push(&data->free_elements, ptr))
    assert(false);
}

#ifndef __MEMORY_VECTOR_POOL_H__
#define __MEMORY_VECTOR_POOL_H__

#include <libaeds/memory/allocator.h>


extern allocator new_vpool(
  allocator,
  size_t size,
  size_t elem_size,
  void (*mem_error)(void)
);
extern void delete_vpool(allocator*);


#endif /* __MEMORY_VECTOR_POOL_H__ */

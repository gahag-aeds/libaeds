#ifndef __LIBAEDS_RESOURCES_MEMORY_H__
#define __LIBAEDS_RESOURCES_MEMORY_H__

#include <libaeds/resources/resource.h>


void* rs_register_alloc(
  Allocator,
  size_t count,
  size_t size,
  ResourceDisposer,
  Resources*
);

ResourceDisposer rs_disposer_al(Allocator*);

void al_dealloc_void(void* al, void* ptr);


#endif /* __LIBAEDS_RESOURCES_MEMORY_H__ */

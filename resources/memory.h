#ifndef __LIBAEDS_RESOURCES_MEMORY_H__
#define __LIBAEDS_RESOURCES_MEMORY_H__

#include <libaeds/resources/resource.h>


// Allocate memory using the given allocator,
// and register it as a resource with the given disposer in the given resource collection.
// Returns a pointer to the allocated memory.
// If the allocation fails, returns NULL.
// Note: Allocation failure is handled with the
// `mem_error` function of the allocator before returning.
void* rs_register_alloc(
  Allocator,
  size_t count,
  size_t size,
  ResourceDisposer,
  Resources*
);

// Create a disposer for memory allocated with the given allocator.
ResourceDisposer rs_disposer_al(Allocator*);

// An alias of `al_dealloc`, but taking the allocator as a void*.
void al_dealloc_void(void* al, void* ptr);


#endif /* __LIBAEDS_RESOURCES_MEMORY_H__ */

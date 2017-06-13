#ifndef __LIBAEDS_RESOURCES_RESOURCE_H__
#define __LIBAEDS_RESOURCES_RESOURCE_H__

#include <libaeds/data/container/stack.h>
#include <libaeds/data/resources/disposer.h>


// A type for representing a resource.
// It contains a pointer to the resource and a method to dispose it.
typedef struct Resource {
  void* rs;
  ResourceDisposer disposer;
} Resource;

// A ordered collection of resources.
typedef struct Resources {
  const Allocator* allocator;
  Stack resources;
} Resources;


// Creates a resource from the given pointer and dipose method,
// and register it in a resource collection.
// The order of registration is conserved in the resource collection.
// Returns whether the operation succeeded.
// Attempting to register a NULL pointer automatically returns false.
bool rs_register(void* rs, ResourceDisposer, Resources*);

// Create a resource collection, using the given allocator.
// The returned collection must be passed to delete_resources
// to free the allocated memory.
Resources new_resources(const Allocator*);
// Dispose a collection of resources, previously created with new_resources.
// The resources are disposed in the reverse order of registration.
// Each resource is disposed using the dispose method provided for the resource.
void delete_resources(Resources*);


#endif /* __LIBAEDS_RESOURCES_RESOURCE_H__ */

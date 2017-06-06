#ifndef __LIBAEDS_RESOURCES_RESOURCE_H__
#define __LIBAEDS_RESOURCES_RESOURCE_H__

#include <libaeds/adt/stack.h>
#include <libaeds/resources/disposer.h>


typedef struct Resource {
  void* rs;
  ResourceDisposer disposer;
} Resource;

typedef struct Resources {
  const Allocator* allocator;
  Stack resources;
} Resources;

bool rs_open(void* rs, ResourceDisposer, Resources*);

Resources new_resources(const Allocator*);
void delete_resources(Resources*);


#endif /* __LIBAEDS_RESOURCES_RESOURCE_H__ */

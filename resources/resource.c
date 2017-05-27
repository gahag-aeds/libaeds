#include "resource.h"

#include <assert.h>


bool rs_open(void* rs, ResourceDisposer disposer, Resources* rss) {
  assert(rss != NULL);
  
  if (rs == NULL)
    return false;
  
  Resource* resource = al_alloc(rss->allocator, 1, sizeof(*resource)); {
    *resource = (Resource) {
      .rs = rs,
      .disposer = disposer
    };
  }
  
  return stack_push(
    &rss->resources,
    resource
  );
}

static void rs_close(Allocator al, void* rs) {
  assert(rs != NULL);
  
  Resource* resource = rs;
  
  rs_dispose(&resource->rs, resource->disposer);
  
  al_dealloc(al, rs);
}


Resources new_resources(Allocator al) {
  return (Resources) {
    .allocator = al,
    .resources = new_lstack(al)
  };
}

void delete_resources(Resources* rss) {
  delete_stack(&rss->resources, rs_close, rss->allocator);
  rss->allocator = null_allocator();
}



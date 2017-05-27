#ifndef __LIBAEDS_RESOURCES_MEMORY_H__
#define __LIBAEDS_RESOURCES_MEMORY_H__

#include <libaeds/resources/resource.h>


ResourceDisposer rs_disposer_al(Allocator*);

void al_dealloc_void(void* al, void* ptr);


#endif /* __LIBAEDS_RESOURCES_MEMORY_H__ */

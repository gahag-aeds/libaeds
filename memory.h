#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stddef.h>


typedef struct allocator {
  void* (*allocate)(size_t);
  void (*deallocate)(void*);
  
  void (*mem_error)(void);
} allocator;


extern void* alloc(allocator, size_t);
extern void dealloc(allocator, void*);

// Create a malloc/free allocator for the supplied memory error function:
extern allocator mallocator(void (*mem_error)(void));


#endif /* __MEMORY_H__ */

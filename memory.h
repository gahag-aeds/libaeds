#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stddef.h>


// An allocator is a set of methods for allocating/deallocating memory,
// and error handling when a memory allocation fails.
// The member functions of an allocator should not be called directly.
// Use the helper functions below instead.
// TODO add realloc / calloc
typedef struct allocator {
  void* (*allocate)(size_t);
  void (*deallocate)(void*);
  
  void (*mem_error)(void);
} allocator;


// Allocate a number of bytes in memory using the provided allocator.
// If the supplyed size is 0, a null pointer is returned. That is a valid allocation.
// If the allocation fails, returning a null pointer,
// the allocator.mem_error function, if not null, is called.
extern void* alloc(allocator, size_t);

// Deallocate memory previously allocated via a call to alloc.
extern void dealloc(allocator, void*);

// Create a malloc/free allocator for the supplied memory error function:
// If a null pointer is supplyed as the memory error function,
// memory allocation failure is ignored, returning a null pointer.
extern allocator std_allocator(void (*mem_error)(void));


#endif /* __MEMORY_H__ */

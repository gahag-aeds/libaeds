#ifndef __MEMORY_ALLOCATOR_H__
#define __MEMORY_ALLOCATOR_H__

#include <stddef.h>


// An allocator is a set of methods for allocating/deallocating memory,
// and error handling when a memory allocation fails.
// The member functions of an allocator should not be called directly.
// Use the helper functions below instead.
typedef struct allocator {
  // A pointer to the data internally used by the allocator.
  // If the allocator uses no additional data, this should be NULL.
  void* data;
  
  // Allocate an array of `num` elements of the specified size in memory.
  // If size/num is zero, the behavior is implementation defined. Null pointer may
  // be returned, or some non-null pointer may be returned that may not be used
  // to access storage.
  // The returned pointer, if not null, must be passed to al_dealloc/al_realloc at
  // some point, otherwise a memory leak occurs.
  // The data pointer of the allocator is passed as the last argument to this function.
  void* (*allocate)(size_t num, size_t size, void*);
  
  // Allocate an array of `num` elements of the specified size in memory.
  // If size is zero, the behavior is implementation defined. Null pointer may
  // be returned, or some non-null pointer may be returned that may not be used
  // to access storage.
  // The returned pointer, if not null, must be passed to al_dealloc/al_realloc at
  // some point, otherwise a memory leak occurs.
  // The allocated memory is guaranteed to be 0 initialized.
  // The data pointer of the allocator is passed as the last argument to this function.
  void* (*allocate_clear)(size_t num, size_t size, void*);
  
  // Reallocate previosly allocated memory, with new dimensions of
  // `num` elements of the specified size in memory.
  // The memory must have been allocated via al_alloc/al_alloc_clear/al_realloc,
  // and not yet deallocated (via al_dealloc/al_realloc).
  // 
  // The reallocation is done by either:
  // a) Resizing the existing area pointed to by ptr, if possible.
  // b) Allocating a new memory block of the new size, and copying memory area with size
  //    equal the lesser of the new and the old sizes, and freeing the old block.
  // In both, the original contents of the memory are guaranteed to remain unchanged up to
  // the lesser of the new and old sizes.
  // 
  // If the new size is zero, the behavior is implementation defined. Null pointer may
  // be returned, or some non-null pointer may be returned that may not be used
  // to access storage.
  // The returned pointer, if not null, must be passed to al_dealloc/al_realloc at
  // some point, otherwise a memory leak occurs.
  // The data pointer of the allocator is passed as the last argument to this function.
  void* (*reallocate)(void* prev, size_t num, size_t size, void*);
  
  // Deallocate memory previously allocated via
  // a call to allocate/allocate_clear/reallocate.
  // The data pointer of the allocator is passed as the last argument to this function.
  // A call to al_dealloc supplying a NULL pointer is a no-op.
  void (*deallocate)(void* ptr, void* data);
  
  // Function to call when allocation error is detected.
  // The data pointer of the allocator is passed as the last argument to this function.
  void (*mem_error)(void);
} allocator;


// Allocate an array of `num` elements of the specified size in memory,
// using the provided allocator.
// If size/num is zero, the behavior is implementation defined. Null pointer may
// be returned, or some non-null pointer may be returned that may not be used
// to access storage.
// The returned pointer, if not null, must be passed to al_dealloc/al_realloc at
// some point, otherwise a memory leak occurs.
// If the allocation fails, returning a null pointer,
// the allocator.mem_error function, if not null, is called.
extern void* al_alloc(allocator, size_t num, size_t size);

// Allocate an array of `num` elements of the specified size in memory,
// using the provided allocator.
// If size is zero, the behavior is implementation defined. Null pointer may
// be returned, or some non-null pointer may be returned that may not be used
// to access storage.
// The returned pointer, if not null, must be passed to al_dealloc/al_realloc at
// some point, otherwise a memory leak occurs.
// The allocated memory is guaranteed to be 0 initialized.
// If the allocation fails, returning a null pointer,
// the allocator.mem_error function, if not null, is called.
extern void* al_alloc_clear(allocator, size_t num, size_t size);

// Reallocate previosly allocated memory, with new dimensions of `num` elements of the
// specified size in memory, using the provided allocator.
// The memory must have been allocated via al_alloc/al_alloc_clear/al_realloc,
// and not yet deallocated (via al_dealloc/al_realloc).
// 
// The reallocation is done by either:
// a) Resizing the existing area pointed to by ptr, if possible.
// b) Allocating a new memory block of the new size, and copying memory area with size
//    equal the lesser of the new and the old sizes, and freeing the old block.
// In both, the original contents of the memory are guaranteed to remain unchanged up to
// the lesser of the new and old sizes.
// 
// If the new size is zero, the behavior is implementation defined. Null pointer may
// be returned, or some non-null pointer may be returned that may not be used
// to access storage.
// The returned pointer, if not null, must be passed to al_dealloc/al_realloc at
// some point, otherwise a memory leak occurs.
// If the allocation fails, returning a null pointer, the allocator.mem_error function,
// if not null, is called. The original memory is not deallocated if the allocation fails.
extern void* al_realloc(allocator, void*, size_t num, size_t size);

// Deallocate memory previously allocated via a call to al_alloc/al_alloc_clear/al_realloc.
// A call to al_dealloc supplying a NULL pointer is a no-op.
extern void al_dealloc(allocator, void*);

// Create a malloc/calloc/realloc/free allocator for the supplied memory error function.
// If a null pointer is supplyed as the memory error function,
// memory allocation failure is ignored, returning a null pointer.
extern allocator std_allocator(void (*mem_error)(void));

// Create a allocator with all functions set to NULL.
// Usefull for invalidating an allocator.
extern allocator null_allocator(void);


#endif /* __MEMORY_ALLOCATOR_H__ */

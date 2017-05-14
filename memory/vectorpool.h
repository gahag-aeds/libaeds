#ifndef __MEMORY_VECTOR_POOL_H__
#define __MEMORY_VECTOR_POOL_H__

#include <libaeds/memory/allocator.h>


// Creates an allocator that uses a vector of elements as pool.
// It allocates a vector of the specified size.
// The size of the elements in the vector is `elem_size`.
// The vstack is used to control allocations.
// 
// The resultant allocator has the following properties:
// 
// - It must be deleted with `delete_vpool` when no longer used.
// 
// - It only allows allocations of 1 element of size `elem_size` via
//   al_alloc/al_alloc_clear. An attempt to allocate more than 1 element, or an
//   element of other size results in allocation failure. `mem_error`, if not NULL,
//   is called when an allocation failure occurs. Refer to the allocator.h documentation
//   for more details on allocation failure.
//   
// - If all elements of the pool are in use (where allocated, but not deallocated), an
//   allocation attempt will result in allocation failure.
//   
// - al_realloc is not supported. A call to al_realloc results in assertion failure when
//   assertion is enabled, otherwise, undefined behavior.
//   
// - A call to al_dealloc supplying a NULL pointer is a no-op.
//   A call to al_dealloc supplying a non NULL pointer that matches any of the
//   following is undefined behavior:
//   * The pointer was previously deallocated by al_dealloc.
//   * The pointer was not previously allocated via al_alloc with the same pool.
//   
// - Complexity:
//   * al_alloc, al_dealloc: O(1)
//   * al_alloc_clear: Worst O(n)
//
// Complexity: O(n)
// The space consumed by the vpool is approximately:
// (`size` * `elem_size`) + (`size` * sizeof(void*))
extern allocator new_vpool(
  allocator,
  size_t size,
  size_t elem_size,
  void (*mem_error)(void)
);

// Deletes a pool previously created with new_vpool.
// Supplying a NULL pointer results in assertion failure when assertion is enabled,
// otherwise, undefined behavior.
// Supplying a pointer to a previously deleted stack is undefined behavior.
// Complexity: O(1)
extern void delete_vpool(allocator*);


#endif /* __MEMORY_VECTOR_POOL_H__ */

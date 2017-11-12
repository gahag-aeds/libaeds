#ifndef __LIBAEDS_DATA_RESOURCES_DISPOSER_H__
#define __LIBAEDS_DATA_RESOURCES_DISPOSER_H__

#include "disposer.internal.h"


// A disposing method for a resource.
typedef struct ResourceDisposer ResourceDisposer;


// Create a disposer from a function.
// This function will be called with the resource pointer when the disposer is invoked.
ResourceDisposer rs_disposer(void (*dispose)(void* rs));

// Create a disposer from a data pointer and a function.
// This function will be called with the data
// and resource pointers when the disposer is invoked.
ResourceDisposer rs_disposer_d(void* data, void (*dispose)(void* data, void* rs));

// Create a diposer from a dispose function and an error function.
// The dispose function will be called with the
// resource pointer when the disposer is invoked.
// If the dispose function returns a non-zero status,
// the error function is called with the resource pointer and the returned status.
ResourceDisposer rs_disposer_s(
  int (*dispose)(void* rs),
  void (*error)(void* rs, int status)
);

// Create a disposer from a data pointer, a dispose function and an error function.
// The dispose function will be called with the data
// and resource pointers when the disposer is invoked.
// If the dispose function returns a non-zero status,
// the error function is called with the resource pointer and the returned status.
ResourceDisposer rs_disposer_sd(
  void* data,
  int (*dispose)(void* data, void* rs),
  void (*error)(void* rs, int status)
);


// Invoke the given disposer on the given resource.
// Attempting to dispose a resource that has
// already been disposed with this function is a no-op.
// Returns 0 on success, or the exit code returned by the disposer on failure.
int rs_dispose(void** rs, ResourceDisposer);


#endif /* __LIBAEDS_DATA_RESOURCES_DISPOSER_H__ */

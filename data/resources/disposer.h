#ifndef __LIBAEDS_RESOURCES_DISPOSER_H__
#define __LIBAEDS_RESOURCES_DISPOSER_H__

#include <stdbool.h>


// A disposing method for a resource.
// The intrinsics of this struct are not important for the user.
// It is declared in the header file to provide a complete object type.
typedef struct ResourceDisposer {
  void* data;
  
  bool disposer_reports_status;
  
  union {
    void (*dispose)(void* rs);
    
    void (*dispose_d)(void* data, void* rs);
    
    struct {
      union {
        int (*dispose_s)(void* rs);
        
        int (*dispose_sd)(void* data, void* rs);
      };
      
      void (*error)(void* rs, int status);
    };
  };
} ResourceDisposer;


// Create a disposer from a function.
// This function will be called with the resource pointer when the disposer is invoked.
ResourceDisposer rs_disposer(void (*dispose)(void* rs));

// Create a disposer from a data pointer and a function.
// This function will be called with the data
// and resource pointers when the disposer is invoked.
ResourceDisposer rs_disposer_d(void* data, void (*dispose_d)(void* data, void* rs));

// Create a diposer from a dispose function and an error function.
// The dispose function will be called with the
// resource pointer when the disposer is invoked.
// If the dispose function returns a non-zero status,
// the error function is called with the resource pointer and the returned status.
ResourceDisposer rs_disposer_s(
  int (*dispose_s)(void* rs),
  void (*error)(void* rs, int status)
);

// Create a disposer from a data pointer, a dispose function and an error function.
// The dispose function will be called with the data
// and resource pointers when the disposer is invoked.
// If the dispose function returns a non-zero status,
// the error function is called with the resource pointer and the returned status.
ResourceDisposer rs_disposer_sd(
  void* data,
  int (*dispose_sd)(void* data, void* rs),
  void (*error)(void* rs, int status)
);


// Invoke the given disposer on the given resource.
// Attempting to dispose a resource that has
// already been disposed with this function is a no-op.
int rs_dispose(void** rs, ResourceDisposer);


#endif /* __LIBAEDS_RESOURCES_DISPOSER_H__ */

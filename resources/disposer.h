#ifndef __LIBAEDS_RESOURCES_DISPOSER_H__
#define __LIBAEDS_RESOURCES_DISPOSER_H__

#include <stdbool.h>


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

ResourceDisposer rs_disposer(void (*dispose)(void* rs));

ResourceDisposer rs_disposer_d(void* data, void (*dispose_d)(void* data, void* rs));

ResourceDisposer rs_disposer_s(
  int (*dispose_s)(void* rs),
  void (*error)(void* rs, int status)
);

ResourceDisposer rs_disposer_sd(
  void* data,
  int (*dispose_sd)(void* data, void* rs),
  void (*error)(void* rs, int status)
);


int rs_dispose(void** rs, ResourceDisposer);


#endif /* __LIBAEDS_RESOURCES_DISPOSER_H__ */

#ifndef __LIBAEDS_RESOURCES_DISPOSER_INTERNAL_H__
#define __LIBAEDS_RESOURCES_DISPOSER_INTERNAL_H__

#include <stdbool.h>


struct ResourceDisposer {
  // The tag for the union:
  // 00 : No data parameter and no status reporting.
  // 01 : Has data parameter.
  // 10 : Reports status.
  // 11 : Has data parameter and reports status.
  unsigned type : 2;
  
  union {
    // 0: No data parameter and no status reporting.
    void (*dispose)(void* rs);  // NOT null.
    
    // 1: Has data parameter.
    struct {
      void* data;                            // NOT null.
      void (*dispose)(void* data, void* rs); // NOT null.
    } d;
    
    // 2: Reports status.
    struct {
      int (*dispose)(void* rs);            // NOT null.
      void (*error)(void* rs, int status); // May be NULL.
    } s;
    
    // 3: Has data parameter and reports status.
    struct {
      void* data;                           // NOT null.
      int (*dispose)(void* data, void* rs); // NOT null.
      void (*error)(void* rs, int status);  // May be NULL.
    } sd;
  };
};


#endif /* __LIBAEDS_RESOURCES_DISPOSER_INTERNAL_H__ */

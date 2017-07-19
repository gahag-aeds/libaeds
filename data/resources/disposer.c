#include "disposer.h"

#include <assert.h>
#include <stdlib.h>


struct ResourceDisposer ;
ResourceDisposer rs_disposer(void (*dispose)(void* rs)) {
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .type = 0,
    .dispose = dispose
  };
}

ResourceDisposer rs_disposer_d(void* data, void (*dispose)(void* data, void* rs)) {
  assert(data != NULL);
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .type = 1,
    .d = {
      .data = data,
      .dispose = dispose
    }
  };
}

ResourceDisposer rs_disposer_s(
  int (*dispose)(void* rs),
  void (*error)(void* rs, int status)
) {
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .type = 2,
    .s = {
      .dispose = dispose,
      .error = error
    }
  };
}

ResourceDisposer rs_disposer_sd(
  void* data,
  int (*dispose)(void* data, void* rs),
  void (*error)(void* rs, int status)
) {
  assert(data != NULL);
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .type = 3,
    .sd = {
      .data = data,
      .dispose = dispose,
      .error = error
    }
  };
}


int rs_dispose(void** rs, ResourceDisposer disposer) {
  assert(rs != NULL);
  
  if (*rs == NULL)
    return 0;
  
  
  int status = 0;
  
  switch (disposer.type) {
    case 0:
      assert(disposer.dispose != NULL);
      
      disposer.dispose(*rs);
      
      break;
      
    case 1:
      assert(disposer.d.dispose != NULL);
      assert(disposer.d.data != NULL);
      
      disposer.d.dispose(disposer.d.data, *rs);
      
      break;
      
    case 2:
      assert(disposer.s.dispose != NULL);
      
      status = disposer.s.dispose(*rs);
      
      if (status != 0 && disposer.s.error != NULL)
        disposer.s.error(*rs, status);
      
      break;
        
    case 3:
      assert(disposer.sd.dispose != NULL);
      assert(disposer.sd.data != NULL);
      
      status = disposer.sd.dispose(disposer.sd.data, *rs);
      
      if (status != 0 && disposer.sd.error != NULL)
        disposer.sd.error(*rs, status);
      
      break;
  }
  
  *rs = NULL;

  return status;
}

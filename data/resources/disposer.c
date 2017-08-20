#include "disposer.h"

#include <assert.h>
#include <stdlib.h>


struct ResourceDisposer ;
ResourceDisposer rs_disposer(void (*dispose)(void* rs)) {
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .type = 0,
    .data.dispose = dispose
  };
}

ResourceDisposer rs_disposer_d(void* data, void (*dispose)(void* data, void* rs)) {
  assert(data != NULL);
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .type = 1,
    .data.d = {
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
    .data.s = {
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
    .data.sd = {
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
      assert(disposer.data.dispose != NULL);
      
      disposer.data.dispose(*rs);
      
      break;
      
    case 1:
      assert(disposer.data.d.dispose != NULL);
      assert(disposer.data.d.data != NULL);
      
      disposer.data.d.dispose(disposer.data.d.data, *rs);
      
      break;
      
    case 2:
      assert(disposer.data.s.dispose != NULL);
      
      status = disposer.data.s.dispose(*rs);
      
      if (status != 0 && disposer.data.s.error != NULL)
        disposer.data.s.error(*rs, status);
      
      break;
        
    case 3:
      assert(disposer.data.sd.dispose != NULL);
      assert(disposer.data.sd.data != NULL);
      
      status = disposer.data.sd.dispose(disposer.data.sd.data, *rs);
      
      if (status != 0 && disposer.data.sd.error != NULL)
        disposer.data.sd.error(*rs, status);
      
      break;
  }
  
  *rs = NULL;

  return status;
}

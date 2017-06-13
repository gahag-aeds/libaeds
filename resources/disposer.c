#include "disposer.h"

#include <assert.h>
#include <stdlib.h>


struct ResourceDisposer ;
ResourceDisposer rs_disposer(void (*dispose)(void* rs)) {
  assert(dispose != NULL);
  
  return (ResourceDisposer) {
    .data = NULL,
    .disposer_reports_status = false,
    
    .dispose = dispose
  };
}

ResourceDisposer rs_disposer_d(void* data, void (*dispose_d)(void* data, void* rs)) {
  assert(data != NULL);
  assert(dispose_d != NULL);
  
  return (ResourceDisposer) {
    .data = data,
    .disposer_reports_status = false,
    
    .dispose_d = dispose_d
  };
}

ResourceDisposer rs_disposer_s(
  int (*dispose_s)(void* rs),
  void (*error)(void* rs, int status)
) {
  assert(dispose_s != NULL);
  
  return (ResourceDisposer) {
    .data = NULL,
    .disposer_reports_status = true,
    
    .dispose_s = dispose_s,
    .error = error
  };
}

ResourceDisposer rs_disposer_sd(
  void* data,
  int (*dispose_sd)(void* data, void* rs),
  void (*error)(void* rs, int status)
) {
  assert(data != NULL);
  assert(dispose_sd != NULL);
  
  return (ResourceDisposer) {
    .data = data,
    .disposer_reports_status = true,
    
    .dispose_sd = dispose_sd,
    .error = error
  };
}


int rs_dispose(void** rs, ResourceDisposer disposer) {
  assert(rs != NULL);
  
  if (*rs == NULL)
    return 0;
  
  if (disposer.disposer_reports_status) {
    int status;
    
    if (disposer.data == NULL) {
      assert(disposer.dispose_s != NULL);
      status = disposer.dispose_s(*rs);
    }
    else {
      assert(disposer.dispose_sd != NULL);
      status = disposer.dispose_sd(disposer.data, *rs);
    }
    
    if (status != 0 && disposer.error != NULL)
      disposer.error(*rs, status);
    
    *rs = NULL;
    return status;
  }
  else {
    if (disposer.data == NULL) {
      assert(disposer.dispose != NULL);
      disposer.dispose(*rs);
    }
    else {
      assert(disposer.dispose_d != NULL);
      disposer.dispose_d(disposer.data, *rs);
    }
    
    *rs = NULL;
    return 0;
  }
}

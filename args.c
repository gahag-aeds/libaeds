#include "args.h"

#include <assert.h>
#include <string.h>


argv_handler new_argv_handler(
  allocator allocator,
  size_t argv_size,
  void* param,
  arg_handler handlers[argv_size]
) {
  argv_handler handler = {
    .argv_size = argv_size,
    .parameter = param,
    .handlers = al_alloc(allocator, argv_size, sizeof(arg_handler)),
    .results  = al_alloc(allocator, argv_size, sizeof(int))
  };
  
  memcpy(handler.handlers, handlers, argv_size * sizeof(arg_handler));
  
  return handler;
}

void delete_argv_handler(allocator allocator, argv_handler* handler) {
  al_dealloc(allocator, handler->handlers);
  al_dealloc(allocator, handler->results);
  
  *handler = (argv_handler) {
    .argv_size = 0,
    .parameter = NULL,
    .handlers = NULL,
    .results  = NULL
  };
}


bool handle_args(
  allocator allocator, argv_handler* result_handler,
  size_t argv_size, char* argv[argv_size],
  size_t argv_combinations, argv_handler handlers[argv_combinations]
) {
  assert(
    argv != NULL && argv_size > 0 &&
    handlers != NULL && argv_combinations > 0
  );
  
  argv_handler* handler = NULL;
  
  // argv_dimensions should not be a big array.
  for (size_t i = 0; i < argv_combinations; i++) {
    assert(handlers[i].handlers != NULL);
    
    if (handlers[i].argv_size == argv_size)
      handler = &handlers[i];
    else
      delete_argv_handler(allocator, &handlers[i]);
  }
  
  if (handler == NULL)
    return false;
  
  
  for (size_t i = 0; i < argv_size; i++) {
    arg_handler arg_handler = handler->handlers[i];
    
    if (handler->results != NULL) {
      handler->results[i] =
        arg_handler == NULL ? 0
                            : arg_handler(argv[i], handler->parameter);
    }
    else
      if (arg_handler != NULL)
        arg_handler(argv[i], handler->parameter);
  }
  
  *result_handler = *handler;
  
  return true;
}

#include "args.h"

#include <assert.h>
#include <string.h>


argvhandler new_argvhandler(
  allocator allocator,
  size_t argv_size,
  void* param,
  arg_handler handlers[argv_size]
) {
  argvhandler handler = {
    .argv_size = argv_size,
    .parameter = param,
    .handlers = al_alloc(allocator, argv_size, sizeof(arg_handler))
  };
  
  memcpy(handler.handlers, handlers, argv_size * sizeof(arg_handler));
  
  return handler;
}

void delete_argvhandler(allocator allocator, argvhandler* handler) {
  al_dealloc(allocator, handler->handlers);
  
  *handler = (argvhandler) {
    .argv_size = 0,
    .parameter = NULL,
    .handlers = NULL
  };
}


argvresults new_argvresults(allocator allocator, size_t argv_size) {
  return (argvresults) {
    .argv_size = argv_size,
    .data = al_alloc(allocator, argv_size, sizeof(int))
  };
}

void delete_argvresults(allocator allocator, argvresults* results) {
  al_dealloc(allocator, results->data);
  
  *results = (argvresults) {
    .argv_size = 0,
    .data = NULL
  };
}


bool handle_args(
  allocator allocator, argvresults* results,
  size_t argv_size, char* argv[argv_size],
  size_t argv_combinations, argvhandler handlers[argv_combinations]
) {
  assert(
    argv != NULL && argv_size > 0 &&
    handlers != NULL && argv_combinations > 0
  );
  
  argvhandler* handler = NULL;
  
  // Find the handler for the exact number of arguments.
  // argv_dimensions should not be a big array, linear search is ok.
  for (size_t i = 0; i < argv_combinations; i++) {
    assert(handlers[i].handlers != NULL);
    
    if (handlers[i].argv_size != argv_size) // Delete the handlers that don't match.
      delete_argvhandler(allocator, &handlers[i]);
    else {
      handler = &handlers[i]; // Found correct handler.
      
      // Just delete the remaining handlers.
      for (i = i + 1; i < argv_combinations; i++) {
        assert(handlers[i].handlers != NULL);
        delete_argvhandler(allocator, &handlers[i]);
      }
      
      break;
    }
  }
  
  if (handler == NULL)  // No matching handler found.
    return false;
  
  
  if (results == NULL)
    for (size_t i = 0; i < argv_size; i++) {
      arg_handler arg_handler = handler->handlers[i];
    
      if (arg_handler != NULL)
        arg_handler(argv[i], handler->parameter);
    }
  else {
    *results = new_argvresults(allocator, argv_size);
    
    for (size_t i = 0; i < argv_size; i++) {
      arg_handler arg_handler = handler->handlers[i];
      
      results->data[i] = arg_handler == NULL ? 0
                                             : arg_handler(argv[i], handler->parameter);
    }
  }
  
  delete_argvhandler(allocator, handler);
  
  return true;
}

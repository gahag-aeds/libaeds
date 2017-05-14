#include "args.h"

#include <assert.h>
#include <string.h>

#include <libaeds/array.h>


// Worst: O(n)
argvhandler new_argvhandler(
  allocator allocator,
  size_t argv_size,
  void* param,
  arghandler handlers[static argv_size]
) {
  assert(argv_size != 0);
  assert(handlers != NULL);
  
  argvhandler handler = {
    .allocator = allocator,
    
    .argv_size = argv_size,
    .parameter = param,
    .handlers = al_alloc(allocator, argv_size, sizeof(arghandler))
  };
  
  memcpy(handler.handlers, handlers, argv_size * sizeof(arghandler));
  
  return handler;
}

// O(1)
void delete_argvhandler(argvhandler* handler) {
  assert(handler != NULL);
  
  al_dealloc(handler->allocator, handler->handlers);
  
  *handler = (argvhandler) {
    .allocator = null_allocator(),
    
    .argv_size = 0,
    .parameter = NULL,
    .handlers = NULL
  };
}


// O(1)
argvresults new_argvresults(allocator allocator, size_t argv_size) {
  assert(argv_size != 0);
  
  return (argvresults) {
    .allocator = allocator,
    
    .argv_size = argv_size,
    .data = al_alloc(allocator, argv_size, sizeof(int))
  };
}

// O(1)
void delete_argvresults(argvresults* results) {
  assert(results != NULL);
  
  al_dealloc(results->allocator, results->data);
  
  *results = (argvresults) {
    .allocator = null_allocator(),
    
    .argv_size = 0,
    .data = NULL
  };
}


// Find the handler for the exact number of arguments. Deletes the remaining handlers.
// O(n) where n is the number of elements in argv_handlers
static argvhandler* extract_argv_handler(
  size_t argv_size,
  size_t argv_combinations,
  argvhandler argv_handlers[static argv_combinations]
) {
  argvhandler* argv_handler = NULL;
  
  // Find the handler for the exact number of arguments.
  // argv_dimensions should not be a big array, linear search is ok.
  foreach_ix (i, 0, argv_combinations) { // O(n)
    assert(argv_handlers[i].handlers != NULL);
    
    if (argv_handlers[i].argv_size != argv_size) // Delete the handlers that don't match.
      delete_argvhandler(&argv_handlers[i]);  // O(1)
    else {
      argv_handler = &argv_handlers[i]; // Found correct handler. O(1)
      
      // Just delete the remaining handlers.
      for (i = i + 1; i < argv_combinations; i++) { // O(n - i)
        assert(argv_handlers[i].handlers != NULL);
        delete_argvhandler(&argv_handlers[i]); // O(1)
      }
      
      break;
    }
  }
  
  return argv_handler;
}

// O(argv_combinations + argv_size) if a handler matches the argv_size.
// O(argv_combinations) otherwise.
bool handle_args(
  allocator allocator, argvresults* results,
  size_t argv_size, char* argv[static argv_size],
  size_t argv_combinations, argvhandler argv_handlers[static argv_combinations]
) {
  assert(
    argv != NULL && argv_size > 0 &&
    argv_handlers != NULL && argv_combinations > 0
  );
  
  argvhandler* argv_handler = extract_argv_handler(
    argv_size,
    argv_combinations,
    argv_handlers
  );  // O(argv_combinations)
  
  if (argv_handler == NULL)  // No matching handler found.
    return false;
  
  void* parameter = argv_handler->parameter;
  
  if (results == NULL)  // O(argv_size)
    foreach_ix (i, 0, argv_size) { // O(argv_size)
      arghandler handler = argv_handler->handlers[i];
    
      if (handler != NULL)
        handler(argv[i], parameter);
    }
  else {  // O(argv_size)
    *results = new_argvresults(allocator, argv_size); // O(1)
    
    foreach_ix (i, 0, argv_size) { // O(argv_size)
      arghandler handler = argv_handler->handlers[i];
      
      results->data[i] = handler == NULL ? 0
                                         : handler(argv[i], parameter); // O(1)
    }
  }
  
  delete_argvhandler(argv_handler); // O(1)
  
  return true;
}

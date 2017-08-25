#include "args.h"

#include <assert.h>
#include <string.h>

#include <libaeds/data/ix/ix.h>


// Worst: O(n)
ArgVHandler new_argvhandler(
  const Allocator* allocator,
  size_t argv_size,
  void* param,
  ArgHandler handlers[static argv_size]
) {
  assert(allocator != NULL);
  assert(argv_size != 0);
  assert(handlers != NULL);
  
  ArgVHandler handler = {
    .allocator = allocator,
    
    .argv_size = argv_size,
    .parameter = param,
    .handlers = al_alloc(allocator, argv_size, sizeof(ArgHandler))
  };
  
  memcpy(handler.handlers, handlers, argv_size * sizeof(ArgHandler));
  
  return handler;
}

// O(1)
void delete_argvhandler(ArgVHandler* handler) {
  assert(handler != NULL);
  
  al_dealloc(handler->allocator, handler->handlers);
  
  *handler = (ArgVHandler) {
    .allocator = NULL,
    
    .argv_size = 0,
    .parameter = NULL,
    .handlers = NULL
  };
}


// O(1)
ArgVResults new_argvresults(const Allocator* allocator, size_t argv_size) {
  assert(allocator != NULL);
  assert(argv_size != 0);
  
  return (ArgVResults) {
    .allocator = allocator,
    
    .argv_size = argv_size,
    .data = al_alloc(allocator, argv_size, sizeof(int))
  };
}

// O(1)
void delete_argvresults(ArgVResults* results) {
  assert(results != NULL);
  
  al_dealloc(results->allocator, results->data);
  
  *results = (ArgVResults) {
    .allocator = NULL,
    
    .argv_size = 0,
    .data = NULL
  };
}


// Find the handler for the exact number of arguments. Deletes the remaining handlers.
// O(n) where n is the number of elements in argv_handlers
static ArgVHandler* extract_argv_handler(
  size_t argv_size,
  size_t argv_combinations,
  ArgVHandler argv_handlers[static argv_combinations]
) {
  ArgVHandler* argv_handler = NULL;
  
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
  const Allocator* allocator, ArgVResults* results,
  size_t argv_size, char* argv[static argv_size],
  size_t argv_combinations, ArgVHandler argv_handlers[static argv_combinations]
) {
  assert(allocator != NULL);
  assert(
    argv != NULL && argv_size > 0 &&
    argv_handlers != NULL && argv_combinations > 0
  );
  
  ArgVHandler* argv_handler = extract_argv_handler(
    argv_size,
    argv_combinations,
    argv_handlers
  );  // O(argv_combinations)
  
  if (argv_handler == NULL)  // No matching handler found.
    return false;
  
  void* parameter = argv_handler->parameter;
  
  if (results == NULL)  // O(argv_size)
    foreach_ix (i, 0, argv_size) { // O(argv_size)
      ArgHandler handler = argv_handler->handlers[i];
    
      if (handler != NULL)
        handler(argv[i], parameter);
    }
  else {  // O(argv_size)
    *results = new_argvresults(allocator, argv_size); // O(1)
    
    foreach_ix (i, 0, argv_size) { // O(argv_size)
      ArgHandler handler = argv_handler->handlers[i];
      
      results->data[i] = handler == NULL ? 0
                                         : handler(argv[i], parameter); // O(1)
    }
  }
  
  delete_argvhandler(argv_handler); // O(1)
  
  return true;
}

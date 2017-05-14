#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/memory/allocator.h>


// A handler for an argument is a function that takes that argument
// and an additional parameter, returning a status code.
typedef int (*arghandler)(const char*, void*);

// A handler for an argv of size `argv_size` is a collection of handlers
// for each argument in argv, plus the parameter to be supplied to those
// handlers. Also, the allocator used to allocate the handlers vector
// is stored to deallocate it when necessary.
typedef struct argvhandler {
  allocator allocator;
  
  size_t argv_size;
  void* parameter;
  arghandler* handlers;
} argvhandler;

// The results produced by an argvhandler for an argv of size `argv_size`
// is a collection of the status codes produced by each arghandler. Also, the allocator
// used to allocate the handlers vector is stored to deallocate it when necessary.
typedef struct argvresults {
  allocator allocator;
  
  size_t argv_size;
  int* data;
} argvresults;



// Creates an argvhandler for the specified argv size,
// with the specified param and handlers.
// The produced handler must be deleted with delete_argvhandler when no longer used.
// It uses the specified allocator for allocations.
// Complexity: Worst O(n)
extern argvhandler new_argvhandler(
  allocator,
  size_t argv_size,
  void* param,
  arghandler[static argv_size]
);

// Deletes an argvhandler created with new_argvhandler.
// Complexity: O(1)
extern void delete_argvhandler(argvhandler*);


// Creates an argvresults for the specified argv size.
// The produced argvresults must be deleted with delete_argvresults when no longer used.
// It uses the specified allocator for allocations.
// Complexity: O(1)
extern argvresults new_argvresults(allocator, size_t argv_size);

// Deletes an argvresults created with new_argvresults.
// Complexity: O(1)
extern void delete_argvresults(argvresults*);


// Applies the first matching argvhandler to the supplied argv.
// A match happens if the argv_size of an argvhandler equals the size of the supplied argv.
// If `results` is not NULL, it is initialized with new_argvresults, and the results of the
// handlers are collected. It must be deleted by the caller with delete_argvresults.
// Returns wether a matching handler was found.
// Complexity:
// O(argv_size + argv_combinations) if a handler matches the argv_size.
// O(argv_combinations) otherwise.
extern bool handle_args(
  allocator, argvresults* results,
  size_t argv_size, char* argv[static argv_size],
  size_t argv_combinations, argvhandler[static argv_combinations]
);


#endif /* __ARGS_H__ */

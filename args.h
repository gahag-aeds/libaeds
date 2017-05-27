#ifndef __LIBAEDS_ARGS_H__
#define __LIBAEDS_ARGS_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/memory/allocator.h>


// A handler for an argument is a function that takes that argument
// and an additional parameter, returning a status code.
typedef int (*ArgHandler)(const char*, void*);

// A handler for an argv of size `argv_size` is a collection of handlers
// for each argument in argv, plus the parameter to be supplied to those
// handlers. Also, the allocator used to allocate the handlers vector
// is stored to deallocate it when necessary.
typedef struct ArgVHandler {
  Allocator allocator;
  
  size_t argv_size;
  void* parameter;
  ArgHandler* handlers;
} ArgVHandler;

// The results produced by an ArgVHandler for an argv of size `argv_size`
// is a collection of the status codes produced by each ArgHandler. Also, the allocator
// used to allocate the handlers vector is stored to deallocate it when necessary.
typedef struct ArgVResults {
  Allocator allocator;
  
  size_t argv_size;
  int* data;
} ArgVResults;



// Creates an ArgVHandler for the specified argv size,
// with the specified param and handlers.
// The produced handler must be deleted with delete_argvhandler when no longer used.
// It uses the specified allocator for allocations.
// Complexity: Worst O(n)
ArgVHandler new_argvhandler(
  Allocator,
  size_t argv_size,
  void* param,
  ArgHandler[static argv_size]
);

// Deletes an ArgVHandler created with new_argvhandler.
// Complexity: O(1)
void delete_argvhandler(ArgVHandler*);


// Creates an ArgVResults for the specified argv size.
// The produced ArgVResults must be deleted with delete_argvresults when no longer used.
// It uses the specified allocator for allocations.
// Complexity: O(1)
ArgVResults new_argvresults(Allocator, size_t argv_size);

// Deletes an ArgVResults created with new_argvresults.
// Complexity: O(1)
void delete_argvresults(ArgVResults*);


// Applies the first matching ArgVHandler to the supplied argv.
// A match happens if the argv_size of an ArgVHandler equals the size of the supplied argv.
// If `results` is not NULL, it is initialized with new_argvresults, and the results of the
// handlers are collected. It must be deleted by the caller with delete_argvresults.
// Returns wether a matching handler was found.
// Complexity:
// O(argv_size + argv_combinations) if a handler matches the argv_size.
// O(argv_combinations) otherwise.
bool handle_args(
  Allocator, ArgVResults* results,
  size_t argv_size, char* argv[static argv_size],
  size_t argv_combinations, ArgVHandler[static argv_combinations]
);


#endif /* __LIBAEDS_ARGS_H__ */

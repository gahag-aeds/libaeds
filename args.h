#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/memory/allocator.h>


typedef int (*arg_handler)(const char*, void*);

typedef struct argvhandler {
  size_t argv_size;
  void* parameter;
  arg_handler* handlers;
} argvhandler;

typedef struct argvresults {
  size_t argv_size;
  int* data;
} argvresults;


extern argvhandler new_argvhandler(
  allocator,
  size_t argv_size,
  void* param,
  arg_handler[static argv_size]
);
extern void delete_argvhandler(allocator, argvhandler*);

extern argvresults new_argvresults(allocator, size_t argv_size);
extern void delete_argvresults(allocator, argvresults*);

extern bool handle_args(
  allocator, argvresults* result_handler,
  size_t argv_size, char* argv[static argv_size],
  size_t argv_combinations, argvhandler handlers[static argv_combinations]
);


#endif /* __ARGS_H__ */

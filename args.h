#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdbool.h>
#include <stddef.h>

#include <libaeds/memory.h>


typedef int (*arg_handler)(const char*, void*);

typedef struct argv_handler {
  size_t argv_size;
  void* parameter;
  arg_handler* handlers;
  int* results;
} argv_handler;


extern argv_handler new_argv_handler(
  allocator,
  size_t argv_size,
  void* param,
  arg_handler[argv_size]
);

extern void delete_argv_handler(allocator, argv_handler*);


extern bool handle_args(
  allocator, argv_handler* result_handler,
  size_t argv_size, char* argv[argv_size],
  size_t argv_combinations, argv_handler handlers[argv_combinations]
);


#endif /* __ARGS_H__ */

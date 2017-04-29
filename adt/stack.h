#ifndef __STACK_H__
#define __STACK_H__

#include <libaeds/adt/storagetype.h>
#include <libaeds/adt/linkedlist.h>
#include <libaeds/adt/vectorlist.h>


typedef struct stack {
  storagetype type;
  
  union {
    linkedlist llist;
    vectorlist vlist;
  } data;
  
  
  void (*delete)(struct stack*, void (*delete)(allocator, void*), allocator);
  
  bool (*empty)(struct stack);
  
  bool (*push)(struct stack*, const void*);
  void* (*pop)(struct stack*);
} stack;


stack new_lstack(allocator);
stack new_vstack(allocator, size_t);

void delete_stack(stack*, void (*delete)(allocator, void*), allocator);

bool stack_empty(stack);

bool stack_push(stack*, const void*);
void* stack_pop(stack*);


#endif /* __STACK_H__ */

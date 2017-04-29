#include "stack.h"


bool  vstack_empty(stack);
bool  vstack_push(stack*, const void*);
void* vstack_pop(stack*);

bool  lstack_empty(stack);
bool  lstack_push(stack*, const void*);
void* lstack_pop(stack*);


void delete_lstack(stack* s, void (*delete)(allocator, void*), allocator allocator) {
  delete_llist(&s->data.llist, delete, allocator);
  
  *s = (stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}

void delete_vstack(stack* s, void (*delete)(allocator, void*), allocator allocator) {
  delete_vlist(&s->data.vlist, delete, allocator);
  
  *s = (stack) {
    .type = -1,
    
    .delete = NULL,
    
    .empty = NULL,
    
    .push = NULL,
    .pop  = NULL
  };
}


stack new_lstack(allocator allocator) {
  return (stack) {
    .type = LinkedList,
    .data.llist = new_llist(allocator),
    
    .delete = delete_lstack,
    
    .empty = lstack_empty,
    
    .push = lstack_push,
    .pop  = lstack_pop
  };
}

stack new_vstack(allocator allocator, size_t size) {
  return (stack) {
    .type = VectorList,
    .data.vlist = new_vlist(allocator, size),
    
    .delete = delete_vstack,
    
    .empty = vstack_empty,
    
    .push  = vstack_push,
    .pop   = vstack_pop
  };
}


void delete_stack(stack* s, void (*delete)(allocator, void*), allocator allocator) {
  return s->delete(s, delete, allocator);
}


bool stack_empty(stack s) {
  return s.empty(s);
}


bool stack_push(stack* s, const void* obj) {
  return s->push(s, obj);
}

void* stack_pop(stack* s) {
  return s->pop(s);
}



bool vstack_empty(stack s) {
  return vlist_empty(s.data.vlist);
}

bool vstack_push(stack* s, const void* obj) {
  return vlist_push_head(&s->data.vlist, obj);
}

void* vstack_pop(stack* s) {
  return vlist_pop_head(&s->data.vlist);
}


bool lstack_empty(stack s) {
  return llist_empty(s.data.llist);
}

bool lstack_push(stack* s, const void* obj) {
  llist_push_head(&s->data.llist, obj);
  return true;
}

void* lstack_pop(stack* s) {
  return llist_pop_head(&s->data.llist);
}

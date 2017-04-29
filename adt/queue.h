#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <libaeds/memory.h>
#include <libaeds/adt/storagetype.h>
#include <libaeds/adt/linkedlist.h>
#include <libaeds/adt/vectorlist.h>


typedef struct queue {
  storagetype type;
  
  union {
    linkedlist llist;
    vectorlist vlist;
  } data;
  
  
  void (*delete)(struct queue*, void (*delete)(allocator, void*), allocator);
  
  bool (*empty)(struct queue);
  
  bool (*enqueue)(struct queue*, const void*);
  void* (*dequeue)(struct queue*);
} queue;


queue new_lqueue(allocator);
queue new_vqueue(allocator, size_t);

void delete_queue(queue*, void (*delete)(allocator, void*), allocator);

bool queue_empty(queue);

bool enqueue(queue*, const void*);
void* dequeue(queue*);


#endif /* __QUEUE_H__ */

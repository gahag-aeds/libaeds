#ifndef __LIBAEDS_DATA_CONTAINER_ITERATOR_H__
#define __LIBAEDS_DATA_CONTAINER_ITERATOR_H__


// An iterator is a trait to identify and traverse elements of a container.
typedef struct Iterator {
  const void* container;  // The container where the iterator iterates.
  void* data; // The inner state of the iterator,
              // used to localize itself inside the container.
  
  // Returns the element identified by the iterator.
  // If the iterator was advanced past the end of the container, returns NULL.
  void* (*get)(struct Iterator*);
  
  // Move the iterator to the next position in the container.
  // If the iterator was at the last position of the container,
  // this function invalidates it, so further calls to `get` will return NULL.
  void (*advance)(struct Iterator*);
} Iterator;


// Returns the element identified by the iterator.
// If the iterator was advanced past the end of the container, returns NULL.
void* it_get(Iterator);

// Move the iterator to the next position in the container.
// If the iterator was at the last position of the container,
// this function invalidates it, so further calls to `get` will return NULL.
void it_next(Iterator);


#endif /* __LIBAEDS_DATA_CONTAINER_ITERATOR_H__ */

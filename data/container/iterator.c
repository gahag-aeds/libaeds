#include "iterator.h"

#include <assert.h>
#include <stddef.h>


void* it_get(Iterator* it) {
  assert(it != NULL);
  assert(it->get != NULL);
  return it->get(it);
}

void it_next(Iterator* it) {
  assert(it != NULL);
  assert(it->advance != NULL);
  it->advance(it);
}

#include "monoid.h"

#include <assert.h>
#include <stddef.h>


void monoid_clear(Monoid m, void* data) {
  assert(m.clear != NULL);
  
  m.clear(data);
}

void monoid_append(Monoid m, void* data, const void* new) {
  assert(m.append != NULL);
  
  m.append(data, new);
}

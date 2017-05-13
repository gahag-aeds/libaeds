#include "file.h"

#include <assert.h>


bool file_skip_line(FILE* stream) {
  assert(stream != NULL);
  
  int c;
  
  do {
    c = fgetc(stream);  // O(1)
  } while(c != '\n' && c != EOF); // O(n)
  
  return c != EOF;
}

#include "file.h"

#include <assert.h>


// O(n)
bool file_skip_line(FILE* stream) {
  assert(stream != NULL);
  
  int c;
  
  do {  // O(n)
    c = fgetc(stream);  // O(1)
  } while(c != '\n' && c != EOF);
  
  return c != EOF;
}

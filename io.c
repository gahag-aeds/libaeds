#include "io.h"

#include <assert.h>


bool file_skip_line(FILE* stream) {
  assert(stream != NULL);
  
  int c;
  
  do {
    c = fgetc(stream);
  } while(c != '\n' && c != EOF);
  
  return c != EOF;
}

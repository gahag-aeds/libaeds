#include "file.h"

#include <assert.h>


bool rs_register_file(
  FILE** file,
  const char* restrict filename,
  const char* restrict mode,
  ResourceDisposer disposer,
  Resources* rss
) {
  assert(file != NULL);
  assert(rss != NULL);
  
  return rs_register(
    *file = fopen(filename, mode),
    disposer,
    rss
  );
}

ResourceDisposer rs_disposer_file(void (*error)(void* file, int status)) {
  return rs_disposer_s(fclose_void, error);
}

int fclose_void(void* file) {
  return fclose(file);
}

void fclose_stderr(__attribute__((unused)) void* file, int err) {
  fprintf(stderr, "fclose: %d", err);
}

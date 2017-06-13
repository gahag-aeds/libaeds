#ifndef __LIBAEDS_RESOURCES_FILE_H__
#define __LIBAEDS_RESOURCES_FILE_H__

#include <stdio.h>

#include <libaeds/resources/resource.h>


// Open a file using `fopen` and the given parameters,
// and register it as a resource with the given disposer in the given resource collection.
// Returns wether the operation succeeded.
bool rs_register_file(
  FILE** file,
  const char* restrict filename,
  const char* restrict mode,
  ResourceDisposer,
  Resources*
);

// Create a disposer for a file opened with `fopen`.
// Disposing is done through `fclose`.
// If `fclose` returns a non-zero status, the given error function,
// if not NULL, is invoked with the file pointer and the returned status from `fclose`.
// Note: fclose_stderr (below) is an example of a possible error function for the disposer.
ResourceDisposer rs_disposer_file(void (*error)(void* file, int status));

// An alias of `fclose`, but taking the file as a void*.
int fclose_void(void*);

// A function to handle a fclose error.
// Because fcloses sets errno on error, both parameters are ignored and perror is called.
void fclose_stderr(void* file, int err);


#endif /* __LIBAEDS_RESOURCES_FILE_H__ */

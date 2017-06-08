#ifndef __LIBAEDS_RESOURCES_FILE_H__
#define __LIBAEDS_RESOURCES_FILE_H__

#include <stdio.h>

#include <libaeds/resources/resource.h>


bool rs_register_file(
  FILE** file,
  const char* restrict filename,
  const char* restrict mode,
  ResourceDisposer,
  Resources*
);

ResourceDisposer rs_disposer_file(void (*error)(void* file, int status));

int fclose_void(void*);

void fclose_stderr(void* file, int err);


#endif /* __LIBAEDS_RESOURCES_FILE_H__ */

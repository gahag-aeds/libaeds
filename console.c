#include "console.h"

#include <assert.h>
#include <stdio.h>


bool prompt(const char* prompt, const char* format, void* ptr) {
  assert(prompt != NULL && format != NULL && ptr != NULL);
  
  return fputs(prompt, stdout) >= 0
      && scanf(format, ptr) == 1;
}

#include "console.h"

#include <assert.h>
#include <stdio.h>


// O(1)
bool prompt(const char* prompt, const char* format, ...) {
  assert(prompt != NULL && format != NULL);
  
  va_list va;
  va_start(va, format);
  
  bool result = prompt_va(prompt, format, va);
  
  va_end(va);
  
  return result;
}

// O(1)
bool prompt_va(const char* prompt, const char* format, va_list va) {
  assert(prompt != NULL && format != NULL);
  
  return fputs(prompt, stdout) >= 0
      && vscanf(format, va) == 1;
}

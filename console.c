#include "console.h"

#include <stdio.h>


bool prompt(const char* prompt, const char* format, void* ptr) {
  return fputs(prompt, stdout) >= 0
      && scanf(format, ptr) == 1;
}

#include "util.h"


void mem_swap(void* first, void* second, size_t size) {
  char* a = first;
  char* b = second;
  
  do {
	  char tmp = *a;
	  *a++ = *b;
	  *b++ = tmp;
	} while (--size > 0);
}

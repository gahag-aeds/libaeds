#ifndef __LIBAEDS_IO_CONSOLE_H__
#define __LIBAEDS_IO_CONSOLE_H__

#include <stdarg.h>
#include <stdbool.h>


// Prompt input from stdin. First, fputs the prompt parameter to stdout.
// Then, scanf with the format and the remaining parameters.
// Returns wether fputs or scanf succeeded.
// Complexity: O(1)
bool prompt(const char* prompt, const char* format, ...);

// Varargs version of prompt.
// Complexity: O(1)
bool prompt_va(const char* prompt, const char* format, va_list);


#endif /* __LIBAEDS_IO_CONSOLE_H__ */

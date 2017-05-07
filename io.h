#ifndef __IO_H__
#define __IO_H__

#include <stdbool.h>
#include <stdio.h>


// Skips characters until a newline character is found.
// The newline character is also skipped.
// Returns wether EOF was not reached.
extern bool file_skip_line(FILE*);


#endif /* __IO_H__ */

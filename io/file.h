#ifndef __LIBAEDS_IO_FILE_H__
#define __LIBAEDS_IO_FILE_H__

#include <stdbool.h>
#include <stdio.h>


// Skips characters until a newline character is found.
// The newline character is also skipped.
// Returns wether EOF was not reached.
// Complexity: O(n) where n is the number of characters preceding the line break.
bool file_skip_line(FILE*);


#endif /* __LIBAEDS_IO_FILE_H__ */

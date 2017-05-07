#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stddef.h>


#define foreach(var, from, size) for (size_t var = (from); var < (size); var++)

extern void array_fill(size_t size, void* array[size], void* value);


#endif /* __ARRAY_H__ */

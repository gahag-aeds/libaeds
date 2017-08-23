#ifndef __LIBAEDS_DATA_ORDERING_H__
#define __LIBAEDS_DATA_ORDERING_H__


// A function type for comparing two elements of a given type.
// A comparison function such as `compare(a,b)` returns:
// * a value lower than 0 if a < b.
// * 0 if a == b.
// * a value larger than 0 if a > b.
typedef int compare_fn(const void*, const void*);


// Comparing functions for the standard data types:

int compare_schar(const void*, const void*);
int compare_uchar(const void*, const void*);

int compare_short(const void*, const void*);
int compare_ushort(const void*, const void*);

int compare_int(const void*, const void*);
int compare_uint(const void*, const void*);

int compare_long(const void*, const void*);
int compare_ulong(const void*, const void*);

int compare_longlong(const void*, const void*);
int compare_ulonglong(const void*, const void*);

int compare_float(const void*, const void*);

int compare_double(const void*, const void*);

int compare_ldouble(const void*, const void*);


#endif /* __LIBAEDS_DATA_ORDERING_H__ */

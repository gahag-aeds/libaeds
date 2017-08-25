#ifndef __LIBAEDS_CLASS_MONOID_H__
#define __LIBAEDS_CLASS_MONOID_H__


// A monoid class for a given type.
// A instance of this class must satisfy the following laws:
// `*append(clear(any), x) == *x` (Identity).
// `*append(x, clear(any)) == *x` (Identity).
// `*append(x, append(y, z)) == *append(append(x, y), z)` (Associative).
typedef struct Monoid {
  void* (*clear)(void*);
  void* (*append)(void*, const void*);
} Monoid;


// Simple shortcuts for the monoid members:
void* monoid_clear(Monoid m, void*);
void* monoid_append(Monoid m, void*, const void*);


#endif /* __LIBAEDS_CLASS_MONOID_H__ */

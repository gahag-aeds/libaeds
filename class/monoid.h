#ifndef __LIBAEDS_CLASS_MONOID_H__
#define __LIBAEDS_CLASS_MONOID_H__


typedef struct Monoid {
  void (*clear)(void*);
  void (*append)(void*, const void*);
} Monoid;


void monoid_clear(Monoid m, void*);
void monoid_append(Monoid m, void*, const void*);


#endif /* __LIBAEDS_CLASS_MONOID_H__ */

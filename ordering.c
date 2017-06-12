#include "ordering.h"


#define def_compare(type, name) int compare_##name(const void* a, const void* b) {  \
  type a1 = *(const type*) a;                                                       \
  type a2 = *(const type*) b;                                                       \
                                                                                    \
  if (a1 < a2) return -1;                                                           \
  if (a1 > a2) return 1;                                                            \
  return 0;                                                                         \
}

def_compare(signed char, schar)
def_compare(unsigned char, uchar)

def_compare(short, short);
def_compare(unsigned short, ushort);

def_compare(int, int);
def_compare(unsigned int, uint);

def_compare(long, long);
def_compare(unsigned long, ulong);

def_compare(long long, longlong);
def_compare(unsigned long long, ulonglong);

def_compare(float, float);

def_compare(double, double);

def_compare(long double, ldouble);

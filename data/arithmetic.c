#include "arithmetic.h"

#define def_inc(type, name) void inc_##name(void* _val) { \
  type* val = (type*) _val;                               \
  (*val)++;                                               \
}

#define def_dec(type, name) void dec_##name(void* _val) { \
  type* val = (type*) _val;                               \
  (*val)--;                                               \
}

def_inc(signed char, schar)
def_dec(signed char, schar)

def_inc(unsigned char, uchar)
def_dec(unsigned char, uchar)


def_inc(short, short)
def_dec(short, short)

def_inc(unsigned short, ushort)
def_dec(unsigned short, ushort)


def_inc(int, int)
def_dec(int, int)

def_inc(unsigned int, uint)
def_dec(unsigned int, uint)


def_inc(long, long)
def_dec(long, long)

def_inc(unsigned long, ulong)
def_dec(unsigned long, ulong)


def_inc(long long, longlong)
def_dec(long long, longlong)

def_inc(unsigned long long, ulonglong)
def_dec(unsigned long long, ulonglong)


def_inc(float, float)
def_dec(float, float)


def_inc(double, double)
def_dec(double, double)


def_inc(long double, ldouble)
def_dec(long double, ldouble)

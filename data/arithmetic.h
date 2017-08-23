#ifndef __LIBAEDS_DATA_ARITHMETIC_H__
#define __LIBAEDS_DATA_ARITHMETIC_H__


// A function type for performing basic arithmetic on numerical values.
typedef void arith_fn(void*);


// Basic arithmetic functions for the standard data types:

void inc_schar(void*);
void dec_schar(void*);

void inc_uchar(void*);
void dec_uchar(void*);


void inc_short(void*);
void dec_short(void*);

void inc_ushort(void*);
void dec_ushort(void*);


void inc_int(void*);
void dec_int(void*);

void inc_uint(void*);
void dec_uint(void*);


void inc_long(void*);
void dec_long(void*);

void inc_ulong(void*);
void dec_ulong(void*);


void inc_longlong(void*);
void dec_longlong(void*);

void inc_ulonglong(void*);
void dec_ulonglong(void*);


void inc_float(void*);
void dec_float(void*);


void inc_double(void*);
void dec_double(void*);


void inc_ldouble(void*);
void dec_ldouble(void*);


#endif /* __LIBAEDS_DATA_ARITHMETIC_H__ */

#include "bits.h"


uint8_t popcount_8(uint8_t v) {
  return __builtin_popcount(v);
}

uint8_t popcount_16(uint16_t v) {
  return __builtin_popcount(v);
}

uint8_t popcount_32(uint32_t v) {
  return __builtin_popcountl(v);
}

uint8_t popcount_64(uint64_t v) {
  return __builtin_popcountll(v);
}


#define def_testbit(width) bool testbit_##width(uint##width##_t v, uint8_t b) { \
  const uint##width##_t _1 = 1;                                                 \
  return v & (_1 << b);                                                         \
}

def_testbit(8)
def_testbit(16)
def_testbit(32)
def_testbit(64)


#define def_setbit(width) uint##width##_t setbit_##width(uint##width##_t v, uint8_t b) {  \
  const uint##width##_t _1 = 1;                                                           \
  return v | (_1 << b);                                                                   \
}

def_setbit(8)
def_setbit(16)
def_setbit(32)
def_setbit(64)


#define def_unsetbit(width) uint##width##_t unsetbit_##width(uint##width##_t v, uint8_t b) {  \
  const uint##width##_t _1 = 1;                                                               \
  return v & ~(_1 << b);                                                                      \
}

def_unsetbit(8)
def_unsetbit(16)
def_unsetbit(32)
def_unsetbit(64)

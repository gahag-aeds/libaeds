#include "math.h"

#include <assert.h>

#include <libaeds/data/bits.h>


uint8_t pow2_8(uint8_t v) {
  assert(v < 7);
  return ((uint8_t) 1) << v;
}
uint16_t pow2_16(uint8_t v) {
  assert(v < 15);
  return ((uint16_t) 1) << v;
}
uint32_t pow2_32(uint8_t v) {
  assert(v < 31);
  return ((uint32_t) 1) << v;
}
uint64_t pow2_64(uint8_t v) {
  assert(v < 63);
  return ((uint64_t) 1) << v;
}


uint8_t log2_8(uint8_t v) {
  return msb_8(v);
}
uint8_t log2_16(uint16_t v) {
  return msb_16(v);
}
uint8_t log2_32(uint32_t v) {
  return msb_32(v);
}
uint8_t log2_64(uint64_t v) {
  return msb_64(v);
}

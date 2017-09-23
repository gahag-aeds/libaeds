#include "bits.h"


uint8_t popcount_32(uint32_t v) {
  return (v * 01001001001ULL & 042104210421ULL) % 017;
}

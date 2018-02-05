#ifndef __LIBAEDS_DATA_MATH_H__
#define __LIBAEDS_DATA_MATH_H__

#include <stdint.h>


// pow2: 2^x.
// Complexity: O(1).
uint8_t pow2_8(uint8_t);
uint16_t pow2_16(uint8_t);
uint32_t pow2_32(uint8_t);
uint64_t pow2_64(uint8_t);

// log2: log_2 x.
// Complexity: O(1).
uint8_t log2_8(uint8_t);
uint8_t log2_16(uint16_t);
uint8_t log2_32(uint32_t);
uint8_t log2_64(uint64_t);


#endif /* __LIBAEDS_DATA_MATH_H__ */

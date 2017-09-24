#ifndef __LIBAEDS_DATA_BITS_H__
#define __LIBAEDS_DATA_BITS_H__

#include <stdbool.h>
#include <stdint.h>


// popcount: counts the number of set bits in the given value.
// Complexity: O(1).
uint8_t popcount_8(uint8_t);
uint8_t popcount_16(uint16_t);
uint8_t popcount_32(uint32_t);
uint8_t popcount_64(uint64_t);

// testbit: returns wheter a given bit is set in the value.
// Complexity: O(1).
bool testbit_8(uint8_t, uint8_t);
bool testbit_16(uint16_t, uint8_t);
bool testbit_32(uint32_t, uint8_t);
bool testbit_64(uint64_t, uint8_t);

// setbit: sets the given bit in the value.
// Complexity: O(1).
uint8_t  setbit_8(uint8_t, uint8_t);
uint16_t setbit_16(uint16_t, uint8_t);
uint32_t setbit_32(uint32_t, uint8_t);
uint64_t setbit_64(uint64_t, uint8_t);

// unsetbit: clears the given bit in the value.
// Complexity: O(1).
uint8_t  unsetbit_8(uint8_t, uint8_t);
uint16_t unsetbit_16(uint16_t, uint8_t);
uint32_t unsetbit_32(uint32_t, uint8_t);
uint64_t unsetbit_64(uint64_t, uint8_t);


#endif /* __LIBAEDS_DATA_BITS_H__ */

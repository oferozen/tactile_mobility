#ifndef SRC_BITS_H_
#define SRC_BITS_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/macros.h"

enum endian_t {
    little_endian,
    big_endian
};

enum e_signed_t {
    e_signed,
    e_unsigned,
};

enum endian_t get_endiannes ();
void change_endianness (char* bytes, size_t size);
void inject_field(uint8_t* data, size_t data_size, uint8_t* field, size_t start_bit, size_t length);

// Create a bitmask of length \a len.
#define BIT_MASK(len)           ( (1<<(len))-1 )

// Create a bitfield mask of length \a starting at bit \a start.
#define BIT_MASK_FROM(start, len)     ( BIT_MASK(len)<<(start) )

// Get y[start:(start+len)]
#define BIT_GET(y, start, len)   ( ((y)>>(start)) & BIT_MASK(len) )

// Move x to correct location
#define BIT_PREP(x, start, len)  ( ((x) & BIT_MASK(len)) << (start) )

// Set y[start:(start+len)] = x
#define BIT_SET(y, x, start, len)    \
    ( (y) = (len == 0) ? (y) : ((y) & (~BIT_MASK_FROM((start), (len)))) | BIT_PREP((x), (start), (len)) )

#endif /* SRC_BITS_H_ */

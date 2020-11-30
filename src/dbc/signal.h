#ifndef SRC_SIGNAL_H_
#define SRC_SIGNAL_H_

#include <stdbool.h>
#include <stdint.h>
#include "../utils/bits.h"

typedef struct _signal_t {

    char* name;
    size_t start_bit;
    size_t length;

    union {
        uint32_t usigned_int;
        int32_t signed_int;
    } min;

    union {
        uint32_t usigned_int;
        int32_t signed_int;
    } max;

    size_t byte_size;

    enum endian_t endian;
    enum e_signed_t sign;
    char* units;

}* signal_t;

signal_t signal_create (char* name, size_t start_bit, size_t length, enum endian_t, enum e_signed_t);
void signal_set_unsigned_limits (signal_t signal, uint32_t min, uint32_t max);
void signal_set_signed_limits (signal_t signal, int32_t min, int32_t max);
uint32_t signal_generate_data (signal_t signal);

#endif /* SRC_SIGNAL_H_ */

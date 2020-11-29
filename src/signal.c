#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "signal.h"
#include "utils/memory.h"
#include "random.h"
#include "bits.h"

signal_t signal_create (char* name, size_t start_bit, size_t length, enum endian_t endian, bool is_signed){

    ALLOCATE_AND_ASSIGN(signal_t, signal);
    signal->name = strdup(name);
    signal->start_bit = start_bit;
    signal->length = length;
    signal->byte_size = (length / 8) + 1;
    signal->endian = endian;
    signal->is_signed = is_signed;
    return signal;

}

void signal_set_unsigned_limits (signal_t signal, uint32_t min, uint32_t max) {
    signal->min.usigned_int = min;
    signal->max.usigned_int = max;
}

void signal_set_signed_limits (signal_t signal, int32_t min, int32_t max) {
    signal->min.signed_int = min;
    signal->max.signed_int = max;
}

uint32_t signal_generate_data (signal_t signal) {

    uint32_t result;
    if (signal->is_signed) {
        result = generate_random_signed(signal->min.signed_int, signal->max.signed_int);
    } else {
        result = generate_random_signed(signal->min.usigned_int, signal->max.usigned_int);
    }

    enum endian_t endian = get_endiannes();
    if (endian != signal->endian) {
       change_endianness((char*)&result, 4);
    }

    result <<= (32 - (signal->length));

    return result;
}

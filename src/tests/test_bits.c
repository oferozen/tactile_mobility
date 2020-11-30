#include "tests.h"
#include <stdbool.h>
#include <stdint.h>
#include "../utils/bits.h"
#include "../hw/monitor/monitor.h"

bool test_bits(){
    bool passed = true;

    uint64_t data;
    uint32_t field;


    data = 0x0;//BBBBBBBB;
    field = 0xFF;
    inject_field((uint8_t*) &data, 8,  (uint8_t*) &field, 8, 8);
    ASSERT(data == 0xFF << 8);

    data = 0x0;
    field = 0xFFF;
    inject_field((uint8_t*) &data, 4, (uint8_t*) &field, 16, 12);
    ASSERT(data == 0xFFF << 16);

    data = 0x0;
    field = 0x123;
    inject_field((uint8_t*) &data, 4, (uint8_t*) &field, 13, 12);
    ASSERT(data == 0x123 << 13);

    return passed;
}


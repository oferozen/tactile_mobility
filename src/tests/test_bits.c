#include "tests.h"
#include "../utils/print.h"
#include <stdbool.h>
#include <stdint.h>
#include "../bits.h"

bool test_bits(){
    bool passed = PASSED;

    uint32_t data = 0xBBBBBBBB;
    uint32_t field = 0xFF;
    /*

    inject_field((char*) &data, (char*) &field, 8, 8);
    ASSERT(data == 0xBBBBffBB);
    data = 0xBBBBBBBB;
    field = 0xFFF;
    inject_field((char*) &data, (char*) &field, 16, 12);
    ASSERT(data == 0xBfffBBBB);
    */

    return passed;
}


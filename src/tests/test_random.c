#include <stdbool.h>
#include "../random.h"
#include "tests.h"
#include "../utils/print.h"

bool test_random () {

    bool passed = true;

    uint32_t data;
    int i = 200;
    while (i--) {
        data = generate_random(201, 201);
        ASSERT(passed = data == 201);
    }

    i = 200;
    while (i--) {
        data = generate_random(201, 202);
        ASSERT(passed = (data >= 201 && data <= 202));
    }

    i = 200;
    while (i--) {
        data = generate_random(0, 1 << 17);
        ASSERT(passed = (data >= 0 && data <= 1 << 17));
    }
    return true;
}

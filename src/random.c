#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"
/*
 * RAND_MAX minimum values is 1 << 15.
 * For simpliciy let assume that it is the actual value.
 * More optimization can be done here.
 */
#undef RAND_MAX // Redundant, but makes it clear
#define RAND_MAX (1 << 15)

void random_init() {
    time_t t;
    srand((unsigned) time(&t));
}

uint32_t generate_small_random(uint32_t range) {

    uint32_t result = 0;
    uint32_t limit = RAND_MAX - (RAND_MAX % range);
    while((result = rand()) >= limit);
    return result % range;

}

uint32_t generate_big_random (uint32_t range) {

    uint32_t rand_max_32b = ~0;
    uint32_t limit = rand_max_32b - (rand_max_32b % range);

    while (true) {

        uint32_t low = generate_small_random(RAND_MAX);
        uint32_t high = generate_small_random(RAND_MAX);
        uint32_t result = (high << 15) | low;

        if (result < limit)
            return result % range;
    }
}

uint32_t generate_random_in_range(uint32_t range) {
    return range <= RAND_MAX ?
           generate_small_random(range) :
           generate_big_random(range);
}


uint32_t generate_random(uint32_t min, uint32_t max ) {
    return generate_random_in_range (max - min + 1) + min;
}

int32_t generate_random_signed(int32_t min, int32_t max) {
    return ((int32_t) generate_random_in_range( (uint32_t) (max - min + 1) )) + min;
}

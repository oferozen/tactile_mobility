#ifndef SRC_RANDOM_H_
#define SRC_RANDOM_H_

#include <stdint.h>

uint32_t generate_random_in_range(uint32_t range);
uint32_t generate_random(uint32_t min, uint32_t max );
int32_t generate_random_signed(int32_t min, int32_t max);

#endif /* SRC_RANDOM_H_ */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <stdint.h>
#include <time.h>

typedef clock_t timer_t;

#define CONVERT_TIMER_2_100US(x) (((x) * 1000 * 10) / (CLOCKS_PER_SEC))
#define CONVERT_100US_2_TIMER(x) (CLOCKS_PER_SEC / CONVERT_TIMER_2_100US(x))
#define CONVERT_SECONDS_2_100US(x) ((x) * 1000 * 10)
#define CONVERT_100US_2_MS(x) ((x) * 10)

timer_t timer_create();
timer_t timer_diff(timer_t timer);

void wait(uint32_t units_100us);
#endif /* SRC_TIMER_H_ */

#include <time.h>
#include <stdio.h>

#include "timer.h"
#include "utils/memory.h"

struct _timer_t {
    clock_t clk;
};

timer_t get_time() {
    ALLOCATE_AND_ASSIGN(timer_t, timer);

    return timer;
}

#include <time.h>
#include <stdio.h>

#include "timer.h"
#include "utils/memory.h"

struct _timer_t {
    clock_t clk;
};

timer_t timer_create() {
    ALLOCATE_AND_ASSIGN(timer_t, timer);
    timer->clk = clock();
    return timer;
}

void timer_destroy (timer_t timer) {
    DEALLOCATE(timer);
}

void timer_update(timer_t timer){
    timer->clk = clock();
}

int timer_s_diff(timer_t timer){
    return (clock() - timer->clk) / CLOCKS_PER_SEC;
}

int timer_ms_diff(timer_t timer){
    return (clock() - timer->clk) / (CLOCKS_PER_SEC * 1000);
}

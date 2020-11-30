#include "../timer.h"
#include "tests.h"
#include <stdint.h>
#include <stdio.h>

bool test_timer(){

    timer_t timer = timer_create();

    timer = timer_create();

    int i = 1;
    timer_t timestamp;
    while (i <= 20) {
        printf("\nstart");
        while((timestamp = timer_diff(timer)) < CONVERT_TIMER_2_100US(i));
        printf("\ntime_stamp: %lu", timestamp);
        i++;
    }

    return true;
}


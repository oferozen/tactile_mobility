#include <time.h>
#include <stdio.h>
#include "timer.h"
#include "../../utils/memory.h"


timer_t timer_create() {
    return clock();
}

timer_t timer_diff(timer_t timer) {
    return clock() - timer;
}

#ifdef _WIN32
#include <windows.h>
void wait(uint32_t units_100us){
    Sleep (units_100us / 10 );
}

#elif __unix
#define _POSIX_C_SOURCE 199309L // or greater
void wait(uint32_t units_100us){
        uint32_t units_ms = units_100us / 100;
        struct timespec ts;
        ts.tv_sec = units_ms/1000;
        ts.tv_nsec = units_ms%1000*1000;
        nanosleep(&ts, NULL);
}
#else
#   error "Unknown system"
#endif



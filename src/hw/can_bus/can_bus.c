#include "can_bus.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

static const char* __file = "can_bus.txt";
static FILE *__fp;
static bool __init = false;

void print(const char * string, ...){

    if (!__init){
        __init = true;
        __fp = fopen(__file, "w+");
    }

    va_list arg;
    va_start (arg, string);
    vfprintf(__fp, string, arg);
    va_end (arg);
}

void can_bus_transmit(timer_t timestamp, uint32_t id, uint8_t* payload, uint32_t payload_size) {
    static int i = 0;
    i++;
    print("\n %u %u ", id, timestamp);
    for(int index = payload_size - 1; index >= 0; index --){
        print("%02x ", payload[index]);
    }
}


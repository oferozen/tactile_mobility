#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

#define PRINT_ERROR(msg) logError(msg, __FILE__, __LINE__)

static const char* __file = "monitor.txt";
static FILE *__fp;
static bool __init = false;

void monitor_print(const char * string, ...){

    if (!__init){
        __init = true;
        __fp = fopen(__file, "w+");
    }

    va_list arg;
    va_start (arg, string);
    vfprintf(__fp, string, arg);
    va_end (arg);
}

void monitor_print_error (const char* msg, const char* file, int line){
    monitor_print("ERROR: (%s:%d): %s\n", file, line, msg);
    fflush(stdout);
}

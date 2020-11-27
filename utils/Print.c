#include <stdarg.h>
#include <stdio.h>

#define PRINT_ERROR(msg) logError(msg, __FILE__, __LINE__)

void print(const char * string, ...){
    va_list args;
    va_start(args, string);
    vprintf(string, args);
    va_end(args);
}

void print_noskip(const char * string, ...){

}

void logError(const char* msg, const char* file, int line){
    print("ERROR: (%s:%d): %s", file, line, msg);
}

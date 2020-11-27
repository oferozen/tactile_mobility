#ifndef SRC_UTILS_PRINT_H_
#define SRC_UTILS_PRINT_H_

#include <stdarg.h>
#include <stdio.h>

#define PRINT_ERROR(msg) logError(msg, __FILE__, __LINE__)

inline void print(const char * string, ...){
    va_list args;
    va_start(args, string);
    vprintf(string, args);
    va_end(args);
}

inline void print_noskip(const char * string, ...){

}


inline void logError(const char* msg, const char* file, int line){
    print("ERROR: (%s:%d): %s", file, line, msg);
}
#endif /* SRC_UTILS_PRINT_H_ */

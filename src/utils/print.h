#ifndef SRC_UTILS_PRINT_H_
#define SRC_UTILS_PRINT_H_

#include <stdarg.h>
#include <stdio.h>

#define ASSERT(condition) \
    if (!(condition)) print_error(#condition, __FILE__, __LINE__)

#define PRINT_ERROR(msg) print_error(msg, __FILE__, __LINE__)

void print(const char * string, ...);
void print_noskip(const char * string, ...);
void print_error(const char* msg, const char* file, int line);

#endif /* SRC_UTILS_PRINT_H_ */


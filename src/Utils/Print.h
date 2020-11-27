#ifndef SRC_UTILS_PRINT_H_
#define SRC_UTILS_PRINT_H_

#include <stdarg.h>
#include <stdio.h>

#define PRINT_ERROR(msg) logError(msg, __FILE__, __LINE__)

void print(const char * string, ...);
void print_noskip(const char * string, ...);
void logError(const char* msg, const char* file, int line);

#endif /* SRC_UTILS_PRINT_H_ */

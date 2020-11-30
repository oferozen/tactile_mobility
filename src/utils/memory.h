#ifndef SRC_UTILS_MEMORY_H_
#define SRC_UTILS_MEMORY_H_

#include <stdlib.h>
#include "../hw/monitor/monitor.h"

#if DEBUG
#define ALLOCATE(size) allocate(size, __FILE__, __LINE__)
#else
#define ALLOCATE(size) allocate(size)
#endif

#define ALLOCATE_AND_ASSIGN(type,name) type name = (type) ALLOCATE(sizeof(*name))

#define DEALLOCATE(p) deallocate(p)

#ifdef DEBUG
void* allocate(size_t _Size, const char* file, int line );
#else
void* allocate(size_t _Size);
#endif

void deallocate(void* p);



#endif /* SRC_UTILS_MEMORY_H_ */

#include <stdlib.h>
#include "memory.h"
#include "../hw/monitor/monitor.h"


#if DEBUG
#define ALLOCATE(size) allocate(size, __FILE__, __LINE__)
#else
#define ALLOCATE(size) allocate(size)
#endif

#define ALLOCATE_AND_ASSIGN(type,name) type name = (type) ALLOCATE(sizeof(*name))

#ifdef DEBUG
void* allocate(size_t _Size, const char* file, int line ) {
    void* result;
    if (!(result = malloc(_Size))) {
        PRINT_ERROR("malloc error", file, line);
        return NULL;
    }
    return malloc(_Size);
}
#else
void* allocate(size_t _Size) {
    return malloc(_Size);
}
#endif

void deallocate(void* p){
    free(p);
}

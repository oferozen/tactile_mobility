#ifndef CONTAINERS_CONTAINER_H_
#define CONTAINERS_CONTAINER_H_

#include <stdbool.h>

typedef void* element_t;
typedef void* meta_t;

typedef int (*compare_fun_t) (element_t element1, element_t element2, meta_t meta);
typedef void (*action_fun_t) (element_t element, meta_t meta, bool* stop);

#endif /* CONTAINERS_CONTAINER_H_ */


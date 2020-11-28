/*
 * Container.h
 *
 *  Created on: Nov 27, 2020
 *      Author: oferozen
 */

#ifndef CONTAINERS_CONTAINER_H_
#define CONTAINERS_CONTAINER_H_

#include <stdbool.h>

typedef void* element_t;

typedef int (*element_compare_method_t) (element_t element1, element_t element2);
typedef void (*element_action_method_t) (element_t element, void* meta, bool* stop);

#endif /* CONTAINERS_CONTAINER_H_ */


/*
 * MinHeap.h
 *
 *  Created on: Nov 27, 2020
 *      Author: oferozen
 */

#ifndef SRC_CONTAINERS_MINHEAP_H_
#define SRC_CONTAINERS_MINHEAP_H_

#include "container.h"

typedef struct _min_heap_t* min_heap_t;

min_heap_t min_heap_create (element_compare_method_t e);
void min_heap_insert (min_heap_t, element_t);
element_t min_heap_peek(min_heap_t);
element_t min_heap_pop(min_heap_t);
void min_heap_action(min_heap_t min_heap, element_action_method_t action, void* meta);

#endif /* SRC_CONTAINERS_MINHEAP_H_ */

/*
 * List.h
 *
 *  Created on: Nov 27, 2020
 *      Author: oferozen
 */

#ifndef CONTAINERS_LIST_H_
#define CONTAINERS_LIST_H_

#include <stdlib.h>
#include "container.h"

typedef struct _list_t* list_t;

list_t list_create();
void list_append(list_t, element_t);
element_t list_first(list_t);
element_t list_next(list_t);
element_t list_pop(list_t);
size_t list_size(list_t);

#endif /* CONTAINERS_LIST_H_ */


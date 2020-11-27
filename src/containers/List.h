/*
 * List.h
 *
 *  Created on: Nov 27, 2020
 *      Author: oferozen
 */

#ifndef CONTAINERS_LIST_H_
#define CONTAINERS_LIST_H_

#include "Container.h"

typedef struct _list_t* list_t;

list_t list_create();
void list_append(list_t, element_t);
element_t list_first(list_t);
element_t list_next(list_t);

#endif /* CONTAINERS_LIST_H_ */


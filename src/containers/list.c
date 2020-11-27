#include <stddef.h>
#include "List.h"
#include "../Utils/Memory.h"

typedef struct _node_t {
    element_t element;
    struct _node_t* next;
}* node_t;

struct _list_t {
    node_t head;
    node_t iterator;
};

list_t list_create() {

    //ALLOCATE_AND_ASSIGN(list_t, list);
    list_t  list = (list_t) allocate(sizeof(*list));
    list->head = NULL;
    list->iterator = NULL;
    return list;

}

void list_append(list_t list, element_t element) {

    ALLOCATE_AND_ASSIGN(node_t, new_node);
    new_node->next = NULL;
    new_node->element = element;

    node_t node = NULL;
    for (node = list->head ; node->next != NULL ; node = node->next);

    node->next = new_node;

}

element_t list_first(list_t list) {

    list->iterator = list->head->next;
    return list->iterator->element;

}

element_t list_next(list_t list){

    if (!list->iterator->next) return NULL;
    list->iterator = list->iterator->next;
    return list->iterator->element;

}

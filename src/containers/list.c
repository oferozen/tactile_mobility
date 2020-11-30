#include <stddef.h>
#include "list.h"
#include "../utils/memory.h"

typedef struct _node_t {
    element_t element;
    struct _node_t* next;
    struct _node_t* prev;
}* node_t;

struct _list_t {
    node_t head;
    node_t tail;
    node_t iterator;
    size_t size;
};

node_t node_create(node_t next, node_t prev, element_t element ) {
    ALLOCATE_AND_ASSIGN(node_t, node);
    node->next = next;
    node->prev = prev;
    node->element = element;
    return node;
}

list_t list_create() {

    ALLOCATE_AND_ASSIGN(list_t, list);
    list->head = node_create(list->tail, NULL, NULL);
    list->tail = node_create(NULL, list->head, NULL);
    list->iterator = NULL;
    list->size = 0;
    return list;

}

void list_append(list_t list, element_t element) {

    node_t node = node_create(list->tail, list->tail->prev, element);
    list->tail->prev->next = node;
    list->tail->prev = node;
    list->size++;

}

element_t list_first(list_t list) {

    if (list->size == 0) return NULL;
    list->iterator = list->head->next;
    return list->iterator->element;

}

element_t list_next(list_t list){

    if (!list->iterator->next) return NULL;
    list->iterator = list->iterator->next;
    return list->iterator->element;

}

void node_remove (node_t node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    DEALLOCATE(node);
}

element_t list_pop(list_t list) {

    if (!list->size) return NULL;

    element_t result = list->head->next->element;
    node_remove(list->head->next);
    list->size--;
    return result;
}

size_t list_size(list_t list) {
    return list->size;
}


void list_cycle_first(list_t list){

    if (list->size <= 1) return;

    node_t node = list->head->next;

    list->head->next = node->next;
    node->next->prev = list->head;

    list->tail->prev->next = node;
    list->tail->prev = node;

}

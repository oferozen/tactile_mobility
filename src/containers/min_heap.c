#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "min_heap.h"
#include "../utils/memory.h"
#include "../utils/macros.h"

#define INIT_HEAP_SIZE 4

struct _min_heap_t {
    size_t count;
    size_t size;
    element_t* elements;
    compare_fun_t compare;
};

min_heap_t min_heap_create (compare_fun_t compare) {
    ALLOCATE_AND_ASSIGN(min_heap_t, min_heap);
    min_heap->count = 0;
    min_heap->compare = compare;
    min_heap->elements = ALLOCATE(sizeof(element_t) * INIT_HEAP_SIZE);
    min_heap->size = INIT_HEAP_SIZE;
    return min_heap;
}

bool indexValid (min_heap_t minHeap, size_t index) { return index < minHeap->count; }
size_t left(size_t index) { return ((index * 2) + 1); }
size_t right(size_t index) { return ((index * 2) + 2); }
size_t parent(size_t index) { return ((index - 1) / 2); }



void sift_down ( min_heap_t minHeap ) {
    element_t* elements = minHeap->elements;
    size_t i = 0;

    while (true){

        bool swap_left = indexValid(minHeap, left(i)) &&
                         minHeap->compare(elements[i], elements[left(i)]) < 0;
        bool swap_right = indexValid(minHeap, right(i)) &&
                          minHeap->compare(elements[i], elements[right(i)]) < 0;

        if (swap_right && swap_left){
            swap_right = minHeap->compare(elements[left(i)], elements[right(i)]) < 0;
            swap_left = !swap_right;
        }

        if (swap_left) {
            SWAP(elements[i], elements[left(i)], element_t);
            i = left(i);

        } else if (swap_right) {
            SWAP(elements[i], elements[right(i)], element_t);
            i = right(i);

        } else {
            return;
        }
    }
}

void sift_up (min_heap_t min_heap) {

    element_t* elements = min_heap->elements;
    size_t index = min_heap->count - 1;
    while (index != 0 &&
          (min_heap->compare(elements[index], elements[parent(index)]) > 0)) {

        SWAP(elements[parent(index)], elements[index], element_t);
        index = parent(index);
    }
}

void min_heap_insert (min_heap_t min_heap, element_t element){

    if (min_heap->count == min_heap->size) {

        size_t new_size = min_heap->size * 2; // TODO: Check for overflow
        element_t* new_array = ALLOCATE(sizeof(element_t) * new_size);

        // memmove could prove useful when overriding the memory management
        memmove(new_array, min_heap->elements, sizeof(element_t) * min_heap->count);

        DEALLOCATE(min_heap->elements);
        min_heap->elements = new_array;
        min_heap->size = new_size;
    }

    min_heap->elements[min_heap->count] = element;
    min_heap->count++;
    sift_up(min_heap);

}

element_t min_heap_peek(min_heap_t min_heap) {
    return min_heap->count ? min_heap->elements[0] : NULL;
}

element_t min_heap_pop(min_heap_t min_heap){

    if (min_heap->count == 0) return NULL;

    element_t result = min_heap->elements[0];
    min_heap->elements[0] = min_heap->elements[min_heap->count - 1];
    min_heap->count--;
    sift_down(min_heap);

    return result;
}


void min_heap_action(min_heap_t min_heap, action_fun_t action, void* meta){
    bool stop = false;
    for (size_t index = 0; index < min_heap->count; index++){
        action(min_heap->elements[index], meta, &stop);
        if (stop) break;
    }
}

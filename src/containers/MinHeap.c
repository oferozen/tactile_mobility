#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "MinHeap.h"
#include "../Utils/Memory.h"
#include "../Utils/Macros.h"

#define INIT_HEAP_SIZE 4

struct _min_heap_t {
    size_t count;
    size_t size;
    element_t* elements;
    element_compare_method_t elementCompare;
};

min_heap_t min_heap_create (element_compare_method_t elementCompare) {
    ALLOCATE_AND_ASSIGN(min_heap_t, min_heap);
    min_heap->count = 0;
    min_heap->elementCompare = elementCompare;
    min_heap->elements = ALLOCATE(sizeof(element_t) * INIT_HEAP_SIZE);
    min_heap->size = INIT_HEAP_SIZE;
    return min_heap;
}

bool indexValid (min_heap_t minHeap, size_t index) { return index < minHeap->count -1; }
size_t left(size_t index) { return ((index * 2) + 1); }
size_t right(size_t index) { return ((index * 2) + 1); }
size_t parent(size_t index) { return ((index - 1) / 2); }

void siftDown ( min_heap_t minHeap ) {
    element_t* elements = minHeap->elements;
    size_t index = 0;
    while (true){

        bool is_left_smaller = indexValid(minHeap, left(index)) &&
                               minHeap->elementCompare(elements[index], elements[left(index)]) > 0;
        bool is_right_smaller = indexValid(minHeap, right(index)) &&
                                minHeap->elementCompare(elements[index], elements[right(index)]) > 0;

        if (is_left_smaller) {
            SWAP(elements[index], elements[left(index)], element_t);
            index = left(index);

        } else if (is_right_smaller) {
            SWAP(elements[index], elements[right(index)], element_t);
            index = right(index);

        } else {
            return;
        }
    }
}

void siftUp (min_heap_t min_heap) {

    element_t* elements = min_heap->elements;
    size_t index = min_heap->count;

    while (index &&
           min_heap->elementCompare(elements[parent(index)], elements[index]) < 0) {

        SWAP(elements[parent(index)], elements[index], element_t);
        index = parent(index);
    }
}

void min_heap_insert (min_heap_t min_heap, element_t element){

    if (min_heap->count == min_heap->size) {

        size_t new_size = min_heap->size * 2; // TODO: Check for overflow
        element_t* new_element_array = ALLOCATE(sizeof(element_t) * new_size);

        // memmove could prove useful when overriding the memory management
        memmove(new_element_array, min_heap->elements, min_heap->count);

        DEALLOCATE(min_heap->elements);
        min_heap->elements = new_element_array;
        min_heap->size = new_size;
    }

    min_heap->elements[min_heap->count] = element;
    min_heap->count++;

}

element_t min_heap_peek(min_heap_t);
element_t min_heap_pop(min_heap_t);

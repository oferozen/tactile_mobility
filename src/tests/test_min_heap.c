#include "tests.h"
#include "../utils/memory.h"
#include "../containers/min_heap.h"
#include "../utils/print.h"

typedef struct _int_t {
    int data;
}* int_t;

int_t int_create(int val) {
   ALLOCATE_AND_ASSIGN(int_t, result);
   result->data = val;
   return result;
}

int int_compare(element_t element1, element_t element2 ){
    int_t int1 = (int_t) element1;
    int_t int2 = (int_t) element2;
    return int2->data - int1->data;
}

static int idx = -1;

void print_int (element_t element, void* meta, bool* stop) {
    idx += 1;
    int value = ((int_t) element)->data;
    printf("%d_%d ", idx, value);
    fflush(stdout);
}

void print_heap (min_heap_t mh) {
    print("\n");
    min_heap_action(mh, print_int, NULL);
    print("\n");
}

bool test_min_heap() {

    bool result = true;
    min_heap_t mh = min_heap_create(int_compare);
    min_heap_insert(mh, int_create(50));
    print_heap(mh);
    min_heap_insert(mh, int_create(40));
    print_heap(mh);
    min_heap_insert(mh, int_create(60));
    print_heap(mh);
    min_heap_insert(mh, int_create(100));
    print_heap(mh);
    min_heap_insert(mh, int_create(3));
    print_heap(mh);
    min_heap_insert(mh, int_create(17));
    print_heap(mh);


    ASSERT(((int_t) min_heap_peek(mh))->data == 2);
    ASSERT(((int_t) min_heap_pop(mh))->data == 3);

    printf("\nvalue = %d", ((int_t) min_heap_peek(mh))->data );
    ASSERT(((int_t) min_heap_peek(mh))->data == 17);
    ASSERT(((int_t) min_heap_pop(mh))->data == 17);



    return true;

    return result;


}
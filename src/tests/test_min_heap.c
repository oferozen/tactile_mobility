#include "tests.h"
#include "../utils/memory.h"
#include "../containers/min_heap.h"
#include "../hw/monitor/monitor.h"

typedef struct _int_t {
    int data;
}* int_t;

int_t int_create(int val) {
   ALLOCATE_AND_ASSIGN(int_t, result);
   result->data = val;
   return result;
}

int int_compare(element_t element1, element_t element2, meta_t meta ){
    int_t int1 = (int_t) element1;
    int_t int2 = (int_t) element2;
    return int2->data - int1->data;
}

static int idx = -1;

void print_int (element_t element, meta_t meta, bool* stop) {
    idx += 1;
    int value = ((int_t) element)->data;
    printf("%d_%d ", idx, value);
    fflush(stdout);
}

void print_int_min_heap (min_heap_t mh) {
    monitor_print("\n");
    min_heap_action(mh, print_int, NULL);
    monitor_print("\n");
}

bool test_min_heap() {

    bool result = true;
    min_heap_t mh = min_heap_create(int_compare);
    min_heap_insert(mh, int_create(50));
    print_int_min_heap(mh);
    min_heap_insert(mh, int_create(40));
    print_int_min_heap(mh);
    min_heap_insert(mh, int_create(60));
    print_int_min_heap(mh);
    min_heap_insert(mh, int_create(100));
    print_int_min_heap(mh);
    min_heap_insert(mh, int_create(3));
    print_int_min_heap(mh);
    min_heap_insert(mh, int_create(17));

    ASSERT(((int_t) min_heap_peek(mh))->data == 3);
    ASSERT(result &= (((int_t) min_heap_pop(mh))->data == 3));

    ASSERT(((int_t) min_heap_peek(mh))->data == 17);
    ASSERT(result &= (((int_t) min_heap_pop(mh))->data == 17));

    min_heap_insert(mh, int_create(6));
    min_heap_insert(mh, int_create(16));
    min_heap_insert(mh, int_create(18));
    min_heap_insert(mh, int_create(-1));
    print_int_min_heap(mh);

    ASSERT(result &= (((int_t) min_heap_pop(mh))->data == -1));
    ASSERT(result &= (((int_t) min_heap_pop(mh))->data == 6));
    ASSERT(result &= (((int_t) min_heap_pop(mh))->data == 16));

    ASSERT(result);

    return result;
}

#include "tests.h"
#include <stdbool.h>
#include "../containers/list.h"
#include "../utils/memory.h"

typedef struct _int_t {
    int data;
}* int_t;

static int_t int_create(int val) {
   ALLOCATE_AND_ASSIGN(int_t, result);
   result->data = val;
   return result;
}

bool test_list () {

    list_t list = list_create();

    list_append(list, int_create(1));
    list_append(list, int_create(2));
    list_append(list, int_create(3));
    list_append(list, int_create(4));
    list_append(list, int_create(5));
    list_append(list, int_create(6));


    printf("\n");
    for (int_t i = (int_t) list_first(list);
         i ;
         i = (int_t) list_next(list)){

        printf("%d -> ", i->data);
    }

    list_pop(list);
    list_pop(list);
    list_append(list, int_create(5));
    list_append(list, int_create(6));

    printf("\n");
    for (int_t i = (int_t) list_first(list);
         i ;
         i = (int_t) list_next(list)){

        printf("%d -> ", i->data);
    }
    list_pop(list);
    list_pop(list);
    list_pop(list);
    list_pop(list);
    list_pop(list);
    list_pop(list);

    list_append(list, int_create(1));
    list_append(list, int_create(2));
    list_append(list, int_create(3));
    list_append(list, int_create(4));
    list_append(list, int_create(5));
    list_append(list, int_create(6));

    printf("\n");
    for (int_t i = (int_t) list_first(list);
         i ;
         i = (int_t) list_next(list)){

        printf("%d -> ", i->data);
    }

    list_pop(list);
    list_pop(list);
    list_pop(list);
    list_pop(list);
    list_pop(list);
    list_pop(list);

    list_append(list, int_create(1));
    list_append(list, int_create(2));
    list_append(list, int_create(3));
    list_append(list, int_create(4));
    list_append(list, int_create(5));
    list_append(list, int_create(6));

    printf("\n");
    for (int_t i = (int_t) list_first(list);
         i ;
         i = (int_t) list_next(list)){

        printf("%d -> ", i->data);
    }
    return true;
}

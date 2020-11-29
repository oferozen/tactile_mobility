#include <stdio.h>
#include <stdlib.h>
#include "containers/List.h"
#include "tests/tests.h"

int main(void) {
    bool failed = false;
    //failed &= test_min_heap();
    //failed &= test_bits();
    //failed &= test_random();
    failed &= test_message();
    printf("\n====\nDone");
	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "tests/tests.h"
#include "controller/controller.h"
#include "hw/timer/timer.h"
#include "config.h"
#include "utils/random.h"

int main(void) {

#if 0
    bool failed = false;
    failed &= test_min_heap();
    failed &= test_bits();
    failed &= test_random();
    failed &= test_message();
    failed &= test_timer();
    failed &= test_list();
    if (failed) print_error("\nfailed tests");
    return 0;
#endif

    cofig_init();
    random_init();

    dbc_reader_t dbc_reader = dbc_reader_create("path");
    controller_t controller = controller_create(dbc_reader);

    controller_run(controller, CONVERT_SECONDS_2_100US(10));
    controller_print_jitter(controller);

    printf("\n====\nDone");
	return EXIT_SUCCESS;
}

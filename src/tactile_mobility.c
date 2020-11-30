#include <stdio.h>
#include <stdlib.h>
#include "tests/tests.h"
#include "transmitter.h"
#include "timer.h"
#include "config.h"
#include "random.h"

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
    transmitter_t transmitter = transmitter_create(dbc_reader);

    transmitter_run(transmitter, CONVERT_SECONDS_2_100US(10));
    transmitter_print_jitter(transmitter);

    printf("\n====\nDone");
	return EXIT_SUCCESS;
}

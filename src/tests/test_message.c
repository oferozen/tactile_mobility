#include "stdbool.h"
#include "../dbc/message.h"
#include "../hw/monitor/monitor.h"
#include "tests.h"


bool test_message(){

    bool passed = true;

    int x = 0;
    BIT_SET(x,0xFFF,0,0);

    uint32_t val1 = 0x5555;
    uint32_t val2 = 0x1111;
    uint32_t val3 = 0xFFFF;

    signal_t signal1 = signal_create("sig1", 15, 15, big_endian, false);
    signal_t signal2 = signal_create("sig2", 30, 15, big_endian, false);
    signal_t signal3 = signal_create("sig3", 45 ,15, big_endian, false);

    signal_set_unsigned_limits(signal1, val1, val1);
    signal_set_unsigned_limits(signal2, val2, val2);
    signal_set_unsigned_limits(signal3, val3, val3);

    message_t message = message_create("msg1", "ofer", 123, 8, 100);
    message_add_signal(message, signal1);
    message_add_signal(message, signal2);
    message_add_signal(message, signal3);

    uint64_t data = 0;


    message_generate_payload(message, 1);
    message_generate_payload(message, 1);
    message_generate_payload(message, 1);
    message_generate_payload(message, 1);

    data = * (uint64_t*) message_pop_payload(message);
    ASSERT(passed = (BIT_GET(data, 64 - 45 - 15 , 15) == (val3 &( ( 1 << 15 ) -1))));
    ASSERT(passed = (BIT_GET(data, 64 - 30 - 15 , 15) == (val2 &( ( 1 << 15 ) -1)) ));
    ASSERT(passed = (BIT_GET(data, 64 - 15 - 15, 15) == (val1 &( ( 1 << 15 ) -1))));

    data = * (uint64_t*) message_pop_payload(message);
    ASSERT(passed = (message_pop_payload(message) == NULL));

    return passed;
}

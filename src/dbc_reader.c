#include "dbc_reader.h"
#include "containers/list.h"
#include "utils/memory.h"

struct _dbc_reader_t {
    list_t messages;
    bool init;
};

void dbc_reader_create_messages() {

    message_t message = message_create("WHEEL_SPEEDS", "VSA", 464, 8);

    signal_t signal1 = signal_create("sig1", 15, 15, big_endian, false);
    signal_t signal2 = signal_create("sig2", 30, 15, big_endian, false);
    signal_t signal3 = signal_create("sig3", 45 ,15, big_endian, false);
/*
    signal_set_unsigned_limits(signal1, val1, val1);
    signal_set_unsigned_limits(signal2, val2, val2);
    signal_set_unsigned_limits(signal3, val3, val3);

    message_add_signal(message, signal1);
    message_add_signal(message, signal2);
    */

}

dbc_reader_t dbc_reader_create(const char* path){
    ALLOCATE_AND_ASSIGN(dbc_reader_t, dbc_reader);
    dbc_reader->init = false;
    dbc_reader->messages = list_create();
    return dbc_reader;
}

message_t dbc_reader_get_message(dbc_reader_t dbc_reader){

    if (!dbc_reader->init){
        dbc_reader->init = true;
        return list_first(dbc_reader->messages);

    } else {
        return list_next(dbc_reader->messages);
    }
}

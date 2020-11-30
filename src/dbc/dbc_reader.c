#include "dbc_reader.h"
#include "../containers/list.h"
#include "../utils/memory.h"

struct _dbc_reader_t {
    list_t messages;
    bool init;
};

void dbc_reader_create_messages(dbc_reader_t dbc_reader) {

    signal_t signal = NULL;

    message_t message_wheels = message_create("WHEEL_SPEEDS", "VSA", 464, 8, 100);

    signal = signal_create("WHEEL_SPEED_FL", 0, 15, big_endian, e_unsigned);
    signal_set_unsigned_limits(signal, 0, 250);
    message_add_signal(message_wheels, signal);

    signal = signal_create("WHEEL_SPEED_FR", 15, 15, big_endian, e_unsigned);
    signal_set_unsigned_limits(signal, 0, 250);
    message_add_signal(message_wheels, signal);

    signal = signal_create("WHEEL_SPEED_RL", 30, 15, big_endian, e_unsigned);
    signal_set_signed_limits(signal, 0, 250);
    message_add_signal(message_wheels, signal);

    signal = signal_create("WHEEL_SPEED_RR", 45, 15, big_endian, e_unsigned);
    signal_set_signed_limits(signal, 0, 250);
    message_add_signal(message_wheels, signal);

    message_t message_break = message_create("BREAK_MODULE", "VSA", 446, 3, 10);
    signal = signal_create("BREAK_PRESSED", 4, 1, big_endian, e_unsigned);
    signal_set_signed_limits(signal, 0, 1);
    message_add_signal(message_break, signal);

    list_t messages = list_create();


    list_append(messages, message_wheels);
    list_append(messages, message_break);

    dbc_reader->messages = messages;

}

dbc_reader_t dbc_reader_create(const char* path){
    ALLOCATE_AND_ASSIGN(dbc_reader_t, dbc_reader);
    dbc_reader->init = false;
    dbc_reader->messages = list_create();
    dbc_reader_create_messages(dbc_reader);
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

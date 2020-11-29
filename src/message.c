#include <string.h>
#include "utils/memory.h"
#include "message.h"
#include "utils/macros.h"

message_t message_create (char* name, char* sender, size_t id, size_t length){
    ALLOCATE_AND_ASSIGN(message_t, message);
    message->name = strdup(name);
    message->sender = strdup(sender);
    message->id = id;
    message->length = length;
    message->signals = list_create();
    message->payloads = list_create();
    return message;
}

void message_add_signal (message_t message, signal_t signal) {
    list_append(message->signals, signal);
}

bool message_generate_payload (message_t message, size_t num) {

    num = MIN(num, MESSAGE_BUFFER_SIZE - list_size(message->payloads));
    if (num == 0) return false;

    char* message_payload = ALLOCATE(message->length);
    memset(message_payload, 0, message->length);

    for (signal_t signal = (signal_t) list_first(message->signals);
         signal ;
         signal = (signal_t) list_next(message->signals)){

        uint32_t signal_payload = signal_generate_data(signal);
        inject_field(message_payload, message->length, (char*)&signal_payload, signal->start_bit, signal->length);
    }

    list_append(message->payloads, message_payload);
    return true;
}

char* message_pop_payload(message_t message){
    return (char*) list_pop(message->payloads);
}

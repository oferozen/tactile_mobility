#include <string.h>
#include "utils/memory.h"
#include "message.h"
#include "utils/macros.h"
#include "config.h"
#include "timer.h"

message_t message_create (char* name, char* sender, size_t id, size_t length, float hz)
{
    ALLOCATE_AND_ASSIGN(message_t, message);
    message->name = strdup(name);
    message->sender = strdup(sender);
    message->id = id;
    message->length = length;
    message->signals = list_create();
    message->payloads = list_create();
    message->period = CONVERT_SECONDS_2_100US(1 / hz);
    message->buffer_size = cofig_get_message_buffer_size();
    message->next_xmit_100us = message->period;
    message->count = 0;
    message->jitter = 0;
    return message;
}

void message_add_signal (message_t message, signal_t signal) {
    list_append(message->signals, signal);
}

bool message_generate_payload (message_t message, size_t num) {

    num = MIN(num, message->buffer_size - list_size(message->payloads));
    if (num == 0) return false;

    while (num--) {

        payload_t message_payload = ALLOCATE(message->length);
        memset(message_payload, 0, message->length);

        for (signal_t signal = (signal_t) list_first(message->signals);
             signal ;
             signal = (signal_t) list_next(message->signals)){

            uint32_t signal_payload = signal_generate_data(signal);
            inject_field(message_payload, message->length, (uint8_t*)&signal_payload, signal->start_bit, signal->length);
        }

        list_append(message->payloads, message_payload);
    }
    return true;
}

char* message_pop_payload(message_t message){
    return (char*) list_pop(message->payloads);
}

bool message_is_buffer_empty(message_t message){
   return list_size(message->payloads) == 0;
}

bool message_is_buffer_full(message_t message){
   return list_size(message->payloads) == message->buffer_size;
}

void message_transmit_event(message_t message, uint32_t timestamp_100us){
    message->jitter += timestamp_100us - message->next_xmit_100us;
    message->count++;
    message->next_xmit_100us += message->period;
}

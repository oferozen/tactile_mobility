#ifndef SRC_MESSAGE_H_
#define SRC_MESSAGE_H_

#include <stdbool.h>
#include "../hw/timer/timer.h"
#include "../containers/list.h"
#include "signal.h"

typedef uint8_t* payload_t;

typedef struct _message_t {

    char* name;
    char* sender;
    size_t id;
    size_t length;
    list_t signals;

    // meta data
    list_t payloads;
    clock_t period;
    uint8_t buffer_size;
    uint32_t next_xmit_100us;
    uint32_t jitter;
    uint32_t count;

}* message_t;

message_t message_create (char* name, char* sender, size_t id, size_t length, float hz);
void message_add_signal (message_t message, signal_t signal);
bool message_generate_payload (message_t message, size_t num);
char* message_pop_payload(message_t message);
bool message_is_buffer_empty(message_t message);
void message_transmit_event(message_t message, uint32_t timestamp_100us);
bool message_is_buffer_full(message_t message);

#endif /* SRC_MESSAGE_H_ */

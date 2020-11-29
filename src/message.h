#ifndef SRC_MESSAGE_H_
#define SRC_MESSAGE_H_

#include <stdbool.h>
#include "containers/list.h"
#include "signal.h"

#define MESSAGE_BUFFER_SIZE 3

typedef struct _message_t {
    char* name;
    char* sender;
    size_t id;
    size_t length;
    list_t signals;
    list_t payloads;
}* message_t;

message_t message_create (char* name, char* sender, size_t id, size_t length);
void message_add_signal (message_t message, signal_t signal);
bool message_generate_payload (message_t message, size_t num);
char* message_pop_payload(message_t message);

#endif /* SRC_MESSAGE_H_ */

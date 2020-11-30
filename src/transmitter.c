#include "transmitter.h"
#include "timer.h"
#include "utils/memory.h"
#include "containers/min_heap.h"
#include "containers/list.h"
#include "config.h"

struct _transmitter_t {

    list_t pending_messages_with_empty_payloads; // long name, but accurate.
    min_heap_t messages_heap;
    dbc_reader_t dbc_reader;
    timer_t timer;
    clock_t run_100us;

};

int __message_time_compare (element_t element1, element_t element2, meta_t meta){

    message_t msg1 = (message_t) element1;
    message_t msg2 = (message_t) element2;

    return (msg2->next_xmit_100us - msg1->next_xmit_100us);
}

timer_t __current_time_100us(transmitter_t transmitter){
    return CONVERT_TIMER_2_100US(timer_diff(transmitter->timer));
}

bool __fill_message_buffers(transmitter_t transmitter) {

    message_t message = (message_t) list_first(transmitter->pending_messages_with_empty_payloads);
    if (!message) return false;

    // Only generate a single payload so we wouldn't miss an event.
    message_generate_payload(message, 1);
    if (message_is_buffer_full(message)) {
        list_pop(transmitter->pending_messages_with_empty_payloads);
    } else {
        list_cycle_first(transmitter->pending_messages_with_empty_payloads);
    }
    return true;
}

void __transmit(timer_t timestamp, uint32_t id, payload_t payload, uint32_t payload_size) {
    static int i = 0;
    i++;
    print("\n %u %u ", id, timestamp);
    for(int index = payload_size - 1; index >= 0; index --){
        print("%02x ", payload[index]);
    }
}

bool __run_ended (transmitter_t transmitter){
    return CONVERT_TIMER_2_100US(timer_diff(transmitter->timer)) >= transmitter->run_100us;
}

void __poll(transmitter_t transmitter){

    message_t message = min_heap_peek(transmitter->messages_heap);

    // no messages error
    if (!message) {
        PRINT_ERROR("poll error");
        return;
    }

    // wait for transit time
    timer_t timestamp;
    while ((timestamp = __current_time_100us(transmitter)) < message->next_xmit_100us);

    /*
     * Send all message that should be sent as soon as possible.
     * This way we are not wasting time going back to the external method.
     */
    while (true) {

        __transmit(timestamp, message->id, (payload_t) list_first(message->payloads), message->length);
        DEALLOCATE(list_pop(message->payloads));

        message_transmit_event(message, timestamp);

        // Notify that current message have an empty butter
        list_append(transmitter->pending_messages_with_empty_payloads, message);

        /*
         * Check current message should be send before the next time.
         * If so, don't remove it from the heap.
         */
        element_t next = min_heap_peek_second(transmitter->messages_heap);
        if (next && __message_time_compare(message, next, NULL) < 0){
            min_heap_pop(transmitter->messages_heap);
            min_heap_insert(transmitter->messages_heap, message);
        }

        /*
         * Don't leave before checking if there are other messages which should be sent
         */
        if (!(message = next) || __current_time_100us(transmitter) < message->next_xmit_100us){
            break;
        }

        /*
         * make sure you have a payload in the buffer
         */
        if (message_is_buffer_empty(message)){
            message_generate_payload(message, 1);
        }
    }
}

transmitter_t transmitter_create( dbc_reader_t dbc_reader){

    ALLOCATE_AND_ASSIGN(transmitter_t, transmitter);
    transmitter->dbc_reader = dbc_reader;
    transmitter->messages_heap = min_heap_create(__message_time_compare);
    transmitter->pending_messages_with_empty_payloads = list_create();
    transmitter->timer = timer_create();
    return transmitter;

}

void transmitter_run (transmitter_t transmitter, uint32_t run_time_100us){

    /*
     * Read the dbc file, add all messages to the heap, and fill each message's
     * payload buffers.
     */
    dbc_reader_t dbc_reader = transmitter->dbc_reader;
    for (message_t message = (message_t) dbc_reader_get_message(dbc_reader);
         message;
         message = (message_t) dbc_reader_get_message(dbc_reader)){

        message_generate_payload(message, cofig_get_message_buffer_size());
        min_heap_insert(transmitter->messages_heap, message);
    }

    // setup timer
    transmitter->run_100us = run_time_100us;
    transmitter->timer = timer_create();

    message_t next_message = min_heap_peek(transmitter->messages_heap);

    while (true){

        // Check for runtime
        if (__run_ended (transmitter)) {
            break;
        }

        // make sure the next message has at least 1 payload ready
        if (message_is_buffer_empty(next_message)){
            message_generate_payload(next_message, 1);
        }

        /*
         * if we are at (transmit_time - packet_tx_time) than stop filling buffer and poll
         */
        bool transmit = false;
        if (next_message->next_xmit_100us > __current_time_100us(transmitter) &&
           (next_message->next_xmit_100us - __current_time_100us(transmitter)) < cofig_get_packet_tx_time_ms()){

            transmit = true;
        }

        // check for transmit
        if (transmit || next_message->next_xmit_100us < __current_time_100us(transmitter)){

            __poll(transmitter);
            next_message = min_heap_peek(transmitter->messages_heap);
            continue;
        }

        // generate a signle message payload if needed.
        if (!__fill_message_buffers(transmitter)){

            uint32_t time_until_next_event = next_message->next_xmit_100us -
                                             __current_time_100us(transmitter);

            // Wake up a little before next event;
            wait(time_until_next_event - cofig_get_packet_tx_time_ms());
        }
    }
}

void transmitter_print_jitter (transmitter_t transmitter){
    message_t message = NULL;

    print("\n\n JITTER");
    while (true){
        message = (message_t) min_heap_pop(transmitter->messages_heap);
        if (!message) break;

        float jitter_average = 0xFFFFFFFF;
        if (message->count)
            jitter_average =  ((float) message->jitter) / ((float) message->count);
        print("\n%u %f", message->id, jitter_average);
    }
}

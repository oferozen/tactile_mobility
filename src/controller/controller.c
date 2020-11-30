#include "controller.h"
#include "../hw/timer/timer.h"
#include "../hw/can_bus/can_bus.h"
#include "../utils/memory.h"
#include "../containers/min_heap.h"
#include "../containers/list.h"
#include "../config.h"

struct _controller_t {

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

timer_t __current_time_100us(controller_t controller){
    return CONVERT_TIMER_2_100US(timer_diff(controller->timer));
}

bool __fill_message_buffers(controller_t controller) {

    message_t message = (message_t) list_first(controller->pending_messages_with_empty_payloads);
    if (!message) return false;

    // Only generate a single payload so we wouldn't miss an event.
    message_generate_payload(message, 1);
    if (message_is_buffer_full(message)) {
        list_pop(controller->pending_messages_with_empty_payloads);
    } else {
        list_cycle_first(controller->pending_messages_with_empty_payloads);
    }
    return true;
}

bool __run_ended (controller_t controller){
    return CONVERT_TIMER_2_100US(timer_diff(controller->timer)) >= controller->run_100us;
}

void __poll(controller_t controller){

    message_t message = min_heap_peek(controller->messages_heap);

    // no messages error
    if (!message) {
        PRINT_ERROR("poll error");
        return;
    }

    // wait for transit time
    timer_t timestamp;
    while ((timestamp = __current_time_100us(controller)) < message->next_xmit_100us);

    /*
     * Send all message that should be sent as soon as possible.
     * This way we are not wasting time going back to the external method.
     */
    while (true) {

        can_bus_transmit(timestamp,
                         message->id,
                         (payload_t) list_first(message->payloads),
                         message->length);

        DEALLOCATE(list_pop(message->payloads));

        message_transmit_event(message, timestamp);

        // Notify that current message have an empty butter
        list_append(controller->pending_messages_with_empty_payloads, message);

        /*
         * Check current message should be send before the next time.
         * If so, don't remove it from the heap.
         */
        element_t next = min_heap_peek_second(controller->messages_heap);
        if (next && __message_time_compare(message, next, NULL) < 0){
            min_heap_pop(controller->messages_heap);
            min_heap_insert(controller->messages_heap, message);
        }

        /*
         * Don't leave before checking if there are other messages which should be sent
         */
        if (!(message = next) || __current_time_100us(controller) < message->next_xmit_100us){
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

controller_t controller_create( dbc_reader_t dbc_reader){

    ALLOCATE_AND_ASSIGN(controller_t, controller);
    controller->dbc_reader = dbc_reader;
    controller->messages_heap = min_heap_create(__message_time_compare);
    controller->pending_messages_with_empty_payloads = list_create();
    controller->timer = timer_create();
    return controller;

}

void controller_run (controller_t controller, uint32_t run_time_100us){

    /*
     * Read the dbc file, add all messages to the heap, and fill each message's
     * payload buffers.
     */
    dbc_reader_t dbc_reader = controller->dbc_reader;
    for (message_t message = (message_t) dbc_reader_get_message(dbc_reader);
         message;
         message = (message_t) dbc_reader_get_message(dbc_reader)){

        message_generate_payload(message, cofig_get_message_buffer_size());
        min_heap_insert(controller->messages_heap, message);
    }

    // setup timer
    controller->run_100us = run_time_100us;
    controller->timer = timer_create();

    message_t next_message = min_heap_peek(controller->messages_heap);

    while (true){

        // Check for runtime
        if (__run_ended (controller)) {
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
        if (next_message->next_xmit_100us > __current_time_100us(controller) &&
           (next_message->next_xmit_100us - __current_time_100us(controller)) < cofig_get_packet_tx_time_ms()){

            transmit = true;
        }

        // check for transmit
        if (transmit || next_message->next_xmit_100us < __current_time_100us(controller)){

            __poll(controller);
            next_message = min_heap_peek(controller->messages_heap);
            continue;
        }

        // generate a signle message payload if needed.
        if (!__fill_message_buffers(controller)){

            uint32_t time_until_next_event = next_message->next_xmit_100us -
                                             __current_time_100us(controller);

            // Wake up a little before next event;
            wait(time_until_next_event - cofig_get_packet_tx_time_ms());
        }
    }
}

void controller_print_jitter (controller_t controller){
    message_t message = NULL;

    monitor_print("\n\n===========");
    while (true){
        message = (message_t) min_heap_pop(controller->messages_heap);
        if (!message) break;

        float jitter_average = 0xFFFFFFFF;
        if (message->count)
            jitter_average =  ((float) message->jitter) / ((float) message->count);
        monitor_print("\nMessage [%u], jitter [%f], count [%u]",
                      message->id,
                      jitter_average,
                      message->count);
    }
}

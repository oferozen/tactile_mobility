#include <stdint.h>
#include "config.h"

struct config_t{
    uint32_t packet_tx_delay;
    uint32_t message_buffer_size;
};

static struct config_t config;

void cofig_init(){
    config.packet_tx_delay = 200;
    config.message_buffer_size = 4;
}


uint32_t cofig_get_packet_tx_time_ms(){
    return config.packet_tx_delay;
}

uint32_t cofig_get_message_buffer_size(){
    return config.message_buffer_size;
}

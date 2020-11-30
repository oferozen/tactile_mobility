#ifndef SRC_HW_CAN_BUS_CAN_BUS_H_
#define SRC_HW_CAN_BUS_CAN_BUS_H_

#include <stdint.h>
#include "../timer/timer.h"

void can_bus_transmit(timer_t timestamp, uint32_t id, uint8_t* payload, uint32_t payload_size);


#endif /* SRC_HW_CAN_BUS_CAN_BUS_H_ */

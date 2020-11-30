#ifndef SRC_controller_H_
#define SRC_controller_H_

#include "../dbc/dbc_reader.h"

typedef struct _controller_t* controller_t;

controller_t controller_create( dbc_reader_t );
void controller_run (controller_t controller, uint32_t miliseconds);
void controller_print_jitter (controller_t controller);

#endif /* SRC_controller_H_ */

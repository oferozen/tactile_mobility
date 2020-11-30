#ifndef SRC_TRANSMITTER_H_
#define SRC_TRANSMITTER_H_

#include "dbc_reader.h"

typedef struct _transmitter_t* transmitter_t;

transmitter_t transmitter_create( dbc_reader_t );
void transmitter_run (transmitter_t transmitter, uint32_t miliseconds);
void transmitter_print_jitter (transmitter_t transmitter);

#endif /* SRC_TRANSMITTER_H_ */

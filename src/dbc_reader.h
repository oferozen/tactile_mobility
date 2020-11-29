#ifndef SRC_DBC_READER_H_
#define SRC_DBC_READER_H_

#include "message.h"

typedef struct _dbc_reader_t* dbc_reader_t;

dbc_reader_t dbc_reader_create(const char* path);
message_t dbc_reader_get_message(dbc_reader_t);

#endif /* SRC_DBC_READER_H_ */

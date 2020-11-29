#include "bits.h"

enum endian_t get_endiannes (){
    int canary = 1;
    return (((char *)&canary)[0]) ? big_endian : little_endian;
}

void change_endianness (char* bytes, size_t size) {
    for (size_t i = 0; i < (size / 2); i++) {
        SWAP(bytes[i], bytes[size - i - 1], char);
    }
}

void inject_field(uint8_t* data, size_t data_size, char* field, size_t start_bit, size_t length){

    //uint64_t* info = data;

    size_t end_byte = (start_bit + length + 1) / 8;
    size_t start_byte = start_bit / 8;
    size_t byte_size = end_byte - start_byte;
    uint8_t bits_in_last_data_byte = (start_bit + length +1) % 8;
    uint8_t bits_in_last_field_byte = (length + 1) % 8;

    uint8_t right_size = start_bit % 8;
    uint8_t left_size = 8 - right_size;

    uint8_t right_start_bit = 8 - right_size;
    uint8_t left_start_bit = 0;

    bool is_overflow = bits_in_last_field_byte < bits_in_last_data_byte;
    uint8_t last_right_size = is_overflow ? bits_in_last_data_byte : 0;
    uint8_t last_left_size = is_overflow ?  left_size : bits_in_last_field_byte;

    uint8_t last_right_start_bit =  is_overflow ? 8 - bits_in_last_data_byte : 0;
    uint8_t last_left_start_bit =  is_overflow ? 0 : 8 - (left_size + last_right_size);

    for (size_t index = 0 ; index <= byte_size - 1; index++) {

        size_t data_index = data_size - index - 1 - start_byte;
        size_t field_index = end_byte - start_byte + 1 - index;
        bool is_last_byte = index == byte_size - 1;

        uint8_t field_byte = field[field_index];

        if (is_last_byte) {
            left_size = last_left_size;
            right_size = last_right_size;
            right_start_bit = last_right_start_bit;
            left_start_bit = last_left_start_bit;
            field_byte >>= 8 - (last_left_size + last_right_size);
        }

        BIT_SET(data[data_index], field_byte >> right_size , left_start_bit, left_size);
        BIT_SET(data[data_index - 1], field_byte, right_start_bit , right_size);
    }
}

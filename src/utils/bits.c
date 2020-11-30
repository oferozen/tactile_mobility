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

void inject_field(uint8_t* data, size_t data_size, uint8_t* field, size_t start_bit, size_t length){

    //uint64_t* info = data;

    size_t end_bit = start_bit + length - 1;
    size_t data_start_byte = start_bit / 8;
    size_t field_byte_size = ((length - 1) / 8) + 1;
    uint8_t bits_in_last_field_byte = length % 8 == 0 ? 8 : length % 8;

    uint8_t right_size = 8 - (start_bit % 8);
    uint8_t left_size = 8 - right_size;

    uint8_t right_start_bit = 8 - right_size;
    uint8_t left_start_bit = 0;

    bool is_single_data_byte = ( end_bit / 8) == (start_bit / 8);

    bool is_overflow = bits_in_last_field_byte > right_size;
    uint8_t bits_in_last_data_byte = is_single_data_byte ? length : (start_bit + length) % 8;
    uint8_t last_right_size = is_overflow ? right_size : bits_in_last_field_byte;
    uint8_t last_left_size = is_overflow ? bits_in_last_data_byte : 0;


    for (size_t index = 0 ; index <= field_byte_size - 1; index++) {

        size_t data_index = index + data_start_byte;
        size_t field_index = index;
        bool is_last_byte = index == field_byte_size - 1;
        uint8_t field_byte = field[field_index];

        if (is_last_byte) {
            left_size = last_left_size;
            right_size = last_right_size;
        }

        BIT_SET(data[data_index], field_byte,                right_start_bit , right_size);
        BIT_SET(data[data_index+1],     field_byte >>= right_size, left_start_bit, left_size);
    }
    return;
}


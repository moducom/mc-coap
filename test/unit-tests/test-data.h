#pragma once

#include <stdint.h>

static uint8_t buffer_16bit_delta[] = {
        0x40, 0x00, 0x01, 0x23, // 4: fully blank header
        0xE1, // 5: option with 16-bit delta 1 length 1
        0x00, // 6: delta ext byte #1
        0x01, // 7: delta ext byte #2
        0x03, // 8: value single byte of data
        0x12, // 9: option with delta 1 length 2
        0x04, //10: value byte of data #1
        0x05, //11: value byte of data #2
        0xFF, //12: denotes a payload presence
        // payload itself
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16
};


static uint8_t buffer_plausible[] = {
        0x40, 0x00, 0x00, 0x00, // 4: fully blank header
        0xB4, // 5: option delta 11 (Uri-Path) with value length of 4
        'T',
        'E',
        'S',
        'T',
        0x03, // 9: option delta 0 (Uri-Path, again) with value length of 3
        'P', 'O', 'S',
        0xFF,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16
};


const static uint8_t buffer_payload_only[] =
{
    0x40, 0x00, 0x00, 0x00, // 4: fully blank header
    0xFF,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16
};


const static uint8_t buffer_oversimplified_observe[] =
{
    0x40, 0x00, 0x01, 0x23, // 4: fully blank header
    0x60    // the most minimal registration possible. a 0-length uint == 0.  clever
};

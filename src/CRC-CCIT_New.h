#pragma once
// CRC-CCIT Implementation based on work by Francesco Sacchi

#include <Arduino.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#define CRC_CCIT_INIT_VAL ((uint16_t)0xFFFF)
#define CRC_CCITT_CORRECT  0xF0B8

extern const uint16_t crc_ccit_table_new[256] PROGMEM;
//static inline uint16_t update_crc_ccit_new(uint8_t c, uint16_t prev_crc) __attribute__((always_inline));
//static inline bool verify_crc_ccitt_new(uint16_t crc) __attribute__((always_inline));

static inline uint16_t update_crc_ccit_new(uint8_t c, uint16_t prev_crc)
{
    return (prev_crc >> 8) ^ pgm_read_word(&crc_ccit_table_new[(prev_crc ^ c) & 0xff]);
}

static inline bool verify_crc_ccitt_new(uint16_t crc)
{
	return crc == CRC_CCITT_CORRECT;
}

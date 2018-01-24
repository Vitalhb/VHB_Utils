#pragma once

#include <arduino.h>

#define BIT_MASK 0xff
#define SHIFT_RIGHT 0 // 4
#define SCALE_VALUE		128
#define ZERO_VALUE		128

#include "TableGenerator.h"

#define SINE_LENGTH_128 128
#define SINE_LENGTH_512 512

class SineSamples
{
public:
	// phase goes from 0 to SineSize-1 
	static uint8_t GetSample128(uint8_t phase);
	static uint8_t GetSample512(uint16_t phase);

	static const uint8_t PROGMEM sine_table128[];
	static const uint8_t PROGMEM sine_table512[];
};


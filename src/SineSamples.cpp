#include "SineSamples.h"

uint8_t SineSamples::GetSample128(uint8_t phase)
{
	uint8_t newI = (uint8_t)(phase % (SINE_LENGTH_128 / 2));
	newI = (newI >= (SINE_LENGTH_128 / 4)) ? (SINE_LENGTH_128 / 2 - 1 - newI) : newI;
	uint8_t sine = pgm_read_byte(&sine_table128[newI]);
	return (phase >= (SINE_LENGTH_128 / 2)) ? ((255 >> SHIFT_RIGHT) - sine) : sine;
}

uint8_t SineSamples::GetSample512(uint16_t phase)
{
	uint8_t newI = (uint8_t)(phase % (SINE_LENGTH_512 / 2));
	newI = (newI >= (SINE_LENGTH_512 / 4)) ? (SINE_LENGTH_512 / 2 - 1 - newI) : newI;
	uint8_t sine = pgm_read_byte(&sine_table512[newI]);
	return (phase >= (SINE_LENGTH_512 / 2)) ? ((255 >> SHIFT_RIGHT) - sine) : sine;
}

const uint8_t PROGMEM SineSamples::sine_table128[] = INITIALIZE_SIN_TABLE(32);

const uint8_t PROGMEM SineSamples::sine_table512[] = INITIALIZE_SIN_TABLE(128);



#pragma once

#include <math.h>
#include <avr\pgmspace.h>

#define FUNC_TABLE2(func, i, n)		(func(i,n)), (func(i+1,n))											//	table with 2 elements
#define FUNC_TABLE4(func, i, n)		FUNC_TABLE2(func, i, n), FUNC_TABLE2(func, i+2,n)			//	table with 4 elements
#define FUNC_TABLE8(func, i, n)		FUNC_TABLE4(func, i, n), FUNC_TABLE4(func, i+4,n)			//	table with 8 elements
#define FUNC_TABLE16(func, i, n)		FUNC_TABLE8(func, i, n), FUNC_TABLE8(func, i+8,n)			//	table with 16 elements
#define FUNC_TABLE32(func, i, n)		FUNC_TABLE16(func, i, n), FUNC_TABLE16(func, i+16,n)		//	table with 32 elements
#define FUNC_TABLE64(func, i, n)		FUNC_TABLE32(func, i, n), FUNC_TABLE32(func, i+32,n)		//	table with 64 elements
#define FUNC_TABLE128(func, i, n)	FUNC_TABLE64(func, i, n), FUNC_TABLE64(func, i+64,n)		//	table with 128 elements
#define FUNC_TABLE256(func, i, n)	FUNC_TABLE128(func, i, n), FUNC_TABLE128(func, i+128,n)	//	table with 256 elements

#define BUILD_TABLE_IN_FLASH(tableName, func, n) const uint8_t PROGMEM table_##tableName_Flash##n[] = { FUNC_TABLE##n(func, 0, n) }
#define GET_VALUE_FROM_FLASH(tableName, i, n)	(pgm_read_byte_near(table_##tableName_Flash##n + i))

#define BUILD_TABLE_IN_RAM(tableName, func, n) const uint8_t table_##tableName_RAM##n[] = { FUNC_TABLE##n(func, 0, n) }
#define GET_VALUE_FROM_RAM(tableName, i, n)	(table_##tableName_RAM##n[i])
/*
#define FUNC_TABLE2(func, i)		(func(i)), (func(i+1))											//	table with 2 elements
#define FUNC_TABLE4(func, i)		FUNC_TABLE2(func, i), FUNC_TABLE2(func, i+2)			//	table with 4 elements
#define FUNC_TABLE8(func, i)		FUNC_TABLE4(func, i), FUNC_TABLE4(func, i+4)			//	table with 8 elements
#define FUNC_TABLE16(func, i)		FUNC_TABLE8(func, i), FUNC_TABLE8(func, i+8)			//	table with 16 elements
#define FUNC_TABLE32(func, i)		FUNC_TABLE16(func, i), FUNC_TABLE16(func, i+16)		//	table with 32 elements
#define FUNC_TABLE64(func, i)		FUNC_TABLE32(func, i), FUNC_TABLE32(func, i+32)		//	table with 64 elements
#define FUNC_TABLE128(func, i)	FUNC_TABLE64(func, i), FUNC_TABLE64(func, i+64)		//	table with 128 elements
#define FUNC_TABLE256(func, i)	FUNC_TABLE128(func, i), FUNC_TABLE128(func, i+128)	//	table with 256 elements

#define BUILD_TABLE_IN_FLASH(tableName, func, n) const uint8_t PROGMEM table_##tableName_Flash##n[] = { FUNC_TABLE##n(func, 0) }
#define GET_VALUE_FROM_FLASH(tableName, i, n)	(pgm_read_byte_near(table_##tableName_Flash##n + i))

#define BUILD_TABLE_IN_RAM(tableName, func, n) const uint8_t table_##tableName_RAM##n[] = { FUNC_TABLE##n(func, 0) }
#define GET_VALUE_FROM_RAM(tableName, i, n)	(table_##tableName_RAM##n[i])
*/

#ifndef BIT_MASK
#define BIT_MASK			0xff
#endif //BIT_MASK

#ifndef SHIFT_RIGHT
#define SHIFT_RIGHT		0
#endif //SHIFT_RIGHT

#ifndef SCALE_VALUE
#define SCALE_VALUE		128
#endif //SCALE_VALUE

#ifndef ZERO_VALUE
#define ZERO_VALUE		128
#endif //ZERO_VALUE

#define SCALE_FUNC(i, n)		(((ZERO_VALUE + SIN_FUNC(i, n)) & BIT_MASK) >> SHIFT_RIGHT)
#define SIN_FUNC(i, n)	((uint8_t)(double(SCALE_VALUE)*sin(double(i)*M_PI/(2.0*double(n)))))

#define INITIALIZE_SIN_TABLE(n)  { FUNC_TABLE##n(SCALE_FUNC, 0, n) }
#define BUILD_SIN_TABLE_IN_FLASH(n)	BUILD_TABLE_IN_FLASH(sine, SCALE_FUNC, n)
#define BUILD_SIN_TABLE_IN_RAM(n)	BUILD_TABLE_IN_RAM(sine, SCALE_FUNC, n)

#define GET_SIN_VALUE_FROM_FLASH(i, n)	GET_VALUE_FROM_FLASH(sine, i, n)
#define GET_SIN_VALUE_FROM_RAM(i, n)	GET_VALUE_FROM_RAM(sine, i, n)

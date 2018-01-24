#pragma once

#ifdef USE_NILSERIAL
#include "NilSerial_.h"
#define Serial NilSerial
#endif //USE_NILSERIAL
#include <VHB_Utils.h>

#if defined(SERIAL_DEBUG) || defined (DEBUG_SERIAL)

#define DEBUG_LOGLN(str) do {  Serial.print(__PRETTY_FUNCTION__); Serial.print(' '); Serial.println(str); } while(0)
#define DEBUG_LOG(str) do {  Serial.print(__PRETTY_FUNCTION__); Serial.print(' '); Serial.print(str); } while(0)

#define DEBUG_LOGLN_LITERAL(str)    DEBUG_LOGLN(F(str))
#define DEBUG_LOG_LITERAL(str)		DEBUG_LOG(F(str))

#define DEBUG_BEGIN(x)					Serial.begin(x)
#define DEBUG_PRINT(x)					Serial.print(x)
#define DEBUG_PRINT_LITERAL(x)		Serial.print(F(x))
#define DEBUG_PRINT_BASE(x, base)	Serial.print(x, base)
#define DEBUG_PRINT_HEX(x)				Serial.print(StringUtils::sprint(x, 16, 2*sizeof(x)))
#define DEBUG_PRINT_BASE_PAD(x, base, digits)	Serial.print(StringUtils::sprint(x, base, digits))
#define DEBUG_PRINTLN(x)				Serial.println(x)
#define DEBUG_PRINTLN_LITERAL(x)		Serial.println(F(x))
#define DEBUG_PRINTLN_BASE(x, base)	Serial.println(x, base)
#define DEBUG_PRINTLN_HEX(x)			Serial.println(StringUtils::sprint(x, 16, 2*sizeof(x)))
#define DEBUG_PRINTLN_BASE_PAD(x, base, digits)	Serial.println(StringUtils::sprint(x, base, digits))
#define DEBUG_PRINT_CHAR_ARRAY(str, len) StringUtils::printCharArray(str, (len), false)
#define DEBUG_PRINTLN_CHAR_ARRAY(str, len) StringUtils::printCharArray(str, (len), true)

#define DEBUG_PRINT_VAR(x)	DEBUG_PRINT_LITERAL(#x ": "); DEBUG_PRINT(x)
#define DEBUG_PRINTLN_VAR(x)	DEBUG_PRINT_LITERAL(#x ": "); DEBUG_PRINTLN(x)
#define DEBUG_PRINT_BASE_VAR(x, base) DEBUG_PRINT_LITERAL(#x ": "); DEBUG_PRINT_BASE(x, base)
#define DEBUG_PRINTLN_BASE_VAR(x, base) DEBUG_PRINT_LITERAL(#x ": ");  DEBUG_PRINTLN_BASE(x, base)
#define DEBUG_PRINT_HEX_VAR(x) DEBUG_PRINT_LITERAL(#x ": 0x"); DEBUG_PRINT_HEX(x)
#define DEBUG_PRINTLN_HEX_VAR(x) DEBUG_PRINT_LITERAL(#x ": 0x"); DEBUG_PRINTLN_HEX(x)
#define DEBUG_PRINT_BASE_PAD_VAR(x, base, digits) DEBUG_PRINT_LITERAL(#x ": "); DEBUG_PRINT_BASE_PAD(x, base, digits)
#define DEBUG_PRINTLN_BASE_PAD_VAR(x, base, digits) DEBUG_PRINT_LITERAL(#x ": "); DEBUG_PRINTLN_BASE_PAD(x, base, digits)
#define DEBUG_PRINT_CHAR_ARRAY_VAR(str, len)	DEBUG_PRINT_LITERAL(#str ": "); DEBUG_PRINT_CHAR_ARRAY(str, len)
#define DEBUG_PRINTLN_CHAR_ARRAY_VAR(str, len)	DEBUG_PRINT_LITERAL(#str ": "); DEBUG_PRINTLN_CHAR_ARRAY(str, len)
#define DEBUG_DUMP(Xclass)	Xclass.dump()
#define DEBUG_DUMP_VAR(Xclass)	DEBUG_PRINT_LITERAL(#Xclass ": "); Xclass.dump()

#else
#define DEBUG_LOGLN_LITERAL(str)
#define DEBUG_LOG_LITERAL(str)
#define DEBUG_LOG(str)
#define DEBUG_LOGLN(str)
#define DEBUG_BEGIN(x)
#define DEBUG_PRINT(x)
#define DEBUG_PRINT_LITERAL(x)
#define DEBUG_PRINT_BASE(x, base)
#define DEBUG_PRINT_HEX(x)
#define DEBUG_PRINT_BASE_PAD(x, base, digits)
#define DEBUG_PRINTLN(x) 
#define DEBUG_PRINTLN_LITERAL(x)
#define DEBUG_PRINTLN_BASE(x, base)
#define DEBUG_PRINTLN_HEX(x)
#define DEBUG_PRINTLN_BASE_PAD(x, base, digits)
#define DEBUG_PRINT_CHAR_ARRAY(str, len)
#define DEBUG_PRINTLN_CHAR_ARRAY(str, len)

#define DEBUG_PRINT_VAR(x)
#define DEBUG_PRINTLN_VAR(x)
#define DEBUG_PRINT_BASE_VAR(x, base)
#define DEBUG_PRINTLN_BASE_VAR(x, base)
#define DEBUG_PRINT_HEX_VAR(x)
#define DEBUG_PRINTLN_HEX_VAR(x)
#define DEBUG_PRINT_BASE_PAD_VAR(x, base, digits)
#define DEBUG_PRINTLN_BASE_PAD_VAR(x, base, digits)
#define DEBUG_PRINT_CHAR_ARRAY_VAR(str, len)
#define DEBUG_PRINTLN_CHAR_ARRAY_VAR(str, len)
#define DEBUG_DUMP(Xclass)	
#define DEBUG_DUMP_VAR(Xclass)

#endif //SERIAL_DEBUG

#define _CONDITIONAL_ACTION(condition, action) if (condition) { action; } else {}

#define _CONDITIONAL_LOGLN(condition, str)								_CONDITIONAL_ACTION(condition, Serial.print(__PRETTY_FUNCTION__); Serial.print(' '); Serial.println(str)) 
#define _CONDITIONAL_LOG(condition, str)									_CONDITIONAL_ACTION(condition, Serial.print(__PRETTY_FUNCTION__); Serial.print(' '); Serial.print(str)) 

#define _CONDITIONAL_LOGLN_LITERAL(condition, str)						_CONDITIONAL_LOGLN(condition, F(str))
#define _CONDITIONAL_LOG_LITERAL(condition, str)						_CONDITIONAL_LOG(condition, F(str))

#define _CONDITIONAL_BEGIN(condition, x)									_CONDITIONAL_ACTION(condition, Serial.begin(x))

#define _CONDITIONAL_WRITE(condition, x)									_CONDITIONAL_ACTION(condition, Serial.write(x))
#define _CONDITIONAL_PRINT(condition, x)									_CONDITIONAL_ACTION(condition, Serial.print(x))
#define _CONDITIONAL_PRINT_LITERAL(condition, x)						_CONDITIONAL_ACTION(condition, Serial.print(F(x)))
#define _CONDITIONAL_PRINT_BASE(condition, x, base)					_CONDITIONAL_ACTION(condition, Serial.print(x, base))
#define _CONDITIONAL_PRINT_HEX(condition, x)								_CONDITIONAL_ACTION(condition, Serial.print(StringUtils::sprint(x, 16, 2*sizeof(x))))
#define _CONDITIONAL_PRINT_BASE_PAD(condition, x, base, digits)	_CONDITIONAL_ACTION(condition, Serial.print(StringUtils::sprint(x, base, digits)))
#define _CONDITIONAL_PRINTLN(condition, x)								_CONDITIONAL_ACTION(condition, Serial.println(x))
#define _CONDITIONAL_PRINTLN_LITERAL(condition, x)						_CONDITIONAL_ACTION(condition, Serial.println(F(x)))
#define _CONDITIONAL_PRINTLN_BASE(condition, x, base)					_CONDITIONAL_ACTION(condition, Serial.println(x, base))
#define _CONDITIONAL_PRINTLN_HEX(condition, x)							_CONDITIONAL_ACTION(condition, Serial.print(StringUtils::sprint(x, 16, 2*sizeof(x))))
#define _CONDITIONAL_PRINTLN_BASE_PAD(condition, x, base, digits)	_CONDITIONAL_ACTION(condition, Serial.println(StringUtils::sprint(x, base, digits)))
#define _CONDITIONAL_PRINT_CHAR_ARRAY(condition, str, len)			_CONDITIONAL_ACTION(condition, printCharArray(str, (len), false))
#define _CONDITIONAL_PRINTLN_CHAR_ARRAY(condition, str, len)		_CONDITIONAL_ACTION(condition, printCharArray(str, (len), true))



/* Arduino NilRTOS Library
 * Copyright (C) 2013 by William Greiman
 *
 * This file is part of the Arduino NilRTOS Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino NilRTOS Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
 /**
 * @file    NilSerial.cpp
 * @brief   Nil RTOS serial library source
 *
 * @defgroup Serial NilSerial
 * @details Nil RTOS serial library.
 * @{
 */
#include <Arduino.h>

#ifdef __AVR_ATmega32__
#define UDR0 UDR
#define UCSR0A UCSRA
#define RXC0 RXC
#define U2X0 U2X
#define UBRR0H UBRRH
#define UBRR0L UBRRL
#define UCSR0B UCSRB
#define TXEN0 TXEN
#define RXEN0 RXEN
#define UDRIE0 UDRIE
#define UDRE0 UDRE
#endif //__AVR_ATmega32__

#if defined(UDR0) || defined(__DOXYGEN__)
#include "NilSerial_.h"
//------------------------------------------------------------------------------
/** @return one if a character is available else return zero. */
int NilSerialClass::available() {
  return UCSR0A & (1 << RXC0) ? 1 : 0;
}
//------------------------------------------------------------------------------
/**
 * Set baud rate for serial port zero and enable in non interrupt mode.
 * Do not call this function if you use another serial library.
 *
 * @param[in] baud rate
 */
void NilSerialClass::begin(unsigned long baud) {
  uint16_t baud_setting;
  // don't worry, the compiler will squeeze out F_CPU != 16000000UL
  if (F_CPU != 16000000UL || baud != 57600) {
    // Double the USART Transmission Speed
    UCSR0A = 1 << U2X0;
    baud_setting = (F_CPU / 4 / baud - 1) / 2;
  } else {
    // hardcoded exception for compatibility with the bootloader shipped
    // with the Duemilanove and previous boards and the firmware on the 8U2
    // on the Uno and Mega 2560.
    UCSR0A = 0;
    baud_setting = (F_CPU / 8 / baud - 1) / 2;
  }
  // assign the baud_setting
  UBRR0H = baud_setting >> 8;
  UBRR0L = baud_setting;
  // enable transmit and receive
  UCSR0B |= (1 << TXEN0) | (1 << RXEN0) ;
}
//------------------------------------------------------------------------------
/**
 *  Unbuffered read
 *  @return -1 if no character is available or an available character.
 */
int NilSerialClass::read() {
  if (UCSR0A & (1 << RXC0)) return UDR0;
  return -1;
}
//------------------------------------------------------------------------------
/**
 * Unbuffered write
 *
 * @param[in] b byte to write.
 * @return 1
 */
size_t NilSerialClass::write(uint8_t b) {
  while (((1 << UDRIE0) & UCSR0B) || !(UCSR0A & (1 << UDRE0))) {}
  UDR0 = b;
  return 1;
}
/** NilSerial object.
 *
 */
NilSerialClass NilSerial;
#endif  //  defined(UDR0) || defined(__DOXYGEN__)
/** @} */
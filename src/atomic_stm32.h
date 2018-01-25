/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2016 edogaldo.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

#ifndef _LIBMAPLE_ATOMIC_H_
#define _LIBMAPLE_ATOMIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ARDUINO_ARCH_STM32
	/**
	 * Disable interrupts and configurable fault handlers (set PRIMASK - save it first).
	 */
	static void __start_critical()  __attribute__((always_inline));
	
	void __start_critical()
	{
		asm volatile("mrs r0, PRIMASK; cpsid i; push {r0}" ::: "r0", "memory");
	}

	/**
	 * Restore saved PRIMASK.
	 */
	static void __stop_critical() __attribute__((always_inline));

	void __stop_critical()
	{
		asm volatile("pop {r0}; msr primask, r0" ::: "r0", "memory");
	}

	/**
	 * ATOMIC_BLOCK() guarantees the instructions block is executed without interruption (interrupts are disabled first);
	 * this is useful for example to safely access data modified by interrupts.
	 * After the block execution, interrupts registry PRIMASK is restored to its previous status.
	 *
	 * Usage:
	 *
	 * ATOMIC_BLOCK() {
	 *     instr 1;
	 *     [...]
	 *     instr N;
	 * }
	 *
	 */

#define ATOMIC_BLOCK() __start_critical(); \
	                   for ( uint32_t __ToDo  = 1; \
	                       __ToDo ; __ToDo = 0, __stop_critical() )

#endif //ARDUINO_ARCH_STM32

#ifdef __cplusplus
}
#endif

#endif

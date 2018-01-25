#pragma once

#include <stddef.h>
#ifdef ARDUINO_ARCH_AVR
#include <util/atomic.h>
#define _ATOMIC_BLOCK_() ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#endif //ARDUINO_ARCH_AVR

#ifdef ARDUINO_ARCH_STM32
#include "atomic_stm32.h"
#define _ATOMIC_BLOCK_() ATOMIC_BLOCK()
#endif //ARDUINO_ARCH_STM32

template <typename BufferType, const size_t BufferSize> class FifoBuffer_New
{
public:
	FifoBuffer_New() __attribute__((always_inline))
	{
		head = tail = buffer;
	}

	inline bool isempty() __attribute__((always_inline))
	{
		return head == tail;
	}

	inline bool isfull() __attribute__((always_inline))
	{
		return ((head == buffer) && (tail == &buffer[BufferSize - 1])) || (tail == head - 1);
	}

	inline void push(BufferType val) __attribute__((always_inline))
	{
		*(tail) = val;

		if (tail == &buffer[BufferSize - 1])
			tail = buffer;
		else
			tail++;
	}

	inline BufferType pop() __attribute__((always_inline))
	{
		BufferType retVal;

		if (head == &buffer[BufferSize - 1])
		{
			head = buffer;
			retVal = buffer[BufferSize - 1];
		}
		else
			retVal = *(head++);
		return retVal;
	}

	inline void flush() __attribute__((always_inline))
	{
		head = tail = buffer;
	}

	inline bool isempty_locked() __attribute__((always_inline))
	{
		bool result;
		noInterrupts();
		interrupts();
		_ATOMIC_BLOCK_()
		{
			result = isempty();
		}
		return result;
	}

	inline bool isfull_locked() __attribute__((always_inline))
	{
		bool result;
		_ATOMIC_BLOCK_()
		{
			result = isfull();
		}
		return result;
	}

	inline void push_locked(BufferType val) __attribute__((always_inline))
	{
		_ATOMIC_BLOCK_()
		{
			push(val);
		}
	}

	inline BufferType pop_locked() __attribute__((always_inline))
	{
		BufferType c;
		_ATOMIC_BLOCK_()
		{
			c = pop();
		}
		return c;
	}

protected:
	BufferType buffer[BufferSize];
	BufferType * volatile head;
	BufferType * volatile tail;
};


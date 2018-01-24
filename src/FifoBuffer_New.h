#pragma once

#include <stddef.h>
#include <util/atomic.h>

template <typename BufferType, const size_t BufferSize> class FifoBuffer_New
{
public:
	FifoBuffer() __attribute__((always_inline))
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
/*
		DEBUG_PRINT("\npush - head: ");
		DEBUG_PRINT_BASE((uint16_t)head, HEX);
		DEBUG_PRINT(", tail: ");
		DEBUG_PRINT_BASE((uint16_t)tail, HEX);
		DEBUG_PRINT(", buffer: ");
		DEBUG_PRINTLN_BASE((uint16_t)buffer, HEX);
		*/
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
/*
		DEBUG_PRINT("\npop - head: ");
		DEBUG_PRINT_BASE((uint16_t)head, HEX);
		DEBUG_PRINT(", tail: ");
		DEBUG_PRINT_BASE((uint16_t)tail, HEX);
		DEBUG_PRINT(", buffer: ");
		DEBUG_PRINTLN_BASE((uint16_t)buffer, HEX);
*/
		return retVal;
	}

	inline void flush() __attribute__((always_inline))
	{
		head = tail = buffer;
	}

	inline bool isempty_locked() __attribute__((always_inline))
	{
		bool result;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			result = isempty();
		}
		return result;
	}

	inline bool isfull_locked() __attribute__((always_inline))
	{
		bool result;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			result = isfull();
		}
		return result;
	}

	inline void push_locked(BufferType val) __attribute__((always_inline))
	{
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			push(val);
		}
	}

	inline BufferType pop_locked() __attribute__((always_inline))
	{
		BufferType c;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
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


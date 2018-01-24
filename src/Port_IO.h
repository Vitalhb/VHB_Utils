#pragma once

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

enum Bits : uint8_t
{
	bit0 = 0x01, bit1 = 0x02, bit2 = 0x04, bit3 = 0x08, bit4 = 0x10, bit5 = 0x20, bit6 = 0x40, bit7 = 0x80
};

class Port_IO
{
public:

	Port_IO(volatile uint8_t *_port)
	{
		_Port = _port;
		_Ddr = _port - 1;
		_Pin = _port - 2;
	}

	Port_IO(volatile uint8_t *_port, uint8_t inputBits, uint8_t outputBits) : Port_IO(_port)
	{
		if (inputBits != 0)
			SetBitsForInput(inputBits);
		if (outputBits != 0)
		{
			SetBitsForOutput(outputBits);
			ClearBits(outputBits);
		}
	}

	void SetBitsForOutput(uint8_t bits) __attribute__((always_inline))
	{
		*_Ddr |= bits;
	}

	void SetBitsForInput(uint8_t bits) __attribute__((always_inline))
	{
		*_Ddr &= ~bits;
	}

	void Write(uint8_t value) __attribute__((always_inline))
	{
		*_Port = value;
	}

	void Write(uint8_t value, uint8_t mask) __attribute__((always_inline))
	{
		*_Port = (*_Port & ~mask) | (value & mask);
	}

	uint8_t Read() __attribute__((always_inline))
	{
		return *_Pin;
	}

	void ToggleBits(uint8_t bits) __attribute__((always_inline))
	{
		*_Pin = bits;
	}

	void SetBits(uint8_t bits) __attribute__((always_inline))
	{
		*_Port |= bits;
	}

	void ClearBits(uint8_t bits) __attribute__((always_inline))
	{
		*_Port &= ~bits;
	}

//private:
	// &DDR = &PORT -1, &PIN = &PORT - 2
	volatile uint8_t * _Port;
	volatile uint8_t * _Ddr;
	volatile uint8_t * _Pin;
};

template <uint16_t PortBaseAddress> class TPort_IO
{
public:
#define _PORT(PORT_ADDRESS)	 ((volatile uint8_t *)(PORT_ADDRESS))
#define _DDR(PORT_ADDRESS)	 ((volatile uint8_t *)(PORT_ADDRESS - 1))
#define _PIN(PORT_ADDRESS)	 ((volatile uint8_t *)(PORT_ADDRESS - 2))

	TPort_IO()
	{
	}

	TPort_IO(uint8_t inputBits, uint8_t outputBits)
	{
		Init(inputBits, outputBits);
	}

	void Init(uint8_t inputBits, uint8_t outputBits)
	{
		if (inputBits != 0)
			SetBitsForInput(inputBits);
		if (outputBits != 0)
		{
			SetBitsForOutput(outputBits);
			ClearBits(outputBits);
		}
	}

	void SetBitsForOutput(uint8_t bits) __attribute__((always_inline))
	{
		*_DDR(PortBaseAddress) |= bits;
	}

	void SetBitsForInput(uint8_t bits) __attribute__((always_inline))
	{
		*_DDR(PortBaseAddress) &= ~bits;
	}

	void Write(uint8_t value) __attribute__((always_inline))
	{
		*_PORT(PortBaseAddress) = value;
	}

	void Write(uint8_t value, uint8_t mask) __attribute__((always_inline))
	{
		*_PORT(PortBaseAddress) = (*_PORT(PortBaseAddress) & ~mask) | (value & mask);
	}

	uint8_t Read() __attribute__((always_inline))
	{
		return *_PIN(PortBaseAddress);
	}

	void ToggleBits(uint8_t bits) __attribute__((always_inline))
	{
		*_PIN(PortBaseAddress) = bits;
	}

	void SetBits(uint8_t bits) __attribute__((always_inline))
	{
		*_PORT(PortBaseAddress) |= bits;
	}

	void ClearBits(uint8_t bits) __attribute__((always_inline))
	{
		*_PORT(PortBaseAddress) &= ~bits;
	}
};

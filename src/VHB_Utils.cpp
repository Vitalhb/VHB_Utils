#include <arduino.h>
//#define SERIAL_DEBUG
#include <VHB_Debug_Utils.h>
#include "VHB_Utils.h"

void Led::begin(uint8_t lport, bool bPolarity)
{
	if (lport != 0)
	{
		port = lport;
		bPol = bPolarity;
		pinMode(port, OUTPUT);
		Off();
	}
}

void Led::Blink(uint16_t timeOn, uint16_t timeOff)
{
	if (bBlinking)
	{
		if (timer.Timeout())
		{
			if (digitalRead(port) == bPol) // if led is on
			{
				digitalWrite(port, !bPol); //toggle led port
				timer.Delay(timeOff);
			}
			else
			{
				digitalWrite(port, bPol); //toggle led port
				timer.Delay(timeOn);
			}
		}
	}
	else
	{
		bBlinking = true;
		digitalWrite(port, bPol); //toggle led port
		timer.Delay(timeOn);
	}
}

void Led::DoubleBlink(uint16_t timeOn, uint16_t timeOff, uint16_t timeBlinking, uint16_t timeNotBlinking)
{
	if (bBlinkPeriod)
	{
		if (timerDB.Timeout())
		{
			DEBUG_PRINTLN_LITERAL("No blinking period");
			bBlinkPeriod = false;
			timerDB.Delay(timeNotBlinking);
		}
		else
		{
			Blink(timeOn, timeOff);
		}
	}
	else
	{
		if (timerDB.Timeout())
		{
			DEBUG_PRINTLN_LITERAL("Blinking period");
			bBlinkPeriod = true;
			timerDB.Delay(timeBlinking);
		}
		else
		{
			digitalWrite(port, !bPol);
			bBlinking = false;
		}
	}
}

void Led::DoubleBlink(uint16_t time1_On, uint16_t time1_Off, uint16_t time2_On, uint16_t time2_Off, uint16_t time1_Blinking, uint16_t time2_Blinking)
{
	if (bBlinkPeriod)
	{
		if (timerDB.Timeout())
		{
			DEBUG_PRINTLN_LITERAL("Blinking period 2");
			bBlinkPeriod = false;
			timerDB.Delay(time2_Blinking);
		}
		else
		{
			Blink(time1_On, time1_Off);
		}
	}
	else
	{
		if (timerDB.Timeout())
		{
			DEBUG_PRINTLN_LITERAL("Blinking period 1");
			bBlinkPeriod = true;
			timerDB.Delay(time1_Blinking);
		}
		else
		{
			Blink(time2_On, time2_Off);
		}
	}
}

void Buzzer::begin(uint8_t lport, unsigned int lfrequency, bool bEnabled)
{
	port = lport;
	frequency = lfrequency;
	bBeeping = bSounding = false;
	bEnable = bEnabled;
}

void Buzzer::On(int duration)
{
	if (bEnable)
	{
		if (duration == 0)
			tone(port, frequency);
		else
			tone(port, frequency, duration);
	}
}

void Buzzer::Beep(uint8_t nTimes, int Duration, int Interval)
{
	if (bEnable)
	{
		while (nTimes)
		{
			nTimes--;
			tone(port, frequency);
			delay(Duration);
			noTone(port);
			if (nTimes > 0)
				delay(Interval);
		}
	}
}

void Buzzer::BeepNonBlock(int Duration, int Interval)
{
	if (bEnable)
	{
		if (bBeeping)
		{
			if (timer.Timeout())
			{
				if (bSounding)
				{
					noTone(port);
					timer.Delay(Interval);
				}
				else
				{
					tone(port, frequency);
					timer.Delay(Duration);
				}
				bSounding = !bSounding;
			}
		}
		else
		{
			tone(port, frequency);
			timer.Delay(Duration);
			bBeeping = true;
			bSounding = true;
		}
	}
}

char *StringUtils::CopyAndPad(char *dstStr, uint8_t dstSize, const char *srcStr, bool toUpper, char padChar)
{
	uint8_t i = 0;
	char tmpChar;

	while (*srcStr && i < dstSize)
	{
		tmpChar = *(srcStr++);
		if (toUpper)
		{
			tmpChar = toupper(tmpChar);
		}
		dstStr[i++] = tmpChar;
	}

	while (i < dstSize)
	{
		dstStr[i++] = padChar;
	}

	return dstStr;
}

bool StringUtils::CheckChars(char *str, uint8_t size, char min, char max)
{
	bool result = true;
	while (*str && size-- && result)
	{
		result &= *str >= min;
		result &= *str <= max;
		str++;
	}
	return result;
}

bool StringUtils::CheckChars(char *str, uint8_t size, bool(*func)(int c))
{
	bool result = true;
	while (*str && size-- && result)
	{
		result &= func(*str);
		str++;
	}
	return result;
}

void StringUtils::UnsignedToStr(uint16_t number, char *str, uint8_t digits)
{
	int8_t index = 0, size;
	char strTmp[5];

	if (digits > sizeof(strTmp))
		digits = sizeof(strTmp);

	do
	{
		strTmp[index++] = BYTE_TO_CHAR(number % 10);
		number /= 10;
	}
	while (number != 0);

	while (digits > index)
	{
		str[index++] = '0';
	}

	size = index;
	while (index)
	{
		str[index - 1] = strTmp[size - index];
		index--;
	}

	str[size] = 0;
}

const char *UnsignedToStr(uint16_t number, uint8_t digits = 0)
{
	static char strTmp[6];
	int8_t index = sizeof(strTmp) - 1;

	if (digits > sizeof(strTmp) - 1)
		digits = sizeof(strTmp) - 1;

	strTmp[index] = 0;
	
	do
	{
		if (index > 0)
			index--;
		if (digits > 0)
			digits--;
		strTmp[index] = BYTE_TO_CHAR(number % 10);
		number /= 10;
	}
	while (number != 0);

	while (digits > 0)
	{
		if (index > 0)
			index--;
		digits--;
		strTmp[index] = '0';
	}

	return &strTmp[index];
}

void StringUtils::printCharArray(const char *str, uint8_t len, bool bEol)
{
	for (int8_t i = 0; i < len; i++)
	{
		Serial.print(str[i]);
	}
	if (bEol)
		Serial.println();
}


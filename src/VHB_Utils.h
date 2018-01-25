#ifndef VHB_UTILS
#define VHB_UTILS

#define	ALWAYS_INLINE __attribute__((always_inline))
#define	BYTE_TO_CHAR(i)	('0' + (uint8_t)(i))
#define	CHAR_TO_BYTE(c)	((uint8_t)(c) - '0')

#define STRINGIFY(x) #x
#define TOKEN_TO_STRING(x) STRINGIFY(x)

#ifdef ARDUINO_ARCH_AVR
inline void* operator new(size_t size, void* ptr)
{
	return ptr;
}
#endif //ARDUINO_ARCH_AVR

// Non blocking timer. Slightly faster than the NonBlockTimer_OS 
// Not safe for millis() overflows. Works for devices that do not operate more than 49 days without restart.
class NonBlockDelay
{
	unsigned long iTimeout = 0;
	bool bRunning = false;

public:
	inline void begin(bool bStartRunning = true) ALWAYS_INLINE
	{
		iTimeout = millis();
		bRunning = bStartRunning;
	}

	inline void Delay(unsigned long t) ALWAYS_INLINE
	{
		iTimeout = millis() + t;
		bRunning = true;
	}

	inline void Stop() ALWAYS_INLINE
	{
		bRunning = false;
	}

	inline bool IsRunning() ALWAYS_INLINE
	{
		return bRunning;
	}

	inline bool Timeout(void) ALWAYS_INLINE
	{
		return bRunning && (iTimeout < millis());
	}

	inline bool TimeoutAutoReload(unsigned long t) ALWAYS_INLINE
	{
		if (bRunning && (iTimeout < millis()))
		{
			Delay(t);
			return true;
		}

		return false;
	}

	inline unsigned long Time(void) ALWAYS_INLINE
	{
		return iTimeout;
	}

	inline unsigned long TimeLeft(void) ALWAYS_INLINE
	{
		if (Timeout())
			return 0;
		else
			return (iTimeout - millis());
	}
};

// Non blocking timer. 
// Safe for millis() overflows. Works for devices that operate more than 49 days without restart.
class NonBlockTimer_OS
{
	unsigned long ulStartTime = 0;

public:
	inline void Start() ALWAYS_INLINE
	{
		ulStartTime = millis();
	}

	inline bool Timeout(unsigned long t) ALWAYS_INLINE
	{
		return (millis() - ulStartTime > t);
	}

	inline bool TimeoutAutoRestart(unsigned long t) ALWAYS_INLINE
	{
		if (Timeout(t))
		{
			Start();
			return true;
		}

		return false;
	}

	inline unsigned long TimeLeft(unsigned long t) ALWAYS_INLINE
	{
		if (Timeout(t))
			return 0;
		else
			return (t - (millis() - ulStartTime));
	}
};

class Chronometer
{
public:
	Chronometer()
	{
		Init();
	}

	inline void Init() ALWAYS_INLINE
	{
		max = 0;
		min = -1;
	}

	inline void UpdateMaxMin() ALWAYS_INLINE
	{
		if (dtime > max)
			max = dtime;
		if (dtime < min)
			min = dtime;
	}

	inline bool UpdateMax() ALWAYS_INLINE
	{
		if (dtime > max)
		{
			max = dtime;
			return true;
		}
		return false;
	}

	inline bool UpdateMin() ALWAYS_INLINE
	{
		if (dtime < min)
		{
			min = dtime;
			return true;
		}
		return false;
	}

	inline void StartMicros() ALWAYS_INLINE
	{
		dtime = micros();
	}

	inline uint32_t StopMicros() ALWAYS_INLINE
	{
		dtime = micros() - dtime;
		return dtime;
	}

	inline void StartMillis() ALWAYS_INLINE
	{
		dtime = millis();
	}

	inline uint32_t StopMillis() ALWAYS_INLINE
	{
		dtime = millis() - dtime;
		return dtime;
	}

	inline uint32_t Time() ALWAYS_INLINE
	{
		return dtime;
	}

	inline uint32_t Max() ALWAYS_INLINE
	{
		return max;
	}

	inline uint32_t Min() ALWAYS_INLINE
	{
		return min;
	}

private:
	uint32_t dtime, max, min;
};

class Led
{
public:
	//	Led(byte lport = 0, bool bPolarity = true);	// Polarity is true when the Led lights on port HIGH and false when led lights on port LOW
	void begin(byte lport, bool bPolarity = true);	// Polarity is true when the Led lights on port HIGH and false when led lights on port LOW
	inline void On() ALWAYS_INLINE
	{
		digitalWrite(port, bPol);
		bBlinking = false;
		bBlinkPeriod = false;
		timerDB.begin();
	}

	inline void Off() ALWAYS_INLINE
	{
		digitalWrite(port, !bPol);
		bBlinking = false;
		bBlinkPeriod = false;
		timerDB.begin();
	}

	inline void Toggle() ALWAYS_INLINE
	{
		digitalWrite(port, !digitalRead(port));
		bBlinking = false;
	}

	void Blink(uint16_t timeOn, uint16_t timeOff);
	void DoubleBlink(uint16_t timeOn, uint16_t timeOff, uint16_t timeBlinking, uint16_t timeNotBlinking);
	void DoubleBlink(uint16_t time1_On, uint16_t time1_Off, uint16_t time2_On, uint16_t time2_Off, uint16_t time1_Blinking, uint16_t time2_Blinking);

	inline void Blink(uint16_t period) ALWAYS_INLINE
	{
		Blink(period, period);
	}
private:
	byte port = 0;
	bool bPol = true;
	NonBlockDelay timer, timerDB;
	bool bBlinking = false, bBlinkPeriod = false;
};

class Buzzer
{
public:
	Buzzer() 
	{
		port = 0;
		frequency = 0;
		bBeeping = bSounding = bEnable = false;
	}

	Buzzer(byte lport, unsigned int lfrequency, bool bEnabled = true)
	{
		begin(lport, lfrequency, bEnabled);
	}

	void begin(byte lport, unsigned int lfrequency = 1000, bool bEnabled = true);
	void On(int duration = 0);

	inline void Off()
	{
		noTone(port);
		bBeeping = bSounding = false;
	}

	inline void SetFrequency(unsigned int lfrequency)
	{
		frequency = lfrequency;
	}

	void Beep(byte nTimes = 1, int Duration = 200, int Interval = 200);
	void BeepNonBlock(int Duration = 200, int Interval = 200);

	inline void Enable()
	{
		bEnable = true;
	}

	inline void Disable() 
	{ 
		if (bEnable)
			Off();
		bEnable = false;
	}

private:
	byte port;
	unsigned int frequency;
	NonBlockDelay timer;
	bool bBeeping, bSounding, bEnable;
};

class StringUtils
{
public:
	static char *CopyAndPad(char *dstStr, uint8_t dstSize, const char *srcStr, bool toUpper = false, char padChar = ' ');
	static bool CheckChars(char *str, int8_t size, char min, char max);
	static bool CheckChars(char *str, int8_t size, bool (*func)(int c));
	static inline bool isalnumspace(int ch) { return (isAlphaNumeric(ch) || isblank(ch)); }
	static void UnsignedToStr(uint16_t number, char *str, int8_t digits = 0);
	static void printCharArray(const char *str, int8_t len, bool bEol);

	template <typename T>
	static char *sprint(T number, uint8_t base = 10, uint8_t digits = 0)
	{
		static char buf[8 * sizeof(T) + 1]; // Assumes 8-bit chars plus zero byte.
		char *str = &buf[sizeof(buf) - 1];

		*str = '\0';

		// prevent crash if called with base == 1 or 0
		if (base < 2) base = 10;
		if (digits > sizeof(buf) - 1) digits = sizeof(buf) - 1;

		do
		{
			char c = number % base;
			number /= base;
			if (digits) digits--;

			*--str = c < 10 ? c + '0' : c + 'A' - 10;
		}
		while (number > 0 || digits > 0);

		return str;
	}
};

#endif // VHB_UTILS
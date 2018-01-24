
#define SERIAL_DEBUG
#include <VHB_Debug_Utils.h>
#include <VHB_Utils.h>

Led led;
NonBlockTimer_OS timer;

void setup()
{
	DEBUG_BEGIN(115200);
	led.begin(13);
	timer.Start();
}

void loop()
{
	led.Off();
	DEBUG_PRINTLN("Blink test");
	while (!timer.TimeoutAutoRestart(10000))
	{
		led.Blink(50, 50);
	}

	led.Off();
	DEBUG_PRINTLN("DoubleBlink test 1");
	while (!timer.TimeoutAutoRestart(12000))
	{
		led.DoubleBlink(50, 100, 2000, 2000);
	}

	led.Off();
	DEBUG_PRINTLN("DoubleBlink test 2");
	while (!timer.TimeoutAutoRestart(20000))
	{
		led.DoubleBlink(50, 100, 100, 400, 5000, 5000);
	}
}

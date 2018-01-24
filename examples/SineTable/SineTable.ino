#define TABLE_SIZE 32
#define BIT_MASK 0xf0
#define SHIFT_RIGHT 0

#include <TableGenerator.h>

BUILD_SIN_TABLE_IN_FLASH(TABLE_SIZE);
BUILD_SIN_TABLE_IN_RAM(TABLE_SIZE);

void setup()
{
	uint16_t i = 0;
	Serial.begin(2000000);
	delay(100);

	for (i = 0; i < TABLE_SIZE; i++)
	{
		Serial.print(GET_SIN_VALUE_FROM_FLASH(i, TABLE_SIZE));
		Serial.print(", ");
		Serial.println(GET_SIN_VALUE_FROM_RAM(i, TABLE_SIZE));
	}
}

void loop()
{

  /* add main program code here */

}

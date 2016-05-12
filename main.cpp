/*
 * roomba_wall_v2.cpp
 *
 * Created: 5/11/2016 9:12:04 PM
 * Author : Peter Dunshee
 */ 

#include "roomba_wall_v2.h"
#include <avr/io.h>
#include <avr/power.h>

int main(void)
{
	init();

	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);

	// Red-Status LED
	DDRB |= _BV(4);   // Set PORTB pin 4 to digital output (equivalent to pinMode(4, OUTPUT))
	PORTB &= ~_BV(4); // Pin 4 set to LOW (equivalent to digitalWrite(4, LOW))

    /* Replace with your application code */
	int i = 0;
	while (1)
	{
		i++;
		if (i == 0) PORTB &= ~_BV(4); // digitalWrite(4, LOW);
		if (i == 100) PORTB |= _BV(4);// digitalWrite(4, HIGH);
		if (i == 105) i = -1;

		roomba_send(162); // Virtual Wall
		delay(1000);
	}
}

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
	// Red-Status LED
	DDRB |= _BV(0);   // Set PORTB pin 4 to digital output (equivalent to pinMode(0, OUTPUT))
	PORTB &= ~_BV(0); // Pin 0 set to LOW (equivalent to digitalWrite(0, LOW))

    /* Replace with your application code */
	int i = 0;
	while (1)
	{
		i++;
		if (i == 0) PORTB |= _BV(0);// digitalWrite(4, HIGH);
		if (i == 2) PORTB &= ~_BV(0); // digitalWrite(4, LOW);
		if (i == 12) i = -1;

		roomba_send(162); // Virtual Wall
		delay_ten_us(1000);
	}
}

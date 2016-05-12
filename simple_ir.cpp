// Simple_IR, based on functions from IRremote by Ken Shirriff, referenced below
//
//******************************************************************************
// IRremote
// Version 2.0.1 June, 2015
// Copyright 2009 Ken Shirriff
// For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
// Edited by Mitra to add new controller SANYO
//
// Interrupt code based on NECIRrcv by Joe Knapp
// http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
// Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
//
// JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
// LG added by Darryl Smith (based on the JVC protocol)
// Whynter A/C ARC-110WD added by Francesco Meschia
//******************************************************************************

#include "roomba_wall_v2.h"
#include <avr/io.h>

//------------------------------------------------------------------------------
// CPU Frequency
//
#ifdef F_CPU
#	define SYSCLOCK  F_CPU     // main Arduino clock
#else
#	define SYSCLOCK  16000000  // main Arduino clock
#endif

#define STRINGIZE1(X) #X
#define STRINGIZE(X) STRINGIZE1(X)
#define IR_CLOCK_MESSAGE "Building simple IR for " STRINGIZE(F_CPU) " Hz clock"
#pragma message IR_CLOCK_MESSAGE

// IR_USE_TIMER_TINY0 for ATTiny85

#define TIMER_RESET
#define TIMER_ENABLE_PWM     (TCCR0A |= _BV(COM0B1))
#define TIMER_DISABLE_PWM    (TCCR0A &= ~(_BV(COM0B1)))
#define TIMER_ENABLE_INTR    (TIMSK |= _BV(OCIE0A))
#define TIMER_DISABLE_INTR   (TIMSK &= ~(_BV(OCIE0A)))
#define TIMER_INTR_NAME      TIMER0_COMPA_vect
#define TIMER_CONFIG_KHZ(val) ({ \
  const uint8_t pwmval = SYSCLOCK / 2000 / (val); \
  TCCR0A = _BV(WGM00); \
  TCCR0B = _BV(WGM02) | _BV(CS00); \
  OCR0A = pwmval; \
  OCR0B = pwmval / 3; \
})
#define TIMER_COUNT_TOP      (SYSCLOCK * USECPERTICK / 1000000)

#define TIMER_CONFIG_NORMAL() ({ \
  TCCR0A = _BV(WGM01); \
  TCCR0B = _BV(CS00); \
  OCR0A = TIMER_COUNT_TOP; \
  TCNT0 = 0; \
})

#define TIMER_PWM_PIN        1  /* ATtiny85 */

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

//IRsend::sendRaw
void  sendRawIR(const unsigned int buf[], unsigned int len, unsigned int hz)
{
	// Set IR carrier frequency
	enableIROut(hz);

	for (unsigned int i = 0; i < len; i++) {
		if (i & 1)  spaceIR(buf[i]);
		else        markIR(buf[i]);
	}

	spaceIR(0);  // Always end with the LED off
}

//+=============================================================================
// Enables IR output.  The khz value controls the modulation frequency in kilohertz.
// The IR output will be on pin 3 (OC2B).
// This routine is designed for 36-40KHz; if you use it for other values, it's up to you
// to make sure it gives reasonable results.  (Watch out for overflow / underflow / rounding.)
// TIMER2 is used in phase-correct PWM mode, with OCR2A controlling the frequency and OCR2B
// controlling the duty cycle.
// There is no prescaling, so the output frequency is 16MHz / (2 * OCR2A)
// To turn the output on and off, we leave the PWM running, but connect and disconnect the output pin.
// A few hours staring at the ATmega documentation and this will all make sense.
// See my Secrets of Arduino PWM at http://arcfn.com/2009/07/secrets-of-arduino-pwm.html for details.
//
//IRsend::enableIROut
void enableIROut(int khz)
{
	// Disable the Timer2 Interrupt (which is used for receiving IR)
	TIMER_DISABLE_INTR; //Timer2 Overflow Interrupt
			
	DDRB |= _BV(TIMER_PWM_PIN);   // Set PORTB PWM pin to digital output (equivalent to pinMode(TIMER_PWM_PIN, OUTPUT))
	TIMER_DISABLE_PWM;
	PORTB &= ~_BV(TIMER_PWM_PIN); // digitalWrite(TIMER_PWM_PIN, LOW); // When not sending PWM, we want it low

									  // COM2A = 00: disconnect OC2A
									  // COM2B = 00: disconnect OC2B; to send signal set to 10: OC2B non-inverted
									  // WGM2 = 101: phase-correct PWM with OCRA as top
									  // CS2  = 000: no prescaling
									  // The top value for the timer.  The modulation frequency will be SYSCLOCK / 2 / OCR2A.
	TIMER_CONFIG_KHZ(khz);
}

//+=============================================================================
// Custom delay function that circumvents Arduino's delayMicroseconds limit
//IRsend::custom_delay_usec
void custom_delay_usec(unsigned long uSecs) {
	if (uSecs > 4) {
		unsigned long start = micros();
		unsigned long endMicros = start + uSecs - 4;
		if (endMicros < start) { // Check if overflow
			while (micros() > start) {} // wait until overflow
		}
		while (micros() < endMicros) {} // normal wait
	}
	//else {
	//  __asm__("nop\n\t"); // must have or compiler optimizes out
	//}
}

//+=============================================================================
// Leave pin off for time (given in microseconds)
// Sends an IR space for the specified number of microseconds.
// A space is no output, so the PWM output is disabled.
//
//IRsend::space
void spaceIR(unsigned int time)
{
	TIMER_DISABLE_PWM; // Disable pin 3 PWM output
	if (time > 0) custom_delay_usec(time);
}

//+=============================================================================
// Sends an IR mark for the specified number of microseconds.
// The mark output is modulated at the PWM frequency.
//
//IRsend::mark
void markIR(unsigned int time)
{
	TIMER_ENABLE_PWM; // Enable pin 3 PWM output
	if (time > 0) custom_delay_usec(time);
}

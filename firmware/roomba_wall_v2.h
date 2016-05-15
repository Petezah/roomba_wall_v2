/*
Name:		roomba_wall_v2.h
Author:	Peter Dunshee
*/

#ifndef _ROOMBA_WALL_V2_h
#define _ROOMBA_WALL_V2_h

#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Shortcut to insert single, non-optimized-out nop
#define NOP __asm__ __volatile__ ("nop")

// Tweak this if neccessary to change timing
#define DELAY_CNT 11

#ifdef __cplusplus
} // extern "C"
#endif

void delay_ten_us(unsigned long us);
void roomba_send(int code);
void sendRawIR(const unsigned int buf[], unsigned int len, unsigned int hz);
void enableIROut(int khz);
void spaceIR(unsigned int time);
void markIR(unsigned int time);

#endif


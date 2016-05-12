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

void init();
unsigned long micros();
void delay(unsigned long ms);

#ifdef __cplusplus
} // extern "C"
#endif

void roomba_send(int code);
void sendRawIR(const unsigned int buf[], unsigned int len, unsigned int hz);
void enableIROut(int khz);
void spaceIR(unsigned int time);
void markIR(unsigned int time);

#endif


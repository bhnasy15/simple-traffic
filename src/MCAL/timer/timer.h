#ifndef TIMER_H
#define TIMER_H

#include "../../Util/util.h"
#include "../registers/registers.h"

// list all timer states
typedef enum {
	STOP 				= 0x00,	   //No clock source (Timer/Counter stopped).
	T_1					= 0x01,	   //clkI/O /(No prescaling)
	T_8					= 0x02,	   //clkI/O /8 (From prescaler)
	T_64 				= 0x03,	   //clkI/O /64 (From prescaler)
	T_256 				= 0x04,	   //clkI/O /256 (From prescaler)
	T_1024 				= 0x05,	   //clkI/O /1024 (From prescaler)
	EXTERNAL_FALLIMG 	= 0x06,	   //External clock source on T0 pin. Clock on
								   //falling edge
	EXTERNAL_RAISING 	= 0x07	   //External clock source on T0 pin. Clock on
								   //rising edge
} timer_mode_t;

typedef struct {
	unsigned long cycle;
	timer_mode_t mode;
} timer_t;

byte delay_ms(unsigned long);

void timer_mode(timer_mode_t);
byte get_delay(unsigned long , timer_mode_t, timer_t*);


#endif

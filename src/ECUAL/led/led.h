
#ifndef LED_H
#define LED_H

#include "../../Util/util.h"
#include "../../MCAL/dio/dio.h"

typedef struct {
	const port_t port;
	const pin_t pin;
} led_t;

byte LED_INIT(led_t);
byte LED_ON(led_t);
byte LED_OFF(led_t);
byte LED_TOGGLE(led_t);
byte LED_STATE(led_t, bit_t*);

#endif


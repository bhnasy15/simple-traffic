#ifndef BUTTON_H
#define BUTTON_H

#include "../../Util/util.h"
#include "../../MCAL/dio/dio.h"

typedef struct {
	port_t port;
	pin_t pin;
} button_t;

byte BUTTON_INIT(button_t);
byte BUTTON_STATE(button_t, bit_t*);

#endif


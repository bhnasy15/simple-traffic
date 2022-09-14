#ifndef DIO_H
#define DIO_H

#include "../../Util/util.h"
#include "../registers/registers.h"

// list of all avilable ports
typedef enum {
	A, B, C, D
} port_t;

// list of all avilable pins
typedef enum {
	_0, _1, _2, _3, _4, _5, _6, _7
} pin_t;

typedef enum {
	LOW = 0,
	HIGH = 1,
} bit_t;

typedef enum {
	IN = 0,
	OUT = 1
} direction_t;

byte DIO_INIT(port_t, pin_t, direction_t);
byte DIO_WRITE(port_t, pin_t, bit_t);
byte DIO_READ(port_t, pin_t, bit_t*);
byte DIO_STATE(port_t, pin_t, bit_t*);
byte DIO_TOGGLE(port_t, pin_t);

#endif


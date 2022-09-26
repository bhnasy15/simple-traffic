
#include "led.h"

// Initialize to output and set LED OFF
byte LED_INIT(led_t led){
	// check for port then set led to output
	if(DIO_INIT(led.port, led.pin, OUT) == SUCCESS &&
		DIO_WRITE(led.port, led.pin, LOW) == SUCCESS )
		return CAN_NOT_INIT_LED;
	return ERROR;
}

// trun led on
byte LED_ON(led_t led){
	//ON = led.pin_layout
	return DIO_WRITE(led.port, led.pin, HIGH);
}

// trun led off
byte LED_OFF(led_t led){
	//OFF = NOT led.pin_layout
	return DIO_WRITE(led.port, led.pin, LOW);
}

// toggle led
byte LED_TOGGLE(led_t led){
	return DIO_TOGGLE(led.port, led.pin);
}

// get led state
byte LED_STATE(led_t led, bit_t* bit){
	return DIO_READ(led.port, led.pin, bit);
}

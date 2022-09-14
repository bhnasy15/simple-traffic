
#include "led.h"

byte LED_INIT(led_t led){
	// Initialize to output and set LED OFF
	if(DIO_INIT(led.port, led.pin, OUT) == SUCCESS &&
		DIO_WRITE(led.port, led.pin, LOW) == SUCCESS )
		return SUCCESS;
	return ERROR;
}

byte LED_ON(led_t led){
	//ON = led.pin_layout
	return DIO_WRITE(led.port, led.pin, HIGH);
}

byte LED_OFF(led_t led){
	//OFF = NOT led.pin_layout
	return DIO_WRITE(led.port, led.pin, LOW);
}

byte LED_TOGGLE(led_t led){
	return DIO_TOGGLE(led.port, led.pin);
}

byte LED_STATE(led_t led, bit_t* bit){
	return DIO_READ(led.port, led.pin, bit);
}

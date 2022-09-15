
#include "../src/MCAL/dio/dio.h"
#include "../src/MCAL/timer/timer.h"
#include "../src/ECUAL/led/led.h"
#include "../src/ECUAL/button/button.h"

int main(void){
	/******************************************/
	// MCAL test
	// dio and timer testing
	// will use portC pin 0 and 1
	// with pin0 as output and pin1 as input
	// all functions are used atleas once
	//
	// // procedure
	// //* run the sim
	// //* press the button
	//
	// // expected out come
	// /* the led is only on when button is pressed
	/******************************************/
	led_t led = { .port = C, .pin = 0};
	button_t button = {.port = C, .pin = 1};
	LED_INIT(led);
	BUTTON_INIT(button);
	bit_t is_pressed = 0;

	//press and hold
	while (1) {
		BUTTON_STATE(button, &is_pressed);
		if(is_pressed) LED_ON(led);
		if(!is_pressed) LED_OFF(led);
	}
	/******************************************/
}


#include "../src/MCAL/dio/dio.h"
#include "../src/MCAL/timer/timer.h"
#include "../src/ECUAL/led/led.h"

int main(void){
	/******************************************/
	// led test
	// will use portC pin 0
	// all functions are used atleas once
	//
	// // procedure
	// //* run the sim
	//
	// // expected out come
	// /*the led will be on for 1s and off for 1s
	// /** loop
	// /* the led will blik fast for 4s then slow for 4s
	/******************************************/
	led_t led = { .port = C, .pin = 0};
	bit_t state = 0;
	LED_INIT(led);

	LED_ON(led);
	delay_ms(1000);
	LED_OFF(led);
	delay_ms(1000);
	
	while (1) {
		for (int i = 0; i < 8; i++) {
			LED_TOGGLE(led);
			delay_ms(250);
			LED_TOGGLE(led);
			delay_ms(250);
			
		}


		for (int i = 0; i < 2; i++) {
			LED_TOGGLE(led);
			delay_ms(500);
			LED_TOGGLE(led);
			delay_ms(500);


			LED_STATE(led, &state);
			if(state) LED_OFF(led);
			if(!state) LED_ON(led);
			delay_ms(500);
			if(state) LED_OFF(led);
			if(!state) LED_ON(led);
			delay_ms(500);
		}
	}
	/******************************************/
}

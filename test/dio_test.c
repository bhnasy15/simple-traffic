
#include "../src/MCAL/dio/dio.h"
#include "../src/MCAL/timer/timer.h"

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
	// /* the led is on for 1s then off for 1s
	// /* if button is pressed teh led will blick 
	// 		twice per second.
	/******************************************/

	DIO_INIT( C, 0, OUT);
	DIO_INIT( C, 1, IN);

	DIO_WRITE( C, 0, HIGH);
	delay_ms(1000);
	DIO_WRITE( C, 0, LOW);
	
	bit_t is_pressed = 0;
	bit_t is_high = 0;
	while (1) {
		DIO_STATE( C, 1, &is_pressed);

		// toggle with state read
		if(is_pressed){
			DIO_READ( C, 0, &is_high);
			if( is_high)		DIO_WRITE( C, 0, LOW);
			if( !is_high)	DIO_WRITE( C, 0, HIGH);
			delay_ms(500);
			DIO_TOGGLE( C, 0);
			delay_ms(500);
		}
	}
	/******************************************/
}


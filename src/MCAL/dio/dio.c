#include "dio.h"

// initiate port direction

byte DIO_INIT(port_t port, pin_t pin, direction_t direction){
	// determine port letter
	switch (port) {
		case A : {
					 // deternine and set port direction
			direction ? (DDRA |= (1 << pin)) : (DDRA &= ~(1 << pin));
			return SUCCESS ;	
		}
		case B : {
					 // deternine and set port direction
			direction ? (DDRB |= (1 << pin)) : (DDRB &= ~(1 << pin));
			return SUCCESS ;	
		}
		case C : {
					 // deternine and set port direction
			direction ? (DDRC |= (1 << pin)) : (DDRC &= ~(1 << pin));
			return SUCCESS ;	
		}
		case D : {
					 // deternine and set port direction
			direction ? (DDRD |= (1 << pin)) : (DDRD &= ~(1 << pin));
			return SUCCESS ;	
		}
		default : {
			return PORT_NOT_FOUND_ERROR;	
		}
	}
}

// initiate port data
byte DIO_WRITE(port_t port, pin_t pin, bit_t bit){
	// determine port letter
	switch (port) {
		case A : {
					 // determine and set port data
			bit ? (PORTA |= (1 << pin)) : (PORTA &= ~(1 << pin));
			return SUCCESS ;	
		}
		case B : {
					 // determine and set port data
			bit ? (PORTB |= (1 << pin)) : (PORTB &= ~(1 << pin));
			return SUCCESS ;	
		}
		case C : {
					 // determine and set port data
			bit ? (PORTC |= (1 << pin)) : (PORTC &= ~(1 << pin));
			return SUCCESS ;	
		}
		case D : {
					 // determine and set port data
			bit ? (PORTD |= (1 << pin)) : (PORTD &= ~(1 << pin));
			return SUCCESS ;	
		}
		default : {
			return PORT_NOT_FOUND_ERROR;	
		}
	}
}

// read port data
byte DIO_READ(port_t port, pin_t pin, bit_t* bit){
	// determine port letter
	switch (port) {
		case A : {
					 // put data into bit
			*bit = (PORTA & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		case B : {
					 // put data into bit
			*bit = (PORTB & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		case C : {
					 // put data into bit
			*bit = (PORTC & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		case D : {
					 // put data into bit
			*bit = (PORTD & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		default : {
			return PORT_NOT_FOUND_ERROR;	
		 }
	}
}

// read pin state
byte DIO_STATE(port_t port, pin_t pin, bit_t* bit){
	// determine port letter
	switch (port) {
		case A : {
					 // put pin state into pin
			*bit = (PINA & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		case B : {
					 // put pin state into pin
			*bit = (PINB & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		case C : {
					 // put pin state into pin
			*bit = (PINC & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		case D : {
					 // put pin state into pin
			*bit = (PIND & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		default : {
			return PORT_NOT_FOUND_ERROR;	
		}
	}
}

// swap port data
byte DIO_TOGGLE(port_t port, pin_t pin){
	// determine port letter
	switch (port) {
		case A:{
				   // swap bit 
			PORTA ^= (1 << pin);
			return SUCCESS ;	
		}
		case B:{
				   // swap bit 
			PORTB ^= (1 << pin);
			return SUCCESS ;	
		}
		case C:{
				   // swap bit 
			PORTC ^= (1 << pin);
			return SUCCESS ;	
		}
		case D:{
				   // swap bit 
			PORTD ^= (1 << pin);
			return SUCCESS ;	
		}
		default:{
			return PORT_NOT_FOUND_ERROR;	
		}
	}
}


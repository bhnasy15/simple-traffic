#include "dio.h"

byte DIO_INIT(port_t port, pin_t pin, direction_t direction){
	switch (port) {
		case A : {
			direction ? (DDRA |= (1 << pin)) : (DDRA &= ~(1 << pin));
			return SUCCESS ;	
		}
		case B : {
			direction ? (DDRB |= (1 << pin)) : (DDRB &= ~(1 << pin));
			return SUCCESS ;	
		}
		case C : {
			direction ? (DDRC |= (1 << pin)) : (DDRC &= ~(1 << pin));
			return SUCCESS ;	
		}
		case D : {
			direction ? (DDRD |= (1 << pin)) : (DDRD &= ~(1 << pin));
			return SUCCESS ;	
		}
		default : {
			return ERROR;	
		}
	}
}

byte DIO_WRITE(port_t port, pin_t pin, bit_t bit){
	switch (port) {
		case A : {
			bit ? (PORTA |= (1 << pin)) : (PORTA &= ~(1 << pin));
			return SUCCESS ;	
		}
		case B : {
			bit ? (PORTB |= (1 << pin)) : (PORTB &= ~(1 << pin));
			return SUCCESS ;	
		}
		case C : {
			bit ? (PORTC |= (1 << pin)) : (PORTC &= ~(1 << pin));
			return SUCCESS ;	
		}
		case D : {
			bit ? (PORTD |= (1 << pin)) : (PORTD &= ~(1 << pin));
			return SUCCESS ;	
		}
		default : {
			return ERROR;	
		}
	}
}

byte DIO_READ(port_t port, pin_t pin, bit_t* bit){
	switch (port) {
		case A : {
			*bit = (PORTA & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		case B : {
			*bit = (PORTB & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		case C : {
			*bit = (PORTC & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		case D : {
			*bit = (PORTD & (1 << pin)) >> pin;
			return SUCCESS;
		 }
		default : {
			return ERROR;
		 }
	}
}

byte DIO_STATE(port_t port, pin_t pin, bit_t* bit){
	switch (port) {
		case A : {
			*bit = (PINA & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		case B : {
			*bit = (PINB & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		case C : {
			*bit = (PINC & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		case D : {
			*bit = (PIND & (1 << pin))>>pin;
			return SUCCESS ;	
		}
		default : {
			return ERROR;	
		}
	}
}

byte DIO_TOGGLE(port_t port, pin_t pin){
	switch (port) {
		case A:{
			PORTA ^= (1 << pin);
			return SUCCESS ;	
		}
		case B:{
			PORTB ^= (1 << pin);
			return SUCCESS ;	
		}
		case C:{
			PORTC ^= (1 << pin);
			return SUCCESS ;	
		}
		case D:{
			PORTD ^= (1 << pin);
			return SUCCESS ;	
		}
		default:{
			return ERROR;	
		}
	}
}


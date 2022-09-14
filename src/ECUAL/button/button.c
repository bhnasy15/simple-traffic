
#include "button.h"

byte BUTTON_INIT(button_t button){
	return DIO_INIT(button.port, button.pin, IN);
}

byte BUTTON_STATE(button_t button, bit_t* bit){
	return DIO_STATE(button.port, button.pin, bit);
}


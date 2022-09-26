
#include "button.h"

// initialize button to input
byte BUTTON_INIT(button_t button){
	return DIO_INIT(button.port, button.pin, IN);
}

// read button state
byte BUTTON_STATE(button_t button, bit_t* bit){
	return DIO_STATE(button.port, button.pin, bit);
}


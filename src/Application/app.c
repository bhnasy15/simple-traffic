#include "app.h"

/*********************************************/
// consts
/*********************************************/
// time of each color cycle
const int cycle = 5;
// delay of blinking light
const int delay = 400;
/*********************************************/

/*********************************************/
// status variables
/*********************************************/
bit_t is_car = 1;
bit_t is_ped = 0;
int tic = 1;
/*********************************************/

/*********************************************/
// hardware difinition
/*********************************************/
led_t car[3] = {
	{.port = A , .pin = _0}, // green
	{.port = A , .pin = _1}, // yellow
	{.port = A , .pin = _2} // red
};

led_t ped[3] = {
	{.port = B , .pin = _0}, // green
	{.port = B , .pin = _1}, // yellow
	{.port = B , .pin = _2} // red
};

button_t walk_btn = { .port = D, .pin = _2 };
bit_t is_pressed ;
bit_t is_down ;
/*********************************************/

/*********************************************/
// function difinition
/*********************************************/


/*********************************************/
// initialize all hardware
/*********************************************/
byte APP_INIT(){
	for (int i = 0; i < sizeof(car)/sizeof(car[0]); i++) {
		LED_INIT(car[i]);
	}
	for (int i = 0; i < sizeof(ped)/sizeof(ped[0]); i++) {
		LED_INIT(ped[i]);
	}

	BUTTON_INIT(walk_btn);
}

/*********************************************/
// main loop
/*********************************************/

byte APP_LOOP(){

	BUTTON_STATE(walk_btn, &is_down);
	if(is_down){
		delay_ms(300);
		BUTTON_STATE(walk_btn, &is_down);
		is_pressed = !is_down;
	}
	// number of loops = cycle / delay

	// after every cycle >> yellow
	if((tic % (int) (cycle*1000/delay)) == 0) yellow();
	
	// only check button if not pedesterian mode

	if(is_car) green();
	
	if(!is_car) red();
	
	tic++; delay_ms(delay);

}

/*********************************************/
// transition fuction
// called every cycle apart form yellow
/*********************************************/
void swap(){
	// reset all lights to OFF
	for (int i = 0; i < sizeof(car)/sizeof(car[0]); i++) { LED_OFF(car[i]); }
	for (int i = 0; i < sizeof(ped)/sizeof(ped[0]); i++) { LED_OFF(ped[i]); }

	// do a full cycle of yellow
	for (int i = 0; i < (int) (cycle*1000/delay); i++) {
		// if button is not pressed toggle the input list only
		if(!is_pressed) {
			LED_TOGGLE(car[YELLOW]);
			delay_ms(delay);

			BUTTON_STATE(walk_btn, &is_down);
			if(is_down){
				delay_ms(300);
				BUTTON_STATE(walk_btn, &is_down);
				is_pressed = !is_down;
			}
		}

		// if button is pressed toggle all yellow lights
		if(is_pressed) { 
			LED_TOGGLE(car[YELLOW]); LED_TOGGLE(ped[YELLOW]);
			delay_ms(delay);
		}
	}
	// exit with black
	LED_OFF(car[1]); LED_OFF(ped[1]); 
}

/*********************************************/
// yellow light
// if ped mode blink both lights
// else only blink car light
/*********************************************/
void yellow(){
	if( is_ped){
		swap();
	}
	if( !is_ped){
		swap();
	}
	is_car = ! is_car;
	is_ped = is_pressed;
}

/*********************************************/
// green light 
/*********************************************/
void green(){
	// initial state
	LED_ON(car[GREEN]);
	LED_OFF(car[RED]);

	LED_ON(ped[RED]);

	// if button is pressed >> ped->red is on
	if(is_pressed){
		//complete GREEN cycle with ped->red on
		while ((tic % (int) (cycle*1000/delay)) != 0) {
			LED_ON(car[GREEN]);
			LED_OFF(car[RED]);
			LED_ON(ped[RED]);
			tic++;
			delay_ms(delay);
		}
		swap();
		is_car = 0;
		is_ped = 1;
		tic = 1;
		is_pressed = 0;
	}
}

/*********************************************/
// red light 
/*********************************************/
void red(){
		LED_ON(car[RED]);
		LED_OFF(car[GREEN]);

		if(is_ped) LED_ON(ped[GREEN]);

		// if pressed -> ped mode
		if(is_pressed){
			is_car = 0;
			is_ped = 1;
			tic = 1;
			is_pressed = 0;
		}
}
/*********************************************/

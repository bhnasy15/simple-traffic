
#include "main.h"

void swap(led_t*, int);
int main(void){

	const int cycle = 5;
	const int delay = 400;
	// 1 = GO , 0 = sTOP
	bit_t is_car = 1;
	bit_t is_ped = 0;
	bit_t was_ped = 0;
	int tic = 0;

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

	for (int i = 0; i < sizeof(car)/sizeof(car[0]); i++) {
		LED_INIT(car[i]);
	}
	for (int i = 0; i < sizeof(ped)/sizeof(ped[0]); i++) {
		LED_INIT(ped[i]);
	}

	BUTTON_INIT(walk_btn);

	// green -> yellow -> red -> yellow -> green ...
	
	void swap(led_t *led, int size){
		for (int i = 0; i < sizeof(car)/sizeof(car[0]); i++) {
			LED_OFF(car[i]);
		}
		for (int i = 0; i < sizeof(ped)/sizeof(ped[0]); i++) {
			LED_OFF(ped[i]);
		}
		for (int i = 0; i < (int) (cycle*1000/delay); i++) {
			
			if(!is_pressed) for (int x = 0; x < size; x++) { LED_TOGGLE(led[x]); }
			if(is_pressed) { LED_TOGGLE(car[1]); LED_TOGGLE(ped[1]); }

			delay_ms(delay);
			if( !is_pressed && !is_ped) BUTTON_STATE(walk_btn, &is_pressed);
		}
		// exit with black
		LED_OFF(car[1]); LED_OFF(ped[1]); 
	}

	while(1){
		tic++;
		delay_ms(delay);
		if((tic % (int) (cycle*1000/delay)) == 0){
			if( is_ped){
				led_t next[2] = { car[1], ped[1]};
				swap(next, sizeof(next)/sizeof(next[0]));
				was_ped = 1;
			}
			if( !is_ped){
				led_t next[1] = { car[1]};
				swap(next, sizeof(next)/sizeof(next[0]));
				was_ped = 0;
			}
			is_car = ! is_car;
			is_ped = is_pressed;
		}

		if( !is_pressed && !is_ped) BUTTON_STATE(walk_btn, &is_pressed);

		if(is_car){
			LED_ON(car[0]);
			LED_OFF(car[2]);

			if( was_ped) LED_ON(ped[2]);

			if(is_pressed){
				//complete GREEN cycle with ped(red) on
				while ((tic % (int) (cycle*1000/delay)) != 0) {
					LED_ON(car[0]);
					LED_OFF(car[2]);
					LED_ON(ped[2]);
					tic++;
					delay_ms(delay);
				}
				led_t next[2] = { car[1], ped[1]};
				swap(next, sizeof(next)/sizeof(next[0]));
				is_car = 0;
				is_ped = 1;
				tic = 1;
				is_pressed = 0;
			}
		}
		if(!is_car){
			LED_ON(car[2]);
			LED_OFF(car[0]);

			if(is_ped) LED_ON(ped[0]);

			if(is_pressed){
				//led_t next[2] = { car[1], ped[1]};
				//swap(next, sizeof(next)/sizeof(next[0]));
				is_car = 0;
				is_ped = 1;
				tic = 1;
				is_pressed = 0;
			}
		}
	}



}

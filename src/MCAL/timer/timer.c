
#include "timer.h"

const unsigned long long CPU_F = 16000000;

byte delay_ms(unsigned long delay){

	timer_t _timer;

	if( get_delay(delay, T_1, &_timer) != SUCCESS)
		return ERROR;

	timer_mode(_timer.mode);

	for (unsigned long i = 0; i < _timer.cycle; i++) {
		while( !(TIFR & 1) );
		TIFR |= 1;
	}

	timer_mode(STOP);

	return SUCCESS;
}

/*********************************************/
// calculate number of cycles and timer mode
/*********************************************/
byte get_delay(unsigned long delay , timer_mode_t mode, timer_t* timer){
	// unsigned long = 4294967295
	// count = delsy * f / (  1000 * cycle );
	switch (mode) {
		case STOP :{ return ERROR;}
		case T_1 : {
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL );

			if(c > 4000000000UL) get_delay(delay, T_8, timer);

			timer->cycle = c; 	timer->mode = T_1;

			return SUCCESS;
		}
		case T_8 : {
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 8UL );

			if(c > 4000000000UL) get_delay(delay, T_64, timer);

			timer->cycle = c; 	timer->mode = T_8;

			return SUCCESS;
		}
		case T_64 : {
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 64UL );

			if(c > 4000000000UL) get_delay(delay, T_256, timer);

			timer->cycle = c; 	timer->mode = T_64;

			return SUCCESS;
		}
		case T_256 : {

			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 256UL );

			if(c > 4000000000UL) get_delay(delay, T_1024, timer);

			timer->cycle = c; 	timer->mode = T_256;

			return SUCCESS;
		}
		case T_1024 : {

			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 1024UL);

			if(c > 4000000000UL) return ERROR;

			timer->cycle = c; 	timer->mode = T_1024;

			return SUCCESS;
		}
		default : {return ERROR;}
	}
}
	
void timer_mode(timer_mode_t mode){
	// reset to stop 
 	TCCR0 &= ~(0x07);
	// set
	TCCR0 |= mode;
}


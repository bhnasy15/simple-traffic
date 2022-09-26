
#include "timer.h"

const unsigned long long CPU_F = 16000000;

// get and register delay form the user
byte delay_ms(unsigned long delay){

	// initialize a simple timer container
	timer_t _timer;

	// determine timer state and cyle count
	if( get_delay(delay, T_1, &_timer) != SUCCESS)
		return CAN_NOT_SET_TIMER;

	// set timer mode
	timer_mode(_timer.mode);

	// run counter
	for (unsigned long i = 0; i < _timer.cycle; i++) {
		while( !(TIFR & 1) );
		TIFR |= 1;
	}

	// stop timer
	timer_mode(STOP);

	return SUCCESS;
}

/*********************************************/
// calculate number of cycles and timer mode
/*********************************************/
byte get_delay(unsigned long delay , timer_mode_t mode, timer_t* timer){
	// unsigned long = 4294967295
	// count = delsy * f / (  1000 * cycle );
	// determine timer status
	switch (mode) {
		case STOP :{ return TIMER_STOPPED;}
		case T_1 : {
					   // calculate number of cycles
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL );

						// check cycle count
			if(c > 4000000000UL) get_delay(delay, T_8, timer);

						// set timer mode and cycle count
			timer->cycle = c; 	timer->mode = T_1;

			return SUCCESS;
		}
		case T_8 : {
					   // calculate number of cycles
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 8UL );

						// check cycle count
			if(c > 4000000000UL) get_delay(delay, T_64, timer);

						// set timer mode and cycle count
			timer->cycle = c; 	timer->mode = T_8;

			return SUCCESS;
		}
		case T_64 : {
					   // calculate number of cycles
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 64UL );

			if(c > 4000000000UL) get_delay(delay, T_256, timer);

						// set timer mode and cycle count
			timer->cycle = c; 	timer->mode = T_64;

			return SUCCESS;
		}
		case T_256 : {

					   // calculate number of cycles
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 256UL );

			if(c > 4000000000UL) get_delay(delay, T_1024, timer);

						// set timer mode and cycle count
			timer->cycle = c; 	timer->mode = T_256;

			return SUCCESS;
		}
		case T_1024 : {

					   // calculate number of cycles
			unsigned long c = ( delay * CPU_F) / ( 1000UL * 256UL * 1024UL);

						// check cycle count
			if(c > 4000000000UL) return ERROR;

						// set timer mode and cycle count
			timer->cycle = c; 	timer->mode = T_1024;

			return SUCCESS;
		}
		default : {return CAN_NOT_SET_TIMER;}
	}
}
	
// set timer mode
void timer_mode(timer_mode_t mode){
	// reset to stop 
 	TCCR0 &= ~(0x07);
	// set to mo
	TCCR0 |= mode;
}


#ifndef APP_H
#define APP_H


#include "../Util/util.h"
#include "../MCAL/dio/dio.h"
#include "../MCAL/timer/timer.h"
#include "../ECUAL/led/led.h"
#include "../ECUAL/button/button.h"

enum color {
	GREEN 	= 0,
	YELLOW 	= 1,
	RED 	= 2
};

void swap();

byte APP_INIT();
byte APP_LOOP();

void green();
void yellow();
void red();

#endif


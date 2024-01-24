/*
 * My_System_Lib.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Admin
 */
#include <EVSELab_System.h>

//Delay 1ms unit

void System_Delay(uint16_t delay_time_ms)
{
	uint32_t tickstart = SYSTIMER_GetTickCount();
	uint32_t wait = delay_time_ms;
	while ((SYSTIMER_GetTickCount() - tickstart) < wait)
	{
	}
}

_Bool Delay_100us(uint32_t Delay_time)
{
	static uint32_t delay_100us_count = 0;
	if( delay_100us_count < Delay_time){
		delay_100us_count++;
		return false;
	}
	else{
		delay_100us_count = 0;
		return true;
	}
}

_Bool Delay_100ms(uint32_t Delay_time)
{
	static uint32_t time_100us_count = 0;
	static uint32_t delay_100ms_count = 0;
	if( time_100us_count < 1000U) time_100us_count++;
	else {
		time_100us_count = 0;
		delay_100ms_count++;
	}

	if( delay_100ms_count < Delay_time)
		return false;
	else{
		delay_100ms_count = 0;
		return true;
	}
}






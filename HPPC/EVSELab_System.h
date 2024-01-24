/*
 * My_System_Lib.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Admin
 */

#ifndef EVSELAB_SYSTEM_H_
#define EVSELAB_SYSTEM_H_
#include "DAVE.h"

void System_Delay(uint16_t delay_time_ms);
_Bool Delay_100us(uint32_t Delay_time);
_Bool Delay_100ms(uint32_t Delay_time);

void Update_Dead_Time_CCU8_Channel_1(uint32_t deadtime_ns);



#endif /* EVSELAB_SYSTEM_H_ */

/*
 * Fridge_300W.h
 *
 *  Created on: Dec 26, 2022
 *      Author: ADMIN
 */

#ifndef FRIDGE_300W_H_
#define FRIDGE_300W_H_
#include "DAVE.h"
#include <Fixed_point_math.h>

typedef enum{
	/*--------------Normal Charge Operating Modes ---------------*/
	Idle_Mode  				  = 0x00,
	Battery_Check 			  = 0x01,
	Soft_start_Mode 		  = 0x02,
	Hand_Shake_Mode 		  = 0x03,
	Wait_For_CC_Mode 		  = 0x04,
	CC_Mode_PFM 			  = 0x05,
	CC_Mode_PWM 			  = 0x06,
	CV_Mode_PWM 			  = 0x07,
	CV_Mode_PFM				  = 0x08,
	Fully_Charged 			  = 0x09,
	CC_Mode_HPPC 			  = 0x0A,
	Soft_start_Mode_HPPC 	  = 0x0B,
	Fully_discharged		  = 0x0C,

	/*-------------- MSCC Operating Modes ---------------*/

	Soft_start_Mode_MSCC	  = 0x0D,
	CC_Mode_PWM_MSCC		  = 0x0E,
	CC_Mode_PWM_MSCC_1        = 0x0F,
	CC_Mode_PWM_MSCC_2 		  = 0x10,
	CC_Mode_PWM_MSCC_3        = 0x11,
	CC_Mode_PWM_MSCC_4        = 0x12,

	/*--------------Normal Discharge Operating Modes---------------*/
	Open_Loop 				  = 0xD0,
	Discharge_Soft_start_Mode = 0xD1,
	Discharge_CC_Mode_PWM     = 0xD2,

	/*--------------------Operating Error Modes--------------------*/
	Reverse_Polarity 		  = 0xE0,
	Over_Primary_Current	  = 0xE1,
	Over_Output_Voltage 	  = 0xE2,
	Over_Temperature          = 0xE3,
	Over_Power 				  = 0xE4,
	Low_Input_Voltage_Protect = 0xE5,
	Derate_75_Percent_Current = 0xE6,
	Derate_50_Percent_Current = 0xE7,
	Derate_25_Percent_Current = 0xE8,
	Grid_Off				  = 0xE9,
	Over_Input_Voltage		  = 0xEA,
	Over_Charge_Current		  = 0xEB,
	Over_Discharge_Current	  = 0xEC


} Operating_Mode;
#define Tz  						2.0e-5f  //ZOH frequency is 40k kHz
#define V_BAT_GAIN					0.00505f
#define V_IN_GAIN					0.01343f
#define I_BAT_GAIN					7.4e-4f
#define ADC_IBAT_OFFSET				1671U

#define V_BAT_HIGH_LIMIT  			4.75f    //Volts
#define V_IN_HIGH_LIMIT 			10.0f    //Volts
#define V_IN_LOW_LIMIT				5.0f	 //Volts
#define I_BAT_CHARGE_HIGH_LIMIT		1.79f	 //Amps
#define I_BAT_DISCHARGE_HIGH_LIMIT	1.236f	 //Amps
#define V_BAT_LOW_LIMIT     		2.7f	 //Volts

#define DUTY_DISCHARGE_HIGH_LIMIT   0.99f
#define DUTY_DISCHARGE_LOW_LIMIT    0.0f

#define DUTY_CHARGE_HIGH_LIMIT  	0.99f
#define DUTY_CHARGE_LOW_LIMIT    	0.0f

#define I_BAT_CHARGE_REF  			1.0f     //Amps
#define I_BAT_CHARGE_REF_1          0.8f	 //Amps
#define I_BAT_CHARGE_REF_2  		0.5f     //Amps
#define I_BAT_CHARGE_REF_3 			0.3f     //Amps
#define I_BAT_CHARGE_REF_4          0.2f	 //Amps

#define I_BAT_DISCHARGE_REF  		-1.0f     //Amps

#define V_BAT_REF  					4.2f    //Volts
#define V_BAT_REF_MSCC				4.25f	//Volts
#define I_BAT_FULL					0.25f	//Amps


void Check_Protection(Operating_Mode *Charging_Mode, uint16_t ADC_Vbat, uint16_t ADC_Ibat, uint16_t ADC_Vin);
void Check_Charging_Mode(Operating_Mode *Charging_Mode, uint16_t ADC_Vbat, uint16_t ADC_Ibat, uint16_t ADC_Vin);

void Set_CC_CV_Control_Mode(Operating_Mode *Charging_Mode, uint16_t ADC_Vbat, uint16_t ADC_Ibat);
void Set_Voltage_Loop(Operating_Mode* Charging_Mode, uint16_t ADC_Vbat, int *f_I_vol);
void Set_Current_Loop_PI_Charge(Operating_Mode *Charging_Mode, uint16_t ADC_Ibat, uint16_t f_I_ref);
void Set_Current_Loop_PI_Discharge(Operating_Mode *Charging_Mode, uint16_t ADC_Ibat);
void Set_Discharge_CC_Control(Operating_Mode *Charging_Mode, int f_I_ref, uint16_t ADC_Ibat);

void System_Initialize(void);
void Update_Duty(int f_Duty);
void Restart_PWM(void);
void Stop_PWM(void);
#endif /* FRIDGE_300W_H_ */

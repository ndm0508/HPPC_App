/*
 * Fridge_300W.c
 *
 *  Created on: Dec 26, 2022
 *      Author: ADMIN
 */

#ifndef LIBRARIES_XMCLIB_SRC_FRIDGE_300W_C_
#define LIBRARIES_XMCLIB_SRC_FRIDGE_300W_C_
#include "Fridge_300W.h"
extern uint16_t seconds_counter;
extern uint16_t ADC_Vbat_Average_32768_Cycles, ADC_Ibat_Average_32768_Cycles;
void Check_Protection(Operating_Mode *Charging_Mode, uint16_t ADC_Vbat, uint16_t ADC_Ibat, uint16_t ADC_Vin)
{
//	const uint16_t ADC_Vbat_High_Limit = (uint32_t)(V_BAT_HIGH_LIMIT / V_BAT_GAIN);
//	const uint16_t ADC_Ibat_Charge_High_Limit = ADC_IBAT_OFFSET + (uint32_t)(I_BAT_CHARGE_HIGH_LIMIT / I_BAT_GAIN);
//	const uint16_t ADC_Ibat_Discharge_High_Limit = ADC_IBAT_OFFSET - (uint32_t)(I_BAT_DISCHARGE_HIGH_LIMIT / I_BAT_GAIN);
//	const uint16_t ADC_Vin_High_Limit = (uint32_t)(V_IN_HIGH_LIMIT / V_IN_GAIN);
//
//
////	/*---------------Check all protection conditions--------------*/
////	if( ADC_Vbat > ADC_Vbat_High_Limit ){    /* Over Output Voltage Protect */
////		Stop_PWM();
////		*Charging_Mode = Over_Output_Voltage;
////	}
////
////	else if ( ADC_Ibat > ADC_Ibat_Charge_High_Limit && seconds_counter){  /* Over Power Protect */
////		Stop_PWM();
////		*Charging_Mode = Over_Charge_Current;
////	}
////
////	else if ( ADC_Ibat < ADC_Ibat_Discharge_High_Limit && seconds_counter){  /* Over Power Protect */
////		Stop_PWM();
////		*Charging_Mode = Over_Discharge_Current;
////	}
////
////	else if ( ADC_Vin > ADC_Vin_High_Limit) { /* Over Input Voltage Protect */
////		Stop_PWM();
////		*Charging_Mode = Over_Input_Voltage;
////	}
//
//	/*------------------------------------------------------------*/
//	return;
}

void Check_Charging_Mode(Operating_Mode *Charging_Mode, uint16_t ADC_Vbat, uint16_t ADC_Ibat, uint16_t ADC_Vin)
{
	/*-------------------Startup Modes Check----------------------*/
	/**
	 * Soft start when output relay turn off (no load)
	 * When output voltage of charger higher than battery, stop PWM
	 * Wait for voltage on output capacitors decrease lower than battery voltage, turn on output relay
	 */
	const uint16_t ADC_Vin_low_limit = (uint16_t)(V_IN_LOW_LIMIT / V_IN_GAIN);
	const uint16_t ADC_Vbat_low_limit = (uint16_t)(V_BAT_LOW_LIMIT / V_BAT_GAIN);
	const uint16_t ADC_Vbat_CV_Mode = (uint32_t)(V_BAT_REF / V_BAT_GAIN);
	const uint16_t ADC_Vbat_MSCC_Mode= (uint32_t)(V_BAT_REF_MSCC/V_BAT_GAIN);
	const uint16_t ADC_Ibat_Fully_Charged = (uint32_t)(I_BAT_FULL / I_BAT_GAIN) + ADC_IBAT_OFFSET;

	/*----------------- CC-CV Charging mode ------------------*/
	if( *Charging_Mode == CV_Mode_PWM && ADC_Ibat_Average_32768_Cycles < ADC_Ibat_Fully_Charged )
	{
		Stop_PWM();
		*Charging_Mode = Fully_Charged;
	}
	else if ( *Charging_Mode == CC_Mode_PWM && ADC_Vbat_Average_32768_Cycles > ADC_Vbat_CV_Mode )
		*Charging_Mode = CV_Mode_PWM;

	else if ( *Charging_Mode == Soft_start_Mode && ADC_Vbat > ADC_Vbat_low_limit && (ADC_Vin > ADC_Vin_low_limit) )
	{
		DIGITAL_IO_SetOutputLow(&RELAY_IN_12);
		DIGITAL_IO_SetOutputHigh(&RELAY_OUT_8);
		*Charging_Mode = CC_Mode_PWM;
		 Restart_PWM();
	}
	/*----------------- HPPC ------------------*/
	else if ( *Charging_Mode == Soft_start_Mode_HPPC && ADC_Vbat > ADC_Vbat_low_limit && (ADC_Vin > ADC_Vin_low_limit))
	{
		DIGITAL_IO_SetOutputLow(&RELAY_IN_12);
		DIGITAL_IO_SetOutputHigh(&RELAY_OUT_8);
		*Charging_Mode = CC_Mode_HPPC;
		Restart_PWM();
	}
	else if( (*Charging_Mode == Discharge_Soft_start_Mode) && (ADC_Vbat > ADC_Vbat_low_limit) )
	{
		DIGITAL_IO_SetOutputHigh(&RELAY_IN_12);
		DIGITAL_IO_SetOutputHigh(&RELAY_OUT_8);
		*Charging_Mode = Discharge_CC_Mode_PWM;
		Restart_PWM();
	}
	else if((*Charging_Mode)==Discharge_CC_Mode_PWM && (ADC_Vbat<ADC_Vbat_low_limit))
	{
		Stop_PWM();
		*Charging_Mode=Fully_discharged;
	}
	else if(*Charging_Mode== Idle_Mode)
	{
		DIGITAL_IO_SetOutputLow(&RELAY_IN_12);
		Stop_PWM();
	}
	/*----------------- MSCC Charging mode ------------------*/
	else if ( *Charging_Mode == Soft_start_Mode_MSCC && ADC_Vbat > ADC_Vbat_low_limit && ADC_Vin > ADC_Vin_low_limit && ADC_Vbat < ADC_Vbat_CV_Mode )
	{
		DIGITAL_IO_SetOutputLow(&RELAY_IN_12);
		DIGITAL_IO_SetOutputHigh(&RELAY_OUT_8);
		*Charging_Mode = CC_Mode_PWM_MSCC;
		Restart_PWM();
	}
	else if ( *Charging_Mode == CC_Mode_PWM_MSCC && ADC_Vbat > ADC_Vbat_MSCC_Mode )
	{
		*Charging_Mode = CC_Mode_PWM_MSCC_1;
	}
	else if ( *Charging_Mode == CC_Mode_PWM_MSCC_1 && ADC_Vbat > ADC_Vbat_MSCC_Mode )
	{
		*Charging_Mode = CC_Mode_PWM_MSCC_2;
	}
	else if ( *Charging_Mode == CC_Mode_PWM_MSCC_2 && ADC_Vbat > ADC_Vbat_MSCC_Mode )
	{
		*Charging_Mode = CC_Mode_PWM_MSCC_3;
	}
	else if ( *Charging_Mode == CC_Mode_PWM_MSCC_3 && ADC_Vbat > ADC_Vbat_MSCC_Mode )
	{
		*Charging_Mode = CC_Mode_PWM_MSCC_4;
	}
	if( *Charging_Mode == CC_Mode_PWM_MSCC_4 && ADC_Vbat > ADC_Vbat_MSCC_Mode )
	{
		Stop_PWM();
		*Charging_Mode = Fully_Charged;
	}


	/*---------------------------------------------- --------------*/
	return;
}

void Set_CC_CV_Control_Mode(Operating_Mode *Charging_Mode, uint16_t ADC_Vbat, uint16_t ADC_Ibat)
{
	static int f_I_vol = TOFIX(I_BAT_CHARGE_REF, Q);
	static int f_I_vol_1 = TOFIX(I_BAT_CHARGE_REF_1,Q);
	static int f_I_vol_2 = TOFIX(I_BAT_CHARGE_REF_2,Q);
	static int f_I_vol_3 = TOFIX(I_BAT_CHARGE_REF_3,Q);
	static int f_I_vol_4 = TOFIX(I_BAT_CHARGE_REF_4,Q);

	/*-----------------Normal-Charging Modes Set------------------*/

	if( *Charging_Mode == CV_Mode_PWM || *Charging_Mode == Idle_Mode )
	{
		Set_Voltage_Loop(Charging_Mode, ADC_Vbat, &f_I_vol);
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol);
	}
	else if( *Charging_Mode == CC_Mode_PWM || *Charging_Mode == CV_Mode_PWM || *Charging_Mode == Idle_Mode || *Charging_Mode == CC_Mode_HPPC )
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol);

	else if ( *Charging_Mode == Discharge_CC_Mode_PWM || *Charging_Mode == Idle_Mode )
		Set_Current_Loop_PI_Discharge(Charging_Mode, ADC_Ibat);
	/*----------------- MSCC Charging mode ------------------*/
	else if (*Charging_Mode == CC_Mode_PWM_MSCC )
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol);
	else if (*Charging_Mode == CC_Mode_PWM_MSCC_1)
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol_1);
	else if (*Charging_Mode == CC_Mode_PWM_MSCC_2 )
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol_2);
	else if (*Charging_Mode == CC_Mode_PWM_MSCC_3 )
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol_3);
	else if (*Charging_Mode == CC_Mode_PWM_MSCC_4 )
		Set_Current_Loop_PI_Charge(Charging_Mode, ADC_Ibat, f_I_vol_4);

    /*------------------------------------------------------------*/
    return;
}

void Set_Voltage_Loop(Operating_Mode* Charging_Mode, uint16_t ADC_Vbat, int *f_I_vol)
{
	/*-----------------Floating-point constants-------------------*/
	const float KI_vol = 9000.0f;
	const float KI_vol_x_Tz = KI_vol*Tz;
	/*------------------------------------------------------------*/

	/*-----------------To Fixed-point constants-------------------*/
	const int f_KI_vol_x_Tz = TOFIX(KI_vol_x_Tz, Q);
	const int f_Vbat_gain = TOFIX(V_BAT_GAIN, Q);
	const int f_I_ref = TOFIX(I_BAT_CHARGE_REF, Q);
	const int f_I_full = TOFIX(I_BAT_FULL, Q);
	const int f_V_ref = TOFIX(V_BAT_REF, Q);
	/*------------------------------------------------------------*/
	if( *Charging_Mode == Idle_Mode)
		{
			*f_I_vol = TOFIX(I_BAT_CHARGE_REF, Q);
			return;
		}
	/*---------------PI controller--------------------------------*/
	int f_Vbat = FMULI(f_Vbat_gain, ADC_Vbat);
	int f_e_vol = f_V_ref - f_Vbat;
	*f_I_vol += FMUL(f_KI_vol_x_Tz, f_e_vol, Q);
	/*------------------------------------------------------------*/

	/*---------------Anti wind-up PI controller-------------------*/
	if (*f_I_vol > f_I_ref)
		*f_I_vol =  f_I_ref;
	else if (*f_I_vol < f_I_full)
		*f_I_vol = f_I_full;


	return;
}

void Set_Current_Loop_PI_Discharge(Operating_Mode *Charging_Mode, uint16_t ADC_Ibat)
{
	/*-----------------Floating-point constants-------------------*/
	const float KP_cur = 1.5f;
	const float KI_cur = 1000.0f;
	const float KI_cur_x_Tz = KI_cur*Tz;
	/*------------------------------------------------------------*/

	/*-----------------To Fixed-point constants-------------------*/
	const int f_KP_cur = TOFIX(KP_cur, Q);
	const int f_KI_cur_x_Tz = TOFIX(KI_cur_x_Tz, Q);
	const int f_Ibat_gain = TOFIX(I_BAT_GAIN, Q);
	const int f_Duty_higher_limit = TOFIX(DUTY_DISCHARGE_HIGH_LIMIT, Q);
	const int f_Duty_low_limit = TOFIX(DUTY_DISCHARGE_LOW_LIMIT, Q);
	const int f_Duty_init = f_Duty_higher_limit;

	const int f_I_ref = TOFIX(I_BAT_DISCHARGE_REF, Q);
	/*------------------------------------------------------------*/

	/*---------------------Static variables-----------------------*/
	static int f_I_cur, f_I_cur_old;
	/*------------------------------------------------------------*/
	if ( *Charging_Mode == Idle_Mode )
	{
		f_I_cur = 0;
		f_I_cur_old = 0;
		return;
	}
	/*---------------------PI controller--------------------------*/
	int Ibat_real = ADC_Ibat - ADC_IBAT_OFFSET-10 ;
	int f_Ibat = FMULI(f_Ibat_gain, Ibat_real);
	int f_e_cur = f_I_ref - f_Ibat ;
	int f_P_cur = FMUL(f_KP_cur, f_e_cur, Q);
	f_I_cur = f_I_cur + FMUL(f_KI_cur_x_Tz, f_e_cur, Q);

	int f_Duty = f_P_cur + f_I_cur + f_Duty_init;
	/*--------------------------- ---------------------------------*/

	/*---------------Anti wind-up PI controller-------------------*/
	if (f_Duty > f_Duty_higher_limit){
		f_I_cur = f_I_cur_old;
		f_Duty = f_Duty_higher_limit;
	}
	else if (f_Duty < f_Duty_low_limit){
		f_I_cur = f_I_cur_old;
		f_Duty = f_Duty_low_limit;
	}

	f_I_cur_old = f_I_cur;
	/*------------------------------------------------------------*/


	/*---------------------Update Duty Cycle----------------------*/
	Update_Duty(f_Duty);
	return;
	/*------------------------------------------------------------*/
}


void Set_Current_Loop_PI_Charge(Operating_Mode *Charging_Mode, uint16_t ADC_Ibat, uint16_t f_I_ref)
{

	/*-----------------Floating-point constants-------------------*/
	const float KP_cur = 0.1933;
	const float KI_cur = 159.7156;
	const float KI_cur_x_Tz = KI_cur*Tz;
	/*------------------------------------------------------------*/

	/*-----------------To Fixed-point constants-------------------*/
	const int f_KP_cur = TOFIX(KP_cur, Q);
	const int f_KI_cur_x_Tz = TOFIX(KI_cur_x_Tz, Q);
	const int f_Ibat_gain = TOFIX(I_BAT_GAIN, Q);
	const int f_Duty_higher_limit = TOFIX(DUTY_CHARGE_HIGH_LIMIT, Q);
	const int f_Duty_low_limit = TOFIX(DUTY_CHARGE_LOW_LIMIT, Q);

	/*------------------------------------------------------------*/

	/*---------------------Static variables-----------------------*/
	static int f_I_cur, f_I_cur_old;
	/*------------------------------------------------------------*/
	if ( *Charging_Mode == Idle_Mode )
		{
			f_I_cur = 0;
			f_I_cur_old = 0;
			return;
		}
	/*----------------PI controller-------------------------------*/
	int Ibat_real = ADC_Ibat - ADC_IBAT_OFFSET + 220U;
	int f_Ibat = FMULI(f_Ibat_gain, Ibat_real);
	int f_e_cur = f_I_ref - f_Ibat ;
	int f_P_cur = FMUL(f_KP_cur, f_e_cur, Q);
	f_I_cur = f_I_cur + FMUL(f_KI_cur_x_Tz, f_e_cur, Q);

	int f_Duty = f_P_cur + f_I_cur + f_Duty_low_limit;
	/*--------------------------- ---------------------------------*/

	/*---------------Anti wind-up PI controller-------------------*/
	if (f_Duty > f_Duty_higher_limit){
		f_I_cur = f_I_cur_old;
		f_Duty = f_Duty_higher_limit;
	}
	else if (f_Duty < f_Duty_low_limit){
		f_I_cur = f_I_cur_old;
		f_Duty = f_Duty_low_limit;
	}
	f_I_cur_old = f_I_cur;
	/*------------------------------------------------------------*/

	/*---------------------Update Duty Cycle----------------------*/
	Update_Duty(f_Duty);
	return;
	/*------------------------------------------------------------*/
}

void System_Initialize(void)
{
	/*-----------Reset static variables if reset charging mode----*/
	Operating_Mode Mode = Battery_Check;
	Set_CC_CV_Control_Mode(&Mode, 0, 0);
	/*------------------------------------------------------------*/
	Restart_PWM();
	Stop_PWM();

}

void Update_Duty(int f_Duty)
{
	const uint16_t period = PWM_CCU8_0.ccu8_slice_ptr->PR + 1U;
	uint32_t compare_val = (uint32_t)(f_Duty*period >> Q);
	PWM_CCU8_0.ccu8_slice_ptr->CR1S = (uint32_t)(period - compare_val);
	PWM_CCU8_0.ccu8_module_ptr->GCSS = (uint32_t)XMC_CCU8_SHADOW_TRANSFER_SLICE_1;
}

/*
 * Disable both high-side and low-side gate control pins
 * Solved at https://community.infineon.com/t5/XMC/Problems-with-symmetric-CCU-8-always-keep-a-pin-at-a-high-level-after-the-PWM/td-p/350719
 * In this case, P0.7 used as high-side, P0.6 used as low-side
 * Port control coding founded in 1222-1223/1337, XMC1300 Reference Manual
 */
void Stop_PWM(void)
{
	  PORT0->IOCR4 &= ~PORT0_IOCR4_PC6_Msk;
	  PORT0->IOCR4 |= 0x10 << PORT0_IOCR4_PC6_Pos; // Set 1XXXXB for output
	  PORT0->IOCR4 &= ~PORT0_IOCR4_PC7_Msk;
	  PORT0->IOCR4 |= 0x10 << PORT0_IOCR4_PC7_Pos; // Set 1XXXXB for output
	  PWM_CCU8_Stop(&PWM_CCU8_0);
}

void Restart_PWM(void)
{
	/*-------------------Set initial duty cycle-------------------*/
	Update_Duty(0U);
	/*------------------------------------------------------------*/
	PORT0->IOCR4 &= ~PORT0_IOCR4_PC6_Msk;
	PORT0->IOCR4 |= 0x15 << PORT0_IOCR4_PC6_Pos; // Set ALT Func 5 for PWM.
	PORT0->IOCR4 &= ~PORT0_IOCR4_PC7_Msk;
	PORT0->IOCR4 |= 0x15 << PORT0_IOCR4_PC7_Pos; // Set ALT Func 5 for PWM.
	PWM_CCU8_Start(&PWM_CCU8_0);
}
#endif /* LIBRARIES_XMCLIB_SRC_FRIDGE_300W_C_ */

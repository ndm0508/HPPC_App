/*
 * main.c
 *
 *  Created on: 2022 Dec 14 17:33:01
 *  Author: ADMIN
 */
#include <Fridge_300W.h>
#include "DAVE.h"                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "string.h"
#include "stdio.h"
#include <EVSELab_System.h>
#include "xmc1300.h"
/**

 * Voltage Loop Controller in nominal mode
 * Current Loop Controller when output avg current bigger than 15A

 */
char uart_transmit_buffer[100];
char uart_receive_buffer[1];
//uint32_t ampe_s;
uint16_t measure, test, Instant_Mode, Command_Mode ,seconds_counter, last_seconds_counter;
uint16_t ADC_Vbat_Average_32768_Cycles, ADC_Ibat_Average_32768_Cycles, ADC_Ibat_Non_Offset;
_Bool Update_Uart = true;
int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }
  System_Delay(1000);
  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  System_Initialize();
  //PWM_CCU8_Start(&PWM_CCU8_0);
  /* IN+ terminal connected to Resistor */


  /* Wait for pre-charge */
  //System_Delay(2000); //Delay 400ms

  /*-----ZOH_TIMER----------*/
  TIMER_Start(&ZOH_TIMER);


  UART_Receive(&UART_0, (uint8_t*)uart_receive_buffer, sizeof(uart_receive_buffer));

  while(1U)
  {
	  sprintf(uart_transmit_buffer,"Runtime = %ds, Vbat = %d, Ibat = %d, Mode %d\r\n", seconds_counter, ADC_Vbat_Average_32768_Cycles, ADC_Ibat_Non_Offset, Instant_Mode);
	  if(Update_Uart)
	  {
		  UART_Transmit(&UART_0, (uint8_t*)uart_transmit_buffer, strlen(uart_transmit_buffer));
		  Update_Uart = false;
	  }
  }
}

void ZOH_Handler()
{
	//MEASURE_TIMER.ccu4_slice_ptr->TCCLR = (uint32_t) CCU4_CC4_TCCLR_TCC_Msk; //Clear timer
	//static Operating_Mode Charging_Mode = Soft_start_Mode ;
	static Operating_Mode Charging_Mode=Idle_Mode ;
	static uint32_t ADC_Vbat_Sum_32768_Cycles = 0;
	static uint32_t ADC_Ibat_Sum_32768_Cycles = 0;
	static uint16_t Cycles_of_Average_Cal = 0U;
	static uint16_t Cycles_of_Seconds_Count = 0U;
	if ((Command_Mode == Soft_start_Mode) && (Charging_Mode != Soft_start_Mode) && (Charging_Mode != CC_Mode_PWM) && (Charging_Mode != CV_Mode_PWM) && (Charging_Mode != Fully_Charged))
		Charging_Mode = Command_Mode;
	else if ((Command_Mode == Discharge_Soft_start_Mode) && (Charging_Mode != Discharge_CC_Mode_PWM)&&(Charging_Mode!=Fully_discharged))
		Charging_Mode = Command_Mode;
	else if ((Command_Mode == Soft_start_Mode_HPPC) && (Charging_Mode != Soft_start_Mode_HPPC) && (Charging_Mode != CC_Mode_HPPC))
		Charging_Mode = Command_Mode;
	else if ((Command_Mode == Idle_Mode) && (Charging_Mode != Idle_Mode))
		Charging_Mode = Command_Mode;
	else if ((Command_Mode == Soft_start_Mode_MSCC) && (Charging_Mode != Soft_start_Mode_MSCC) && (Charging_Mode != CC_Mode_PWM_MSCC)&& (Charging_Mode != CC_Mode_PWM_MSCC_1)&& (Charging_Mode != CC_Mode_PWM_MSCC_2)&& (Charging_Mode != CC_Mode_PWM_MSCC_3)&& (Charging_Mode != CC_Mode_PWM_MSCC_4)&& (Charging_Mode != Fully_Charged))
		Charging_Mode = Command_Mode;

	uint16_t ADC_Vbat = ADC_MEASUREMENT_Vbat_sens_handle.group_handle->RES[ADC_MEASUREMENT_Vbat_sens_handle.ch_handle->result_reg_number];
	uint16_t ADC_Vin = ADC_MEASUREMENT_Vin_sens_handle.group_handle->RES[ADC_MEASUREMENT_Vin_sens_handle.ch_handle->result_reg_number];
	uint16_t ADC_Ibat = ADC_MEASUREMENT_Ibat_sens_handle.group_handle->RES[ADC_MEASUREMENT_Ibat_sens_handle.ch_handle->result_reg_number];

	Check_Protection(&Charging_Mode, ADC_Vbat, ADC_Ibat, ADC_Vin);
	Check_Charging_Mode(&Charging_Mode, ADC_Vbat, ADC_Ibat, ADC_Vin);
	Set_CC_CV_Control_Mode(&Charging_Mode, ADC_Vbat, ADC_Ibat);

	Instant_Mode = Charging_Mode;

	ADC_MEASUREMENT_0.global_handle->module_ptr->BRSMR |= (uint32_t)VADC_BRSMR_LDEV_Msk; //ADC start

	ADC_Vbat_Sum_32768_Cycles = ADC_Vbat_Sum_32768_Cycles + ADC_Vbat;
	ADC_Ibat_Sum_32768_Cycles = ADC_Ibat_Sum_32768_Cycles + ADC_Ibat;

	Cycles_of_Average_Cal++;
	if (Cycles_of_Average_Cal == 32768U)
	{
		ADC_Vbat_Average_32768_Cycles = ADC_Vbat_Sum_32768_Cycles >> 15;
		ADC_Ibat_Average_32768_Cycles = ADC_Ibat_Sum_32768_Cycles >> 15 ;
		if (ADC_Ibat_Average_32768_Cycles >= ADC_IBAT_OFFSET)
		{
			ADC_Ibat_Average_32768_Cycles = ADC_Ibat_Average_32768_Cycles + 220;
			ADC_Ibat_Non_Offset = (ADC_Ibat_Average_32768_Cycles - ADC_IBAT_OFFSET);
		}
		else if (ADC_Ibat_Average_32768_Cycles < ADC_IBAT_OFFSET)
		{
			ADC_Ibat_Non_Offset = (ADC_IBAT_OFFSET - ADC_Ibat_Average_32768_Cycles);
		}
		ADC_Vbat_Sum_32768_Cycles = 0;
		ADC_Ibat_Sum_32768_Cycles = 0;
		Cycles_of_Average_Cal = 0;
	}
	Cycles_of_Seconds_Count++;
	if (Cycles_of_Seconds_Count == 50000U)
	{

		seconds_counter++;
		Update_Uart = true;
		Cycles_of_Seconds_Count = 0;
	}
	//measure = MEASURE_TIMER.ccu4_slice_ptr->TIMER; // Get Timer value
}

void UART_End_of_Receive_Call_Back()
{
	UART_Receive(&UART_0, (uint8_t*)uart_receive_buffer, sizeof(uart_receive_buffer));
	Command_Mode = uart_receive_buffer[0];
}


/*
 * Fixed_point_math.c
 *
 *  Created on: Feb 25, 2023
 *      Author: ADMIN
 */
#include <Fixed_point_math.h>

//uint32_t FIX_Low_pass_filter(int f_input)
//{
//	const float wf = 6.28f*2.0f;
//	const float a = Tz*wf/(1+Tz*wf);
//
//	const int f_a = TOFIX(a, Q);
//
//	static int f_y_k_minus_1 = 0;
//	int f_y_k = 0;
//	f_y_k =  f_y_k_minus_1 -  FMUL(f_a, f_y_k_minus_1, 14) + FMUL(f_a, f_input, 14);
//	f_y_k_minus_1 = f_y_k;
//
//	return (uint32_t)f_y_k;
//}
//
//void Q2_Low_pass_filter(uint16_t *Input, uint16_t *Output, const uint16_t Cut_off_Frequency)
//{
//	const float wf = 6.28f*Cut_off_Frequency;
//	const float a = Tz*wf/(1+Tz*wf);
//
//	const int f_a = TOFIX(a, 2);
//	int f_input= TOFIX(*Input, 2);
//
//	static int f_y_k_minus_1 = 0;
//	int f_y_k = 0;
//	f_y_k =  f_y_k_minus_1 -  FMUL(f_a, f_y_k_minus_1, 14) + FMUL(f_a, f_input, 14);
//	f_y_k_minus_1 = f_y_k;
//
//	*Output = (uint16_t)TOFLT(f_y_k,2);
//}

/*
 * Fixed_point_math.h
 *
 *  Created on: Feb 25, 2023
 *      Author: ADMIN
 */

#include "DAVE.h"

#ifndef LIBRARIES_XMCLIB_FIX_POINT_MATH_H_
#define LIBRARIES_XMCLIB_FIX_POINT_MATH_H_

/* The basic operations perfomed on two numbers a and b
of fixed point q format returning the answer in q format */
#define FADD(a,b) ((a)+(b))
#define FSUB(a,b) ((a)-(b))
#define FMUL(a,b,q) (((a)*(b))>>(q))
#define FDIV(a,b,q) (((a)<<(q))/(b))

/* The basic operations where a is of fixed point q format and b is an integer */
#define FADDI(a,b,q) ((a)+((b)<<(q)))
#define FSUBI(a,b,q) ((a)-((b)<<(q)))
#define FMULI(a,b) ((a)*(b))
#define FDIVI(a,b) ((a)/(b))

/* convert a from q1 format to q2 format */
#define FCONV(a, q1, q2) (((q2)>(q1)) ? (a)<<((q2)-(q1)) : (a)>>((q1)-(q2)))

/* the general operation between a in q1 format and b in q2
format returning the result in q3 format */
#define FADDG(a,b,q1,q2,q3) (FCONV(a,q1,q3)+FCONV(b,q2,q3))
#define FSUBG(a,b,q1,q2,q3) (FCONV(a,q1,q3)-FCONV(b,q2,q3))
#define FMULG(a,b,q1,q2,q3) FCONV((a)*(b), (q1)+(q2), q3)
#define FDIVG(a,b,q1,q2,q3) (FCONV(a, q1, (q2)+(q3))/(b))

/* convert to and from floating point */
#define TOFIX(d, q) ((int)( (d)*(float)(1<<(q)) ))
#define TOFLT(a, q) ((float)(a) / (float)(1<<(q)))

#define PI					3.141592654f
#define Q					15U

uint32_t FIX_Low_pass_filter(int f_input);
void Q2_Low_pass_filter(uint16_t *Input, uint16_t *Output, const uint16_t Cut_off_Frequency);
#endif /* LIBRARIES_XMCLIB_FIXED_POINT_MATH_H_ */

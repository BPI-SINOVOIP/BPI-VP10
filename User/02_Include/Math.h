/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Math.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : Math library
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MATH_H__
#define __MATH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"


/* Q format define ---------------------------------------------------------------------------------*/
#define _Q4(A)                          (int16)(A * 16)
#define _Q7(A)                          (int16)(A * 128)
#define _Q8(A)                          (int16)(A * 256)
#define _Q9(A)                          (int16)(A * 512)                            // Q9 format
#define _Q10(A)                         (int16)(A * 1024)                           // Q10 format
#define _Q11(A)                         (int16)(A * 2048)							// Q11 format
#define _Q12(A)                         (int16)(A * 4096)							// Q12 format
#define _Q13(A)                         (int16)(A * 8192)							// Q13 format
#define _Q14(A)                         (int16)(A * 16384)							// Q14 format
#define _Q15(A)                         (int16)(A * 32768)							// Q15 format
#define _Q16(A)							(int16)(A * 65536)							// Q16 format value
#define _Q27(A)                         (int32)((int32)A * 32767 * 4096)            // Q27 format

#define PI_Q12                          (12868L)


/* Electrical angle definitions */
#define DEGREE_0                        (short)(0)
#define DEGREE_30                       (short)(5461)
#define DEGREE_60                       (short)(10922)
#define DEGREE_90                       (short)(16384)
#define DEGREE_120                      (short)(21845)
#define DEGREE_180                      (short)(32767)
#define DEGREE_240                      (short)(-21845)
#define DEGREE_300                      (short)(-10922)
#define DEGREE_480                      (long)(87831)


//Get absolute value
#define ABS(A)      (((A)>=0) ? (A) : (-(A)))

//Get minimum of parameters A and B
#define MIN(A,B)    (((A)<(B))? (A) : (B))

//Get maximum of parameters A and B
#define MAX(A,B)    (((A)>(B))? (A) : (B))

//Lower limit
#define MINLMT(A,Min) (((A)<(Min))? (Min) : (A))

//Upper limit
#define MAXLMT(A,Max) (((A)>(Max))? (Max) : (A))

//Upper and lower limits
#define MAX_MIN_LMT(A,Pos,Neg)  MAX(MIN(A,Pos),Neg)

//Get sign
#define Sign_NP(A)  (((A)>=0) ? 1 : -1)


/*************************************************************************************///External Function
extern int16 SinCalc(int16 Theta, uint16 Vs);
extern int16 CosCalc(int16 Theta, uint16 Vs);
extern int32 TanCalc(int16 Theta);
extern int16 Abs_F16(int16 value);
extern int32 Abs_F32(int32 value);
extern int32 Log2_32(int32 x);
extern int32 Log2_64(uint64 x);
extern float InvSqrt(float x);
extern uint32 Sqrt_32(uint32 M);
extern uint32 Sqrt_64(uint64 M);
extern float MagicCubeRoot(float x);
extern uint32 CubeRoot_U32(uint32 x);
extern uint32 CubeRoot_U64(uint64 x);
extern int64 Mul_64_32(int64 x, int32 y);

#ifdef __cplusplus
}
#endif

#endif
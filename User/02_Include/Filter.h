/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Filter.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : General-purpose filters
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FILTER_H__
#define __FILTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "math.h"


/*************************************************************************************///External Function
// 1st low pass filter
#define INLPF_Q_SHIFT						(15)
#define pi_Q15								(102944)


// Allocated memory size (bytes)
#define LPFILT_MEM_SIZE						( 44 )  // LowPassFiltTypedef memory size
#define POSLPFILT_MEM_SIZE					( 36 )  // PosLowPassFiltTypedef memory size
#define AVGFILT_MEM_SIZE					( 526 ) // AvgFiltTypedef memory size



typedef struct LowPassFiltTypedef_t LowPassFiltTypedef;
typedef struct PosLowPassFiltTypedef_t PosLowPassFiltTypedef;
typedef struct AvgFiltTypedef_t AvgFiltTypedef;


/*---------------------------------------------------------------------------
 * Name		:	LowPassFilt_Init
 * Input	:	memory_buffer - Externally preallocated memory of size LowPassFiltTypedef
 *				freq - Filter cutoff frequency
 *				sampFreq - Filter update frequency
 * Output	:	Pointer to the configured LowPassFiltTypedef instance
 * Description:	Initialize the low-pass filter: y(n) = b0 * x(n) + b1 * x(n-1) - a1 * y(n-1)
 *---------------------------------------------------------------------------*/
extern LowPassFiltTypedef* LowPassFilt_Init(void* memory_buffer, int32 freq, int32 sampFreq);


/*---------------------------------------------------------------------------
 * Name		:	LowPassFilt_realize
 * Input	:	p - Pointer to the low-pass filter instance returned by LowPassFilt_Init on success
 *				Input - Filter input value x(n)
 * Output	:	Filter output value y(n)
 * Description:  Compute the filter output for the next time step; call this function at fixed time intervals	
 *				y(n) = b0 * x(n) + b1 * x(n-1) - a1 * y(n-1)
 *---------------------------------------------------------------------------*/
extern int32 LowPassFilt_realize(LowPassFiltTypedef* p, int32 Input);


/*---------------------------------------------------------------------------
 * Name		:	LowPassFilt_Clr
 * Input	:	p - Pointer to the low-pass filter instance returned by LowPassFilt_Init on success
 * Output	:	None
 * Description: Reset the filter
 *---------------------------------------------------------------------------*/
extern void LowPassFilt_Clr(LowPassFiltTypedef* p);


/*---------------------------------------------------------------------------
 * Name		:	PosLowPassFilt_Init
 * Input	:	memory_buffer - Externally preallocated memory of size PosLowPassFiltTypedef
 *				freq - Filter cutoff frequency
 *				sampFreq - Filter update frequency
 * Output	:	Pointer to the configured PosLowPassFiltTypedef instance
 * Description:	Initialize the low-pass filter.
 *---------------------------------------------------------------------------*/
extern PosLowPassFiltTypedef* PosLowPassFilt_Init(void* memory_buffer, int32 freq, int32 sampFreq);


/*---------------------------------------------------------------------------
 * Name		:	PosLowPassFilt_realize
 * Input	:	p - Pointer to the low-pass filter instance returned by PosLowPassFilt_Init on success
 *				Input - Filter input value x(n)
 * Output	:	Filter output value y(n)
 * Description:  Compute the filter output for the next time step; call this function at fixed time intervals
 *				PosLowPassFilt will take slightly more computation time than LowPassFilt
 *				y(n) = ( x(n) - y(n-1) ) / K + y(n-1)
 *---------------------------------------------------------------------------*/
extern int32 PosLowPassFilt_realize(PosLowPassFiltTypedef* p, int32 Input);


/*---------------------------------------------------------------------------
 * Name		:	PosLowPassFilt_Clr
 * Input	:	p - Pointer to the low-pass filter instance returned by PosLowPassFilt_Init on success
 * Output	:	None
 * Description: Reset the filter
 *---------------------------------------------------------------------------*/
extern void PosLowPassFilt_Clr(PosLowPassFiltTypedef* p);


/*---------------------------------------------------------------------------
 * Name		:	AvgFilt_Init
 * Input	:	memory_buffer - Externally preallocated memory of size AvgFiltTypedef
 *				filtSize - Filter depth is (1 << filtSize)
 * Output	:	Pointer to the configured AvgFiltTypedef instance
 * Description:	Initialize the moving average filter.
 *---------------------------------------------------------------------------*/
extern AvgFiltTypedef* AvgFilt_Init(void* memory_buffer, uint16 filtSize);


/*---------------------------------------------------------------------------
 * Name		:	AvgFilt_realize
 * Input	:	p - Pointer to the AvgFilt instance returned by AvgFilt_Init on success
 *				Input - Filter input value x(n)
 * Output	:	Filter output value y(n)
 * Description:  Compute the filter output for the next time step; call this function at fixed time intervals
 *				y(n) = [x(n)+x(n−1)+x(n−2)+...+x(n−N+1)] / N
 *---------------------------------------------------------------------------*/
extern int16 AvgFilt_realize(AvgFiltTypedef* p, int16 Input);


/*---------------------------------------------------------------------------
 * Name		:	AvgFilt_Clr
 * Input	:	p - Pointer to the smoothing filter instance returned by AvgFilt_Init on success
 * Output	:	None
 * Description: Reset the filter
 *---------------------------------------------------------------------------*/
extern void AvgFilt_Clr(AvgFiltTypedef* p);

#ifdef __cplusplus
}
#endif

#endif
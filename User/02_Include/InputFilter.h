/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : InputFilter.h
 * Author        : Summer
 * Date          : 2023-09-20
 * Description   : Input filter (velocity feedback filter/position command filter)
 *
 * Record        :
 * V1.0, 2023-09-20, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __INPUTFILTER_H__
#define __INPUTFILTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Filter.h"


#define INF1POSREF							(0)   // Position command filter 1 
#define INF2POSREF							(1)   // Position command filter 2
#define INF1VELFEB							(2)   // Velocity feedback filter 1
#define INF2VELFEB							(3)   // Velocity feedback filter 2

/* Filter types */
#define INPUTFILTER_NOFILT					(0)
#define INPUTFILTER_LPF						(1)   // First-order low-pass
#define INPUTFILTER_AVF						(2)   // Moving average

/* Maximum depth for moving average filter */
#define MAX_INFILT_RANK						(8)

 /*************************************************************************************///External Function

typedef struct
{
	int16 Mode;							// Filter type
	int32 OutData;						// Stores output data
	
	PosLowPassFiltTypedef* LowFilter;	// First-order low-pass
	uint8 LowFilterMem[POSLPFILT_MEM_SIZE];
	uint16 LowFilterFreq;
	
	AvgFiltTypedef* AvgFilter;			// Moving average
	uint8 AvgFilterMem[AVGFILT_MEM_SIZE];
	uint16 AvgFiltSize;
} InputFilterTypedef;


typedef struct
{
	int16 Mode;                    // Filter type
	uint16 LpfK;
	uint16 FiltSize;
} HardInputFilterTypedef;

extern InputFilterTypedef InFilt1PosRef;
extern InputFilterTypedef InFilt2PosRef;

extern HardInputFilterTypedef HardInFilt1VelFeb;
extern HardInputFilterTypedef HardInFilt2VelFeb;


extern void InputFilter_Init(void);
extern void InputPosFilter_Init(InputFilterTypedef* p, uint8 Num);
extern void InputFilter_Clr(InputFilterTypedef* p);
extern int32 InputPosFilter_realize(int32 indata, InputFilterTypedef* p);
extern void InputFilter_Rst(void);

extern void HardVelFilter_Init(HardInputFilterTypedef* p, uint8 Num);
extern void HardVelFilter_Clr(HardInputFilterTypedef* p);

#endif
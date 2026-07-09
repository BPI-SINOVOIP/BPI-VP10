/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FreqDiv.h
 * Author        : Victor.jin
 * Date          : 2024-04-07
 * Description   : Frequency division output
 *
 * Record        :
 * V1.0, 2024-04-07, Victor.jin: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FREQDIV_H__
#define __FREQDIV_H__


#ifdef __cplusplus
extern "C"{
#endif

	
#include "fu7502.h"


/*************************************************************************************///External Function
typedef struct
{
	// QEPOUT
	uint8	OUT_SourceSel;			// Servo pulse output source selection
	uint8	OUT_PhaseSel;			// Output phase selection
	int8	OUT_PhaseFlag;			// Output phase flag
	uint8	OUT_Z_ModeSel;			// Z signal output mode selection
	uint8	OUT_Z_PolaritySel;		// Z signal polarity selection
	
	uint32	OUT_FreqDivPulse;		// Encoder divided output pulse count, i.e., pulses output per revolution/pole pitch
	int32	OUT_PulseDelta;			// Number of divided output pulses per interrupt cycle

	int32	OUT_PulseRemain;		// Remainder of divided output pulses per interrupt cycle
	int64	OUT_PulseDecimal;		// Divided output pulses per interrupt cycle including fractional part
	int32	OUT_PulseSum;			// Total number of encoder divided output pulses

	uint32	OUT_Z_PulseInterval;	// Interval count between Z signal output pulses
	int32   EncPos;
	int32   EncPosLatch;
	
} FreqDivTypedef;


extern FreqDivTypedef FreqDiv;

extern void FreqDiv_Init(void);
extern void FreqDiv_Handler(void);


#ifdef __cplusplus
}
#endif

#endif
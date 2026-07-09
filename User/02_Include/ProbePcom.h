/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ProbePcom.h
 * Author        : Summer
 * Date          : 2024-08-21
 * Description   : Probe and position compare output
 *
 * Record        :
 * V1.0, 2024-08-21, Summer: Created file
 */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __PROBEPCOM_H__
#define __PROBEPCOM_H__


#ifdef __cplusplus
extern "C"{
#endif

	
#include "fu7502.h"


/*! \brief If Touch Probe Input is enabled. */
#define FUNC_PROBE_ENABLED							(FUNC_PROBE1_ENABLED | FUNC_PROBE2_ENABLED)


#define PCOM_DELAY									( 4 )                               // Position compare output delay, 4 clock cycles


// Definition of PROBECONFIG
#define PROBE1EN									(0x0001) // 0 - probe 1 disabled; 1 - probe 1 enabled;
#define PROBE1MODE									(0x0002) // 0 - single trigger; 1 - continuous trigger;
#define PROBE1SIGNAL								(0x0004) // 0 - DI signal; 1 - Z signal;
#define PROBE1RISEEN								(0x0010) // 0 - rising edge not latched; 1 - rising edge latched;
#define PROBE1FALLEN								(0x0020) // 0 - falling edge not latched; 1 - falling edge latched;
#define PROBE2EN									(0x0100)
#define PROBE2MODE									(0x0200)
#define PROBE2SIGNAL								(0x0400)
#define PROBE2RISEEN								(0x1000)
#define PROBE2FALLEN								(0x2000)


// Definition of PCOM1CNTRL
#define PCOM1EN										(0x0001) // 0 - PCOM disabled; 1 - PCOM enabled;
#define PCOM1MODE									(0x0002) // 0 - fixed interval; 1 - table position;
#define PCOM1DIR									(0x000C) // 0 - reverse motion; 1 - forward motion; 2 - bidirectional motion; 


// Definition of PCOM1DIR
#define PCOMDIR1SHIFT								( 2 ) // Right shift by 2 bits
#define PCOMDIRNEG									(0x0001) // Reverse motion
#define PCOMDIRPOS									(0x0002) // Forward motion
#define PCOMDIRBOTH									(0x0003) // Bidirectional motion;


// Definition of PROBESTATUS
#define PROBE1ENSTA									(0x0001) // 0 - probe 1 disabled; 1 - probe 1 enabled;
#define PROBE1RISESTA								(0x0002) // 0 - probe 1 rising edge not executed; 1 - probe 1 rising edge executed;
#define PROBE1FALLSTA								(0x0004) // 0 - probe 1 falling edge not executed; 1 - probe 1 falling edge executed;
#define PROBE1TRIGTIMES								(0x00C0) // Total trigger count of probe 1
#define PROBE2ENSTA									(0x0100) // 0 - probe 2 disabled; 1 - probe 2 enabled;
#define PROBE2RISESTA								(0x0200) // 0 - probe 2 rising edge not executed; 1 - probe 2 rising edge executed;
#define PROBE2FALLSTA								(0x0400) // 0 - probe 2 falling edge not executed; 1 - probe 2 falling edge executed;
#define PROBE2TRIGTIMES								(0xC000) // Total trigger count of probe 2

#define PROBE1TRIGTIMESSHIFT						(0x0006) // Left shift amount for probe 1 total trigger count
#define PROBE2TRIGTIMESSHIFT						(0x000E) // Left shift amount for probe 2 total trigger count
	
	
typedef struct
{
	int32 ActPos;
	int32 PosMargin;
	int32 PosMarginPre;
} VelEstTypeDef;


typedef struct
{
	uint16 ProbeConfig;
	uint8 Probe1En;
	uint8 Probe2En;
	
#if FUNC_PROBE1_ENABLED
	uint8 Probe1OffFlag;
	uint8 Probe1TrigSigZ;
	uint8 Probe1TrigCon;
	uint8 Probe1TrigTimes;
#endif // #if FUNC_PROBE1_ENABLED

#if FUNC_PROBE2_ENABLED
	uint8 Probe2OffFlag;
	uint8 Probe2TrigSigZ;
	uint8 Probe2TrigCon;
	uint8 Probe2TrigTimes;
#endif // #if FUNC_PROBE2_ENABLED
} ProbeTypeDef;


typedef struct
{
	uint32 Pcom1Arr;
	int32 *pPcom1Start;
	int32 *pPcom1End;
	int32 Pcom1Offset;
	uint16 Pcom1Ctrl;
	uint8 Pcom1En;
	uint8 Pcom1Mode;
	uint8 Pcom1Dir;
	uint8 Pcom1Flag;
	uint16 Pcom1Width;
	uint16 EncABS;
} PcomTypeDef;

extern VelEstTypeDef mcVelEst;
extern ProbeTypeDef mcProbe;
extern PcomTypeDef mcPcom;

/*************************************************************************************///External Function

extern void Probe_Init(void);
extern void Probe_Update(void);
extern void PCOM_Init(void);
extern void PCOM_Update(void);
extern void ProbePCOM_realize(int ActPos, uint8 EncUpdate);


#ifdef __cplusplus
}
#endif

#endif
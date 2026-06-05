/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ProbePcom.h
 * Author        : Summer
 * Date          : 2024-08-21
 * Description   : 探针和位置比较输出
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


#define PCOM_DELAY									( 4 )                               // 位置比较输出延时，4个时钟周期


// Definition of PROBECONFIG
#define PROBE1EN									(0x0001) // 0 - 探针1不使能; 1 - 探针1使能;
#define PROBE1MODE									(0x0002) // 0 - 单次触发; 1 - 连续触发;
#define PROBE1SIGNAL								(0x0004) // 0 - DI信号; 1 - Z信号;
#define PROBE1RISEEN								(0x0010) // 0 - 上升沿不锁存; 1 - 上升沿锁存;
#define PROBE1FALLEN								(0x0020) // 0 -下降沿不锁存; 1 -下降沿锁存;
#define PROBE2EN									(0x0100)
#define PROBE2MODE									(0x0200)
#define PROBE2SIGNAL								(0x0400)
#define PROBE2RISEEN								(0x1000)
#define PROBE2FALLEN								(0x2000)


// Definition of PCOM1CNTRL
#define PCOM1EN										(0x0001) // 0 - PCOM不使能;1 - PCOM使能;
#define PCOM1MODE									(0x0002) // 0 - 固定间隔; 1 - 表格位置;
#define PCOM1DIR									(0x000C) // 0 - 反向运动; 1 - 正向运动; 2 - 正反向运动; 


// Definition of PCOM1DIR
#define PCOMDIR1SHIFT								( 2 ) // 右移2位
#define PCOMDIRNEG									(0x0001) // 反向运动
#define PCOMDIRPOS									(0x0002) // 正向运动
#define PCOMDIRBOTH									(0x0003) // 正反向运动;


// Definition of PROBESTATUS
#define PROBE1ENSTA									(0x0001) // 0 - 探针1不使能; 1 - 探针1使能;
#define PROBE1RISESTA								(0x0002) // 0 - 探针1上升沿未执行; 1 - 探针1上升沿已执行;
#define PROBE1FALLSTA								(0x0004) // 0 - 探针1下降沿未执行; 1 - 探针1下降沿已执行;
#define PROBE1TRIGTIMES								(0x00C0) // 探针1的触发总次数
#define PROBE2ENSTA									(0x0100) // 0 - 探针2不使能; 1 - 探针2使能;
#define PROBE2RISESTA								(0x0200) // 0 - 探针2上升沿未执行; 1 - 探针2上升沿已执行;
#define PROBE2FALLSTA								(0x0400) // 0 - 探针2下降沿未执行; 1 - 探针2下降沿已执行;
#define PROBE2TRIGTIMES								(0xC000) // 探针2的触发总次数

#define PROBE1TRIGTIMESSHIFT						(0x0006) // 探针1的触发总次数左移位数
#define PROBE2TRIGTIMESSHIFT						(0x000E) // 探针2的触发总次数左移位数
	
	
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

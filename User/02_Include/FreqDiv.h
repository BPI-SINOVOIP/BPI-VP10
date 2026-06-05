/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FreqDiv.h
 * Author        : Victor.jin
 * Date          : 2024-04-07
 * Description   : 分频输出
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
	uint8	OUT_SourceSel;			// 伺服脉冲输出来源选择
	uint8	OUT_PhaseSel;			// 输出相位选择
	int8	OUT_PhaseFlag;			// 输出相位标志位
	uint8	OUT_Z_ModeSel;			// Z信号输出模式选择
	uint8	OUT_Z_PolaritySel;		// Z信号极性选择
	
	uint32	OUT_FreqDivPulse;		// 编码器分频输出脉冲数，即一圈/极距输出的脉冲数
	int32	OUT_PulseDelta;			// 每个中断周期内分频输出的脉冲数

	int32	OUT_PulseRemain;		// 每个中断周期内分频输出的脉冲余数
	int64	OUT_PulseDecimal;		// 每个中断周期内分频输出的包含小数部分的脉冲数
	int32	OUT_PulseSum;			// 编码器分频输出脉冲总数

	uint32	OUT_Z_PulseInterval;	// Z信号输出脉冲间隔数
	
} FreqDivTypedef;


extern FreqDivTypedef FreqDiv;

extern void FreqDiv_Init(void);
extern void FreqDiv_Handler(void);


#ifdef __cplusplus
}
#endif

#endif

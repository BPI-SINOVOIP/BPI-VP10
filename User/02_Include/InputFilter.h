/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : InputFilter.h
 * Author        : Summer
 * Date          : 2023-09-20
 * Description   : 输入滤波器 (速度反馈滤波/位置命令滤波)
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


#define INF1POSREF							(0)   // 位置指令滤波1 
#define INF2POSREF							(1)   // 位置指令滤波2
#define INF1VELFEB							(2)   // 速度反馈滤波1
#define INF2VELFEB							(3)   // 速度反馈滤波2

/* 滤波器类型 */
#define INPUTFILTER_NOFILT					(0)
#define INPUTFILTER_LPF						(1)   // 一阶低通
#define INPUTFILTER_AVF						(2)   // 滑动平均

/* 滑动平均滤波器最大深度 */
#define MAX_INFILT_RANK						(8)

/*************************************************************************************///External Function

typedef struct
{
	int16 Mode;							// 滤波器类型
	int32 OutData;						// 保存输出参数
	
	PosLowPassFiltTypedef* LowFilter;	// 一阶低通
	uint8 LowFilterMem[POSLPFILT_MEM_SIZE];
	uint16 LowFilterFreq;
	
	AvgFiltTypedef* AvgFilter;			// 滑动平均
	uint8 AvgFilterMem[AVGFILT_MEM_SIZE];
	uint16 AvgFiltSize;
} InputFilterTypedef;


typedef struct
{
	int16 Mode;                    //滤波器类型
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
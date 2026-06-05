/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : SpdFeedForward.h
 * Author        : Summer
 * Date          : 2023-11-23
 * Description   : Velocity Feedforward 
 *
 * Record        :
 * V1.0, 2023-11-23, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __SPDFEEDFORWARD_H__
#define __SPDFEEDFORWARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h" 
#include "Filter.h"

/* ------ Speed FeedForward Type ------ */
#define VELFF_MODE_OFF					(0)			// 关闭
#define VELFF_MODE_DIFF					(1)			// 位置指令差分
#define VELFF_MODE_TRAJ					(2)			// 位置运动规划

/*************************************************************************************///External Function
typedef struct
{
	int16 Output;
	int32 Coef;
	LowPassFiltTypedef* Filter; 
	uint8 FilterMem[LPFILT_MEM_SIZE];
} SpdFFTypedef;

extern void SpdFF_Init(void);
extern int16 SpdFF_realize(int16 PosRefDiff);

extern SpdFFTypedef SpdFF;

#ifdef __cplusplus
}
#endif

#endif
/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ToqFeedForward.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : 转矩前馈
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __TOQFEEDFORWARD_H__
#define __TOQFEEDFORWARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h" 
#include "Filter.h"

/*************************************************************************************///External Function

/* ------ Speed FeedForward Type ------ */
#define TOQFF_MODE_OFF					(0)			// 关闭
#define TOQFF_MODE_CMDVEL               (1)			// 环路速度指令
#define TOQFF_MODE_CMDPOS               (2)			// 环路位置指令

#define TOQFDFWD_RANK					(0)
#define TOQFDFWDRS_RANK					(TOQFDFWD_RANK + 12 + 14 + 10) //


typedef struct
{
	int64 SpdToCurCoef;
	int32 SpdRefErr;
	int32 SpdRefLatch;
	LowPassFiltTypedef* Filter;
	uint8 FilterMem[LPFILT_MEM_SIZE];
	AvgFiltTypedef* AvgFilter;  // 滑动平均
	uint8 AvgFilterMem[AVGFILT_MEM_SIZE];
}ToqFdFwdTypedef;


extern ToqFdFwdTypedef ToqFdFwd;


extern void ToqFF_Init(void);
extern int16 ToqFF_realize(void);
extern void SpdErrCal_realize(void);
extern int64 ToqFF_GetSpdToCurCoef(void);

#ifdef __cplusplus
}
#endif

#endif
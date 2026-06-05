/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : CurrentBack.h
 * Author        : wynn.wang
 * Date          : 2025-01-46
 * Description   : Current Foldback.
 *
 * Record        :
 * V1.0, 2025-01-46, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __CURRENTBACK_H__
#define __CURRENTBACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Math.h"
#include "Filter.h"


/* ------ FeedBack Type ------ */
/* ------ 外部输入的变量 ------ */
typedef struct
{
	int32 Tdelay;                        // 峰值电流延迟时间 ms
	int32 Tc;                            // 时间常数 ms
	int16 DriveVal;                      // 持续电流值
	int16 PeakVal;                       // 峰值电流值
	int16 WarnThresHoldVal;              // 警告电流阈值
	int16 FaultThresHoldVal;             // 故障电流阈值
	int16 CurrMax;						// 电流阈值上限
	int16 CurrMin;						// 电流阈值下限
	uint16 CurCtrlFreq;					// 电流环频率
	const int16* pActualCurrent;              // 当前电流值
	const uint8* pFoldbackSon;				// 电流折返使能状态- 1：使能 0：禁止
	const uint8* pLoopEnable;                 // 电流环使能状态- 1：使能 0：禁止
} CurrBackCfgTypedef;


typedef struct CurrBackTypedf_t CurrBackTypedf;

/*************************************************************************************///External Function
extern CurrBackTypedf MotorCurrBack;

extern void CurrBackProtect_Init(CurrBackTypedf* p, CurrBackCfgTypedef * cfg);
extern void CurrBackProtect_Clr(CurrBackTypedf* p);
extern void CurrBackProtect_realize(CurrBackTypedf* p);
extern uint8 CurrBackProtect_Fault(CurrBackTypedf* p);
extern uint8 CurrBackProtect_Warn(CurrBackTypedf* p);

#ifdef __cplusplus
}
#endif

#endif
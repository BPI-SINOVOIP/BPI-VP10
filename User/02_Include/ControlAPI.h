/*
 * Copyright (c) 2026-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ControlAPI.h
 * Author        : Summer
 * Date          : 2026-05-11
 * Description   : This file contains all the API function used for Motor Control.
 *
 * Record        :
 * V1.0, 2026-05-11, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __CONTROLAPI_H__
#define __CONTROLAPI_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "fu7502.h"
#include "Math.h"
#include "PIControl.h"


typedef struct
{
	const uint32* pElecAngSW;
	const uint32* pElecAngMW;
	const int32* pEncRes;
	const int32* pAngToCnt;
	const uint8* pElecAngDir;

} ElecAngCalTypedef;



extern ElecAngCalTypedef ElecAngCal;


/*************************************************************************************///External Function

/*---------------------------------------------------------------------------
 * Name		:	ElecAngCal_realize
 * Input	:	PosSingle - 编码器值低32位
 *				PosMulti - 编码器值高32位
 * Output	:	电角度值
 * Description:	根据当前编码器计算电角度值
 *---------------------------------------------------------------------------*/
extern int16 ElecAngCal_realize(int32 PosSingle, int32 PosMulti);


/*---------------------------------------------------------------------------
 * Name		:	PI_Control_realize
 * Input	:	p - PIControlSimple 类型的有效PI控制实例指针
 *				Cmd - 目标控制值
 *				Act - 实际反馈值
 * Output	:	本次控制周期计算出的PI控制输出值
 * Description:	执行位置式PI控制算法：根据目标值与实际值的偏差计算比例项、
 *				积分项，累加后输出控制量
 *---------------------------------------------------------------------------*/
extern int16 PI_Control_realize(PIControlSimple* p, int16 Cmd, int16 Act);


/*---------------------------------------------------------------------------
 * Name		:	PI_Control_Clear
 * Input	:	p - PIControlSimple 类型的有效PI控制实例指针
 * Output	:	No
 * Description:	PI控制变量清零
 *---------------------------------------------------------------------------*/
extern void PI_Control_Clear(PIControlSimple* p);


/*---------------------------------------------------------------------------
 * Name		:	PI_Control_SetKiSum
 * Input	:	p - PIControlSimple 类型的有效PI控制实例指针
 *				kiSum - 要强制覆盖的PI控制内部积分累计项新值
 * Output	:	No
 * Description:	外部干预位置式PI控制的积分状态：主要用于控制过程中紧急
 *				复位/切换目标时消除积分饱和遗留值、调试阶段手动预加载合理积分量
 *---------------------------------------------------------------------------*/
extern void PI_Control_SetKiSum(PIControlSimple* p, int16 kiSum);


#ifdef __cplusplus
}
#endif

#endif
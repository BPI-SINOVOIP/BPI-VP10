/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ErrorCorrected.h
 * Author        : Zougi.Zou
 * Date          : 2024-12-18
 * Description   : Error corrected Function
 *
 * Record        :
 * V1.0, 2024-12-18, Zougi.Zou: Created file
 */

#ifndef __ERRORCORRECTED_H__
#define __ERRORCORRECTED_H__

#include "fu7502.h"
#include "Math.h"


#define MAX_POINTS					(64)


typedef struct
{
	int32 StartPos;							//开始位置
	int32 Interval;							//间隔距离
	int32 Protaty;							//位置循环周期
	int16 NumPoints;						//点数
	int8 En;							    //使能
	const int16* pPosErr;					//误差表地址
} ErrCorCfgTypedef;



/*---------------------------------------------------------------------------
 * Name		:	ErrorCorrection_Init
 * Input	:	cfg - 配置参数
 * Output	:	NO
 * Description:	Initial ErrorCorrection.
 *---------------------------------------------------------------------------*/
extern void ErrorCorrection_Init(const ErrCorCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	ErrorCorrection_realize
 * Input	:	position before ErrorCorrection
 * Output	:	position after ErrorCorrection
 * Description:	Correct positon base on ErrorCorrection table.
 *---------------------------------------------------------------------------*/
extern int32 ErrorCorrection_realize(int32 position);


#endif  //__ERRORCORRECTED_H__

/*** (C) Copyright 2011-2022 Fortior Technology Co., Ltd. ***/

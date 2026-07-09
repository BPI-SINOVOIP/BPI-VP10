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
	int32 StartPos;							//Start position
	int32 Interval;							//Interval distance
	int32 Protaty;							//Position cycle period
	int16 NumPoints;						//Number of points
	int8 En;							    //Enable
	const int16* pPosErr;					//Pointer to error table
} ErrCorCfgTypedef;



/*---------------------------------------------------------------------------
 * Name		:	ErrorCorrection_Init
 * Input	:	cfg - configuration parameters
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
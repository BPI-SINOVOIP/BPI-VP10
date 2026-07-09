/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : InertiaFrictionIdentify.h
 * Author        : wynn.wang
 * Date          : 2023-07-26
 * Description   : Inertia identification
 *
 * Record        :
 * V1.0, 2023-07-26, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __INERTIAFRICTIONIDENTIFY_H_
#define __INERTIAFRICTIONIDENTIFY_H_


#include "fu7502.h"
#include "Math.h"
#include "Customer.h"


typedef struct
{
	uint8  EstCtrl;
	uint16 SpeedStart;
	uint16 SpeedDelta;
	uint16 SpeedHigh;
	uint16 SpeedMin;
	uint16 Cur0_1;
	uint16 MaxLenSamp;
	uint32 Coff_J;
	const int16* pActVel;
	const int16* pCmdCur;

} InFricIdCfgTypedef;


/*---------------------------------------------------------------------------
 * Name		:	InFricId_Init
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize inertia identification
 *---------------------------------------------------------------------------*/
extern void InFricId_Init(InFricIdCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	InFricId_realize
 * Input	:	*pJm - inertia identification result
 * Output	:	Inertia identification status
 * Description:	Performs inertia identification; should be placed in the position-loop interrupt.
 *---------------------------------------------------------------------------*/
extern uint8 InFricId_realize(uint32* pJm);

#endif
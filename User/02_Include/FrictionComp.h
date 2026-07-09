/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FrictionComp.h
 * Author        : wynn.wang
 * Date          : 2024-08-01
 * Description   : Gravity/Friction Compensation
 *
 * Record        :
 * V1.0, 2024-08-01, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FRICTIONCOMP_H__
#define __FRICTIONCOMP_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"
#include "Filter.h"
#include "Customer.h"

/*************************************************************************************///External Function

typedef struct
{
	int16 PosVelDeadBand;
	int16 NegVelDeadBand;
	int16 PosVelValue;
	int16 NegVelValue;
	int16 PosCmpIq;
	int16 NegCmpIq;

	uint8 FricMod;
	uint8 FricVSrc;
	uint16 FricLpfHz;

	uint16 MaxSpeed;
	uint16 CurFileFreq;

	const int32* pTargetReftoSpd;
	const int16* pCmdVel;
	const int16* pActVel;
	const uint8* pRunMod;
	
} FriCmpCfgTypedef;


/*---------------------------------------------------------------------------
 * Name		:	FricCmp_Init
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize friction compensation
 *---------------------------------------------------------------------------*/
extern void FricCmp_Init(FriCmpCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	FricCmp_realize
 * Input	:	No
 * Output	:	Friction compensation current
 * Description:	Calculate the friction compensation current
 *---------------------------------------------------------------------------*/
extern int16 FricCmp_realize(void);


/*---------------------------------------------------------------------------
 * Name		:	FricCmp_Clr
 * Input	:	No
 * Output	:	No
 * Description:	Reset friction compensation
 *---------------------------------------------------------------------------*/
extern int16 FricCmp_Clr(void);

#ifdef __cplusplus
}
#endif

#endif
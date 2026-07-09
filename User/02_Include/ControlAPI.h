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
 * Input	:	PosSingle - Encoder value low 32 bits
 *				PosMulti - Encoder value high 32 bits
 * Output	:	Electrical angle value
 * Description:	Calculate the electrical angle based on the current encoder value
 *---------------------------------------------------------------------------*/
extern int16 ElecAngCal_realize(int32 PosSingle, int32 PosMulti);


/*---------------------------------------------------------------------------
 * Name		:	PI_Control_realize
 * Input	:	p - Valid PI control instance pointer of type PIControlSimple
 *				Cmd - Target control value
 *				Act - Actual feedback value
 * Output	:	PI control output value calculated for this control cycle
 * Description:	Execute positional PI control algorithm: calculate proportional and 
 *				integral terms based on the deviation between target and actual values, 
 *				then output the control quantity after accumulation
 *---------------------------------------------------------------------------*/
extern int16 PI_Control_realize(PIControlSimple* p, int16 Cmd, int16 Act);


/*---------------------------------------------------------------------------
 * Name		:	PI_Control_Clear
 * Input	:	p - Valid PI control instance pointer of type PIControlSimple
 * Output	:	No
 * Description:	Clear PI control variables
 *---------------------------------------------------------------------------*/
extern void PI_Control_Clear(PIControlSimple* p);


/*---------------------------------------------------------------------------
 * Name		:	PI_Control_SetKiSum
 * Input	:	p - Valid PI control instance pointer of type PIControlSimple
 *				kiSum - New value of internal integral accumulation term for PI control to be forcibly overwritten
 * Output	:	No
 * Description:	Externally intervene in the integral state of positional PI control: mainly used to eliminate 
 *				residual integral saturation values when emergency reset/switching targets during the control process, 
 *				or to manually preload reasonable integral amounts during the debugging stage
 *---------------------------------------------------------------------------*/
extern void PI_Control_SetKiSum(PIControlSimple* p, int16 kiSum);


#ifdef __cplusplus
}
#endif

#endif
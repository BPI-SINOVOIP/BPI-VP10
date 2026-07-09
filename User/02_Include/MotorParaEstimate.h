/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorParaEstimate.h
 * Author        : wynn.wang
 * Date          : 2024-12-02
 * Description   : Motor parameter identification
 *
 * Record        :
 * V1.0, 2024-12-02, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTORPARAESTIMATE_H_
#define __MOTORPARAESTIMATE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"
#include "Math.h"


typedef struct
{
	int16 Mode;
	int16 IAmp;
	uint16 RTime;
	uint16 LTime;
	int16 UMin;
	int16 UMax;
	int16 UDelta;
	int16 FreqMax; // Initial frequency
	int16 FreqMin;
	int16 FreqDelta;
	int16 IMinRatio;
	int16 CVMode;
	uint16 CurFileFreq;

	uint8* pFocThetaFlag;
	int16* pStatus;
	int16* pIdRef;
	int16* pIqRef;

	int16* pId;
	int16* pUd;
	int16* pUq;
	
} MotorEstCfgTypeDef;



/*---------------------------------------------------------------------------
 * Name		:	Motor_Identify_ParamInit
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize motor parameter identification
 *---------------------------------------------------------------------------*/
extern void Motor_Identify_ParamInit(MotorEstCfgTypeDef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	Motor_Identify_realize
 * Input	:	No
 * Output	:	No
 * Description:	Performs motor parameter identification; runs within 1 ms
 *---------------------------------------------------------------------------*/
extern void Motor_Identify_realize(void);


/*---------------------------------------------------------------------------
 * Name		:	Motor_Resistance_Identify_OpenLoop_realize
 * Input	:	No
 * Output	:	No
 * Description:	Resistance parameter identification (open-loop)
 *---------------------------------------------------------------------------*/
extern void Motor_Resistance_Identify_OpenLoop_realize(void);


/*---------------------------------------------------------------------------
 * Name		:	Motor_Resistance_Identify_ClosedLoop_realize
 * Input	:	No
 * Output	:	No
 * Description:	Resistance parameter identification (closed-loop)
 *---------------------------------------------------------------------------*/
extern void Motor_Resistance_Identify_ClosedLoop_realize(void);


/*---------------------------------------------------------------------------
 * Name		:	Motor_Inductance_Identify_realize
 * Input	:	No
 * Output	:	No
 * Description:	Inductance parameter identification
 *---------------------------------------------------------------------------*/
extern void Motor_Inductance_Identify_realize(void);


/*---------------------------------------------------------------------------
 * Name		:	Motor_Identify_realize_Isr
 * Input	:	No
 * Output	:	No
 * Description:	Performs motor parameter identification; to be placed in the carrier interrupt
 *---------------------------------------------------------------------------*/
extern void Motor_Identify_realize_Isr(void);


/*---------------------------------------------------------------------------
 * Name		:	Motor_Identify_GetFinishFlag
 * Input	:	No
 * Output	:	No
 * Description:	Returns the identification complete flag
 *---------------------------------------------------------------------------*/
extern uint8 Motor_Identify_GetFinishFlag(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : SoftControl.h
 * Author        : wynn.wang
 * Date          : 2025-04-20
 * Description   : Compliant control
 *
 * Record        :
 * V1.0, 2025-04-20, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __SOFTCONTROL_H__
#define __SOFTCONTROL_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "fu7502.h"
#include "Math.h"
#include "Filter.h"
#include "PIControl.h"
#include "ToqFeedForward.h"


/*************************************************************************************///External Function
/* ------ Soft Control Type ------ */
#define SC_MODE_OFF					(0)			// Off
#define SC_LOCAL_IMPEDANCE          (1)			// Impedance control (local)
#define SC_LOCAL_ADMITTANCE         (2)			// Admittance control (local)
#define SC_WorkMode                 ((int16)usSRegHoldBuf[SOFTCTRLWORMOD])

typedef struct
{
	uint16 WorkMode;
	int16 VelLimMax;
	int16 VelLimMin;
	int16 CurLimMax;
	int16 CurLimMin;
	int16 VelLmt;

	uint16 ForceConst;
	uint16 CurCoe;
	uint16 PeinPosRange;

	int16 RmsCurrent;
	int16 MotorMaxSpd;
	uint16 CurCtrlFreq;
	uint16 VelCtrlFreq;
	uint16 PosCtrlFreq;

	const uint16* pCompMode; // Mode for impedance control compensation of position error
	const int16* pActVel;
	const int16* pActCur;
	const int16* pSpdFF;
	const int32* pTargetRef;
	const int32* pThetaErr;
	const int32* pTargetReftoSpd;
	const uint32* pSKp;
	const uint32* pSKi;
	const uint32* pSKd;
	const int16* pSXPosCmd;
	const int16* pSXPosAct;
	const int16* pSXForceCmd;
	const int16* pSXForceAct;
} SoftCfgTypedef;



/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_Init
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize soft control
 *---------------------------------------------------------------------------*/
extern void FieldSoftControl_Init(SoftCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_PIDUpdate
 * Input	:	No
 * Output	:	No
 * Description:	Update PID gains for soft control
 *---------------------------------------------------------------------------*/
extern void FieldSoftControl_PIDUpdate(void);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_Clr
 * Input	:	No
 * Output	:	No
 * Description:	Reset soft control
 *---------------------------------------------------------------------------*/
extern void FieldSoftControl_Clr(void);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_realize
 * Input	:	thetaErr - position error
 * Output	:	speed command
 * Description:	Implement soft control and update the speed command
 *---------------------------------------------------------------------------*/
extern int16 FieldSoftControl_realize(int32 thetaErr);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_TiffCalc
 * Input	:	No
 * Output	:	current command
 * Description:	Compensation for elimination of positioning error in impedance control; current-loop scheduling
 *---------------------------------------------------------------------------*/
extern int16 FieldSoftControl_TiffCalc(void);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_AccActCalc
 * Input	:	No
 * Output	:	No
 * Description:	Update speed feedback increment
 *---------------------------------------------------------------------------*/
extern void FieldSoftControl_AccActCalc(void);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_GetSwToPosFlag
 * Input	:	No
 * Output	:	Flag indicating motor has stopped
 * Description:	Determine whether the motor has stopped but position error is large; if so, enable positioning compensation
 *---------------------------------------------------------------------------*/
extern uint8 FieldSoftControl_GetSwToPosFlag(void);


/*---------------------------------------------------------------------------
 * Name		:	FieldSoftControl_GetSwToPosDoneFlag
 * Input	:	No
 * Output	:	Impedance control positioning compensation flag
 * Description:	Get impedance control positioning compensation flag
 *---------------------------------------------------------------------------*/
extern uint8 FieldSoftControl_GetSwToPosDoneFlag(void);

#ifdef __cplusplus
}
#endif

#endif
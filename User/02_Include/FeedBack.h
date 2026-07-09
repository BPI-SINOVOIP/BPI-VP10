/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Feedback.h
 * Author        : wynn.wang
 * Date          : 2025-01-16
 * Description   : Full closed loop control Function
 *
 * Record        :
 * V1.0, 2025-01-16, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FEEDBACK_H__
#define __FEEDBACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Math.h"
#include "Filter.h"


// OnLoadFlag
#define FEEDBACK_MOTOR				( 0 )	// Motor feedback
#define FEEDBACK_LOAD				( 1 )   // Load feedback


// Q-format determined by outer loop resolution being lower than inner loop resolution
// otherwise the Q-format bit count must be modified
#define LOADCOEF                    ( 20 )
#define MOTORCOEF                   ( 10 )


/* ------ FeedBack Config Type ------ */
typedef struct
{
	const uint8* pMode;                   // Full closed-loop mode 0:inner 1:outer 2:switch (function code)
	const uint8* pPosLoopEnable;		  // Position loop enable flag	
	const int16* pMixErrClrRpm;           // Mix error clear turn count (function code)
	const uint32* pLoadFeedPulse;         // External encoder pulse count per motor revolution (function code)
	const int32* pMixErrMaxValue;         // Alarm when inner/outer loop deviation difference exceeds this value (function code)
	const int32* pLoadActualAngle;        // Outer loop real-time position
	const int32* pMotorActualAngle;		  // Inner loop real-time position
	const int32* pTargetAngle;
	const int32* pTargetRef;

	int32 LoadEncRes;				// Outer loop resolution
	int32 EncRes;					// Inner loop resolution
	int16 PosCtrlFreq;				// Position loop control frequency
	int16 LPFFreq;					// Outer loop vibration suppression filter

} FeedBackCfgTypedef;


/*************************************************************************************///External Function

/*---------------------------------------------------------------------------
 * Name		:	FeedBackOnLoad_Init
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize full closed-loop control
 *---------------------------------------------------------------------------*/
extern void FeedBackOnLoad_Init(const FeedBackCfgTypedef * cfg);


/*---------------------------------------------------------------------------
 * Name		:	FeedBackOnLoad_Clr
 * Input	:	No
 * Output	:	No
 * Description:	Reset full closed-loop control
 *---------------------------------------------------------------------------*/
extern void FeedBackOnLoad_Clr(void);


/*---------------------------------------------------------------------------
 * Name		:	FeedBackOnLoad_Update
 * Input	:	No
 * Output	:	No
 * Description:	Full closed-loop variable real-time update
 *---------------------------------------------------------------------------*/
extern void FeedBackOnLoad_Update();


/*---------------------------------------------------------------------------
 * Name     :   PosErrCalc_realize
 * Input    :   No
 * Output   :   position deviation
 * Description: Calculate mixed deviation. This function is always used to calculate position deviation regardless of full closed-loop enable status
 *---------------------------------------------------------------------------*/
extern int32 PosErrCalc_realize();


/*---------------------------------------------------------------------------
 * Name     :   FeedBackMixErrCheck
 * Input    :   No
 * Output   :   Mix error, used only for fault protection, not for closed-loop control.
 * Description: Mixed deviation monitoring. This function is always used to calculate position deviation regardless of full closed-loop enable status
 *---------------------------------------------------------------------------*/
extern int32 FeedBackMixErrCheck();


/*---------------------------------------------------------------------------
 * Name     :   LoadPosFdbCalc_realize
 * Input    :   NO
 * Output   :   outer loop velocity
 * Description: Calculate outer loop position feedback increment
 *---------------------------------------------------------------------------*/
extern int32 LoadPosFdbCalc_realize();


/*---------------------------------------------------------------------------
 * Name     :   Feedback_GetOnLoadFlag
 * Input    :   No
 * Output   :   Working loop flag: 1:working in outer loop, 0:working in inner loop.
 * Description: Get current working loop flag
 *---------------------------------------------------------------------------*/
extern uint8 Feedback_GetOnLoadFlag(void);


/*---------------------------------------------------------------------------
 * Name     :   Feedback_GetMixErrOverFlag
 * Input    :   No
 * Output   :   Mix error too large alarm flag
 * Description: GetMix error too large alarm flag
 *---------------------------------------------------------------------------*/
extern uint8 Feedback_GetMixErrOverFlag(void);


/*---------------------------------------------------------------------------
 * Name     :   Feedback_GetLoadToMotorCoef
 * Input    :   No
 * Output   :   Outer-to-inner loop conversion coefficient 
 * Description: GetOuter-to-inner loop conversion coefficient
 *---------------------------------------------------------------------------*/
extern int64 Feedback_GetLoadToMotorCoef(void);


/*---------------------------------------------------------------------------
 * Name     :   Feedback_GetMotorToLoadCoef
 * Input    :   No
 * Output   :   Inner-to-outer loop conversion coefficient
 * Description: GetInner-to-outer loop conversion coefficient
 *---------------------------------------------------------------------------*/
extern int64 Feedback_GetMotorToLoadCoef(void);

#ifdef __cplusplus
}
#endif

#endif
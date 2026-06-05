/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PhaseFind.h
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : define some function for phasefind.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


#ifndef __PHASEFIND_H_
#define __PHASEFIND_H_
/* Define to prevent recursive inclusion -------------------------------------*/

#include "fu7502.h"
#include "Hall.h"
#include "Math.h"

// The method to be used for the commutation phase finding
#define PHASEFIND_NORMALSTART						( 0 )
#define PHASEFIND_SMOOTHSTART						( 1 )
#define PHASEFIND_SOFTSTART							( 2 )
#define PHASEFIND_HALLLEARN							( 3 )
#define PHASEFIND_AUTOPHASE							( 8 )


// Autophase state machine
#define APSM_IDLE									( 0 )
#define APSM_SETID									( 1 )
#define APSM_DELAY									( 2 )
#define APSM_GOINIT									( 3 )
#define APSM_GOFORWARD								( 4 )
#define APSM_GOBACK									( 5 )
#define APSM_SETOFFSET								( 6 )
#define APSM_RESET									( 7 )
#define APSM_FINISH									( 8 )


// Phasefind Error
#define PFERR_TIMEOUT								( 1 )
#define PFERR_NOMOVE								( 2 )
#define PFERR_DIRERR								( 3 )  // ElecAng Direction Error
#define PFERR_TARANG								( 4 )  // Target Angle Too Small


typedef struct
{
	uint8 State;
	uint8 NextState;
	uint8 StartFlag;
	uint8 FinishFlag;
	int32 QepAngleComp;
	int32 QepAngleStart;
	int32 QepAngleMid;
	int32 QepAngleEnd;
	const int32* pQepAngle;
	int32 FOCThetaTarget;
	int32 FOCThetaValue;
	int32 ActualAngleLatch;
	int32 DeltaAngle;
	const int16* pActVel;
	int16 PhaseInc;
	uint16 TimeCounter;
	int16 FOCThetaInit;
	int16 FOCThetaSign;
	int16 FOCThetaDelta;
	uint16 TimeStamp;
	uint16 SuspendTime;
	int16  IdRef;
	int16  IdTarget;
	int16  IdStep;
	uint16 MoveLimit;
	uint16 WorkTime;
	uint16 Cnt;
  	uint8  Error;
  	uint8  ErrorCounter;
  	uint8  reserved[12];
}PhaseFindTypeDef;



typedef struct
{ 
    int16  FOCTheta;        // Elec Angle
    int16  FOCThetaPos;     // Elec Angle 
    int16  FOCThetaNeg;     // Elec Angle
    int16  ElecAngOffset;   // Elec Angle Offset
    uint8  FOCThetaFlag;    // 0: FOC__THETA = mcElecAng.FOCTheta
    uint8  ElecAngDir;      // 1: Encoder and ElecAng direction are different
    uint8  reserved[10];
}ElecAngTypeDef;


typedef void    ( *pvMotorPhaseFindStart ) ( void );

extern PhaseFindTypeDef             mcDoPhaseFind;
extern ElecAngTypeDef               mcElecAng;
extern pvMotorPhaseFindStart        pvMotor_PhaseFind_Start;

extern void Motor_PhaseFind_Init(void);
extern void Motor_PhaseFind_Update(void);
extern void Motor_PhaseFind(void);
extern void Motor_PhaseFind_NormalStart(void);
extern void Motor_AutoPhase(void);


/*---------------------------------------------------------------------------
 * Name		:	void Motor_PhaseFind_SmoothStart(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Sets commutation angle to 180 degrees and increases
 *              current until a movement of set electrical angle is detected.
 *              Divides the angle by half and repeats until no movement occurs
 *              at maximum current. 
 *---------------------------------------------------------------------------*/
extern void Motor_PhaseFind_SmoothStart(void);


#endif
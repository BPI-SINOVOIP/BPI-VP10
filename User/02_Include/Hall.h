/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Hall.h
 * Author        : Jamie
 * Date          : 2022-10-12
 * Description   : define some new method of Hall.
 *
 * Record        :
 * V1.0, 2022-10-12, Jamie: Created file
 */


#ifndef __HALL_H_
#define __HALL_H_
/* Define to prevent recursive inclusion -------------------------------------*/
#include "Parameter.h"

/*! \brief If Firmware do hall learning calculation is enabled. 0-Software do it; 1- Firmware do it. */
#define HALL_LEARN_CALCULATION_ENABLED					( 0 )

/* Hall pin definition */
#define HA_GPIO							(PB)
#define HA_PIN							(PIN3)
#define HA_OE							(PB_OE)
#define HA_PU							(PB_PU)

#define HB_GPIO							(PB)
#define HB_PIN							(PIN1)
#define HB_OE							(PB_OE)
#define HB_PU							(PB_PU)

#define HC_GPIO							(PB)
#define HC_PIN							(PIN4)
#define HC_OE							(PB_OE)
#define HC_PU							(PB_PU)


/* Electrical angle definitions */
#define DEGREE_SUM                      (uint32)(163840) // DEGREE_60 * 15


// Definition of register HALLMODE
#define HALLMODE_LEARNOK				(0x0080)          //
#define HALLMODE_DIR					(0x0008)          //
#define HALLMODE_HCINV					(0x0004)          //
#define HALLMODE_HBINV					(0x0002)          //
#define HALLMODE_HAINV                  (0x0001)          //

typedef struct
{
#if HALL_LEARN_CALCULATION_ENABLED	
	uint16 LearnHallTheta[6];              // Record electrical angle at Hall transition edges
	uint8 LearnHallStatus[6];             // Hall learning status
	int16 OffsetThetaPos;                 // Compensation angle offset (forward motion)
	int16 OffsetThetaNeg;                 // Compensation angle offset (reverse motion)
	uint8 LearnMoveDirFlag;               // Motion direction flag
#else	
	uint16 *pLearnHallTheta;              // Record electrical angle at Hall transition edges
	uint8* pLearnHallStatus;              // Hall learning status
#endif
	
	uint8 Error;                          // Fault type 1: all-zero condition detected
	uint8 HallStepCnt;                    // counter
	uint8 MCDivFlag;                      // Hall direction reversed
	uint8 Mode;                           // Hall relationship, corresponds to 6 Hall combinations
	uint8 ThetaCalcFlag;                  // Startup angle calibration flag
	uint8 LastHallStatus;                 // Previous angle Hall status
	uint8 NowHallStatus;                  // Current angle Hall status
	int16 FOCThetaStart;                  // Initial electrical angle
	int16 OffsetTheta;                    // Offset angle with compensation added
	
#if ENCODER_SEL_HALLSONLY_ENABLED > 0
	uint8 HallStatusPre;                 // Previous angle Hall status
	uint8 HallStatus;					 // Current angle Hall status
	uint8 LowSpeedStatus;				 // Low speed status; corresponds to Hall timer counter overflow or direction change, where correct angular velocity cannot be calculated
	int16 HallTheta;					 // Current Hall raw electrical angle
	int16 HallThetaOut;					 // Current Hall electrical angle with offset applied
	int16 HallAngle;					 // Hall interpolated angle intermediate value
	int32 HallAngleOut;					 // Hall interpolated angle
	int16 InterpltDltRef;				 // Hall interpolated angleincrement
	int16 InterpltDltRefLatch;			 // Hall interpolated angleincrement latch
	uint16 StillCounter;				 // Hall state change time counter
	uint16 StillPeriod;					 // Hall transition time sum
	uint16 StillPeriodLatch;			 // Hall transition time buffer
	int16 InterpltInputLatch;			 // Hall interpolation input buffer
	uint16 ExcCnt;						 // Hall interpolation time counter
	int32 InterpltOutput;				 // Hall interpolation output result
	int32 InterpltOutputLatch;			 // Hall interpolation output resultbuffer
	int32 InterpltOutputFlt;			 // Hall interpolation output resultfiltered
	int64 InterpltOutputFlt_k;			 // Low-pass filter intermediate value
	int16 InterpltOutputDelta;			 // Low-pass filter input, i.e. interpolated position differential
#endif
	
} HallTypeDef;

extern HallTypeDef mcHall;

extern void Hall_Init(void);
extern void DoHallLearning(void);
extern void UpdateHallPhaseMode(void);
extern int16 UpdateHallOffsetTheta(uint8 Dir);
extern void HallPinInit(void);
extern uint8 GetHallStatus();
extern uint8 GetHallStatus2(uint8 hallinput);
extern void UpdateHallTheta(void);
extern void UpdateHallTheta_Isr(void);
extern int32 UpdateHallsOnlyAngle(void);
extern int16 GetHallsOnlyElecAngle(void);

#endif

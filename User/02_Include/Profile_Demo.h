/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Profile_Demo.h
 * Author        : Summer
 * Date          : 2021-11-15
 * Description   : Base function for profile planning.
 *
 * Record        :
 * V1.0, 2021-11-15, Summer: Created file
 */

#ifndef __PROFILE_DEMO_H_
#define __PROFILE_DEMO_H_


#include <Myproject.h>


typedef struct
{
	int32 StartingAngle;
	uint16 TimeCounter;
	uint8 Flag;
	uint8 Flag_Pre;
	uint8 Dwell_En;
	uint8 ProfileAbsStep;            // Absolute motion phase
	uint8 ProfileAbsFlag;            // Absolute motion flag
	uint8 ProfileRndFlag;            // Reciprocating motion flag
	uint8 ProfileRepFlag;            // Repeat motion flag
	uint8 ProfileCurveType;			 // Profile curve selection 0: T-Curve  1: S-Curve
} ProfileDemoTypeDef;


extern ProfileDemoTypeDef mcProfile;


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Init(void)
/* Input	:	MoveDistance - Negative MoveDistance means moving in the opposite direction, unit: count
/*				MaxVel - Maximum Velocity, positive value, unit: mm/s or rpm
            	MaxAcc - Maximum Acceleration, positive value, unit: mm/s^2 or rps^s
/* Description:	Initialize T profile variable
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_Init(int8 CurveType, int32 MoveDistance, int16 MaxVel, int32 MaxAcc, int32 MaxJerk);


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Reset(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Initialize profile variable
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_Reset(void);

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Align(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Align profile variable
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_Align(void);
	
/*---------------------------------------------------------------------------*/
/* Name		:	int32 Motor_Profile_Move(void)
/* Input	:	NO
/* Output	:	Target Angle
/* Description:	Profile planning result, call this function every cycle time.
/*---------------------------------------------------------------------------*/
extern int32 Motor_Profile_Move(void);

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Update(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	run serial position.
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_Update(void);

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_StartDeceleration(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Start deceleration
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_StartDeceleration(void);

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_StartDeceleration(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Start deceleration
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_Clr(void);

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_TimeCount(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Position movement pause time check; place in the 1 ms loop.
/*---------------------------------------------------------------------------*/
extern void Motor_Profile_TimeCount(void);

#endif
/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Profile.h
 * Author        : Summer
 * Date          : 2021-11-15
 * Description   : Base function for profile planning.
 *
 * Record        :
 * V1.0, 2021-11-15, Summer: Created file
 */


#ifndef __PROFILE_H_
#define __PROFILE_H_

#include "fu7502.h"
#include "Math.h"


#define MAXSCALE			( 29 )
#define T_PROFILE			( 0 )
#define S_PROFILE			( 1 )


typedef enum {
	MS_IDLE = 0,
	MS_READY = 1,
	MS_MOVEING = 2,
	MS_FINISH = 3,
	MS_DECELERATION = 4,
	MS_SUSPEND = 5,
	MS_PLANFAILED = -1,
} MotionStatus_t;



/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_Planning(void)
 * Input	:	MoveDistance - Negative MoveDistance means moving in the opposite direction, unit: count
 *				MaxVel - Maximum Velocity, positive value, unit: count/cycle
 *            	MaxAcc - Maximum Acceleration, positive value, unit: count/cycle^2
 *				MaxJerk - Maximum Jerk, positive value, unit: count/cycle^3
 * Output	:	0 - No error
 * Description:	Initialize profile variable, need about 5ms. 
 *				Position_Profile_Planning for T profile.
 *				Position_Profile_Planning_S for S profile.
 *---------------------------------------------------------------------------*/
extern void Position_Profile_Planning(int32 MoveDistance, int64 MaxVel, int64 MaxAcc);

extern void Position_Profile_Planning_S(int32 MoveDistance, int64 MaxVel, int64 MaxAcc, int64 MaxJerk);


/*---------------------------------------------------------------------------
 * Name		:	int32 Position_Profile_Move(void)
 * Input	:	NO
 * Output	:	Target Angle
 * Description:	Profile planning result, call this function every cycle time.
 *				Position_Profile_Move for T profile.
 *				Position_Profile_Move_S for S profile.
 *---------------------------------------------------------------------------*/
extern int32 Position_Profile_Move(void);
	
extern int32 Position_Profile_Move_S(void);
	

/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_Reset(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Reset profile variable.
 *---------------------------------------------------------------------------*/
extern void Position_Profile_Reset();


/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_Align(int32 initPos)
 * Input	:	NO
 * Output	:	NO
 * Description:	Align to setting initAngle.
 *---------------------------------------------------------------------------*/
extern void Position_Profile_Align(int32 initPos);


/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_StartMove(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Start update profile. 
 *---------------------------------------------------------------------------*/
extern void Position_Profile_StartMove(void);



/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_StartDeceleration(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Profile Start Deceleration
 *---------------------------------------------------------------------------*/
extern void Position_Profile_StartDeceleration(void);



/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_TurnAround(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Profile start turn around and go to the reverse direction.
 *---------------------------------------------------------------------------*/
extern void Position_Profile_TurnAround(void);

	

/*---------------------------------------------------------------------------
 * Name		:	void Position_Profile_Clr(void)
 * Input	:	NO
 * Output	:	NO
 * Description:	Clear MotionStatus.
 *---------------------------------------------------------------------------*/
extern void Position_Profile_Clr(void);



/*---------------------------------------------------------------------------
 * Name		:	int32 Position_Profile_GetVel(int16 qepSpeedCoe)
 * Input	:	qepSpeedCoe
 * Output	:	profile velocity
 * Description:	Get profile velocity.
 *---------------------------------------------------------------------------*/
extern int32 Position_Profile_GetVel(int16 qepSpeedCoe);



/*---------------------------------------------------------------------------
 * Name     :   Position_Profile_GetMotionStatus
 * Input    :   No
 * Output   :   MotionStatus
 * Description: Get MotionStatus, 当前的状态
 *---------------------------------------------------------------------------*/
extern int8 Position_Profile_GetMotionStatus(void);



/*---------------------------------------------------------------------------
 * Name     :   Position_Profile_SetMotionStatus
 * Input    :   MotionStatus
 * Output   :   No
 * Description: Set MotionStatus, 当前的状态
 *---------------------------------------------------------------------------*/
extern void Position_Profile_SetMotionStatus(int8 motionStatus);


#endif
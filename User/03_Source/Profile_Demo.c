/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Profile_Demo.c
 * Author        : Summer
 * Date          : 2021-11-15
 * Description   : Base function for profile planning.
 *
 * Record        :
 * V1.0, 2021-11-15, Summer: Created file
 */


/* Includes -------------------------------------------------------------------------------------*/
#include "Profile_Demo.h"


ProfileDemoTypeDef mcProfile;

/*---------------------------------------------------------------------------*/
/* Name     :   DynTrap_Demo_Update
/* Input    :   CurveType - 0 : T profile; 1 : S profile.
/*				MoveDistance - Relative move distance, Negative MoveDistance means moving in the opposite direction, unit: count
/*				MaxVel - Maximum Velocity, positive value, unit: mm/s or rpm
/*				MaxAcc - Maximum Acceleration, positive value, unit: mm/s^2 or rps^2
/*				MaxJerk - Maximum Jerk, positive value, unit: mm/s^3 or rps^3
/* Output   :   NO
/* Description: Initialize T profile variable，运动曲线离线规划，规划计算大约需要3ms
/*---------------------------------------------------------------------------*/
void Motor_Profile_Init(int8 CurveType, int32 MoveDistance, int16 MaxVel, int32 MaxAcc, int32 MaxJerk)
{
	int32 encRes;
	int64 maxvel, maxacc, maxjerk;

#if FUNC_FEEDBACKONLOAD_ENABLED
	if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
	{
		encRes = ((int32)usSRegHoldBuf[SFBENCRES_H] << 16) | (uint16)usSRegHoldBuf[SFBENCRES_L];
	}
	else
#endif
	{
		encRes = ((int32)usSRegHoldBuf[ENCRES_H] << 16) | (uint16)usSRegHoldBuf[ENCRES_L];
	}
	encRes = (int64)encRes * 1000 / (((int32)usSRegHoldBuf[PITCH_H] << 16) | (uint16)usSRegHoldBuf[PITCH_L]);

	maxvel = ((int64)MaxVel << MAXSCALE) / PROFILE_FREQUENCY * encRes; // mm/s -> count/cycle; rps -> count/cycle
	maxacc = ((int64)MaxAcc << MAXSCALE) / PROFILE_FREQUENCY * encRes / PROFILE_FREQUENCY; // mm/s^2 -> count/cycle^2; rps^2 -> count/cycle^2
	maxjerk = ((int64)MaxJerk << MAXSCALE) / PROFILE_FREQUENCY * encRes / PROFILE_FREQUENCY / PROFILE_FREQUENCY; // mm/s^3 -> count/cycle^3; rps^3 -> count/cycle^3

	if (GetReg(usSRegHoldBuf[DRIVEMODE], MODE_MOTORTYPE)) // Rotary Motor
	{
		maxvel = maxvel / 60;   // rpm -> rps
	}

	if (maxvel < 1)
		maxvel = 1;
	if (maxacc < 1)
		maxacc = 1;
	if (maxjerk < 1)
		maxjerk = 1;

	if (CurveType)
	{
		Position_Profile_Planning_S(MoveDistance, maxvel, maxacc, maxjerk);
	}
	else
	{
		Position_Profile_Planning(MoveDistance, maxvel, maxacc);
	}

	mcProfile.Dwell_En = 0;
	
	Position_Profile_StartMove();
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Reset(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Reset profile variable
/*---------------------------------------------------------------------------*/
void Motor_Profile_Reset(void)
{
	Position_Profile_Reset();
	Motor_Profile_Align();
	Timer6_Reset(); // Reset pulse counter
	Delay_us(250); // 最少要等2个位置环周期
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Align(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Reset profile variable
/*---------------------------------------------------------------------------*/
void Motor_Profile_Align(void)
{
#if FUNC_FEEDBACKONLOAD_ENABLED
	if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
	{
		mcProfile.StartingAngle = ((int32)usSRegInBuf[SFBACTPOS_H] << 16) | (uint16)usSRegInBuf[SFBACTPOS_L];
	}
	else
#endif
	{
		mcProfile.StartingAngle = ((int32)usSRegInBuf[ACTPOS_H] << 16) | (uint16)usSRegInBuf[ACTPOS_L];
	}

	Position_Profile_Align(mcProfile.StartingAngle);
}


/*---------------------------------------------------------------------------*/
/* Name		:	int32 Motor_Profile_Move(void)
/* Input	:	NO
/* Output	:	Target Angle
/* Description:	Profile planning result, call this function every cycle time.
/*---------------------------------------------------------------------------*/
int32 Motor_Profile_Move(void)
{
	int32 targetAngle;
	
	if (Position_Profile_GetMotionStatus() == MS_IDLE)
	{
		Motor_Profile_Align();
	}
	
	if (mcProfile.ProfileCurveType)	// S-Curve
	{
		targetAngle = Position_Profile_Move_S();
	}
	else	// T-Curve
	{
		targetAngle = Position_Profile_Move();
	}
	
	return targetAngle;
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_Update(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	run serial position.
/*---------------------------------------------------------------------------*/
void Motor_Profile_Update(void)
{
	int32 profileMovDis = 0;             // 运动距离
	
	// 所有三种模式下，上位机点开始运动Motion这位都会置一，点停止运动Motion都会清零
	mcProfile.Flag_Pre = GetReg(mcRegParam.ProfileCtrl, PROF_MOTIONEN);
	mcProfile.Flag = GetReg(usSRegHoldBuf[PROFILECTRL], PROF_MOTIONEN);

	// 位置模式且开始运动
	if ((mcRegParam.WorkMode == POSSERIAL) 
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
		|| (usSRegInBuf[FBOPMODE] == PROFILE_POSITION_MODE)
#endif
		)
	{
		if (mcProfile.Flag)
		{
			if (!mcProfile.Flag_Pre) // MOTIONEN 上升沿
			{
				mcProfile.ProfileAbsFlag = ReadBit(usSRegHoldBuf[PROFILECTRL], PROF_PROFILEABS);
				mcProfile.ProfileRndFlag = ReadBit(usSRegHoldBuf[PROFILECTRL], PROF_PROFILERND);
				mcProfile.ProfileRepFlag = ReadBit(usSRegHoldBuf[PROFILECTRL], PROF_PROFILEREP);
				mcProfile.ProfileCurveType = ReadBit(usSRegHoldBuf[PROFILECTRL], PROF_PROFILETYPE);

				if (mcProfile.ProfileAbsFlag)
				{
					profileMovDis = (((int32)usSRegHoldBuf[PROFILEMOVDIS_H] << 16) + (uint32)usSRegHoldBuf[PROFILEMOVDIS_L])
						-(((int32)usSRegInBuf[CMDPOS_H] << 16) + (uint32)usSRegInBuf[CMDPOS_L]);
					mcProfile.ProfileAbsStep = 0;
				}
				else
				{
					profileMovDis = ((int32)usSRegHoldBuf[PROFILEMOVDIS_H] << 16) + (uint32)usSRegHoldBuf[PROFILEMOVDIS_L];
				}

				Motor_Profile_Init(mcProfile.ProfileCurveType, profileMovDis, usSRegHoldBuf[PROFILEMAXVEL],
					((int32)usSRegHoldBuf[PROFILEMAXACC_H] << 16) + (uint32)usSRegHoldBuf[PROFILEMAXACC_L],
					((int32)usSRegHoldBuf[PROFILEMAXJERK_H] << 16) + (uint32)usSRegHoldBuf[PROFILEMAXJERK_L]);
			}

			// update MotionStatus
			if (Position_Profile_GetMotionStatus() == MS_FINISH)
			{
				if (mcProfile.ProfileRepFlag)   // repetitive position loop move
				{
					if (mcProfile.Dwell_En == 0)
					{
						mcProfile.TimeCounter = usSRegHoldBuf[PROFILEDWELLTIME];
						mcProfile.Dwell_En = 1;
					}
					else
					{
						if (mcProfile.TimeCounter == 0)
						{
							mcProfile.Dwell_En = 0;
							if (mcProfile.ProfileAbsFlag)  // absolutely move
							{
								if (!mcProfile.ProfileAbsStep)
								{
									profileMovDis = (((int32)usSRegHoldBuf[PROFILEMOVDIS2_H] << 16)
										+(uint32)usSRegHoldBuf[PROFILEMOVDIS2_L])
										-(((int32)usSRegHoldBuf[PROFILEMOVDIS_H] << 16)
										+(uint32)usSRegHoldBuf[PROFILEMOVDIS_L]);
									mcProfile.ProfileAbsStep = 1;

									Motor_Profile_Init(mcProfile.ProfileCurveType, profileMovDis, usSRegHoldBuf[PROFILEMAXVEL],
										((int32)usSRegHoldBuf[PROFILEMAXACC_H] << 16) + (uint32)usSRegHoldBuf[PROFILEMAXACC_L],
										((int32)usSRegHoldBuf[PROFILEMAXJERK_H] << 16) + (uint32)usSRegHoldBuf[PROFILEMAXJERK_L]);
								}
								else
								{
									Position_Profile_TurnAround();
								}
							}
							else // relatively move
							{
								if (mcProfile.ProfileRndFlag)
									Position_Profile_TurnAround();
								else
									Position_Profile_StartMove();
							}
						}
					}
				}
			}
		}


		// 停止运动
		if (!mcProfile.Flag)  // MOTIONEN 下降沿
		{
			if (mcProfile.Flag_Pre)
			{
				Motor_Profile_StartDeceleration();
				McStaSet.SetFlag.StopSetFlag = 1;
			}
			else if (McStaSet.SetFlag.StopSetFlag == 1)
			{
				// update MotionStatus
				if (Position_Profile_GetMotionStatus() == MS_FINISH || Position_Profile_GetMotionStatus() == MS_READY)
				{
					mcProfile.TimeCounter = 0;
					McStaSet.SetFlag.StopSetFlag = 0;
				}
			}
		}
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_StartDeceleration(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	开始减速
/*---------------------------------------------------------------------------*/
void Motor_Profile_StartDeceleration(void)
{
	Position_Profile_StartDeceleration();
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_StartDeceleration(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	开始减速
/*---------------------------------------------------------------------------*/
void Motor_Profile_Clr(void)
{
	Position_Profile_Clr();
}

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Profile_TimeCount(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	位置运动的停顿时间判断，放在1ms循环里
/*---------------------------------------------------------------------------*/
void Motor_Profile_TimeCount(void)
{
	if (mcProfile.TimeCounter > 0)
		mcProfile.TimeCounter--; 
}
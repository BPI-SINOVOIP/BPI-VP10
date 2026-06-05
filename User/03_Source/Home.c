/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Home.c
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : define some function for home.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>
#include "Home.h"


#if FUNC_HOME_ENABLED
/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
HomeTypeDef mcDoHome __attribute__((section(".pram.data.mcDoHome"))) = { 0 };


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/
/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_Home(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Home Initial & Do home, standard homing methods, as defined
/*               in CiA 402. Call this function every cycle.
/*---------------------------------------------------------------------------*/

void Motor_Home(void)
{
	if (mcDoHome.State == HOME_IDLE)
	{
		uint16 Temp;
		memset(&mcDoHome, 0, sizeof(HomeTypeDef));		           // reset home variable
		if (GetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE) == STATUS_ENABLE)
			mcDoHome.EnableStatus = 1;
		else
			mcDoHome.EnableStatus = 0; 
//		Motor_DisableServo();

		mcFocCtrl.State_Count = usSRegHoldBuf[HOMETIMEOUT];
		//		mcFocCtrl.QEPThetaOffset = 0;

		// avoid overcurrent error
		if ((int16)usSRegHoldBuf[HOMEMETHOD] == HardStopNToIndex || (int16)usSRegHoldBuf[HOMEMETHOD] == HardStopPToIndex
			|| (int16)usSRegHoldBuf[HOMEMETHOD] == HardStopN || (int16)usSRegHoldBuf[HOMEMETHOD] == HardStopP)
		{
			Temp = usSRegHoldBuf[HOMEBLOCKCURRENT] + (usSRegHoldBuf[HOMEBLOCKCURRENT] >> 1);  // set limit current,large than user set
			if (Temp > usSRegHoldBuf[RMSCURRENT])
				Temp = usSRegHoldBuf[RMSCURRENT];

			PI_Spd_UpdateLimit(Temp, -Temp);
		}

		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_HOMECOMPLETE, 0);
		McStaSet.SetFlag.AutoHomeSetFlag = 1;

		mcDoHome.HomeSpeed = ABS((int16)usSRegHoldBuf[HOMESPEED1]);
		mcDoHome.ZeroSpeed = ABS((int16)usSRegHoldBuf[HOMESPEED2]);
		mcDoHome.HomeAcc = ABS((int16)usSRegHoldBuf[HOMEACC]);
	
		mcDoHome.MoveDistance = 30000000;
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagPLimitToIndex:
			mcDoHome.LimitButton = INSTATUS_POSILIMITSWITCH;
			break;
			
		case DisengagNLimitToIndex:
			mcDoHome.LimitButton = INSTATUS_NEGALIMITSWITCH;
			mcDoHome.MoveDistance = -mcDoHome.MoveDistance;
			break;
				
		case DisengagHomeSwitchPToIndex:
		case HardStopPToIndex:
		case HardStopP:
		case NToIndex:
			mcDoHome.LimitButton = INSTATUS_HOMESWITCH;
			break;
			
		case DisengagHomeSwitchNToIndex:
		case HardStopNToIndex:
		case HardStopN:
		case PToIndex:
			mcDoHome.LimitButton = INSTATUS_HOMESWITCH;
			mcDoHome.MoveDistance = -mcDoHome.MoveDistance;
			break;
		}

		mcDoHome.State = HOME_START;
	}
	else
	{
		DoHoming();
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void DoHoming(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Home Initial & Do home, standard homing methods, as defined
/*               in CiA 402. Call this function every cycle.
/*---------------------------------------------------------------------------*/
void DoHoming(void)
{
	if (mcFocCtrl.State_Count <= 2)  // TimeOut
	{
		mcFaultSource = FaultHomeFailed;
		FaultProcess();
		return;
	}

	switch (mcDoHome.State)
	{
	case HOME_START:     // go to limit
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
			if (!ReadBit(usSRegInBuf[DIGINSTATUS], mcDoHome.LimitButton))
			{
				Motor_EnableServo();
				Motor_Profile_Init(T_PROFILE, mcDoHome.MoveDistance, mcDoHome.HomeSpeed, mcDoHome.HomeAcc, 0);
				mcDoHome.State = HOME_SEARCHLIMIT;
			}
			else // on limit
			{
				Motor_EnableServo();
				Motor_Profile_Init(T_PROFILE, -mcDoHome.MoveDistance, mcDoHome.ZeroSpeed, mcDoHome.HomeAcc, 0);
				mcDoHome.State = HOME_REACHLIMIT;
			}
			break;

		case NToIndex:
		case PToIndex:
			mcDoHome.State = HOME_SEARCHINDEX;
			break;

		case NowPositionAsHome:
			mcDoHome.State = HOME_GETABS;
			break;

		case HardStopNToIndex:
		case HardStopPToIndex:
		case HardStopN:
		case HardStopP:
			Motor_EnableServo();
			Motor_Profile_Init(T_PROFILE, mcDoHome.MoveDistance, mcDoHome.HomeSpeed, mcDoHome.HomeAcc, 0);
			mcDoHome.State = HOME_REACHLIMIT;
			break;
		}
		break;
		
	case HOME_SEARCHLIMIT:     // 寻找限位高电平
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
			if (ReadBit(usSRegInBuf[DIGINSTATUS], mcDoHome.LimitButton))
			{
				Motor_Profile_StartDeceleration(); // Start Deceleration
				mcDoHome.State = HOME_SLOWDOWN;
				mcDoHome.NextState = HOME_TURNAROUND;
			}
			break;
		}
		break;

	case HOME_REACHLIMIT:     // 寻找限位低电平
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
			if (!ReadBit(usSRegInBuf[DIGINSTATUS], mcDoHome.LimitButton))
			{
				mcDoHome.State = HOME_SEARCHINDEX;
			}
			break;

		case HardStopNToIndex:
		case HardStopPToIndex:
		case HardStopN:
		case HardStopP:
			mcDoHome.SkipFaultOverPosErr = 1; // skip FaultPosFollowing during hardstop
			if ((mcFocCtrl.State_Count < usSRegHoldBuf[HOMETIMEOUT] - 50)
				&& ABS((int16)usSRegInBuf[ACTCUR]) >= usSRegHoldBuf[HOMEBLOCKCURRENT]
				&& ABS((int16)usSRegInBuf[ACTVEL]) < usSRegHoldBuf[HOMEBLOCKSPEED])
			{
				if (mcDoHome.TimeCounter == 0)
				{
					Motor_DisableServo();
					Delay_ms(HomeBlockEndWaitTime);
					PI_Spd_ResetLimit();
					mcDoHome.SkipFaultOverPosErr = 0;
					mcDoHome.State = HOME_SEARCHINDEX;
				}
			}
			else
			{
				mcDoHome.TimeCounter = usSRegHoldBuf[HOMEBLOCKTIME];
			}
			break;
		}
		break;

	case HOME_SEARCHINDEX:     // find index
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case HardStopN:
		case HardStopP:
			mcDoHome.State = HOME_GETABS;
			break;

		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
			Timer2_ZIndexInt_Enable();   // start interrupt: z rising edge
			mcDoHome.State = HOME_CATCHINDEX;
			break;
		
		case HardStopPToIndex:
		case HardStopNToIndex:
		case NToIndex:
		case PToIndex:
			Timer2_ZIndexInt_Enable();   // start interrupt: z rising edge
			Motor_EnableServo();
			Motor_Profile_Init(T_PROFILE, -mcDoHome.MoveDistance, mcDoHome.ZeroSpeed, mcDoHome.HomeAcc, 0);
			mcDoHome.State = HOME_CATCHINDEX;
			break;
		}
		break;

	case HOME_CATCHINDEX:     // reach index
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
		case HardStopNToIndex:
		case HardStopPToIndex:
		case NToIndex:
		case PToIndex:
			if (mcDoHome.ZCapturedFlag == 1)
			{
				mcDoHome.ZCapturedFlag = 0;
				Motor_Profile_StartDeceleration(); // Start Deceleration
				mcDoHome.State = HOME_SLOWDOWN;
				mcDoHome.NextState = HOME_GETABS;
			}
			break;
		}
		break;
		
	case HOME_TURNAROUND:     // 掉头
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
			Motor_Profile_Init(T_PROFILE, -mcDoHome.MoveDistance, mcDoHome.ZeroSpeed, mcDoHome.HomeAcc, 0);
			mcDoHome.State = HOME_REACHLIMIT;
			break;
		}
		break;

	case HOME_SLOWDOWN:     // 减速
		if ((Position_Profile_GetMotionStatus() == MS_FINISH) && mcFocCtrl.TargetRef == 0 && 
			GetReg(usSRegInBuf[DRIVESTATUS], STATUS_INPOS))
		{
			mcDoHome.State = mcDoHome.NextState;
		}
		break;

	case HOME_GETABS:     // change offset,go zero
		Motor_DisableServo();
		switch ((int16)usSRegHoldBuf[HOMEMETHOD])
		{
		case DisengagNLimitToIndex:
		case DisengagPLimitToIndex:
		case DisengagHomeSwitchPToIndex:
		case DisengagHomeSwitchNToIndex:
		case HardStopNToIndex:
		case HardStopPToIndex:
		case NToIndex:
		case PToIndex:
			mcDoHome.EncThetaBuffer += (((int32)usSRegHoldBuf[HOMEOFFSET_H] << 16) | (uint16)usSRegHoldBuf[HOMEOFFSET_L]);
#if FUNC_FEEDBACKONLOAD_ENABLED
			if (FEEDBACK_MOTOR == Feedback_GetOnLoadFlag())
			{
				mcFocCtrl.QEPThetaOffset += mcDoHome.EncThetaBuffer;
			}
			else
			{
				mcFocCtrl.QEPLoadThetaOffset += mcDoHome.LoadEncThetaBuffer;
				mcFocCtrl.QEPThetaOffset += mcDoHome.EncThetaBuffer;
			}
			*((int32*) & usSRegHoldBuf[SFBANGOFFSET_L]) = mcFocCtrl.QEPLoadThetaOffset;
#else					
			mcFocCtrl.QEPThetaOffset += mcDoHome.EncThetaBuffer;
#endif			
			*((int32*) & usSRegHoldBuf[ANGOFFSET_L]) = mcFocCtrl.QEPThetaOffset;
			break;

		case NowPositionAsHome:
		case HardStopN:
		case HardStopP:			
#if FUNC_FEEDBACKONLOAD_ENABLED
			if (FEEDBACK_MOTOR == Feedback_GetOnLoadFlag())
			{
				mcDoHome.EncThetaBuffer = mcFocCtrl.ActualAngle + (((int32)usSRegHoldBuf[HOMEOFFSET_H] << 16) |
					(uint16)usSRegHoldBuf[HOMEOFFSET_L]);
				mcFocCtrl.QEPThetaOffset += mcDoHome.EncThetaBuffer;
			}
			else
			{
				mcDoHome.LoadEncThetaBuffer = mcEncoder.LoadEncPos + (((int32)usSRegHoldBuf[HOMEOFFSET_H] << 16) |
					(uint16)usSRegHoldBuf[HOMEOFFSET_L]);				
				mcFocCtrl.QEPLoadThetaOffset += mcDoHome.LoadEncThetaBuffer;
				*((int32*) & usSRegHoldBuf[SFBANGOFFSET_L]) = mcFocCtrl.QEPLoadThetaOffset;
				
				mcDoHome.EncThetaBuffer = mcFocCtrl.ActualAngle + (((int32)usSRegHoldBuf[HOMEOFFSET_H] << 16) |
					(uint16)usSRegHoldBuf[HOMEOFFSET_L]);
				mcFocCtrl.QEPThetaOffset += mcDoHome.EncThetaBuffer;
			}
#else
			mcDoHome.EncThetaBuffer = mcFocCtrl.ActualAngle + (((int32)usSRegHoldBuf[HOMEOFFSET_H] << 16) |
				(uint16)usSRegHoldBuf[HOMEOFFSET_L]);
			mcFocCtrl.QEPThetaOffset += mcDoHome.EncThetaBuffer;
#endif			
			*((int32*) & usSRegHoldBuf[ANGOFFSET_L]) = mcFocCtrl.QEPThetaOffset;
			break;
		}
		if ((int16)usSRegHoldBuf[HOMEMETHOD] != NowPositionAsHome)
		{
			Delay_ms(2); // wait until motor is stable
			Motor_EnableServo();  // Enable first to make it stable faster
			Delay_ms(2); // wait until motor is stable
			Motor_Profile_Init(T_PROFILE, -mcFocCtrl.TargetAngle, mcDoHome.HomeSpeed, mcDoHome.HomeAcc, 0); // go to zero
		}
		else if ((int16)usSRegHoldBuf[HOMEMETHOD] == NowPositionAsHome && mcDoHome.EnableStatus)
		{
			Motor_EnableServo();
		}
		mcDoHome.State = HOME_GOTOZERO;
		break;

	case HOME_GOTOZERO: // reach zero
		if( ((Position_Profile_GetMotionStatus() == MS_FINISH) && mcFocCtrl.TargetRef == 0 && 
			GetReg(usSRegInBuf[DRIVESTATUS], STATUS_INPOS)) ||
			((int16)usSRegHoldBuf[HOMEMETHOD] == NowPositionAsHome) )
		{
			mcDoHome.State = HOME_FINISH;
		}
		break;

	default:
		mcDoHome.State = HOME_FINISH;
		break;
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Home_Reset(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Reset Home in the beginning and fault.
/*---------------------------------------------------------------------------*/
void Home_Reset(void)
{
	mcDoHome.State = HOME_IDLE;
	mcDoHome.SkipFaultOverPosErr = 0; // skip FaultPosFollowing during hardstop
	Timer2_ZIndexInt_Disable();  // end interrupt
	PI_Spd_ResetLimit();     // restore PI_Spd Limit
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Home_ZCaptured(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Home_ZCaptured in the interrupt.
/*---------------------------------------------------------------------------*/
void Home_ZCaptured(void)
{
	if (mcDoHome.ZCapturedFlag == 0)
	{
		Timer2_ZIndexInt_Disable();  // end interrupt
		mcDoHome.EncThetaBuffer = read_csr(TIM2_QEP_ARR);

		if (mcFocCtrl.AngDir)
			mcDoHome.EncThetaBuffer = -mcDoHome.EncThetaBuffer - mcFocCtrl.QEPThetaOffset;
		else
			mcDoHome.EncThetaBuffer = mcDoHome.EncThetaBuffer - mcFocCtrl.QEPThetaOffset;

		mcDoHome.ZCapturedFlag = 1;
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Home_TimeCount(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	回零撞硬限位的时间判断，放在1ms循环里
/*---------------------------------------------------------------------------*/
void Home_TimeCount(void)
{
	if (mcDoHome.TimeCounter > 0)
		mcDoHome.TimeCounter--;   // 回零撞硬限位的时间判断
}
#endif // #if FUNC_HOME_ENABLED
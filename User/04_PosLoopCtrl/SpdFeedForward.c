/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : SpdFeedForward.c
 * Author        : Summer
 * Date          : 2023-11-23
 * Description   : Velocity Feedforward 
 *
 * Record        :
 * V1.0, 2023-11-23, Summer: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>

#if FUNC_SPDFF_ENABLED
/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
SpdFFTypedef SpdFF = { 0 };

/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/
void SpdFF_Init(void);
int16 SpdFF_realize(int16 PosRefDiff);


/*---------------------------------------------------------------------------
 * Name		:	SpdFF_Init
 * Input	:	No
 * Output	:	No
 * Description:	Initialize velocity feedforward
 *---------------------------------------------------------------------------*/
void SpdFF_Init(void)
{
	SpdFF.Coef = (int16)VELFEB_FREQUENCY / (int16)POSCTRL_FREQUENCY;
	SpdFF.Output = 0;
	SpdFF.Filter = LowPassFilt_Init(SpdFF.FilterMem, (int32)usSRegHoldBuf[PVFRLPFHZ], 
		(int32)POSCTRL_FREQUENCY * 1000 * 10);
}


/*---------------------------------------------------------------------------
 * Name		:	SpdFF_realize
 * Input	:	PosRefDiff - position command increment
 * Output	:	Output - velocity feedforward value
 * Description:	Initialize velocity feedforward
 *---------------------------------------------------------------------------*/
int16 SpdFF_realize(int16 PosRefDiff)
{	
	int32 SpdFFValue = 0;
	int32 encRes1, encRes2 = 0;
	
	if (usSRegHoldBuf[PVFRMOD] != VELFF_MODE_OFF)
	{		
		if (usSRegHoldBuf[PVFRMOD] == VELFF_MODE_DIFF)
		{
			SpdFFValue = ((int32)PosRefDiff * (int32)mcFocCtrl.QepSpeedCoe) >> usSRegHoldBuf[SPEEDCOERANK];
		}
		else // if (usSRegHoldBuf[PVFRMOD] == VELFF_MODE_TRAJ)
		{
			SpdFFValue = Position_Profile_GetVel(mcFocCtrl.QepSpeedCoe);
			SpdFFValue = SpdFFValue >> usSRegHoldBuf[SPEEDCOERANK];
		}	
		
		SpdFFValue = (int32)SpdFFValue * (int32)usSRegHoldBuf[PVFR] / SpdFF.Coef;

#if FUNC_FEEDBACKONLOAD_ENABLED
		if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
		{
			SpdFFValue = (int32)(((int64)SpdFFValue * Feedback_GetLoadToMotorCoef()) >> MOTORCOEF);
		}
#endif
		
		if (SpdFFValue < 0)
		{
			SpdFFValue = (int32)(-((-(int32) SpdFFValue) >> 14));
		}
		else
		{
			SpdFFValue = (int32)((int32) SpdFFValue >> 14);
		}

	    // Limit feedforward output
		SpdFFValue = MAX_MIN_LMT(SpdFFValue, 32767, -32767);

		SpdFF.Output = LowPassFilt_realize(SpdFF.Filter, SpdFFValue);

	}
	else
	{
		SpdFF.Output = 0;
//		LowPassFilt_Clr(SpdFF.Filter);
	}
		
	return SpdFF.Output;
}
#endif // #if FUNC_SPDFF_ENABLED
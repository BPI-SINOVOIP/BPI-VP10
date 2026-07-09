/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ToqFeedForward.c
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : Torque feedforward
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include <Myproject.h>

#if FUNC_TOQFF_ENABLED
/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/
ToqFdFwdTypedef ToqFdFwd __attribute__((section(".pram.data.ToqFdFwd"))) = {0};

/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
void ToqFF_Init(void);
int16 ToqFF_realize(void);
void SpdErrCal_realize(void);
int64 ToqFF_GetSpdToCurCoef(void);

/*---------------------------------------------------------------------------
 * Name		:	ToqFF_Init
 * Input	:	No
 * Output	:	No
 * Description:	Initialize torque feedforward
 *---------------------------------------------------------------------------*/
void ToqFF_Init(void)
{
	uint32 mass = 0;
	mass = ((uint32)usSRegHoldBuf[MASS_H] << 16) | usSRegHoldBuf[MASS_L];
	mass = (int64)mass * (10 + usSRegHoldBuf[LMJR]) / 10;

	// SpdToCurCoef: unit conversion rpm->A, 1A corresponds to 1000 counts
	ToqFdFwd.SpdToCurCoef = mass * (uint16)VELCTRL_FREQUENCY;
	if (GetReg(usSRegHoldBuf[DRIVEMODE], MODE_MOTORTYPE)) // Rotary Motor
	{ 
		// Coef = J_total*2*pi*FreqSpd/60/Kt          I = Coef * V1
		ToqFdFwd.SpdToCurCoef = ToqFdFwd.SpdToCurCoef * (int64)2 * PI_Q12 * 1000;
		ToqFdFwd.SpdToCurCoef = (ToqFdFwd.SpdToCurCoef << TOQFDFWD_RANK) >> 3;
		ToqFdFwd.SpdToCurCoef = ToqFdFwd.SpdToCurCoef / 60 / 10000;
	}
	else // Linear Motor
	{ 
		// Coef = M_total*FreqSpd/Kt                 I = Coef * V2
		ToqFdFwd.SpdToCurCoef = ToqFdFwd.SpdToCurCoef << (12 + TOQFDFWD_RANK - 3);
	}	
	ToqFdFwd.SpdToCurCoef = ToqFdFwd.SpdToCurCoef / usSRegHoldBuf[FORCECONST];
	ToqFdFwd.SpdToCurCoef = ToqFdFwd.SpdToCurCoef * usSRegHoldBuf[MOTORMAXSPEED] * usSRegHoldBuf[CURCOE];
	
	ToqFdFwd.Filter = LowPassFilt_Init(ToqFdFwd.FilterMem, (int32)usSRegHoldBuf[LPF2FREQ], (int32)VELFILE_FREQUENCY * 10);
	
	ToqFdFwd.AvgFilter = AvgFilt_Init(ToqFdFwd.AvgFilterMem, usSRegHoldBuf[KACAVG]);

	ToqFdFwd.SpdRefLatch = 0;
	ToqFdFwd.SpdRefErr = 0;
}

/*---------------------------------------------------------------------------
 * Name		:	ToqFF_realize
 * Input	:	No
 * Output	:	Calculated value of torque feedforward
 * Description:	Calculate torque feedforward
 *---------------------------------------------------------------------------*/
int16 ToqFF_realize(void)
{
	int16 SpdRef = 0;
	int16 FdFwdRetValue = 0;
	int64 FdFwdValue = 0;
	int16 ToqFbMod = 0;

	ToqFbMod = usSRegHoldBuf[KACMOD];

	if (mcState == mcRun)
	{
		if (ToqFbMod == TOQFF_MODE_OFF)
		{
			FdFwdRetValue = 0;
		}
		else
		{
			if (ToqFbMod == TOQFF_MODE_CMDVEL)
			{
				// Calculate speed command increment
				if (mcFocCtrl.RunMod == POSMOD)
				{
					if (!mcFocCtrl.PosLoopTime)
					{
						SpdRef = (int16)usSRegInBuf[CMDVEL];

						ToqFdFwd.SpdRefErr = (SpdRef - ToqFdFwd.SpdRefLatch) / ((uint16)VELCTRL_FREQUENCY / (uint16)POSCTRL_FREQUENCY);

						ToqFdFwd.SpdRefLatch = SpdRef;
					}	
				}
				else
				{
					SpdRef = (int16)usSRegInBuf[CMDVEL];

					ToqFdFwd.SpdRefErr = SpdRef - ToqFdFwd.SpdRefLatch;

					ToqFdFwd.SpdRefLatch = SpdRef;
				}
			}

			// Smoothing filter
			ToqFdFwd.SpdRefErr = (int16)AvgFilt_realize(ToqFdFwd.AvgFilter, (int16)ToqFdFwd.SpdRefErr);
			
			FdFwdValue = ToqFdFwd.SpdRefErr * usSRegHoldBuf[KACCB];

			FdFwdValue = FdFwdValue * (int64)ToqFdFwd.SpdToCurCoef;

			if (FdFwdValue < 0)
			{
				FdFwdValue = (int64)(-((-FdFwdValue) >> TOQFDFWDRS_RANK));
			}
			else
			{
				FdFwdValue = (int64)(FdFwdValue >> TOQFDFWDRS_RANK);
			}

			
			// Feedforward output clamping + low-pass filtering --- 2.8us
			FdFwdRetValue = MAX_MIN_LMT(FdFwdValue, 32767, -32767);

			if ((usSRegHoldBuf[LPF2FREQ] < 20000) || (usSRegHoldBuf[KACAVG] == 0))
			{
				FdFwdRetValue = (int16) LowPassFilt_realize(ToqFdFwd.Filter, FdFwdRetValue);
			}
		}
	}
	
	return FdFwdRetValue;
}

/*---------------------------------------------------------------------------
 * Name		:	SpdErrCal_realize
 * Input	:	No
 * Output	:	No
 * Description:	Calculate differential value of position command increment
 *---------------------------------------------------------------------------*/
void SpdErrCal_realize(void)
{
	int32 encRes1, encRes2 = 0;
	
	if (mcState == mcRun)
	{
		if (mcFocCtrl.TargetRef == 0)
		{
			mcFocCtrl.TargetReftoSpd = 0;
		}
		else
		{
			mcFocCtrl.TargetReftoSpd = (int32)mcFocCtrl.TargetRef * mcFocCtrl.QepSpeedCoe;

			if (mcFocCtrl.TargetReftoSpd < 0)
			{
				mcFocCtrl.TargetReftoSpd = (int32)(-((-mcFocCtrl.TargetReftoSpd) >> usSRegHoldBuf[SPEEDCOERANK]));
			}
			else
			{
				mcFocCtrl.TargetReftoSpd = (int32)(mcFocCtrl.TargetReftoSpd >> usSRegHoldBuf[SPEEDCOERANK]);
			}

			mcFocCtrl.TargetReftoSpd = mcFocCtrl.TargetReftoSpd / ((uint16)VELFEB_FREQUENCY / (uint16)POSCTRL_FREQUENCY);
		}

#if FUNC_FEEDBACKONLOAD_ENABLED		
		if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag())
		{
			encRes1 = ((int32)usSRegHoldBuf[ENCRES_H] << 16) | (uint16)usSRegHoldBuf[ENCRES_L];
			encRes2 = ((int32)usSRegHoldBuf[SFBENCRES_H] << 16) | (uint16)usSRegHoldBuf[SFBENCRES_L];
			usSRegInBuf[PTPVCMD] = (int16)(((mcFocCtrl.TargetReftoSpd * (int16)usSRegHoldBuf[MOTORMAXSPEED] * (int64)encRes1) >> 14) / encRes2); // Outer-loop unit
		}
		else
		{
			usSRegInBuf[PTPVCMD] = (mcFocCtrl.TargetReftoSpd * (int32)usSRegHoldBuf[MOTORMAXSPEED]) >> 14;
		}
#else
		usSRegInBuf[PTPVCMD] = (mcFocCtrl.TargetReftoSpd * (int32)usSRegHoldBuf[MOTORMAXSPEED]) >> 14;
#endif

		if (usSRegHoldBuf[KACMOD] == TOQFF_MODE_CMDPOS)
		{
			ToqFdFwd.SpdRefErr = (mcFocCtrl.TargetReftoSpd - ToqFdFwd.SpdRefLatch) / ((uint16)VELCTRL_FREQUENCY / (uint16)POSCTRL_FREQUENCY);

			ToqFdFwd.SpdRefLatch = mcFocCtrl.TargetReftoSpd;
		}
	}

}


/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :
/* Description:
/*---------------------------------------------------------------------------*/
int64 ToqFF_GetSpdToCurCoef(void)
{
	return ToqFdFwd.SpdToCurCoef;
}

#endif // #if FUNC_TOQFF_ENABLED
/********************************* END OF FILE *********************************/
/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Hall.c
 * Author        : Jamie
 * Date          : 2022-10-12
 * Description   : define some new method of Hall.
 *
 * Record        :
 * V1.0, 2022-10-12, Jamie: Created file
 */

/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>
#include "Hall.h"

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
#if ENCODER_SEL_HALL_ENABLED
HallTypeDef mcHall;

// Fixed angles
const int16 Hall_Theta_Arr[6] =
{
	DEGREE_60,  //1
	DEGREE_180, //2
	DEGREE_120, //3
	DEGREE_300, //4
	DEGREE_0,   //5
	DEGREE_240  //6
};

// 5->1->3->2->6->4; e.g.5's next is 1,so Hall_Status_CW[5-1] = 1.
const uint8 Hall_Status_CW[6] = { 3, 6, 2, 5, 1, 4 };


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------
 * Name		:	Hall_Init
 * Input	:	No
 * Output	:	No
 * Description:	Hall calculation initialization
 *---------------------------------------------------------------------------*/
void Hall_Init(void)
{
	memset(&mcHall, 0, sizeof(HallTypeDef));                   // reset hall variable

#if !HALL_LEARN_CALCULATION_ENABLED
	mcHall.pLearnHallTheta = (uint16*) & usSRegInBuf[HALLTHETA0];
	mcHall.pLearnHallStatus = (uint8*) & usSRegInBuf[HALLSTATUS01];
#endif
}


/*---------------------------------------------------------------------------
 * Name		:	HallPinInit
 * Input	:	No
 * Output	:	No
 * Description:	Hall hardware initialization
 *---------------------------------------------------------------------------*/
void HallPinInit(void)
{
	// HA
	clr_csr(HA_OE, HA_PIN);  		/* 0: Disable digital output */
	set_csr(HA_PU, HA_PIN);  		/* 1: Enable internal pull up */
	// HB
	clr_csr(HB_OE, HB_PIN);  		/* 0: Disable digital output */
	set_csr(HB_PU, HB_PIN);  		/* 1: Enable internal pull up */
	// HC
	clr_csr(HC_OE, HC_PIN);  		/* 0: Disable digital output */
	set_csr(HC_PU, HC_PIN);  		/* 1: Enable internal pull up */
}


/*---------------------------------------------------------------------------
 * Name		:	GetHallStatus
 * Input	:	No
 * Output	:	Hall status
 * Description:	Read Hall status
 *---------------------------------------------------------------------------*/
uint8 GetHallStatus()
{
	uint8 HallStatus = 0;
	uint8 ha, hb, hc;
	uint8 MCDivFlag;                      // Hall direction reversed
	uint8 Mode;                           // Hall relation, corresponding to 6 Hall combinations

	HallStatus = read_csr(HA_GPIO);
	ha = ReadBit(HallStatus, HA_PIN);
	hb = ReadBit(HallStatus, HB_PIN);
	hc = ReadBit(HallStatus, HC_PIN);

	Mode = GetReg(usSRegHoldBuf[HALLMODE], HALLMODE_HAINV | HALLMODE_HBINV | HALLMODE_HCINV);
	MCDivFlag = GetReg(usSRegHoldBuf[HALLMODE], HALLMODE_DIR);

	if (MCDivFlag)
		HallStatus = (((((uint8)ha) << 2) | (((uint8)hb) << 1) | ((uint8)hc)) ^ Mode) & 0x07;
	else
		HallStatus = (((((uint8)hc) << 2) | (((uint8)hb) << 1) | ((uint8)ha)) ^ Mode) & 0x07;

	return HallStatus;
}


/*---------------------------------------------------------------------------
 * Name		:	UpdateHallTheta
 * Input	:	No
 * Output	:	No
 * Description:	Update approximate electrical angle offset based on Hall status
 *---------------------------------------------------------------------------*/
void UpdateHallTheta(void)
{
	int16 ExpectTheta = 0;
	if (mcHall.ThetaCalcFlag != 2)
	{
		mcHall.Mode = GetReg(usSRegHoldBuf[HALLMODE], HALLMODE_HAINV | HALLMODE_HBINV | HALLMODE_HCINV);
		mcHall.MCDivFlag = GetReg(usSRegHoldBuf[HALLMODE], HALLMODE_DIR);
		mcHall.OffsetTheta = usSRegHoldBuf[ELECANGSHIFT];

		mcHall.NowHallStatus = GetHallStatus();
		ExpectTheta = (int32)(Hall_Theta_Arr[mcHall.NowHallStatus - 1]) + (int16)usSRegHoldBuf[ELECANGSHIFT] + DEGREE_30;

		mcElecAng.ElecAngOffset += mcElecAng.FOCTheta - ExpectTheta;
		usSRegInBuf[ELECANGOFFSET] = mcElecAng.ElecAngOffset;
		mcHall.LastHallStatus = mcHall.NowHallStatus;
		mcHall.ThetaCalcFlag = 1;
	}
}


/*---------------------------------------------------------------------------
 * Name		:	UpdateHallTheta_Isr
 * Input	:	No
 * Output	:	No
 * Description:	Update precise electrical angle offset based on Hall status change edge
 *---------------------------------------------------------------------------*/
void UpdateHallTheta_Isr(void)
{
	int16 ExpectTheta = 0;
	if (mcHall.ThetaCalcFlag == 1)
	{
		mcHall.NowHallStatus = GetHallStatus();
		if (mcHall.LastHallStatus && mcHall.NowHallStatus)
		{
			if (mcHall.LastHallStatus != mcHall.NowHallStatus)
			{
				ExpectTheta = (int32)(Hall_Theta_Arr[mcHall.NowHallStatus - 1]) + (int16)usSRegHoldBuf[ELECANGSHIFT];
				if (Hall_Status_CW[mcHall.NowHallStatus - 1] == mcHall.LastHallStatus)
				{
					ExpectTheta += DEGREE_60;
				}

				usSRegInBuf[ELECANGOFFSET] += mcElecAng.FOCTheta - ExpectTheta;
				mcHall.ThetaCalcFlag = 2;
			}
		}
	}
}

#if ENCODER_SEL_HALLSONLY_ENABLED > 0
/*---------------------------------------------------------------------------
 * Name		:	UpdateHallsOnlyAngle
 * Input	:	No
 * Output	:	Hall angle
 * Description:	Update Hall angle (interpolated), only for Halls-Only
 *---------------------------------------------------------------------------*/
int32 UpdateHallsOnlyAngle(void)
{
	int32 Temp;

	mcHall.HallStatus = GetHallStatus();

	if (mcHall.HallStatusPre != mcHall.HallStatus)
	{
		mcHall.HallAngle = (int32)(Hall_Theta_Arr[mcHall.HallStatus - 1]) + (int16)usSRegHoldBuf[ELECANGSHIFT];
		mcHall.HallTheta = mcHall.HallAngle;
		if (Hall_Status_CW[mcHall.HallStatus - 1] == mcHall.HallStatusPre) // Currently only 60-degree change is considered
		{
			mcHall.HallAngle += DEGREE_60;
		}
		mcHall.HallStatusPre = mcHall.HallStatus;

		mcHall.StillPeriod += mcHall.StillCounter + 1;
		if (mcHall.StillCounter <= usSRegHoldBuf[HALLCOMMTHRESH])
			mcHall.LowSpeedStatus = 0;
		else
			mcHall.LowSpeedStatus = 1;
		mcHall.StillCounter = 0;

		// if (mcHall.ExcCnt > mcHall.StillPeriod)
		{
			mcHall.StillPeriodLatch = mcHall.StillPeriod; // (mcHall.StillPeriod * 3) >> 1;
			mcHall.ExcCnt = mcHall.StillPeriodLatch + 1;

			mcHall.StillPeriod = 0;
			mcHall.InterpltDltRefLatch = mcHall.InterpltDltRef;
			mcHall.InterpltDltRef = mcHall.HallAngle - mcHall.InterpltOutput;
			mcHall.InterpltInputLatch = mcHall.HallAngle;

			mcHall.HallAngleOut = 0;
			mcHall.InterpltOutputLatch = 0;
		}
	}
	else
	{
		if (mcHall.StillCounter < 65530)
		{
			mcHall.StillCounter++;
		}

		if (mcHall.StillCounter > usSRegHoldBuf[HALLCOMMTHRESH])
		{
			mcHall.LowSpeedStatus = 1;
		}
	}


	if (mcHall.ExcCnt > 1)
	{
		mcHall.ExcCnt--;
	}
	else
	{
		if (mcHall.LowSpeedStatus == 1)  // Low speed
		{
			mcHall.ExcCnt = 0;
			mcHall.StillPeriodLatch = 0;
			mcHall.StillPeriod = 0;
			mcHall.InterpltDltRef = 0;

			mcHall.HallAngleOut = 0;
			mcHall.InterpltOutputLatch = 0;
		}
		else
		{
			mcHall.ExcCnt = mcHall.StillPeriodLatch;
			Temp = mcHall.InterpltDltRef;
			mcHall.InterpltDltRef += mcHall.InterpltDltRef - mcHall.InterpltDltRefLatch;
			mcHall.InterpltDltRefLatch = Temp;
			if ((Temp > 0 && mcHall.InterpltDltRef < 0) || (Temp < 0 && mcHall.InterpltDltRef > 0))
			{
				mcHall.InterpltDltRef = 0;
			}
			else
			{
				Temp = mcHall.HallAngle - mcHall.InterpltOutput;
				if ((mcHall.InterpltDltRef > 0 && mcHall.InterpltDltRef - Temp > 0) || // Forward direction
					(mcHall.InterpltDltRef < 0 && mcHall.InterpltDltRef - Temp < 0)) // Negative direction
				{
					mcHall.InterpltDltRef = Temp;
				}
			}


			mcHall.HallAngleOut = 0;
			mcHall.InterpltOutputLatch = 0;
		}
	}

	mcHall.HallAngleOut += mcHall.InterpltDltRef;
	if (mcHall.StillPeriodLatch > 0)
		Temp = mcHall.HallAngleOut / mcHall.StillPeriodLatch;
	else
		Temp = 0;
	mcHall.InterpltOutputDelta = Temp - mcHall.InterpltOutputLatch;
	mcHall.InterpltOutput += mcHall.InterpltOutputDelta;
	mcHall.InterpltOutputLatch = Temp;

	// Electrical angle calculation
	if (mcHall.LowSpeedStatus == 1)  // Low speed
	{
		mcHall.HallThetaOut = mcHall.HallTheta + DEGREE_30;
	}
	else
	{
		if (mcHall.InterpltDltRef > 0) // Forward direction
		{
			mcHall.HallThetaOut = mcHall.InterpltOutput + DEGREE_60;
		}
		else if (mcHall.InterpltDltRef < 0) // Negative direction
		{
			mcHall.HallThetaOut = mcHall.InterpltOutput - DEGREE_60;
		}
	}

	// Position filtering
	mcHall.InterpltOutputFlt_k += (int32)usSRegHoldBuf[HALLPOSLPFK] * (mcHall.InterpltOutput - mcHall.InterpltOutputFlt);
	mcHall.InterpltOutputFlt = mcHall.InterpltOutputFlt_k >> 15;

	return mcHall.InterpltOutputFlt;
}


/*---------------------------------------------------------------------------
 * Name		:	GetHallsOnlyElecAngle
 * Input	:	No
 * Output	:	Hall electrical angle
 * Description:	Get Hall electrical angle, only for Halls-Only
 *---------------------------------------------------------------------------*/
int16 GetHallsOnlyElecAngle(void)
{
	return mcHall.HallThetaOut;
}
#endif // #if ENCODER_SEL_HALLSONLY_ENABLED > 0


/*---------------------------------------------------------------------------
 * Name		:	DoHallLearning
 * Input	:	No
 * Output	:	No
 * Description:	Hall learning: MCU collects electrical angles at Hall change edges, host calculates electrical angle offset
 *---------------------------------------------------------------------------*/
void DoHallLearning(void)
{
	switch (mcDoPhaseFind.State)
	{
	case 0:                     // Collect Hall sequence
		if (mcDoPhaseFind.IdRef < mcDoPhaseFind.IdTarget)
			mcDoPhaseFind.IdRef += mcDoPhaseFind.IdStep;
		else
		{
			mcDoPhaseFind.State = 1;
		}
		break;

	case 1:// delay for a while
		mcDoPhaseFind.TimeCounter++;
		if (mcDoPhaseFind.TimeCounter > mcDoPhaseFind.WorkTime)
		{
			mcDoPhaseFind.TimeCounter = 0;
			mcHall.HallStepCnt = 0;
			mcHall.NowHallStatus = GetHallStatus();
			mcHall.LastHallStatus = mcHall.NowHallStatus;
			mcHall.FOCThetaStart = NFOC_THETAH;
			mcDoPhaseFind.State = 2;
		}
		break;

	case 2: // search hall changing edge
		mcHall.NowHallStatus = GetHallStatus();

		/* Status update */
		if (mcHall.NowHallStatus != mcHall.LastHallStatus)
		{
			/* Record angle */
			if (usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_HALLS_ONLY)
			{
				*mcHall.pLearnHallTheta++ = NFOC_THETAH;
			}
			else
			{
				*mcHall.pLearnHallTheta++ = mcElecAng.FOCTheta;
			}
			*mcHall.pLearnHallStatus++ = mcHall.NowHallStatus;
			mcHall.HallStepCnt++;
			mcHall.LastHallStatus = mcHall.NowHallStatus;

			if (mcHall.HallStepCnt == 6)
				mcDoPhaseFind.State = 3;
		}

		NFOC_THETAH = mcHall.FOCThetaStart + mcDoPhaseFind.FOCThetaValue;
		mcDoPhaseFind.FOCThetaValue += mcDoPhaseFind.FOCThetaDelta;
		if (ABS(mcDoPhaseFind.FOCThetaValue) > DEGREE_480)
		{
			mcHall.Error = 3;
		}
		break;

	case 3: // Finish
		mcElecAng.FOCThetaFlag = 0;
		mcDoPhaseFind.FinishFlag = 1;
		break;

	default:
		break;
	}
}


#endif // #if ENCODER_SEL_HALL_ENABLED
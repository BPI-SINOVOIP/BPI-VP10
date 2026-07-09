/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EmergencyStop.c
 * Author        : Zougi.Zou
 * Date          : 2025-4-24
 * Description   : Emergency Stop Function
 *
 * Record        :
 * V1.0, 2025-4-24, Zougi.Zou: Created file
 */

/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>

#if FUNC_DISMODE_ENABLED

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
EmergencyStopTypeDef mcEmergencyStop = {0};


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------
 * Name		:	Do_EmergencyStop
 * Input	:	No
 * Output	:	No
 * Description:	Stopping method
 *---------------------------------------------------------------------------*/
void Do_EmergencyStop(void)
{	
	if (McStaSet.SetFlag.BrakeFlag == 0)
	{
		McStaSet.SetFlag.BrakeFlag = 1;
		
		if (mcFaultSource == FaultHardOVCurrent || mcFaultSource == FaultPeakOVCurrent \
			|| mcFaultSource == FaultRMSOVCurrent || mcFaultSource == FaultOverVoltage)
		{
			mcEmergencyStop.State = EMER_DISABLE;
		}
		else if (mcEmergencyStop.State == EMER_IDLE)
		{
			if (mcFocCtrl.RunMod == CURMOD || GetReg(usSRegHoldBuf[DISMODE], DISSTOPMODE) == DISSTOP_COAST)
			{
				mcEmergencyStop.State = EMER_DISABLE;
			}
			else
			{
				mcEmergencyStop.State = EMER_DEC;
			}
		}
		else if(mcEmergencyStop.State == EMER_DEC || (mcEmergencyStop.State == EMER_STOP && mcEmergencyStop.StateLatch != EMER_DISABLE))
		{
			mcEmergencyStop.State = EMER_DISABLE;
		}
	}
	
	switch (mcEmergencyStop.State)
	{
	case EMER_DEC:     // Start deceleration
		RampStop_Init();
		mcEmergencyStop.DisSpeed = usSRegHoldBuf[DISSPEED];
		mcEmergencyStop.TimeCounter = usSRegHoldBuf[DISTIME];
		mcEmergencyStop.TimeOutCounter = usSRegHoldBuf[DISTIMEOUT];
		mcEmergencyStop.StateLatch = mcEmergencyStop.State;
		mcEmergencyStop.State = EMER_STOP;
		break;
		
	case EMER_STOP:     // Decelerate to DISSPEED and hold for a period
		if (ABS((int16)usSRegInBuf[ACTVEL]) <= mcEmergencyStop.DisSpeed || mcEmergencyStop.TimeOutCounter == 0)
		{
			if (mcEmergencyStop.TimeCounter == 0 || mcEmergencyStop.TimeOutCounter == 0)
			{
				if (mcEmergencyStop.StateLatch == EMER_DEC)
				{
					mcEmergencyStop.State = EMER_DISABLE;
				}	
				else
				{
					mcEmergencyStop.StartBrakeFlag = 0;
					clr_csr(DRV1_CR, DRVOE);			// Driver output enable	0-->Disable		1-->Enable
					clr_csr(DRV1_OUT, MOE);		// Disable main output enable (DB invalid)
					mcEmergencyStop.State = EMER_FINISH;
				}
			}
		}
		else
		{
			mcEmergencyStop.TimeCounter = usSRegHoldBuf[DISTIME];
		}
		break;

	case EMER_DISABLE:     // Turn off power and enable DB
		Do_DisableServo();
		
		if (GetReg(usSRegHoldBuf[DISMODE], DYNBRKMODE) == DYNBRK_ALWAYS || 
			(GetReg(usSRegHoldBuf[DISMODE], DYNBRKMODE) == DYNBRK_FAULT && mcFaultSource != FaultNoSource))
		{
			Motor_DynamicBrake_Init();
		} 

		if (mcFocCtrl.RunMod == CURMOD || GetReg(usSRegHoldBuf[DISMODE], DISSTOPMODE) == DISSTOP_COAST)
		{
			mcEmergencyStop.DisSpeed = usSRegHoldBuf[DISSPEED];
			mcEmergencyStop.TimeCounter = usSRegHoldBuf[DISTIME];
			mcEmergencyStop.TimeOutCounter = usSRegHoldBuf[DISTIMEOUT];
		}
		else // Ramp/zero-speed stop doesn't need to reconfirm deceleration to desired value
		{
			mcEmergencyStop.DisSpeed = usSRegHoldBuf[DISSPEED] >> 3;
			mcEmergencyStop.TimeCounter = 5;
			mcEmergencyStop.TimeOutCounter = 200;
		}
		mcEmergencyStop.StateLatch = mcEmergencyStop.State;
		mcEmergencyStop.State = EMER_STOP;
		break;

		
	case EMER_IDLE:
	case EMER_FINISH:     // Exit to mcDisable state
		if (mcFaultSource != FaultNoSource)
		{
			mcState = mcFault;
		}
		else
		{
			mcState = mcIdle;
		}
		mcEmergencyStop.State = EMER_IDLE;
		break;

	default:
		break;
	}
}
	

/*---------------------------------------------------------------------------
 * Name		:	Motor_DynamicBrake_Init
 * Input	:	No
 * Output	:	No
 * Description:	Dynamic brake initialization
 *---------------------------------------------------------------------------*/
void Motor_DynamicBrake_Init(void)
{
	mcEmergencyStop.BrakeArrMax = read_csr(DRV1_ARR) + 1;
	mcEmergencyStop.BrakeArr = mcEmergencyStop.BrakeArrMax >> 1;
	
	clr_csr(DRV1_CR, DRVOE);			// Driver output enable	0-->Disable		1-->Enable
	clr_csr(DRV1_OUT, MOE);		// Main output enable, used to select the source of three-phase upper/lower bridge signals
	clr_csr(DRV1_FCR0, NCALEN);	// Disable FOC calculation enable

	write_csr(DRV1_DR, mcEmergencyStop.BrakeArr);		// Three-phase PWM duty setting
	write_csr(DRV1_CMR, 0x0015);					// Upper transistors fully off, lower transistors fully on

	set_csr(DRV1_OUT, MOE);
	set_csr(DRV1_CR, DRVOE);			// Driver output enable	0-->Disable		1-->Enable
	
	if ((int16)usSRegHoldBuf[STOPCURRENT] > 0)
		mcEmergencyStop.StartBrakeFlag = 1;
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_DynamicBrake_realize
 * Input	:	No
 * Output	:	No
 * Description:	Dynamic braking: adjust duty cycle according to current value
 *---------------------------------------------------------------------------*/
void Motor_DynamicBrake_realize(void)
{
	if (mcEmergencyStop.StartBrakeFlag == 1)
	{
		int16 maxIaIb = MAX(ABS((int16)usSRegInBuf[MB_IA]), ABS((int16)usSRegInBuf[MB_IB]));
		// Calculate ARR value, change duty cycle
		mcEmergencyStop.BrakeArr += ((int16)usSRegHoldBuf[STOPCURRENT] - maxIaIb) >> 6;
		
		if (mcEmergencyStop.BrakeArr > mcEmergencyStop.BrakeArrMax)
			mcEmergencyStop.BrakeArr = mcEmergencyStop.BrakeArrMax;
		else if (mcEmergencyStop.BrakeArr < 1)
			mcEmergencyStop.BrakeArr = 1;
		
		write_csr(DRV1_DR, mcEmergencyStop.BrakeArr);		// Three-phase PWM duty setting	
	}
}


/*---------------------------------------------------------------------------
 * Name		:	RampStop_Init
 * Input	:	No
 * Output	:	No
 * Description:	Deceleration stop initialization
 *---------------------------------------------------------------------------*/
void RampStop_Init(void)
{
	mcEmergencyStop.VelInc = (int32)usSRegHoldBuf[DISDEC];
	if (mcEmergencyStop.VelInc < 1)
		mcEmergencyStop.VelInc = 1;
	
	NFOC_IQMAX = (int16)usSRegHoldBuf[STOPCURLIM];
	NFOC_IQMIN = -(int16)usSRegHoldBuf[STOPCURLIM];

	mcEmergencyStop.StartStopFlag = 1;
	mcFocCtrl.FrcLoopEnable = 0;
	mcFocCtrl.PosLoopEnable = 0;
	mcEmergencyStop.DecStopFlag = 1;
}


/*---------------------------------------------------------------------------
 * Name		:	RampStop_realize
 * Input	:	No
 * Output	:	Planned speed command
 * Description:	Execute deceleration stop, executed in interrupt
 *---------------------------------------------------------------------------*/
int16 RampStop_realize(void)
{
	int32 temp;
	if (mcEmergencyStop.StartStopFlag == 1)
	{
		mcEmergencyStop.StartStopFlag = 0;
		if (GetReg(usSRegHoldBuf[DISMODE], DISSTOPMODE) == DISSTOP_RAMP)
		{
			mcEmergencyStop.VelValue = ((int32)(int16) usSRegInBuf[CMDVEL]) << DISDECSCALE;
			if (usSRegHoldBuf[DISDECTIME] > 0)
			{
				temp = ABS(mcEmergencyStop.VelValue) / VELCTRL_FREQUENCY / usSRegHoldBuf[DISDECTIME];
				if (mcEmergencyStop.VelInc < temp)
					mcEmergencyStop.VelInc = temp;
			}			
		}
		else
		{
			mcEmergencyStop.VelValue = 0;
		}
	}
	
	if (mcEmergencyStop.VelValue > 0)
	{
		mcEmergencyStop.VelValue -= mcEmergencyStop.VelInc;
		if (mcEmergencyStop.VelValue < 0)
		{
			mcEmergencyStop.VelValue = 0;
		}
	}
	else if(mcEmergencyStop.VelValue < 0)
	{
		mcEmergencyStop.VelValue += mcEmergencyStop.VelInc;
		if (mcEmergencyStop.VelValue > 0)
		{
			mcEmergencyStop.VelValue = 0;
		}
	}

	return (int16)(mcEmergencyStop.VelValue >> DISDECSCALE);
}


/*---------------------------------------------------------------------------
 * Name		:	EmergencyStop_TimeCount
 * Input	:	No
 * Output	:	No
 * Description:	Stop time judgment, placed in 1ms loop
 *---------------------------------------------------------------------------*/
void EmergencyStop_TimeCount(void)
{
	if (mcEmergencyStop.TimeCounter > 0)
		mcEmergencyStop.TimeCounter--;   // Stop stationary counter
	
	if (mcEmergencyStop.TimeOutCounter > 0)
		mcEmergencyStop.TimeOutCounter--;   // Stop timeout counter
	
	Motor_DynamicBrake_realize();
}

#endif // #if FUNC_DISMODE_ENABLED


/*---------------------------------------------------------------------------
 * Name		:	Do_DisableServo
 * Input	:	No
 * Output	:	No
 * Description:	Turn off motor power.
 *---------------------------------------------------------------------------*/
void Do_DisableServo(void)
{
	Motor_DisableServo();
	
#if FUNC_DISMODE_ENABLED
	mcEmergencyStop.StartStopFlag = 0;
	mcEmergencyStop.DecStopFlag = 0;
#endif // #if FUNC_DISMODE_ENABLED
	
	if (mcRegParam.WorkMode == COMM_ECAT)
	{
		// Used during ECAT communication to clear edge variables for servo control
		ClrBit(usSRegHoldBuf[DRIVECTRL], CTRL_DISABLE);
		ClrBit(usSRegHoldBuf[DRIVECTRL], CTRL_ENABLE);
		ClrBit(usSRegHoldBuf[PROFILECTRL], PROF_MOTIONEN);
	}
#if FUNC_HOME_ENABLED
	Home_Reset();
#endif //#if FUNC_HOME_ENABLED
}
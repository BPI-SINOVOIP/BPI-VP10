/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Waveform.c
 * Author        : Summer
 * Date          : 2024-10-09
 * Description   : Base function for velocity/ current loop waveform, including
 *					trap, sin, constant.
 *
 * Record        :
 * V1.0, 2024-10-09, Summer: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include "Myproject.h"


/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
SigGenTypeDef mcSigGen = { 0 };
SINSWEEP_Typedef SinSweep = { 0 };
#if FUNC_SWEEP_ENABLED
CHIRPSWEEP_Typedef ChirpSweep = { 0 };
#endif


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------
 * Name		:	Motor_SerialIn_Update
 * Input	:	No
 * Output	:	No
 * Description:	Update serial velocity/serial current
 *---------------------------------------------------------------------------*/
void Motor_SerialIn_Update(void)
{
	uint8 motionFlag_Pre, motionFlag;
	
	if ((mcRegParam.WorkMode == VELSERIAL) || (mcRegParam.WorkMode == CURSERIAL) ||
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
		(usSRegInBuf[FBOPMODE] == PROFILE_VELOCITY_MODE) || (usSRegInBuf[FBOPMODE] == PROFILE_TORQUE_MODE) ||
#endif
		(mcRegParam.WorkMode == VELFRF) || (mcRegParam.WorkMode == CURFRF) || (mcRegParam.WorkMode == CURTUNE))
	{	
		motionFlag_Pre = GetReg(mcRegParam.ProfileCtrl, PROF_MOTIONEN);
		motionFlag = GetReg(usSRegHoldBuf[PROFILECTRL], PROF_MOTIONEN);
		
		if (motionFlag && !motionFlag_Pre)// MOTIONEN rising edge
		{
			Motor_SerialIn_Init();
		}

		// Stop motion
		if (!motionFlag && motionFlag_Pre) // MOTIONEN falling edge
		{
			Motor_SerialIn_StartDeceleration();	
		}
	}
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_SerialIn_Update
 * Input	:	No
 * Output	:	No
 * Description:	Initialize serial velocity/serial current
 *---------------------------------------------------------------------------*/
void Motor_SerialIn_Init(void)
{
	memset(&mcSigGen, 0, sizeof(SigGenTypeDef));

	// Serial velocity-loop mode
	if (GetReg(usSRegHoldBuf[PROFILECTRL], PROF_VELJOG) 
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
		|| usSRegInBuf[FBOPMODE] == PROFILE_VELOCITY_MODE
		|| usSRegInBuf[FBOPMODE] == PROFILE_TORQUE_MODE
#endif
		)
	{
		mcSigGen.WaveType = WAVE_CONST;
		mcSigGen.Scale = VEL_SCALE_SHIFT;
		mcSigGen.TestCmd = (((int32)(int16)usSRegHoldBuf[WAVECMD]) << mcSigGen.Scale);
		mcSigGen.TestInc = ((int32)usSRegHoldBuf[WAVEINC]);
	}
#if FUNC_FORCECTRL_ENABLED
	else if (usSRegHoldBuf[FCMOD]) // Force control mode
	{
		if (mcRegParam.WorkMode == VELSERIAL)
			mcSigGen.Scale = VEL_SCALE_SHIFT;
		else
		{
			mcSigGen.Scale = FRC_SCALE_SHIFT;
			mcSigGen.Value = (((int32)ForceCtrl.SwitchCurCmd) << mcSigGen.Scale);
		}

		mcSigGen.TestCmd = (((int32)ForceCtrl.TestCmdPort) << mcSigGen.Scale);
		mcSigGen.TestInc = ((int32)ForceCtrl.TestIncPort);
		mcSigGen.WaveType = WAVE_CONST;
	}
#endif
#if SPECIAL_ELESCREW_ENABLE
	else if (usSRegHoldBuf[ESCMOD]) // Electric screwdriver mode
	{
		if (mcRegParam.WorkMode == VELSERIAL)
			mcSigGen.Scale = VEL_SCALE_SHIFT;
		else
		{
			mcSigGen.Scale = FRC_SCALE_SHIFT;
			mcSigGen.Value = (((int32)ScrewCtrl.SwitchCurCmd) << mcSigGen.Scale);
		}

		mcSigGen.TestCmd = (((int32)ScrewCtrl.TestCmdPort) << mcSigGen.Scale);
		mcSigGen.TestInc = ((int32)ScrewCtrl.TestIncPort);
		mcSigGen.WaveType = WAVE_CONST;
	}
#endif // #if FUNC_FORCECTRL_ENABLED
	else // Normal mode
	{
		mcSigGen.WaveType = usSRegHoldBuf[WAVETYPE];

		if (mcSigGen.WaveType == WAVE_SIN)
		{
			SinSweepFreInit(mcRegParam.WorkMode);
		}
#if FUNC_SWEEP_ENABLED
		else if (mcSigGen.WaveType == WAVE_CHIRP)
		{
			ChirpSweepFreInit(mcRegParam.WorkMode);
		}
#endif
		else
		{
			if (mcRegParam.WorkMode == VELSERIAL) // Serial velocity-loop mode
			{
				mcSigGen.Scale = VEL_SCALE_SHIFT;
				mcSigGen.DwellTime = (uint32)usSRegHoldBuf[WAVEDWELLTIME] * SERIAL_VELOCITY_FREQUENCY;
				mcSigGen.PosConstTime = (uint32)usSRegHoldBuf[WAVEPOSTIME] * SERIAL_VELOCITY_FREQUENCY;
				mcSigGen.NegConstTime = (uint32)usSRegHoldBuf[WAVENEGTIME] * SERIAL_VELOCITY_FREQUENCY;
			}
			else if (mcRegParam.WorkMode == CURSERIAL || mcRegParam.WorkMode == CURTUNE) // Serial current mode
			{
				mcSigGen.Scale = CUR_SCALE_SHIFT;

mcSigGen.DwellTime = usSRegHoldBuf[WAVEDWELLTIME];
				mcSigGen.PosConstTime = usSRegHoldBuf[WAVEPOSTIME];
				mcSigGen.NegConstTime = usSRegHoldBuf[WAVENEGTIME];
			}
			else	// serial pressure mode
			{
				mcSigGen.Scale = FRC_SCALE_SHIFT;
				mcSigGen.DwellTime = usSRegHoldBuf[WAVEDWELLTIME];
				mcSigGen.PosConstTime = usSRegHoldBuf[WAVEPOSTIME];
				mcSigGen.NegConstTime = usSRegHoldBuf[WAVENEGTIME];
			}

			mcSigGen.TestCmd = (((int32)(int16)usSRegHoldBuf[WAVECMD]) << mcSigGen.Scale);
			mcSigGen.TestInc = ((int32)usSRegHoldBuf[WAVEINC]);
		}
	}

	if (mcSigGen.WaveType == WAVE_CONST)
	{
		mcSigGen.CycleCounter = 1;
	}
	else
	{
		mcSigGen.CycleCounter = ((int32)usSRegHoldBuf[WAVEREPTIMES]) << 1;
		if (mcSigGen.CycleCounter == 0) // infinite loop
		{
			mcSigGen.CycleCounter = -1;
		}
	}

	// Start Motion Planning
	if (mcSigGen.TestCmd >= 0)
		mcSigGen.State = WSTEP_POSACC;
	else
	{
		mcSigGen.TestCmd = -mcSigGen.TestCmd;
		mcSigGen.State = WSTEP_NEGACC;
	}

	if (mcSigGen.TestInc <= 0)
		mcSigGen.TestInc = 1;

	mcSigGen.WaveCmdLatch = usSRegHoldBuf[WAVECMD];
	mcSigGen.Status = MS_READY;
	
	Motor_SerialIn_StartMove();
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_SerialIn_StartMove
 * Input	:	No
 * Output	:	No
 * Description:	Start serial speed/serial current
 *---------------------------------------------------------------------------*/
void Motor_SerialIn_StartMove(void)
{
	mcSigGen.Status = MS_MOVING;
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_SerialIn_StartSuspend
 * Input	:	No
 * Output	:	No
 * Description:	Set running state of serial speed/serial current to suspend
 *---------------------------------------------------------------------------*/
void Motor_SerialIn_StartSuspend(void)
{
	mcSigGen.Status = MS_SUSPEND;
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_SerialIn_StartDeceleration
 * Input	:	No
 * Output	:	No
 * Description:	Set running state of serial speed/serial current to deceleration
 *---------------------------------------------------------------------------*/
void Motor_SerialIn_StartDeceleration(void)
{
	mcSigGen.Status = MS_DECELERATION;
}


/*---------------------------------------------------------------------------
 * Name		:	Motor_SerialIn_Handler
 * Input	:	No
 * Output	:	No
 * Description:	Run serial speed/serial current, call this function every cycle time.
 *---------------------------------------------------------------------------*/
int16 Motor_SerialIn_Handler(void)
{
	int16 waveOut = 0;

	if (mcSigGen.WaveType == WAVE_SIN)
	{
		if (mcSigGen.Status == MS_MOVING)
			waveOut = SinSweepFre();
	}
#if FUNC_SWEEP_ENABLED
	else if (mcSigGen.WaveType == WAVE_CHIRP)
	{
		if (mcSigGen.Status == MS_MOVING)
			waveOut = ChirpSweepFre();
	}
#endif
	else
	{
		if (mcSigGen.Status == MS_MOVING)
		{
			if (mcSigGen.WaveType == WAVE_CONST && mcSigGen.WaveCmdLatch != usSRegHoldBuf[WAVECMD]) // dynamically change speed
			{
				mcSigGen.WaveCmdLatch = usSRegHoldBuf[WAVECMD];
				mcSigGen.TestCmd = (((int32)(int16)usSRegHoldBuf[WAVECMD]) << mcSigGen.Scale);
				mcSigGen.TestInc = ((int32)usSRegHoldBuf[WAVEINC]);
				mcSigGen.CycleCounter = 1;
				
				if (mcSigGen.TestCmd >= mcSigGen.Value)
				{
					mcSigGen.State = WSTEP_POSACC;
				}
				else
				{
					mcSigGen.TestCmd = -mcSigGen.TestCmd;
					mcSigGen.State = WSTEP_NEGACC;
				}

				if (mcSigGen.TestInc <= 0)
					mcSigGen.TestInc = 1;
			}
			
			switch (mcSigGen.State)
			{
			case WSTEP_WAIT: // Wait
				if (++mcSigGen.TimeCounter >= mcSigGen.WaitTime)
				{
					mcSigGen.TimeCounter = 0;
					mcSigGen.State = mcSigGen.NextState;
				}
				break;

			case WSTEP_POSACC:
				mcSigGen.Value += mcSigGen.TestInc;
				if (mcSigGen.Value >= mcSigGen.TestCmd)
				{
					mcSigGen.Value = mcSigGen.TestCmd;
					if (mcSigGen.CycleCounter >= 0 && --mcSigGen.CycleCounter == 0)
					{
						mcSigGen.State = WSTEP_HOLD;

}
					else
					{
						mcSigGen.State = WSTEP_WAIT;
						mcSigGen.WaitTime = mcSigGen.PosConstTime;
						if (mcSigGen.WaveType == WAVE_TRAPEXT)
							mcSigGen.NextState = WSTEP_POSDEC;
						else
							mcSigGen.NextState = WSTEP_NEGACC;
					}
				}
				break;

			case WSTEP_POSDEC:
				mcSigGen.Value -= mcSigGen.TestInc;
				if (mcSigGen.Value <= 0)
				{
					mcSigGen.Value = 0;
					if (mcSigGen.CycleCounter >= 0 && --mcSigGen.CycleCounter == 0)
					{
						mcSigGen.State = WSTEP_HOLD;
					}
					else
					{
						mcSigGen.State = WSTEP_WAIT;
						mcSigGen.NextState = WSTEP_NEGACC;
						mcSigGen.WaitTime = mcSigGen.DwellTime;
					}
				}
				break;

			case WSTEP_NEGACC:
				mcSigGen.Value -= mcSigGen.TestInc;
				if (mcSigGen.Value <= -mcSigGen.TestCmd)
				{
					mcSigGen.Value = -mcSigGen.TestCmd;
					if (mcSigGen.CycleCounter >= 0 && --mcSigGen.CycleCounter == 0)
					{
						mcSigGen.State = WSTEP_HOLD;
					}
					else
					{
						mcSigGen.State = WSTEP_WAIT;
						mcSigGen.WaitTime = mcSigGen.NegConstTime;
						if (mcSigGen.WaveType == WAVE_TRAPEXT)
							mcSigGen.NextState = WSTEP_NEGDEC;
						else
							mcSigGen.NextState = WSTEP_POSACC;
					}
				}
				break;

			case WSTEP_NEGDEC:
				mcSigGen.Value += mcSigGen.TestInc;
				if (mcSigGen.Value >= 0)
				{
					mcSigGen.Value = 0;
					if (mcSigGen.CycleCounter >= 0 && --mcSigGen.CycleCounter == 0)
					{
						mcSigGen.State = WSTEP_HOLD;
					}
					else
					{
						mcSigGen.State = WSTEP_WAIT;
						mcSigGen.NextState = WSTEP_POSACC;
						mcSigGen.WaitTime = mcSigGen.DwellTime;
					}
				}
				break;

			default:
				break;
			}

		}
		else if (mcSigGen.Status == MS_SUSPEND)
		{
			mcSigGen.Status = MS_SUSPEND;
		}
		else if (mcSigGen.Status == MS_DECELERATION)
		{
			if (mcSigGen.Value >= 0)
			{
				mcSigGen.Value -= mcSigGen.TestInc;
				if (mcSigGen.Value <= 0)
				{
					mcSigGen.Value = 0;
					mcSigGen.Status = MS_FINISH;
				}
			}
			else // if(mcSigGen.Value < 0)
			{
				mcSigGen.Value += mcSigGen.TestInc;
				if (mcSigGen.Value >= 0)
				{
					mcSigGen.Value = 0;
					mcSigGen.Status = MS_FINISH;
				}
			}
		}
		waveOut = mcSigGen.Value >> mcSigGen.Scale;
	}
	return waveOut;
}


/*---------------------------------------------------------------------------
 * Name		:	SinSweepFreInit
 * Input	:	No
 * Output	:	No
 * Description:	Sine (Sin) initialization
 *---------------------------------------------------------------------------*/
void SinSweepFreInit(uint16 workLoop)
{
	uint16 sinLoopFreq = 0;
	if (workLoop == 0) // Velocity loop
		sinLoopFreq = VELFILE_FREQUENCY;
	else
		sinLoopFreq = CURFILE_FREQUENCY;
	SinSweep.SweepFrequencyValue = usSRegHoldBuf[SINFRE];
	SinSweep.SweepFrequencyStep = (uint32)(SinSweep.SweepFrequencyValue << 16) / 10 / sinLoopFreq;
	SinSweep.Index = usSRegHoldBuf[SINPHASE];
	SinSweep.Vs = usSRegHoldBuf[SINVS];
}


/*---------------------------------------------------------------------------
 * Name		:	SinSweepFre
 * Input	:	No
 * Output	:	Sin signal
 * Description:	Generate sine (Sin) signal, call this function every cycle time.
 *---------------------------------------------------------------------------*/
int16 SinSweepFre(void)
{
	SinSweep.Index = SinSweep.Index + SinSweep.SweepFrequencyStep + 1;
	SinSweep.Out = SinCalc(SinSweep.Index, SinSweep.Vs);

	return SinSweep.Out;
}

#if FUNC_SWEEP_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	ChirpSweepFreInit
 * Input	:	No
 * Output	:	No
 * Description:	Chirp sine sweep initialization
 *---------------------------------------------------------------------------*/
void ChirpSweepFreInit(uint16 workLoop)
{
	uint16 samFreq = 0;

if (workLoop == VELSERIAL) // velocity loop
		samFreq = VELFILE_FREQUENCY;
	else // CURSERIAL/VELFRF/CURFRF
		samFreq = CURFILE_FREQUENCY;

	int32 startFreq, endFreq;
	startFreq = (int32)usSRegHoldBuf[SWEEPSTARTFREQ];
	endFreq = (int32)usSRegHoldBuf[SWEEPENDFREQ];
	ChirpSweep.Point = (int32)usSRegHoldBuf[SWEEPPOINT];
	if (samFreq == 0 || endFreq < startFreq || ChirpSweep.Point == 0)
	{
		ChirpSweep.LinCoe = 0;
		ChirpSweep.QuadCoe = 0;
	}
	else
	{
		ChirpSweep.LinCoe = ((int64)startFreq << 32) / 10 / samFreq;
		ChirpSweep.QuadCoe = ((int64)(endFreq - startFreq) << 32) / 10 / 2 / samFreq / ChirpSweep.Point;
	}

	ChirpSweep.Index = 0;
	ChirpSweep.Amp = usSRegHoldBuf[SWEEPAMP];
}


/*---------------------------------------------------------------------------
 * Name		:	ChirpSweepFre
 * Input	:	No
 * Output	:	Chirp signal
 * Description:	Run sinusoidal Chirp sweep, call this function every cycle time.
 *---------------------------------------------------------------------------*/
int16 ChirpSweepFre(void)
{
	int16 sweepOut, sweepTheta;

	if (ChirpSweep.Index <= ChirpSweep.Point)
	{
		sweepTheta = (ChirpSweep.LinCoe * ChirpSweep.Index + ChirpSweep.QuadCoe * ChirpSweep.Index * ChirpSweep.Index) >> 16;
		sweepOut = SinCalc(sweepTheta, ChirpSweep.Amp);
		ChirpSweep.Index++;
	}

	return sweepOut;
}
#endif // #if FUNC_SWEEP_ENABLED

#if FUNC_CURTUNE_ENABLED
/*---------------------------------------------------------------------------
 * Name		:	Motor_TuningSignal_Handler
 * Input	:	*id - output updated Id command
 *				*iq - output updated Iq command
 * Output	:	No
 * Description:	Current Loop Tuning Signal Handler, square wave for Id and Iq
 *---------------------------------------------------------------------------*/
void Motor_TuningSignal_Handler(int16* id, int16* iq)
{
	int16 waveOut = 0;
	if (mcSigGen.Status == MS_MOVING)
	{
		if (mcSigGen.State == 1 || mcSigGen.State == 3)
		{
			if (mcSigGen.TimeCounter >= mcSigGen.DwellTime)
			{
				mcSigGen.TimeCounter = 0;
				mcSigGen.State = 3 - mcSigGen.State;
				if (mcSigGen.State == 0)
				{
					if (mcSigGen.Scale == 1)
						mcSigGen.State = 4;
					else
						mcSigGen.Scale = 1;
				}
			}
			else
				mcSigGen.TimeCounter++;
		}

		if (mcSigGen.State == 0)  // Acceleration
		{
			if (mcSigGen.Value + mcSigGen.TestInc >= mcSigGen.TestCmd)
			{
				mcSigGen.Value = mcSigGen.TestCmd;
				mcSigGen.State = 1;
			}
			else
				mcSigGen.Value += mcSigGen.TestInc;
		}
		else if (mcSigGen.State == 2)  // Deceleration
		{
			if (mcSigGen.Value - mcSigGen.TestInc <= 0)
			{
				mcSigGen.Value = 0;
				mcSigGen.State = 3;
			}
			else
				mcSigGen.Value -= mcSigGen.TestInc;
		}

		if (mcSigGen.Scale == 1)
			*iq = mcSigGen.Value;
		else
			*id = mcSigGen.Value;

		usSRegInBuf[MB_ID] = NFOC_ID;
		usSRegInBuf[MB_UD] = NFOC_UDFIN;
		usSRegInBuf[MB_UQ] = NFOC_UQFIN;
	}
}
#endif // #if FUNC_CURTUNE_ENABLED
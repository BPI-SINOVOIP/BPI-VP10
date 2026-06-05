/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Waveform.c
 * Author        : Summer
 * Date          : 2024-10-09
 * Description   : Base function for velocity/ current loop waveform.
 *
 * Record        :
 * V1.0, 2024-10-09, Summer: Created file
 */

/* Includes -------------------------------------------------------------------------------------*/
#include "Myproject.h"

SigGenTypeDef mcSigGen = { 0 };
SINSWEEP_Typedef SinSweep = { 0 };
#if FUNC_SWEEP_ENABLED
CHIRPSWEEP_Typedef ChirpSweep = { 0 };
#endif

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_SerialIn_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Initialize profile variable
/*---------------------------------------------------------------------------*/
void Motor_SerialIn_Init(void)
{
	memset(&mcSigGen, 0, sizeof(SigGenTypeDef));

	// 串行速度环模式
	if (GetReg(usSRegHoldBuf[PROFILECTRL], PROF_VELJOG) 
#if EXCTRL_ECAT_ENABLED || EXCTRL_CANOPEN_ENABLED
		|| usSRegInBuf[FBOPMODE] == PROFILE_VELOCITY_MODE
		|| usSRegInBuf[FBOPMODE] == PROFILE_TORQUE_MODE
#endif
		)
	{
		mcSigGen.WaveType = WAVE_CONST;
		mcSigGen.Scale = 8;
		mcSigGen.TestCmd = (((int32)(int16)usSRegHoldBuf[WAVECMD]) << mcSigGen.Scale);
		mcSigGen.TestInc = ((int32)usSRegHoldBuf[WAVEINC]);
	}
#if FUNC_FORCECTRL_ENABLED
	else if (usSRegHoldBuf[FCMOD]) // 力控模式
	{
		if (mcRegParam.WorkMode == VELSERIAL)
			mcSigGen.Scale = 8;
		else
		{
			mcSigGen.Scale = 12;
			mcSigGen.Value = (((int32)ForceCtrl.SwitchCurCmd) << mcSigGen.Scale);
		}

		mcSigGen.TestCmd = (((int32)ForceCtrl.TestCmdPort) << mcSigGen.Scale);
		mcSigGen.TestInc = ((int32)ForceCtrl.TestIncPort);
		mcSigGen.WaveType = WAVE_CONST;
	}
#endif
#if SPECIAL_ELESCREW_ENABLE
	else if (usSRegHoldBuf[ESCMOD]) // 电批模式
	{
		if (mcRegParam.WorkMode == VELSERIAL)
			mcSigGen.Scale = 8;
		else
		{
			mcSigGen.Scale = 12;
			mcSigGen.Value = (((int32)ScrewCtrl.SwitchCurCmd) << mcSigGen.Scale);
		}

		mcSigGen.TestCmd = (((int32)ScrewCtrl.TestCmdPort) << mcSigGen.Scale);
		mcSigGen.TestInc = ((int32)ScrewCtrl.TestIncPort);
		mcSigGen.WaveType = WAVE_CONST;
	}
#endif // #if FUNC_FORCECTRL_ENABLED
	else // 普通模式
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
			if (mcRegParam.WorkMode == VELSERIAL) // 串行速度环模式
			{
				mcSigGen.Scale = 8;
				mcSigGen.DwellTime = (uint32)usSRegHoldBuf[WAVEDWELLTIME] * SERIAL_VELOCITY_FREQUENCY;
				mcSigGen.PosConstTime = (uint32)usSRegHoldBuf[WAVEPOSTIME] * SERIAL_VELOCITY_FREQUENCY;
				mcSigGen.NegConstTime = (uint32)usSRegHoldBuf[WAVENEGTIME] * SERIAL_VELOCITY_FREQUENCY;
			}
			else if (mcRegParam.WorkMode == CURSERIAL || mcRegParam.WorkMode == CURTUNE) // 串行电流模式
			{
				mcSigGen.Scale = 0;
				mcSigGen.DwellTime = usSRegHoldBuf[WAVEDWELLTIME];
				mcSigGen.PosConstTime = usSRegHoldBuf[WAVEPOSTIME];
				mcSigGen.NegConstTime = usSRegHoldBuf[WAVENEGTIME];
			}
			else	// 串行压力模式
			{
				mcSigGen.Scale = 12;
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
		if (mcSigGen.CycleCounter == 0) // 无限循环
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


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_SerialIn_StartMove(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	VelSerial and CurSerial StartMove
/*---------------------------------------------------------------------------*/
void Motor_SerialIn_StartMove(void)
{
	mcSigGen.Status = MS_MOVEING;
}

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_SerialIn_StartDeceleration(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	VelSerial and CurSerial StartDeceleration
/*---------------------------------------------------------------------------*/
void Motor_SerialIn_StartSuspend(void)
{
	mcSigGen.Status = MS_SUSPEND;
}

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_SerialIn_StartDeceleration(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	VelSerial and CurSerial StartDeceleration
/*---------------------------------------------------------------------------*/
void Motor_SerialIn_StartDeceleration(void)
{
	mcSigGen.Status = MS_DECELERATION;
}


/*---------------------------------------------------------------------------*/
/* Name		:	int16 Motor_SerialIn_Handler(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	VelSerial and CurSerial Control
/*---------------------------------------------------------------------------*/
int16 Motor_SerialIn_Handler(void)
{
	int16 waveOut = 0;

	if (mcSigGen.WaveType == WAVE_SIN)
	{
		if (mcSigGen.Status == MS_MOVEING)
			waveOut = SinSweepFre();
	}
#if FUNC_SWEEP_ENABLED
	else if (mcSigGen.WaveType == WAVE_CHIRP)
	{
		if (mcSigGen.Status == MS_MOVEING)
			waveOut = ChirpSweepFre();
	}
#endif
	else
	{
		if (mcSigGen.Status == MS_MOVEING)
		{
			if (mcSigGen.WaveType == WAVE_CONST && mcSigGen.WaveCmdLatch != usSRegHoldBuf[WAVECMD]) // 动态改变速度
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
			case WSTEP_WAIT: // 等待
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


/*---------------------------------------------------------------------------*/
/* Name		:	SinSweepFreInit
/* Input	:	NO
/* Output	:	NO
/* Description:	正弦扫频初始化
/*---------------------------------------------------------------------------*/
void SinSweepFreInit(uint16 workLoop)
{
	uint16 sinLoopFreq = 0;
	if (workLoop == 0) // 速度环
		sinLoopFreq = VELFILE_FREQUENCY;
	else
		sinLoopFreq = CURFILE_FREQUENCY;
	SinSweep.SweepFrequencyValue = usSRegHoldBuf[SINFRE];
	SinSweep.SweepFrequencyStep = (uint32)(SinSweep.SweepFrequencyValue << 16) / 10 / sinLoopFreq;
	SinSweep.Index = usSRegHoldBuf[SINPHASE];
	SinSweep.Vs = usSRegHoldBuf[SINVS];
}


/*---------------------------------------------------------------------------*/
/* Name		:	SinSweepFre
/* Input	:	NO
/* Output	:	NO
/* Description:	正弦扫频输出
/*---------------------------------------------------------------------------*/
int16 SinSweepFre(void)
{
	SinSweep.Index = SinSweep.Index + SinSweep.SweepFrequencyStep + 1;
	SinSweep.Out = SinCalc(SinSweep.Index, SinSweep.Vs);

	return SinSweep.Out;
}

#if FUNC_SWEEP_ENABLED
/*---------------------------------------------------------------------------*/
/* Name		:	ChirpSweepFreInit
/* Input	:	NO
/* Output	:	NO
/* Description:	Chirp扫频初始化
/*---------------------------------------------------------------------------*/
void ChirpSweepFreInit(uint16 workLoop)
{
	uint16 samFreq = 0;

	if (workLoop == VELSERIAL) // 速度环
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


/*---------------------------------------------------------------------------*/
/* Name		:	ChirpSweepFre
/* Input	:	NO
/* Output	:	NO
/* Description:	Chirp扫频输出
/*---------------------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_TuningSignal_Handler(int16* id, int16* iq)
/* Input	:	NO
/* Output	:	NO
/* Description:	Current Loop Tuning Signal Handler, square wave for Id and Iq
/*---------------------------------------------------------------------------*/
void Motor_TuningSignal_Handler(int16* id, int16* iq)
{
	int16 waveOut = 0;
	if (mcSigGen.Status == MS_MOVEING)
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
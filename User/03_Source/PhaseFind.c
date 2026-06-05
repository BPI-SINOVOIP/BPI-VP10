/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PhaseFind.c
 * Author        : Summer
 * Date          : 2021-11-13
 * Description   : define some function for phasefind.
 *
 * Record        :
 * V1.0, 2021-11-13, Summer: Created file
 */


/* Includes -------------------------------------------------------------------------------------*/
#include <Myproject.h>
#include "PhaseFind.h"

PhaseFindTypeDef mcDoPhaseFind;
ElecAngTypeDef mcElecAng;
pvMotorPhaseFindStart pvMotor_PhaseFind_Start;


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_PhaseFind_Init(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Initial Phase Find
/*---------------------------------------------------------------------------*/
void Motor_PhaseFind_Init(void)
{
	if (McStaSet.SetFlag.PhaseFindSetFlag == 0)
	{
		memset(&mcDoPhaseFind, 0, sizeof(PhaseFindTypeDef));	 // reset phase find
		
		if ((!McStaSet.SetFlag.AutoPhaseFindSetFlag) &&
			(ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ENCABS) || usSRegHoldBuf[MOTORCOMMTYPE] == VOICECOIL_MOTOR))
		{
			usSRegInBuf[ELECANGOFFSET] = usSRegHoldBuf[ELECANGSHIFT];
			McStaSet.SetFlag.AutoPhaseFindSetFlag = 1;
			mcDoPhaseFind.FinishFlag = 1;
			return;
		}

#if ENCODER_SEL_HALL_ENABLED
		Hall_Init();
		if ((!McStaSet.SetFlag.AutoPhaseFindSetFlag) && 
			(usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_ABZ_HALL || usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_HALLS_ONLY))
		{
			if(usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_ABZ_HALL)
				UpdateHallTheta();

			McStaSet.SetFlag.AutoPhaseFindSetFlag = 1;
			mcDoPhaseFind.FinishFlag = 1;
			return;
		}
#endif // #if ENCODER_SEL_HALL_ENABLED
		
		FOC_Init();   /*FOC Initialize*/

		NFOC_IDREF = 0;
		NFOC_IQREF = 0;
		usSRegInBuf[CMDCUR] = 0;
		usSRegInBuf[MB_IDREF] = 0;
		

		mcDoPhaseFind.pQepAngle = &mcFocCtrl.QepPos;
		mcDoPhaseFind.pActVel = &usSRegInBuf[ACTVEL];

		mcFocCtrl.State_Count = usSRegHoldBuf[PHASEFINDTIMEOUT];

		mcElecAng.FOCThetaFlag = 1;     // lock the NFOC_THETAH
		Delay_ms(2);  // Wait until mcElecAng.FOCThetaFlag work
		if (usSRegHoldBuf[PHASEFINDMODE] != PHASEFIND_HALLLEARN)
		{
			NFOC_THETAH = 0;    // Initial ElecAngle
		}
		
		if (usSRegHoldBuf[PHASEFINDMODE] != PHASEFIND_HALLLEARN)
		{
			mcElecAng.ElecAngOffset = 0;
			usSRegInBuf[ELECANGOFFSET] = 0;
		}
		else
		{
			mcElecAng.ElecAngOffset = usSRegInBuf[ELECANGOFFSET];
		}
		Delay_ms(2);  // Wait until mcElecAng.FOCTheta update

		mcFocCtrl.CurLoopEnable = 1;
		mcFocCtrl.VelLoopEnable = 0;
		mcFocCtrl.PosLoopEnable = 0;
#if FUNC_FORCECLOSEDLOOP_ENABLED
		mcFocCtrl.FrcLoopEnable = 0;
#endif

		mcDoPhaseFind.IdTarget = usSRegHoldBuf[PHASEFINDCURRENT];
		mcDoPhaseFind.IdStep = usSRegHoldBuf[PHASEFINDIDSTEP];
		mcDoPhaseFind.FOCThetaDelta = usSRegHoldBuf[PHASEFINDTANGLESTEP];
		mcDoPhaseFind.MoveLimit = usSRegHoldBuf[PHASEFINDMOVEMENT];
		mcDoPhaseFind.WorkTime = usSRegHoldBuf[PHASEFINDTIME];

		if (usSRegHoldBuf[PHASEFINDMODE] == PHASEFIND_NORMALSTART)
		{
			mcDoPhaseFind.FOCThetaTarget = 16384; // 90 elec degree
			mcDoPhaseFind.DeltaAngle = 5;
			mcDoPhaseFind.Cnt = 0;
			mcDoPhaseFind.ActualAngleLatch = 0;
			pvMotor_PhaseFind_Start = Motor_PhaseFind_NormalStart;
		}
		else if (usSRegHoldBuf[PHASEFINDMODE] == PHASEFIND_SMOOTHSTART)
		{
			mcDoPhaseFind.TimeStamp = mcDoPhaseFind.WorkTime;
			mcDoPhaseFind.SuspendTime = mcDoPhaseFind.WorkTime; // 50;
			mcDoPhaseFind.PhaseInc = 16384;
			mcDoPhaseFind.QepAngleComp = *mcDoPhaseFind.pQepAngle;
			pvMotor_PhaseFind_Start = Motor_PhaseFind_SmoothStart;
		}
		
#if ENCODER_SEL_HALL_ENABLED
		else if (usSRegHoldBuf[PHASEFINDMODE] == PHASEFIND_HALLLEARN)
		{
			pvMotor_PhaseFind_Start = DoHallLearning;
		}
#endif
		else // if (usSRegHoldBuf[PHASEFINDMODE] == PHASEFIND_AUTOPHASE)
		{
			mcDoPhaseFind.FOCThetaTarget = ((int32)usSRegHoldBuf[PHASEFINDMOVEANG_H] << 16) + (uint32)usSRegHoldBuf[PHASEFINDMOVEANG_L];
			if (mcDoPhaseFind.FOCThetaTarget > 0)
			{
				mcDoPhaseFind.FOCThetaSign = 1;
			}
			else
			{
				mcDoPhaseFind.FOCThetaSign = -1;
				mcDoPhaseFind.FOCThetaTarget = -mcDoPhaseFind.FOCThetaTarget;
			}
				
			if (mcDoPhaseFind.FOCThetaTarget < 7281) // 40 degree
			{
				mcDoPhaseFind.Error = PFERR_TARANG;
			}
			else
			{
				mcDoPhaseFind.QepAngleComp = mcDoPhaseFind.FOCThetaTarget >> 2;
				if (mcDoPhaseFind.QepAngleComp > 16384) // 90 degree
					mcDoPhaseFind.FOCThetaInit = 16384;
				else if (mcDoPhaseFind.QepAngleComp < 3641) // 20 degree
					mcDoPhaseFind.FOCThetaInit = 3641;
				else
					mcDoPhaseFind.FOCThetaInit = mcDoPhaseFind.QepAngleComp;

				mcDoPhaseFind.QepAngleComp = (mcDoPhaseFind.FOCThetaTarget - mcDoPhaseFind.FOCThetaInit) * mcDoPhaseFind.FOCThetaSign;  // 360 elec degree
				usSRegInBuf[HALLTHETA4] = mcDoPhaseFind.QepAngleComp;
				usSRegInBuf[HALLTHETA5] = mcDoPhaseFind.QepAngleComp >> 16;
			}
			pvMotor_PhaseFind_Start = Motor_AutoPhase;
		}

#if (HW_UVW_POLARITY == UVWPOL_NORMAL)
		write_csr(DRV1_CMR, 0x0abF);
#else
		write_csr(DRV1_CMR, 0x057F);
#endif
		set_csr(DRV1_OUT, MOE);
		set_csr(DRV1_CR, DRVOE);			// Driver输出使能	0-->Disable		1-->Enable

		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_PHASEFINDSUCCEED, 0);
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE, STATUS_ENABLE);
		
		McStaSet.SetFlag.PhaseFindSetFlag = 1;
		McStaSet.SetFlag.AutoPhaseFindSetFlag = 1;	
	}
}

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_PhaseFind_Update(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Update Phase Find success Flag.
/*---------------------------------------------------------------------------*/
void Motor_PhaseFind_Update(void)
{
	if (!GetReg(mcRegParam.DriveCtrl, CTRL_CLEARPHASEFIND) &&
		GetReg(usSRegHoldBuf[DRIVECTRL], CTRL_CLEARPHASEFIND))
	{
		McStaSet.SetFlag.AutoPhaseFindSetFlag = 0;
		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_PHASEFINDSUCCEED, 0);
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_PhaseFind(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	Do Phase Find, call this function every cycle.
/*---------------------------------------------------------------------------*/
void Motor_PhaseFind(void)
{
	if (mcFocCtrl.State_Count <= 2 || mcDoPhaseFind.Error != 0)  // TimeOut / Phase find parameter error / No Encoder Signal
	{
		if (mcFocCtrl.State_Count <= 2)
			mcDoPhaseFind.Error = PFERR_TIMEOUT;
		
		usSRegInBuf[PHASEFINDERR] = mcDoPhaseFind.Error;
		mcFaultSource = FaultPhaseFindFailed;
		FaultProcess();
		mcDoPhaseFind.IdRef = 0;
	}
#if ENCODER_SEL_HALL_ENABLED
	else if(mcHall.Error) // 
	{
		mcFaultSource = FaultPhaseFindFailed;
		FaultProcess();
		mcDoPhaseFind.IdRef = 0;
	}
#endif

	if (mcDoPhaseFind.StartFlag == 0) // 启动加个延时
	{
		mcDoPhaseFind.TimeCounter++;
		if (mcDoPhaseFind.TimeCounter > 20)
		{
			mcDoPhaseFind.TimeCounter = 0;
			mcDoPhaseFind.StartFlag = 1;
		}
	}
	else
	{
		pvMotor_PhaseFind_Start();
	}
	usSRegInBuf[ELECANGOFFSET] = mcElecAng.ElecAngOffset;
	usSRegInBuf[MB_IDREF] = mcDoPhaseFind.IdRef;
	
	if (mcDoPhaseFind.FinishFlag && ReadBit(usSRegHoldBuf[DRIVEMODE], MODE_ENCABS))
	{
		usSRegHoldBuf[ELECANGSHIFT] = usSRegInBuf[ELECANGOFFSET];
	}
}


/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_AutoPhase(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	move motor 360 degree electric angle.
/*---------------------------------------------------------------------------*/
void Motor_AutoPhase(void)
{
	// State Machine
	if (mcDoPhaseFind.State < APSM_SETID)  // Increase mcDoPhaseFind.IdRef
	{
		mcDoPhaseFind.State = APSM_SETID;
		mcDoPhaseFind.FOCThetaValue = 0;
	}
	else if (mcDoPhaseFind.State == APSM_SETID)  // Increase mcDoPhaseFind.IdRef
	{
		mcDoPhaseFind.IdRef += mcDoPhaseFind.IdStep;
		if (mcDoPhaseFind.IdRef >= mcDoPhaseFind.IdTarget)
		{
			mcDoPhaseFind.IdRef = mcDoPhaseFind.IdTarget;
			mcDoPhaseFind.State = APSM_DELAY;
			mcDoPhaseFind.NextState = APSM_GOINIT;
		}
		else
		{}
	}
	else if (mcDoPhaseFind.State == APSM_DELAY)  // delay for a while
	{
		mcDoPhaseFind.TimeCounter++;
		if (mcDoPhaseFind.TimeCounter > mcDoPhaseFind.WorkTime)
		{
			mcDoPhaseFind.TimeCounter = 0;
			mcDoPhaseFind.State = mcDoPhaseFind.NextState;
			// check encoder error
			if (mcDoPhaseFind.NextState == APSM_GOFORWARD)
			{
				mcDoPhaseFind.QepAngleComp = *mcDoPhaseFind.pQepAngle;
				mcDoPhaseFind.QepAngleStart = *mcDoPhaseFind.pQepAngle;
				usSRegInBuf[HALLTHETA0] = usSRegInBuf[QEPPOS_L];
				usSRegInBuf[HALLTHETA1] = usSRegInBuf[QEPPOS_H];
			}
			else if (mcDoPhaseFind.NextState == APSM_GOBACK)
			{
				if (*mcDoPhaseFind.pQepAngle == mcDoPhaseFind.QepAngleComp)
					mcDoPhaseFind.Error = PFERR_NOMOVE;
				mcDoPhaseFind.QepAngleEnd = *mcDoPhaseFind.pQepAngle;
				usSRegInBuf[HALLTHETA2] = usSRegInBuf[QEPPOS_L];
				usSRegInBuf[HALLTHETA3] = usSRegInBuf[QEPPOS_H];
				mcElecAng.FOCThetaPos = mcElecAng.FOCTheta;
			}
			else if (mcDoPhaseFind.NextState == APSM_SETOFFSET)
			{
				mcElecAng.FOCThetaNeg = mcElecAng.FOCTheta;
			}
		}
	}
	else if (mcDoPhaseFind.State == APSM_GOINIT)  // go back to some init degree
	{
		mcDoPhaseFind.FOCThetaValue += mcDoPhaseFind.FOCThetaDelta;
		if (mcDoPhaseFind.FOCThetaValue >= mcDoPhaseFind.FOCThetaInit)
		{
			mcDoPhaseFind.FOCThetaValue = mcDoPhaseFind.FOCThetaInit;
			mcDoPhaseFind.State = APSM_DELAY;
			mcDoPhaseFind.NextState = APSM_GOFORWARD;
		}
		else
		{}	
		
		NFOC_THETAH = (int16)(mcDoPhaseFind.FOCThetaValue * mcDoPhaseFind.FOCThetaSign);
	}
	else if (mcDoPhaseFind.State == APSM_GOFORWARD)  // go to 360 elec degree
	{
		mcDoPhaseFind.FOCThetaValue += mcDoPhaseFind.FOCThetaDelta;
		if (mcDoPhaseFind.FOCThetaValue >= mcDoPhaseFind.FOCThetaTarget)
		{
			mcDoPhaseFind.FOCThetaValue = mcDoPhaseFind.FOCThetaTarget;
			mcDoPhaseFind.State = APSM_DELAY;
			mcDoPhaseFind.NextState = APSM_GOBACK; // go back to FOCThetaInit
		}
		else
		{}

		NFOC_THETAH = (int16)(mcDoPhaseFind.FOCThetaValue * mcDoPhaseFind.FOCThetaSign);
	}
	else if (mcDoPhaseFind.State == APSM_GOBACK)  // go back to 0 degree
	{
		mcDoPhaseFind.FOCThetaValue -= mcDoPhaseFind.FOCThetaDelta;
		if (mcDoPhaseFind.FOCThetaValue <= mcDoPhaseFind.FOCThetaInit) //
		{
			mcDoPhaseFind.FOCThetaValue = mcDoPhaseFind.FOCThetaInit;
			mcDoPhaseFind.State = APSM_DELAY;
			mcDoPhaseFind.NextState = APSM_SETOFFSET;
		}
		else
		{}

		NFOC_THETAH = (int16)(mcDoPhaseFind.FOCThetaValue * mcDoPhaseFind.FOCThetaSign);
	}
	else if (mcDoPhaseFind.State == APSM_SETOFFSET)
	{
		mcDoPhaseFind.QepAngleComp = (mcDoPhaseFind.QepAngleEnd - mcDoPhaseFind.QepAngleStart) * mcDoPhaseFind.FOCThetaSign;
		mcDoPhaseFind.FOCThetaTarget = mcDoPhaseFind.FOCThetaTarget * mcDoPhaseFind.FOCThetaSign;
		mcDoPhaseFind.FOCThetaInit = mcDoPhaseFind.FOCThetaInit * mcDoPhaseFind.FOCThetaSign;

		// 计算电角度偏置
		if ((mcElecAng.ElecAngDir == 0 && mcDoPhaseFind.QepAngleComp < 0) ||
			(mcElecAng.ElecAngDir == 1 && mcDoPhaseFind.QepAngleComp > 0))
		{
			mcElecAng.FOCThetaPos = -mcElecAng.FOCThetaPos;
			mcElecAng.FOCThetaNeg = -mcElecAng.FOCThetaNeg;
		}
		mcElecAng.FOCThetaPos -= mcDoPhaseFind.FOCThetaTarget;
		mcElecAng.FOCThetaNeg -= mcDoPhaseFind.FOCThetaInit;
		
		mcElecAng.ElecAngOffset = (mcElecAng.FOCThetaPos + mcElecAng.FOCThetaNeg) / 2;
		if (ABS((int32)mcElecAng.FOCThetaPos - (int32)mcElecAng.FOCThetaNeg) > 32768)
			mcElecAng.ElecAngOffset += 32768;
		
		// 确定方向
		if(mcDoPhaseFind.QepAngleComp < 0)
			SetBit(usSRegHoldBuf[DRIVEMODE], MODE_ELECANGDIR); // 方向相反
		else
			ClrBit(usSRegHoldBuf[DRIVEMODE], MODE_ELECANGDIR); // 方向相同
		
		mcDoPhaseFind.State = APSM_RESET;
	}
	else if (mcDoPhaseFind.State == APSM_RESET)
	{
		if (usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_TMG_ABS_SIN ||
			usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_TMG_ABS_MUL ||
			usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_TMG_INC ||
			usSRegHoldBuf[ENCTYPE] == ENCODER_SEL_BISS)
		{
			usSRegHoldBuf[ELECANGSHIFT] = mcElecAng.ElecAngOffset;
		}
		mcElecAng.FOCThetaFlag = 0;
		mcDoPhaseFind.IdRef = 0;
		mcDoPhaseFind.State = APSM_FINISH;
	}
	else //  if(mcDoPhaseFind.State == APSM_FINISH) // Finish Autophase
	{
		mcDoPhaseFind.FinishFlag = 1;
	}
}

/*---------------------------------------------------------------------------*/
/* Name		:	void Motor_PhaseFind_NormalStart(void)
/* Input	:	NO
/* Output	:	NO
/* Description:	move motor 90 degree electric angle and go back.
/*---------------------------------------------------------------------------*/
void Motor_PhaseFind_NormalStart(void)
{
	// State Machine
	if (mcDoPhaseFind.State <= 1)  // Increase mcDoPhaseFind.IdRef
	{
		mcDoPhaseFind.State = 1;
		if (mcDoPhaseFind.IdRef < mcDoPhaseFind.IdTarget)
		{
			mcDoPhaseFind.IdRef += mcDoPhaseFind.IdStep;
			mcDoPhaseFind.FOCThetaValue = mcDoPhaseFind.FOCThetaTarget / 3; // 30 degree
		}
		else
		{
			if (mcDoPhaseFind.FOCThetaValue - mcDoPhaseFind.FOCThetaDelta < 0) // 0 degree
			{
				mcDoPhaseFind.FOCThetaValue = 0;
				mcDoPhaseFind.State = 2;
				mcDoPhaseFind.NextState = 3;
			}
			else
				mcDoPhaseFind.FOCThetaValue -= mcDoPhaseFind.FOCThetaDelta;
		}
		NFOC_THETAH = (int16)mcDoPhaseFind.FOCThetaValue;  // go to 30 degree		
	}
	else if (mcDoPhaseFind.State == 2)  // delay for a while
	{
		mcDoPhaseFind.TimeCounter++;
		if (mcDoPhaseFind.TimeCounter > mcDoPhaseFind.WorkTime)
		{
			mcDoPhaseFind.TimeCounter = 0;
			mcDoPhaseFind.State = mcDoPhaseFind.NextState;
			// check encoder error or motor parameter error
			if (mcDoPhaseFind.NextState == 3)
			{
				mcDoPhaseFind.QepAngleComp = *mcDoPhaseFind.pQepAngle;
				mcDoPhaseFind.QepAngleStart = *mcDoPhaseFind.pQepAngle;
				usSRegInBuf[HALLTHETA0] = usSRegInBuf[QEPPOS_L]; // 0 degree
				usSRegInBuf[HALLTHETA1] = usSRegInBuf[QEPPOS_H];
			}
			else if (mcDoPhaseFind.NextState == 4 || mcDoPhaseFind.NextState == 5 || mcDoPhaseFind.NextState == 6 || mcDoPhaseFind.NextState == 7)
			{
				if (*mcDoPhaseFind.pQepAngle == mcDoPhaseFind.QepAngleComp)
					mcDoPhaseFind.Error = PFERR_NOMOVE;
				mcDoPhaseFind.QepAngleComp = *mcDoPhaseFind.pQepAngle;
				
				if (mcDoPhaseFind.NextState == 5)
				{
					mcElecAng.FOCThetaPos = mcElecAng.FOCTheta;
					mcDoPhaseFind.QepAngleEnd = *mcDoPhaseFind.pQepAngle;
					usSRegInBuf[HALLTHETA4] = usSRegInBuf[QEPPOS_L]; // 0 degree
					usSRegInBuf[HALLTHETA5] = usSRegInBuf[QEPPOS_H];
				}
				else if (mcDoPhaseFind.NextState == 7)
				{
					mcElecAng.FOCThetaNeg = mcElecAng.FOCTheta;
				}
				else if (mcDoPhaseFind.NextState == 4)
				{
					mcDoPhaseFind.QepAngleMid = *mcDoPhaseFind.pQepAngle;
					usSRegInBuf[HALLTHETA2] = usSRegInBuf[QEPPOS_L]; // 90 degree
					usSRegInBuf[HALLTHETA3] = usSRegInBuf[QEPPOS_H];
				}
				else
				{
				}
			}
		}
	}
	else if (mcDoPhaseFind.State == 3)  // go to 90 degree
	{
		if (mcDoPhaseFind.FOCThetaValue + mcDoPhaseFind.FOCThetaDelta >= mcDoPhaseFind.FOCThetaTarget) // 90 degree
		{
			mcDoPhaseFind.FOCThetaValue = mcDoPhaseFind.FOCThetaTarget;
			
			if (ABS(mcFocCtrl.ActualAngle - mcDoPhaseFind.ActualAngleLatch) < mcDoPhaseFind.DeltaAngle)
			{
				mcDoPhaseFind.Cnt++;
			}
			else
			{
				mcDoPhaseFind.Cnt = 0;
			}
			
			if (mcDoPhaseFind.Cnt >= 5)
			{
				mcDoPhaseFind.State = 2;
				mcDoPhaseFind.NextState = 4;
				mcDoPhaseFind.Cnt = 0;
			}			
		}
		else
		{
			mcDoPhaseFind.FOCThetaValue += mcDoPhaseFind.FOCThetaDelta;
		}
		NFOC_THETAH = (int16)mcDoPhaseFind.FOCThetaValue;
	}
	else if (mcDoPhaseFind.State == 4)  // go back to 0 degree
	{
		if (mcDoPhaseFind.FOCThetaValue - mcDoPhaseFind.FOCThetaDelta <= 0) // 0 degree
		{
			mcDoPhaseFind.FOCThetaValue = 0;
			mcDoPhaseFind.State = 2;
			mcDoPhaseFind.NextState = 5;
			
			if (ABS(mcFocCtrl.ActualAngle - mcDoPhaseFind.ActualAngleLatch) < mcDoPhaseFind.DeltaAngle)
			{
				mcDoPhaseFind.Cnt++;
			}
			else
			{
				mcDoPhaseFind.Cnt = 0;
			}
			
			if (mcDoPhaseFind.Cnt >= 5)
			{
				mcDoPhaseFind.State = 2;
				mcDoPhaseFind.NextState = 5;
//			    mcElecAng.FOCThetaPos = mcElecAng.FOCTheta;
				mcDoPhaseFind.Cnt = 0;
			}
			
		}
		else
			mcDoPhaseFind.FOCThetaValue -= mcDoPhaseFind.FOCThetaDelta;
		NFOC_THETAH = (int16)mcDoPhaseFind.FOCThetaValue;
	}
	else if (mcDoPhaseFind.State == 5)  // go to -90 degree
	{
		if (mcDoPhaseFind.FOCThetaValue - mcDoPhaseFind.FOCThetaDelta <= (-mcDoPhaseFind.FOCThetaTarget)) // -90 degree
		{
			mcDoPhaseFind.FOCThetaValue = -mcDoPhaseFind.FOCThetaTarget;
			
			if (ABS(mcFocCtrl.ActualAngle - mcDoPhaseFind.ActualAngleLatch) < mcDoPhaseFind.DeltaAngle)
			{
				mcDoPhaseFind.Cnt++;
			}
			else
			{
				mcDoPhaseFind.Cnt = 0;
			}

			if (mcDoPhaseFind.Cnt >= 5)
			{
				mcDoPhaseFind.State = 2;
				mcDoPhaseFind.NextState = 6;
				mcDoPhaseFind.Cnt = 0;
			}	
			
		}
		else
			mcDoPhaseFind.FOCThetaValue -= mcDoPhaseFind.FOCThetaDelta;
		NFOC_THETAH = (int16)mcDoPhaseFind.FOCThetaValue;
	}
	else if (mcDoPhaseFind.State == 6)  // go back to 0 degree
	{
		if (mcDoPhaseFind.FOCThetaValue + mcDoPhaseFind.FOCThetaDelta >= 0) // 0 degree
		{
			mcDoPhaseFind.FOCThetaValue = 0;
			mcDoPhaseFind.State = 2;
			mcDoPhaseFind.NextState = 7;
			
			if (ABS(mcFocCtrl.ActualAngle - mcDoPhaseFind.ActualAngleLatch) < mcDoPhaseFind.DeltaAngle)
			{
				mcDoPhaseFind.Cnt++;
			}
			else
			{
				mcDoPhaseFind.Cnt = 0;
			}

			if (mcDoPhaseFind.Cnt >= 5)
			{
				mcDoPhaseFind.State = 2;
				mcDoPhaseFind.NextState = 7;
//				mcElecAng.FOCThetaNeg = mcElecAng.FOCTheta;
				mcDoPhaseFind.Cnt = 0;
			}
			
		}
		else
			mcDoPhaseFind.FOCThetaValue += mcDoPhaseFind.FOCThetaDelta;
		NFOC_THETAH = (int16)mcDoPhaseFind.FOCThetaValue;
	}
	else if (mcDoPhaseFind.State == 7)
	{
		// 计算电角度偏置
		mcElecAng.ElecAngOffset = (mcElecAng.FOCThetaPos + mcElecAng.FOCThetaNeg) / 2;
		if (ABS((int32)mcElecAng.FOCThetaPos - (int32)mcElecAng.FOCThetaNeg) > 32768)
			mcElecAng.ElecAngOffset += 32768;
		
		// 确定方向
		mcDoPhaseFind.QepAngleStart = mcDoPhaseFind.QepAngleMid - mcDoPhaseFind.QepAngleStart;
		mcDoPhaseFind.QepAngleEnd = mcDoPhaseFind.QepAngleMid - mcDoPhaseFind.QepAngleEnd;
		if (mcDoPhaseFind.QepAngleStart < 0 && mcDoPhaseFind.QepAngleEnd < 0)
			SetBit(usSRegHoldBuf[DRIVEMODE], MODE_ELECANGDIR); // 方向相反
		else if (mcDoPhaseFind.QepAngleEnd > 0 && mcDoPhaseFind.QepAngleEnd > 0)
			ClrBit(usSRegHoldBuf[DRIVEMODE], MODE_ELECANGDIR); // 方向相同
		else
			mcDoPhaseFind.Error = PFERR_DIRERR;
		
		mcElecAng.FOCThetaFlag = 0;
		mcDoPhaseFind.IdRef = 0;
		mcDoPhaseFind.State = 8;
	}
	else //  if(mcDoPhaseFind.State == 6) // Finish NormalStart
	{
		mcDoPhaseFind.FinishFlag = 1;
	}
	mcDoPhaseFind.ActualAngleLatch = mcFocCtrl.ActualAngle;
}

/*
 * Copyright (c) 2026-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorFunc.c
 * Author        : Summer
 * Date          : 2026-05-06
 * Description   : Algorithm module calls
 *
 * Record        :
 * V1.0, 2026-05-06, Summer: Created file
 */


/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include "Math.h"
#include "MotorFunc.h"


/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/
FeedBackCfgTypedef FeedBackCfg;
ErrCorCfgTypedef ErrCorCfg;
FriCmpCfgTypedef FriCmpCfg;
CurrBackCfgTypedef CurrBackCfg;
SoftCfgTypedef SoftCfg;
ScopeCfgTypeDef ScopeCfg;

#if FUNC_NTF_MODE == 1
VibrationCfgTypedef VibrationCfg[2];
#else
VibrationCfgTypedef VibrationCfg[1];
#endif

/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
void ElecAngCal_Init(void);
void PI_Control_Init(PIControlSimple* p);
void FeedBackOnLoad_Demo_Init(void);
void NTF_Demo_Init(void);
void ErrorCorrection_Demo_Init(void);
void FricCmp_Demo_Init(void);
void CurrBack_Demo_Init(void);
void FieldSoftControl_Demo_Init(void);
void Scope_Init(void);
void Scope_Update(void);



/*---------------------------------------------------------------------------
 * Name     :   ElecAngCal_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize electrical angle calculation
 *---------------------------------------------------------------------------*/
void ElecAngCal_Init(void)
{
	ElecAngCal.pElecAngSW = (uint32*) & usSRegHoldBuf[ELECANGSW_L];
	ElecAngCal.pElecAngMW = (uint32*) & usSRegHoldBuf[ELECANGMW_L];
	ElecAngCal.pEncRes = (uint32*) & usSRegHoldBuf[ENCRES_L];
	ElecAngCal.pAngToCnt = &mcFocCtrl.AngToCnt;
	ElecAngCal.pElecAngDir = &mcElecAng.ElecAngDir;
}


/*---------------------------------------------------------------------------
 * Name     :   PI_Control_Init(void)
 * Input    :
 * Output   :
 * Description: Initialize PI controller
 *---------------------------------------------------------------------------*/
void PI_Control_Init(PIControlSimple* p)
{
	memset(p, 0, sizeof(PIControlSimple));

	p->pKp = &usSRegHoldBuf[FCKP];
	p->pKi = &usSRegHoldBuf[FCKI];
	p->KpRank = KP_RANK;
	p->KiRank = KI_RANK; // Note: KiRank should be >= KpRank

	p->ValueMax32 = (int32)(int16)usSRegHoldBuf[PEAKCURRENT] << p->KpRank;
	p->ValueMin32 = -p->ValueMax32;
	p->DeSatur = 20000;
}


/*---------------------------------------------------------------------------
 * Name     :   FeedBackOnLoad_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize full closed-loop control
 *---------------------------------------------------------------------------*/
void FeedBackOnLoad_Demo_Init(void)
{
	FeedBackCfg.pMode = &usSRegHoldBuf[FEEDBACKMODE];
	FeedBackCfg.pMixErrMaxValue = (int32*) & usSRegHoldBuf[MIXERRMAXVAL_L];
	FeedBackCfg.pMixErrClrRpm = &usSRegHoldBuf[MIXERRCLRRPM];
	FeedBackCfg.pLoadFeedPulse = (int32*) & usSRegHoldBuf[LOADFEEDPULSE_L];
	FeedBackCfg.pMotorActualAngle = &mcFocCtrl.ActualAngle;		// Inner loop real-time position
	FeedBackCfg.pLoadActualAngle = &mcEncoder.LoadEncPos;
	FeedBackCfg.pTargetAngle = &mcFocCtrl.TargetAngleFilt;
	FeedBackCfg.pTargetRef = &mcFocCtrl.TargetRef;
	FeedBackCfg.pPosLoopEnable = &mcFocCtrl.PosLoopEnable;

	FeedBackCfg.LPFFreq = usSRegHoldBuf[LOADFEEDLPFFREQ];
	FeedBackCfg.LoadEncRes = *(int32*) & usSRegHoldBuf[SFBENCRES_L];
	FeedBackCfg.EncRes = *(int32*) & usSRegHoldBuf[ENCRES_L];
	FeedBackCfg.PosCtrlFreq = PROFILE_FREQUENCY;

	FeedBackOnLoad_Init(&FeedBackCfg);
}


/*---------------------------------------------------------------------------
 * Name     :   NTF_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize vibration suppression
 *---------------------------------------------------------------------------*/
void NTF_Demo_Init(void)
{
	int8 Num = NTF1NUM;
	uint8 BaseNum = Num << 2, CoeNum = 10 *Num;

	VibrationCfg[0].Mode = usSRegHoldBuf[NTF1MODE + BaseNum];

	VibrationCfg[0].SampFreq = (int32)PROFILE_FREQUENCY * 10;    // unit: 0.1Hz
	VibrationCfg[0].NotchFreq = (int32)usSRegHoldBuf[NTF1HZ + BaseNum]; // unit: 0.1Hz
	VibrationCfg[0].NotchSharp = (int32)usSRegHoldBuf[NTF1SHARP + BaseNum]; // unit: 0.01
	VibrationCfg[0].NotchGain = (int32)usSRegHoldBuf[NTF1GAIN + BaseNum];  // unit: Rad*10-3/Nm

	VibrationCfg[0].NumCoeff[0] = (((int32)usSRegHoldBuf[NTF1B0_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1B0_L + CoeNum]);
	VibrationCfg[0].NumCoeff[1] = (((int32)usSRegHoldBuf[NTF1B1_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1B1_L + CoeNum]);
	VibrationCfg[0].NumCoeff[2] = (((int32)usSRegHoldBuf[NTF1B2_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1B2_L + CoeNum]);
	VibrationCfg[0].DenCoeff[0] = 1L << NTF_Q1_SHIFT;
	VibrationCfg[0].DenCoeff[1] = (((int32)usSRegHoldBuf[NTF1A1_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1A1_L + CoeNum]);
	VibrationCfg[0].DenCoeff[2] = (((int32)usSRegHoldBuf[NTF1A2_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1A2_L + CoeNum]);

#if FUNC_NTF_MODE == 1
	Num = NTF2NUM;
	BaseNum = Num << 2;
	CoeNum = 10 *Num;
	VibrationCfg[1].Mode = usSRegHoldBuf[NTF1MODE + BaseNum];

	VibrationCfg[1].SampFreq = (int32)PROFILE_FREQUENCY * 10;    // unit: 0.1Hz
	VibrationCfg[1].NotchFreq = (int32)usSRegHoldBuf[NTF1HZ + BaseNum]; // unit: 0.1Hz

	VibrationCfg[1].NumCoeff[0] = (((int32)usSRegHoldBuf[NTF1B0_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1B0_L + CoeNum]);
	VibrationCfg[1].NumCoeff[1] = (((int32)usSRegHoldBuf[NTF1B1_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1B1_L + CoeNum]);
	VibrationCfg[1].NumCoeff[2] = (((int32)usSRegHoldBuf[NTF1B2_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1B2_L + CoeNum]);
	VibrationCfg[1].DenCoeff[0] = 1L << NTF_Q1_SHIFT;
	VibrationCfg[1].DenCoeff[1] = (((int32)usSRegHoldBuf[NTF1A1_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1A1_L + CoeNum]);
	VibrationCfg[1].DenCoeff[2] = (((int32)usSRegHoldBuf[NTF1A2_H + CoeNum] << 16) + (uint32)usSRegHoldBuf[NTF1A2_L + CoeNum]);
#endif

	//NTF initialization
	NTF_Init(VibrationCfg);

}


/*---------------------------------------------------------------------------
 * Name     :   ErrorCorrection_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize error correction function
 *---------------------------------------------------------------------------*/
void ErrorCorrection_Demo_Init(void)
{
	ErrCorCfg.En = usSRegHoldBuf[ERRCOREN];

	ErrCorCfg.StartPos = ((int32)usSRegHoldBuf[ERRCORSTARTPOS_H] << 16) | usSRegHoldBuf[ERRCORSTARTPOS_L];
	ErrCorCfg.Interval = ((int32)usSRegHoldBuf[ERRCORINTERVAL_H] << 16 | usSRegHoldBuf[ERRCORINTERVAL_L]);
	ErrCorCfg.Protaty = ((int32)usSRegHoldBuf[ERRCORPROTARY_H] << 16 | usSRegHoldBuf[ERRCORPROTARY_L]);

	ErrCorCfg.NumPoints = usSRegHoldBuf[ERRCORNUMPOINTS];		//Error correction number of points
	ErrCorCfg.pPosErr = &usSRegHoldBuf[ERRCORER1];
	
	ErrorCorrection_Init(&ErrCorCfg);
}


/*---------------------------------------------------------------------------
 * Name     :   FricCmp_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize friction compensation function
 *---------------------------------------------------------------------------*/
void FricCmp_Demo_Init(void)
{
	FriCmpCfg.PosVelDeadBand = usSRegHoldBuf[FRICPVHYST];
	FriCmpCfg.NegVelDeadBand = usSRegHoldBuf[FRICNVHYST];

	FriCmpCfg.PosVelValue = (int16)usSRegHoldBuf[FRICPVTHRESH];
	FriCmpCfg.NegVelValue = (int16)usSRegHoldBuf[FRICNVTHRESH];
	
	FriCmpCfg.PosCmpIq = (int16)usSRegHoldBuf[FRICIPOS];
	FriCmpCfg.NegCmpIq = (int16)usSRegHoldBuf[FRICINEG];
	
	FriCmpCfg.FricMod = usSRegHoldBuf[FRICMOD];
	FriCmpCfg.FricVSrc = usSRegHoldBuf[FRICVSRC];
	FriCmpCfg.FricLpfHz = usSRegHoldBuf[FRICLPFHZ];
	
	FriCmpCfg.MaxSpeed = usSRegHoldBuf[MOTORMAXSPEED];
	FriCmpCfg.CurFileFreq = CURFILE_FREQUENCY;
	
	FriCmpCfg.pTargetReftoSpd = &mcFocCtrl.TargetReftoSpd;
	FriCmpCfg.pCmdVel = &usSRegInBuf[CMDVEL];
	FriCmpCfg.pActVel = &usSRegInBuf[ACTVEL];
	FriCmpCfg.pRunMod = &mcFocCtrl.RunMod;

	FricCmp_Init(&FriCmpCfg);
}


/*---------------------------------------------------------------------------
 * Name     :   CurrBack_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize current foldback function
 *---------------------------------------------------------------------------*/
void CurrBack_Demo_Init(void)
{
	CurrBackCfg.DriveVal = MOTORDRIVE;
	CurrBackCfg.PeakVal = MOTORPEAK;
	CurrBackCfg.FaultThresHoldVal = FAULTHOLDVALUE;
	CurrBackCfg.WarnThresHoldVal = WARNHOLDVAL;

	CurrBackCfg.Tdelay = DELAYTIME;
	CurrBackCfg.Tc = TIMECONSTANT;
	CurrBackCfg.CurBackFreq = CURRENTBACK_FREQ;

	CurrBackCfg.CurrMax = usSRegHoldBuf[VOUTMAX];
	CurrBackCfg.CurrMin = usSRegHoldBuf[VOUTMIN];
	CurrBackCfg.pActualCurrent = &usSRegInBuf[ACTCUR];
	CurrBackCfg.pFoldbackSon = &usSRegHoldBuf[FOLDBACKEN];
	CurrBackCfg.pLoopEnable = &mcFocCtrl.CurLoopEnable;

	CurrBackProtect_Init(&MotorCurrBack, &CurrBackCfg);
}


/*---------------------------------------------------------------------------
 * Name     :   FieldSoftControl_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Initialize compliance control function
 *---------------------------------------------------------------------------*/
void FieldSoftControl_Demo_Init(void)
{
	SoftCfg.WorkMode = usSRegHoldBuf[SOFTCTRLWORMOD];

	SoftCfg.VelLimMax = usSRegHoldBuf[POUTMAX];
	SoftCfg.VelLimMin = usSRegHoldBuf[POUTMIN];
	SoftCfg.CurLimMax = usSRegHoldBuf[VOUTMAX];
	SoftCfg.CurLimMin = usSRegHoldBuf[VOUTMIN];
	SoftCfg.VelLmt = usSRegHoldBuf[PROFILEMAXVEL];

	SoftCfg.ForceConst = usSRegHoldBuf[FORCECONST];
	SoftCfg.CurCoe = usSRegHoldBuf[CURCOE];
	SoftCfg.PeinPosRange = usSRegHoldBuf[PEINPOSRANGE];
	SoftCfg.RmsCurrent = usSRegHoldBuf[RMSCURRENT];
	SoftCfg.MotorMaxSpd = usSRegHoldBuf[MOTORMAXSPEED];

	SoftCfg.CurCtrlFreq = CURCTRL_FREQUENCY;
	SoftCfg.VelCtrlFreq = VELCTRL_FREQUENCY;
	SoftCfg.PosCtrlFreq = POSCTRL_FREQUENCY;

	SoftCfg.pCompMode = &usSRegHoldBuf[SOFTCTRLCMPMOD];
	SoftCfg.pTargetRef = &mcFocCtrl.TargetRef;
	SoftCfg.pTargetReftoSpd = &mcFocCtrl.TargetReftoSpd;
	SoftCfg.pThetaErr = &mcFocCtrl.ThetaErr;
	SoftCfg.pActVel = &NFOC_SFOUT; // &usSRegInBuf[ACTVEL];
	SoftCfg.pActCur = &usSRegInBuf[ACTCUR];
	SoftCfg.pSpdFF = &usSRegInBuf[SPEEDFF];

	SoftCfg.pSKp = (uint32*) & usSRegHoldBuf[SOFTCTRLKP_L];
	SoftCfg.pSKi = (uint32*) & usSRegHoldBuf[SOFTCTRLKI_L];
	SoftCfg.pSKd = (uint32*) & usSRegHoldBuf[SOFTCTRLKD_L];
	SoftCfg.pSXPosCmd = &usSRegHoldBuf[SOFTCTRLXD];
	SoftCfg.pSXPosAct = &usSRegHoldBuf[SOFTCTRLXC];
	SoftCfg.pSXForceCmd = &usSRegHoldBuf[SOFTCTRLFD];
	SoftCfg.pSXForceAct = &usSRegHoldBuf[SOFTCTRLFC];

	FieldSoftControl_Init(&SoftCfg);
}


/*---------------------------------------------------------------------------
 * Name     :   Scope_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Oscilloscope sampling initialization
 *---------------------------------------------------------------------------*/
void Scope_Init(void)
{
	memset(&ScopeCfg, 0, sizeof(ScopeCfgTypeDef));
	
	ScopeCfg.BufferSize = S_REG_SCOPE_NREGS;
	ScopeCfg.pScopeCtrl = &usSRegHoldBuf[SCOPECTRL];
	ScopeCfg.pScopeData = usSRegScopeBuf;
}


/*---------------------------------------------------------------------------
 * Name     :   Scope_Update
 * Input    :   NO
 * Output   :   NO
 * Description: Oscilloscope sampling parameter updatnew
 *---------------------------------------------------------------------------*/
void Scope_Update(void)
{
	uint8 i;
	uint16 iRegIndex, scopeAddr = 0;
	
	if (!GetReg(ScopeCfg.ScopeCtrl, SCOPE_EN) && GetReg(*ScopeCfg.pScopeCtrl, SCOPE_EN))
	{
		ScopeCfg.ScopeInterval = usSRegHoldBuf[SCOPEINTERVAL];
		ScopeCfg.ScopeNum = usSRegHoldBuf[SCOPENUM];

		ScopeCfg.Channel = 0;
		scopeAddr = SCOPEADDR_0;
		for (i = 0; i < CHANNELNUM; i++)
		{
			ScopeCfg.pScopeAddr[i] = NULL;
			if ((usSRegHoldBuf[scopeAddr] >> 8) < S_REG_INPUT_INDEX_MAX)
			{
				iRegIndex = (uint16)(usSRegInStartArray[usSRegHoldBuf[scopeAddr] >> 8] + (usSRegHoldBuf[scopeAddr] & 0xFF));
				if (iRegIndex + 1 <= usSRegInStartArray[(usSRegHoldBuf[scopeAddr] >> 8) + 1])
				{
					ScopeCfg.pScopeAddr[i] = &usSRegInBuf[iRegIndex];
					ScopeCfg.Channel++;
					scopeAddr++;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

		// Trigger sampling
		ScopeCfg.TriggerLevel = ((int32)usSRegHoldBuf[SCOPETRIGLEVEL_H] << 16) | usSRegHoldBuf[SCOPETRIGLEVEL_L];
		ScopeCfg.TriggerPrePoints = usSRegHoldBuf[SCOPETRIGPRE];

		ScopeCfg.pScopeTriAddr16 = NULL;
		ScopeCfg.pScopeTriAddr32 = NULL;
		if ((usSRegHoldBuf[SCOPETRIGADDR] >> 8) < S_REG_INPUT_INDEX_MAX)
		{
			iRegIndex = (uint16)(usSRegInStartArray[usSRegHoldBuf[SCOPETRIGADDR] >> 8] + (usSRegHoldBuf[SCOPETRIGADDR] & 0xFF));
			if (iRegIndex + 1 <= usSRegInStartArray[(usSRegHoldBuf[SCOPETRIGADDR] >> 8) + 1])
			{
				ScopeCfg.pScopeTriAddr16 = (int16*) & usSRegInBuf[iRegIndex];
				if (iRegIndex > 0)
				{
					ScopeCfg.pScopeTriAddr32 = (int32*) & usSRegInBuf[iRegIndex - 1];
				}
			}
		}
	}
	
	ScopeCfg.ScopeCtrl = *ScopeCfg.pScopeCtrl;
	usSRegInBuf[SCOPESTATUS] = Scope_UpdateMode(&ScopeCfg, &usSRegInBuf[SCOPETRIGSTA]);
}

/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorIdentify.c
 * Author        : wynn.wang
 * Date          : 2024-12-02
 * Description   : Motor parameter identification and inertia identification initialization
 *
 * Record        :
 * V1.0, 2024-12-02, wynn.wang: Created file
 */

/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include "MotorIdentify.h"


/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/
MotorEstCfgTypeDef mcEstCfg;
InFricIdCfgTypedef InFricIdCfg;

/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
void Motor_Identify_Init(void);
void InFricId_Demo_Init(void);

/*---------------------------------------------------------------------------
 * Name		: Motor_Identify_Init()
 * Input	:
 * Output	:
 * Description: Initial Motor Parameter Identify and set related register.
 *---------------------------------------------------------------------------*/
void Motor_Identify_Init(void)
{
	if (McStaSet.SetFlag.IdentifySetFlag == 0)
	{
		FOC_Init(); /* FOC Initialize */

		NFOC_IDREF = 0;
		NFOC_IQREF = 0;
		usSRegInBuf[CMDCUR] = 0;
		usSRegInBuf[MB_IDREF] = 0;

		mcFocCtrl.CurLoopEnable = 1;
		mcFocCtrl.VelLoopEnable = 0;
		mcFocCtrl.PosLoopEnable = 0;

		mcFocCtrl.RunMod = CURMOD;

		OutputFilter_Init();  // Torque filter initialization
		
		// Identification parameter initialization
		mcEstCfg.Mode = usSRegHoldBuf[ESTMODE];
		mcEstCfg.IAmp = usSRegHoldBuf[ESTIAMP];
		mcEstCfg.RTime = usSRegHoldBuf[ESTRTIME];
		mcEstCfg.LTime = usSRegHoldBuf[ESTLTIME];
		mcEstCfg.UMin = usSRegHoldBuf[ESTUMIN];
		mcEstCfg.UMax = usSRegHoldBuf[ESTUMAX];
		mcEstCfg.UDelta = usSRegHoldBuf[ESTUDELTA];
		mcEstCfg.FreqMax = usSRegHoldBuf[ESTFMAX]; // Initial frequency
		mcEstCfg.FreqMin = usSRegHoldBuf[ESTFMIN];
		mcEstCfg.FreqDelta = usSRegHoldBuf[ESTFDELTA];
		mcEstCfg.IMinRatio = usSRegHoldBuf[ESTIMINRATIO];
		mcEstCfg.CVMode = usSRegHoldBuf[CVMOD];
		mcEstCfg.CurFileFreq = CURFILE_FREQUENCY;
		
		mcEstCfg.pFocThetaFlag = &mcElecAng.FOCThetaFlag;
		mcEstCfg.pStatus = &usSRegInBuf[ESTSTATUS];
		mcEstCfg.pIdRef = &usSRegInBuf[MB_IDREF];
		mcEstCfg.pIqRef = &usSRegInBuf[CMDCUR];

		mcEstCfg.pId = &usSRegInBuf[MB_ID];
		mcEstCfg.pUd = &usSRegInBuf[MB_UD];
		mcEstCfg.pUq = &usSRegInBuf[MB_UQ];
			
		Motor_Identify_ParamInit(&mcEstCfg);  

		/* -----Enable output----- */
#if (HW_UVW_POLARITY == UVWPOL_NORMAL)
		write_csr(DRV1_CMR, 0x0abF);
#else
		write_csr(DRV1_CMR, 0x057F);
#endif
		set_csr(DRV1_OUT, MOE);
		set_csr(DRV1_CR, DRVOE);			// Driver output enable: 0-->Disable, 1-->Enable

		SetReg(usSRegInBuf[DRIVESTATUS], STATUS_ENABLE, STATUS_ENABLE);
		usSRegInBuf[ESTSTATUS] = 0;

		McStaSet.SetFlag.IdentifySetFlag = 1;
	}

}


/*---------------------------------------------------------------------------
 * Name     :   InFricId_Demo_Init
 * Input    :   NO
 * Output   :   NO
 * Description: Inertia identification initialization
 *---------------------------------------------------------------------------*/
void InFricId_Demo_Init(void)
{
	int64 temp = 0;
	memset(&InFricIdCfg, 0, sizeof(InFricIdCfgTypedef));

	InFricIdCfg.SpeedStart = ((uint32)usSRegHoldBuf[LMJRHIGHSPEED] * usSRegHoldBuf[LMJRSTARTRATIO]) >> 10;
	InFricIdCfg.SpeedDelta = ((uint32)10 << 14) / usSRegHoldBuf[MOTORMAXSPEED];     // (mm/s) -> count
	InFricIdCfg.SpeedHigh = usSRegHoldBuf[LMJRHIGHSPEED];
	InFricIdCfg.SpeedMin = ((uint32)2 << 14) / usSRegHoldBuf[MOTORMAXSPEED];        // (mm/s) -> count
	InFricIdCfg.Cur0_1 = (uint16)usSRegHoldBuf[CURCOE] >> 3;
	InFricIdCfg.MaxLenSamp = 1 << usSRegHoldBuf[LMJRCALCLENGTH];
	InFricIdCfg.EstCtrl = usSRegHoldBuf[LMJREST];


	if (GetReg(usSRegHoldBuf[DRIVEMODE], MODE_MOTORTYPE)) // Rotary Motor
	{
		temp = (int64)((int64)usSRegHoldBuf[MOTORMAXSPEED] * (uint16)VELFILE_FREQUENCY * usSRegHoldBuf[CURCOE] * PI_Q12) << 1;
		temp = (int64)((int64)1 << (14 + 12 + 3)) * 1000 *60 *usSRegHoldBuf[FORCECONST] / temp;
		InFricIdCfg.Coff_J = (uint32)(temp * 9);
	}
	else // Line Motor
	{
		InFricIdCfg.Coff_J = (uint32)((uint32)usSRegHoldBuf[MOTORMAXSPEED] * (uint16)VELCTRL_FREQUENCY * usSRegHoldBuf[CURCOE]);
		InFricIdCfg.Coff_J = (uint32)((uint32)1 << (14 + 3)) * usSRegHoldBuf[FORCECONST] / InFricIdCfg.Coff_J;
		InFricIdCfg.Coff_J = InFricIdCfg.Coff_J * 9 / 10;
	}

	InFricIdCfg.pActVel = &usSRegInBuf[ACTVEL];
	InFricIdCfg.pCmdCur = &usSRegInBuf[CMDCUR];

	InFricId_Init(&InFricIdCfg);
}



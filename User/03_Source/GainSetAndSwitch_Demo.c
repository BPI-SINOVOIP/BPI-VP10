/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : GainSetAndSwitch_Demo.c
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : 增益切换
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include "GainSetAndSwitch_Demo.h"

#if FUNC_GAINSW_ENABLED
/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
GnSWPCfgTypedef GainSWCfg;

/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/
void GainSW_Demo_Init(void);
void GainSW_Demo_realize(void);
void GainSW_Demo_Update(void);

/*---------------------------------------------------------------------------*/
/* Name     :   
/* Input    :   NO
/* Output   :   NO
/* Description: 初始化
/*---------------------------------------------------------------------------*/
void GainSW_Demo_Init(void)
{
	GainSWCfg.pVp = &usSRegHoldBuf[VKP];
	GainSWCfg.pVp2 = &usSRegHoldBuf[VKP2];
	GainSWCfg.pVi = &usSRegHoldBuf[VKI];
	GainSWCfg.pVi2 = &usSRegHoldBuf[VKI2];
	
	GainSWCfg.pPp = &usSRegHoldBuf[PKP];
	GainSWCfg.pPp2 = &usSRegHoldBuf[PKP2];
	GainSWCfg.pPi = &usSRegHoldBuf[PKI];
	GainSWCfg.pPi2 = &usSRegHoldBuf[PKI2];
	GainSWCfg.pVfr = &usSRegHoldBuf[VFR];
	GainSWCfg.pVfr2 = &usSRegHoldBuf[VFR2];
	
	GainSWCfg.pGnSWMode = &usSRegHoldBuf[GAINSWMODE];
	GainSWCfg.pGnSWDlyTm = &usSRegHoldBuf[GAINSWDLYTM];
	
	GainSWCfg.pGnSWPAccTm = &usSRegHoldBuf[GAINSWPACCTM];
	GainSWCfg.pGnSWPDecTm = &usSRegHoldBuf[GAINSWPDECTM];
	GainSWCfg.pGnSWVAccTm = &usSRegHoldBuf[GAINSWVACCTM];
	GainSWCfg.pGnSWVDecTm = &usSRegHoldBuf[GAINSWVDECTM];
		
	GainSWCfg.pGnSwLvl = &usSRegHoldBuf[GAINSWLEVEL];
	GainSWCfg.pGnSwHysteresis = &usSRegHoldBuf[GAINSWHYSTERESIS];
	GainSWCfg.pRmsCurrent = &usSRegHoldBuf[RMSCURRENT];
	GainSWCfg.pMaxSpeed = &usSRegHoldBuf[MOTORMAXSPEED];
	
	GainSWCfg.pIqRef = &usSRegInBuf[CMDCUR];
	GainSWCfg.pVelRef = &usSRegInBuf[CMDVEL];
	GainSWCfg.pActVel = &usSRegInBuf[ACTVEL];
	GainSWCfg.pPosErr = (uint32*) &usSRegInBuf[POSERR_L];
	GainSWCfg.pRunMod = &mcFocCtrl.RunMod;
	GainSWCfg.pPosRef = &mcFocCtrl.TargetRef;
	
	GainSWCfg.PosCtrlFreq = POSCTRL_FREQUENCY;
	GainSWCfg.VelCtrlFreq = VELCTRL_FREQUENCY;
	
	GainSWCfg.GnSwitch = ReadBit(usSRegInBuf[DIGINSTATUS], INSTATUS_GAINSWITCH);
	GainSWCfg.InPos = ReadBit(usSRegInBuf[DRIVESTATUS], STATUS_INPOS);
	
	GainSW_Init(&GainSWCfg);
}

/*---------------------------------------------------------------------------*/
/* Name     :   
/* Input    :   NO
/* Output   :   NO
/* Description: 主循环函数调用
/*---------------------------------------------------------------------------*/
void GainSW_Demo_Update(void)
{
	GainSW_Update(&GainSWCfg);
}

/*---------------------------------------------------------------------------*/
/* Name     :   
/* Input    :   NO
/* Output   :   NO
/* Description: 中断调用
/*---------------------------------------------------------------------------*/
void GainSW_Demo_realize(void)
{	
	GainSWCfg.GnSwitch = ReadBit(usSRegInBuf[DIGINSTATUS], INSTATUS_GAINSWITCH);
	GainSWCfg.InPos = ReadBit(usSRegInBuf[DRIVESTATUS], STATUS_INPOS);
	GainSW_realize(&GainSWCfg);
}
/********************************* END OF FILE *********************************/

#endif // #if FUNC_GAINSW_ENABLED
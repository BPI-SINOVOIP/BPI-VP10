/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FieldWeaken.c
 * Author        : wynn.wang
 * Date          : 2025-03-18
 * Description   : Field-weakening control
 *
 * Record        :
 * V1.0, 2025-03-18, wynn.wang: Created file
 */


/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include <Myproject.h>
/********************************************************************************
 * Macro & Structure Definition
 *******************************************************************************/


/********************************************************************************
 * Internal Routine Prototypes
 ********************************************************************************/
FieldWeakenParameter mcFieldWeakenControl;

/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description: Field weakening control initialization
/*---------------------------------------------------------------------------*/
void FieldWeakenControlInit(void)
{
	set_csr(DRV1_FCR2, FWEAK_EN); // Field-weakening enable bit set
	
	FieldWeakenUsPIInit();

//	/****   Hardware field-weakening initialization   ****///  Enable bit still needs to be set
	NFOC_FWREF = mcFieldWeakenControl.Weaken_FocUsRef; //(Weaken_UsRef_Q15 * (NFOC1->UDCFLT >> 16)) >> 15;
	NFOC_FWKP = (Weaken_KP_Q12 | 0x4000);
	NFOC_FWKI = Weaken_KI_Q15;
	NFOC_FWMAX = mcFieldWeakenControl.Weaken_MaxLmt;
	NFOC_FWMIN = mcFieldWeakenControl.Weaken_MinLmt;
	NFOC_FWEK = 0x0000;
	NFOC_FWEK1 = 0x0000;
	NFOC_FWUK = 0x0000;
	
	NFOC_IDRLIM = mcFieldWeakenControl.Weaken_IdRefLimit;
	NFOC_KUSF = mcFieldWeakenControl.UsLpfk;
	NFOC_FWIDR = 0x0000;	
	
	set_csr(DRV1_FCR2, FWEAK_MD); // Field-weakening mode 1 enable bit set
}
/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description:RMSCURRENT
/*---------------------------------------------------------------------------*/
void FieldWeakenUsPIInit(void)
{			
	memset(&mcFieldWeakenControl, 0, sizeof(FieldWeakenParameter));
	
	mcFieldWeakenControl.Weaken_FocUsRef = Weaken_UsRef_Q15;
	mcFieldWeakenControl.Weaken_IdRefLimit = Weaken_ThertaMin0_Q15;
	mcFieldWeakenControl.Weaken_MaxLmt = Weaken_ThertaMax0_Q15;
	mcFieldWeakenControl.Weaken_MinLmt = Weaken_ThertaMin0_Q15;
	
	mcFieldWeakenControl.UsLpfk = UsLpfK_Q15;
	
	mcFieldWeakenControl.Weaken_CncVel = (int16)usSRegHoldBuf[MOTORRATEDSPEED];
	mcFieldWeakenControl.Weaken_IsMax = (int32)usSRegHoldBuf[VOUTMAX] * (int32)usSRegHoldBuf[VOUTMAX];
	mcFieldWeakenControl.Weaken_IMaxRef = (int32)usSRegHoldBuf[VOUTMAX] * (int32)usSRegHoldBuf[VOUTMAX];
}
/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description: DRV carrier interrupt execution 2
/*---------------------------------------------------------------------------*/
void FieldWeakenIqRefAdjust(void)
{
	int32 Is_Temp = 0;
	
	if (mcFieldWeakenControl.Weaken_IdRef == 0)
	{
		mcFieldWeakenControl.Weaken_IqRefLmtPos = (int32)usSRegHoldBuf[VOUTMAX];
		mcFieldWeakenControl.Weaken_IqRefLmtNeg = (int32)usSRegHoldBuf[VOUTMIN];
	}
	else
	{
		if (ABS((int16)usSRegInBuf[ACTVEL]) <= mcFieldWeakenControl.Weaken_CncVel)
		{
			mcFieldWeakenControl.Weaken_IsMaxReal = mcFieldWeakenControl.Weaken_IsMax;
		}
		else
		{
			Is_Temp = (int32)usSRegHoldBuf[VOUTMAX] * (int32)mcFieldWeakenControl.Weaken_CncVel / ABS((int16)usSRegInBuf[ACTVEL]);
			mcFieldWeakenControl.Weaken_IsMaxReal = Is_Temp * Is_Temp;
		}

		mcFieldWeakenControl.Weaken_IqMaxRef = mcFieldWeakenControl.Weaken_IMaxRef - mcFieldWeakenControl.Weaken_IdRef * mcFieldWeakenControl.Weaken_IdRef;

		if (mcFieldWeakenControl.Weaken_IqMaxRef < mcFieldWeakenControl.Weaken_IsMaxReal)
		{
			mcFieldWeakenControl.Weaken_IqRefLmtPos = Sqrt_32(mcFieldWeakenControl.Weaken_IqMaxRef);
		}
		else
		{
			mcFieldWeakenControl.Weaken_IqRefLmtPos = Sqrt_32(mcFieldWeakenControl.Weaken_IsMaxReal);
		}
		
		mcFieldWeakenControl.Weaken_IqRefLmtNeg = 0 - mcFieldWeakenControl.Weaken_IqRefLmtPos;
	}
}
/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description: DRV carrier interrupt execution 2
/*---------------------------------------------------------------------------*/
void FieldWeakenGetIdRefAndIqRef(void)			
{	
	mcFieldWeakenControl.Weaken_IqRef = NFOC_WUFIN; // mcFieldWeakenControl.Weaken_IsRef;
	mcFieldWeakenControl.Weaken_IdRef = NFOC_FWIDR;
	
	FieldWeakenIqRefAdjust();
}
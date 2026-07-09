/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : OutputFilter.c
 * Author        : Summer
 * Date          : 2023-08-23
 * Description   : Torque filter (hardware)
 *
 * Record        :
 * V1.0, 2023-08-23, Summer: Created file
 */


/********************************************************************************
 * Header Definition
 ********************************************************************************/
#include "MyProject.h"


/*---------------------------------------------------------------------------
 * Name		:	OutputFilter_Init
 * Input	:	No
 * Output	:	No
 * Description:	Torque filter initialization
 *---------------------------------------------------------------------------*/
void OutputFilter_Init(void)
{
	if (!(usSRegHoldBuf[OUTFILTCTRL] & OUTCTRL_FILTMASK4))
	{
		clr_csr(DRV1_FCR3, IQRF4_EN);
		if (!(usSRegHoldBuf[OUTFILTCTRL] & OUTCTRL_FILTMASK3))
		{
			clr_csr(DRV1_FCR3, IQRF3_EN);
			if (!(usSRegHoldBuf[OUTFILTCTRL] & OUTCTRL_FILTMASK2))
			{
				clr_csr(DRV1_FCR3, IQRF2_EN);
				set_csr(DRV1_FCR3, IQRF1_EN); // At least one filter must be enabled
			}
			else
			{
				set_csr(DRV1_FCR3, IQRF2_EN);
				set_csr(DRV1_FCR3, IQRF1_EN);
			}
		}
		else
		{
			set_csr(DRV1_FCR3, IQRF3_EN);
			set_csr(DRV1_FCR3, IQRF2_EN);
			set_csr(DRV1_FCR3, IQRF1_EN);
		}
	}
	else
	{
		set_csr(DRV1_FCR3, IQRF4_EN); // If filter 4 is enabled, the other three stages must also be enabled
		set_csr(DRV1_FCR3, IQRF3_EN);
		set_csr(DRV1_FCR3, IQRF2_EN);
		set_csr(DRV1_FCR3, IQRF1_EN);
	}
}

/*---------------------------------------------------------------------------
 * Name		:	OutputFilter_RunModeUpdate
 * Input	:	NO
 * Output	:	NO
 * Description:	Set torque filter parameters; called when motor is enabled or when mode switches
 *				Y(n) = B0*X(n) + B1*X(n-1) + B2*X(n-2) - A1*Y(n-1) - A2*Y(n-2)
 *				The coefficients B0\B1\B2\A1\A2 are calculated by the host; the current loop and speed loop use different coefficients
 *---------------------------------------------------------------------------*/
void OutputFilter_RunModeUpdate(void)
{
	int16 i = 0, j = 0, k = 0, filtStartIndex = 0, qFacSel = 0, reg = 0;
	
#if FUNC_SOFTCTRL_ENABLED
	if ((mcFocCtrl.RunMod == CURMOD) ||
		((mcFocCtrl.RunMod == POS_CURMOD) && (FieldSoftControl_GetSwToPosFlag() != 1)))
#else
	if (mcFocCtrl.RunMod == CURMOD) // current loop
#endif
	{
		filtStartIndex = OUT2FILT1B0_L;
		qFacSel = (usSRegHoldBuf[OUTFILTQFAC] << 4) & 0x0F00;
		clr_csr(DRV1_FCR3, IQRF_SEL); // 0 - current loop calculation; 1 - speed loop calculation
	}
	else
	{
		filtStartIndex = OUT1FILT1B0_L;
		qFacSel = (usSRegHoldBuf[OUTFILTQFAC] << 8) & 0x0F00;
		set_csr(DRV1_FCR3, IQRF_SEL); // 0 - current loop calculation; 1 - speed loop calculation
	}

	// Select coefficient Q29 or Q20
	reset_csr(DRV1_FCR3, QFAC_SEL4 | QFAC_SEL3 | QFAC_SEL2 | QFAC_SEL1, qFacSel); 

	// Set filter coefficients B0\B1\B2\A1\A2
	for (j = 0; j < 10; j++)
	{
		*(&NFOC_F1LB0SH + j) = (int16)usSRegHoldBuf[filtStartIndex + j];
	}
	set_csr(DRV1_FCR5, IQRF_UPDATE);
	
	
	k = 0;
	for (i = 0; i < OUTPUTFILTER_FILTNUM; i++)
	{
		for (j = 0; j < 10; j++)
		{
			*(&NFOC_F1LB0 + k) = (int16)usSRegHoldBuf[filtStartIndex + i * 10 + j];
			k += 1;
		}
		k += 10;
	}
}

/*---------------------------------------------------------------------------
 * Name		:	OutputFilter_CoeUpdate
 * Input	:	No
 * Output	:	No
 * Description:	When enabled, filter 1 coefficients are updated in real time for 
 * easier debugging; only filter 1 supports this, the other three do not.
 *---------------------------------------------------------------------------*/
void OutputFilter_CoeUpdate(void)
{
	int16 filtStartIndex = 0, j = 0;
	uint8 bUpdate = 0;
	static uint8 bUpdatePre = 0;
	
	bUpdate = ReadBit(usSRegHoldBuf[OUTFILTQFAC], OUTFILT1UPDATE);
	
	if (bUpdate && !bUpdatePre) // rising edge
	{
		if (mcFocCtrl.RunMod == CURMOD)
		{
			filtStartIndex = OUT2FILT1B0_L;
		}
		else
		{
			filtStartIndex = OUT1FILT1B0_L;
		}

		for (j = 0; j < 10; j++)
		{
			*(&NFOC_F1LB0SH + j) = (int16)usSRegHoldBuf[filtStartIndex + j];
		}

		set_csr(DRV1_FCR5, IQRF_UPDATE);
	}

	bUpdatePre = bUpdate;

}
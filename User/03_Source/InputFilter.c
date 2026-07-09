/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : InputFilter.c
 * Author        : Summer
 * Date          : 2023-09-20
 * Description   : Input filters (velocity feedback filtering / position command filtering)
 *				   Position command filtering is implemented in software, supports 2 moving average filters (depth 256*2byte) + 2 first-order low-pass filters
 *				   Velocity feedback filtering is implemented in hardware, supports 1 moving average filter (depth 256*2byte) + 2 first-order low-pass filters
 * Record        :
 * V1.0, 2023-09-20, Summer: Created file
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
#if FUNC_INPUTFILT_ENABLED
InputFilterTypedef InFilt1PosRef __attribute__((section(".pram.data.InFilt1PosRef"))) = { 0 };

#if FUNC_DUALFILT_POSREF
InputFilterTypedef InFilt2PosRef __attribute__((section(".pram.data.InFilt2PosRef"))) = { 0 };
#endif //#if FUNC_DUALFILT_POSREF
#endif // #if FUNC_INPUTFILT_ENABLED

HardInputFilterTypedef HardInFilt1VelFeb = { 0 };
HardInputFilterTypedef HardInFilt2VelFeb = { 0 };


/*---------------------------------------------------------------------------
 * Name		:	InputFilter_Init
 * Input	:	No
 * Output	:	No
 * Description:	Velocity feedback filter / position command filter initialization
 *---------------------------------------------------------------------------*/
void InputFilter_Init(void)
{
#if FUNC_INPUTFILT_ENABLED
	// Initialize position command filter 1		
	InputPosFilter_Init(&InFilt1PosRef, INF1POSREF);
	
#if FUNC_DUALFILT_POSREF
	// Initialize position command filter 2	
	InputPosFilter_Init(&InFilt2PosRef, INF2POSREF);
#endif //#if FUNC_DUALFILT_POSREF
#endif // #if FUNC_INPUTFILT_ENABLED

	// Initialize velocity feedback filter 1
	HardVelFilter_Init(&HardInFilt1VelFeb, INF1VELFEB);
	
	// Initialize velocity feedback filter 2
	HardVelFilter_Init(&HardInFilt2VelFeb, INF2VELFEB);
}

/*---------------------------------------------------------------------------
 * Name		:	InputFilter_Rst
 * Input	:	No
 * Output	:	No
 * Description:	Reset position command filters
 *---------------------------------------------------------------------------*/
void InputFilter_Rst(void)
{
#if FUNC_INPUTFILT_ENABLED
	InputFilter_Clr(&InFilt1PosRef);
	
#if FUNC_DUALFILT_POSREF
	InputFilter_Clr(&InFilt2PosRef);
#endif // #if FUNC_DUALFILT_POSREF
#endif // #if FUNC_INPUTFILT_ENABLED
}

/*---------------------------------------------------------------------------
 * Name		:	InputPosFilter_Init
 * Input	:	p - pointer to an instance of InputFilterTypedef
 *				Num - position command filter number; different numbers load parameters from different registers
 * Output	:	No
 * Description:	Position command filter initialization
 *---------------------------------------------------------------------------*/
void InputPosFilter_Init(InputFilterTypedef* p, uint8 Num)
{
	uint8 BaseNum = Num << 1;
	uint16 Temp = 0;
	int32 Num1 = 0;
	int32 Den1 = 0;

	// INFILTCTRL: bit0 - bit1: type of position command filter 1; bit2 - bit3: type of position command filter 2;
	// 0 - No Filter; 1 - first-order low-pass filter; 2 - moving average filter
	Temp = (usSRegHoldBuf[INFILTCTRL] >> BaseNum) & 0x03;
	
	if (p->Mode != Temp)
	{
		p->Mode = Temp;
		InputFilter_Clr(p);
	}
	
	if (p->Mode == INPUTFILTER_LPF) // 1st low pass filter
	{
		Temp = usSRegHoldBuf[INFILT1LPFK + BaseNum];
		
		if (p->LowFilterFreq != Temp)
		{
			p->LowFilterFreq = Temp;
			p->LowFilter = PosLowPassFilt_Init(p->LowFilterMem, p->LowFilterFreq, PROFILE_FREQUENCY * 10);
		}
	}
	else if (p->Mode == INPUTFILTER_AVF) // Moving average filter
	{
		Temp = usSRegHoldBuf[INFILT1AVG + BaseNum];
		if (p->AvgFiltSize != Temp)
		{
			p->AvgFiltSize = Temp;
			p->AvgFilter = AvgFilt_Init(p->AvgFilterMem, p->AvgFiltSize);
		}
	}
}


/*---------------------------------------------------------------------------
 * Name		:	InputPosFilter_realize
 * Input	:	indata - input value to position command filter; if the input exceeds [-32768,32767],
 *				the moving average filter may overflow;
 *				p - pointer to an instance of InputFilterTypedef
 * Output	:	No
 * Description:	Perform filtering calculation for position command filter
 *---------------------------------------------------------------------------*/
int32 InputPosFilter_realize(int32 indata, InputFilterTypedef* p)
{
	if (p->Mode == INPUTFILTER_NOFILT) // No Filter
	{
		p->OutData = indata;
	}
	else if(p->Mode == INPUTFILTER_LPF) // 1st low pass filter
	{
		p->OutData = PosLowPassFilt_realize(p->LowFilter, indata);
	}
	else // if (p->Mode == INPUTFILTER_AVF) // Moving average filter
	{	
		p->OutData = AvgFilt_realize(p->AvgFilter, indata);
	}
	
	return p->OutData;
}


/*---------------------------------------------------------------------------
 * Name		:	InputFilter_Clr
 * Input	:	p - pointer to an InputFilterTypedef instance
 * Output	:	No
 * Description:	Reset position command filter
 *---------------------------------------------------------------------------*/
void InputFilter_Clr(InputFilterTypedef* p)
{	
	/* 1st low pass filter */
	PosLowPassFilt_Clr(p->LowFilter);

	/* Moving average filter */
	AvgFilt_Clr(p->AvgFilter);
}

/*---------------------------------------------------------------------------
 * Name		:	HardVelFilter_Init
 * Input	:	p - pointer to an instance of HardInputFilterTypedef
 *				Num - velocity feedback filter number; different numbers load parameters from different registers
 * Output	:	No
 * Description:	Velocity feedback filter initialization. Supports one moving average filter (depth 256*2byte) + two first-order low-pass filters
 *---------------------------------------------------------------------------*/
void HardVelFilter_Init(HardInputFilterTypedef* p, uint8 Num)
{
	uint8 BaseNum = Num << 1;
	uint16 Temp = 0;
	int64 Num1 = 0;
	int64 Den1 = 0;
	int32 fs;
	int16 Ka;
	bool bTmp;
	
	// INFILTCTRL: bit4 - bit5: type of velocity feedback filter 1; bit6 - bit7: type of velocity feedback filter 2;
	// 0 - No Filter; 1 - first-order low-pass filter; 2 - moving average filter
	Temp = (usSRegHoldBuf[INFILTCTRL] >> BaseNum) & 0x03;

	if (p->Mode != Temp)
	{
		p->Mode = Temp;
		
		if (Num == INF1VELFEB)
		{
			if (p->Mode == INPUTFILTER_LPF)
			{
				set_csr(DRV1_FCR4, SLF1_EN);
				clr_csr(DRV1_FCR4, SMF_EN);
			}
			else if (p->Mode == INPUTFILTER_AVF)
			{
				clr_csr(DRV1_FCR4, SLF1_EN);
				set_csr(DRV1_FCR4, SMF_EN);
			}
			else
			{
				clr_csr(DRV1_FCR4, SLF1_EN);
				clr_csr(DRV1_FCR4, SMF_EN);
			}
		}
		else // if(Num == INF2VELFEB)
		{
			if (p->Mode == INPUTFILTER_LPF)
			{
				set_csr(DRV1_FCR4, SLF2_EN);
			}
			else
			{
				clr_csr(DRV1_FCR4, SLF2_EN);
			}
		}
		
		HardVelFilter_Clr(p);
	}

	if (p->Mode == INPUTFILTER_LPF) // 1st low pass filter
	{
		Temp = usSRegHoldBuf[INFILT1LPFK + BaseNum];

		if (p->LpfK != Temp)
		{
			p->LpfK = Temp;
			fs = (int32) VELFEB_FREQUENCY * 1000;

			Num1 = (int64)2 * pi_Q15 * (int32)p->LpfK;
			Den1 = ((int64)fs * 10) << INLPF_Q_SHIFT;
			Ka = (Num1 << 15) / (Num1 + Den1);
			
			if (Num == INF1VELFEB)
			{
				bTmp = false;
				if (readbit_csr(DRV1_FCR4, SLF1_EN))
				{
					bTmp = true;
					while (readbit_csr(DRV1_FCR4, SF_CAL)) {};
					clr_csr(DRV1_FCR4, SLF1_EN);
				}
				NFOC_SLF1K = Ka;
				NFOC_SLFLT1 = 0;
				NFOC_SLF1IN = 0;
				if (bTmp) set_csr(DRV1_FCR4, SLF1_EN);
			}
			else 
			{
				bTmp = false;
				if (readbit_csr(DRV1_FCR4, SLF2_EN))
				{
					bTmp = true;
					while (readbit_csr(DRV1_FCR4, SF_CAL)) {};
					clr_csr(DRV1_FCR4, SLF2_EN);
				}
				NFOC_SLF2K = Ka;
				NFOC_SLFLT2 = 0;
				NFOC_SLF2IN = 0;
				if (bTmp) set_csr(DRV1_FCR4, SLF2_EN);
			}
		}
	}
	else if (p->Mode == INPUTFILTER_AVF && Num == INF1VELFEB) // Moving average filter
	{
		Temp = usSRegHoldBuf[INFILT3AVG];
		p->FiltSize = NFOC_SMFSIZE;
		if (p->FiltSize != Temp)
//		if ((uint8)NFOC_SMFSIZE != (uint8)Temp)
		{
			if (Temp > MAX_INFILT_RANK)
			{
				Temp = MAX_INFILT_RANK;
			}
			
			bTmp = false;
			if (readbit_csr(DRV1_FCR4, SMF_EN))
			{
				bTmp = true;
				while (readbit_csr(DRV1_FCR4, SF_CAL)) {};
				clr_csr(DRV1_FCR4, SMF_EN);
			}
			memset(&NFOC_SMFPNT, 0, 262 * 2);
			NFOC_SMFSIZE = Temp;
			if (bTmp) set_csr(DRV1_FCR4, SMF_EN);
		}
	}
	
}


/*---------------------------------------------------------------------------
 * Name		:	HardVelFilter_Clr
 * Input	:	p - pointer to a HardInputFilterTypedef instance
 * Output	:	No
 * Description:	Reset velocity feedback filter
 *---------------------------------------------------------------------------*/
void HardVelFilter_Clr(HardInputFilterTypedef* p)
{
	bool bTmp;

	while (readbit_csr(DRV1_FCR4, SF_CAL)) {};

	bTmp = false;
	if (readbit_csr(DRV1_FCR4, SMF_EN))
	{
		bTmp = true;
		clr_csr(DRV1_FCR4, SMF_EN);
	}
	memset(&NFOC_SMFPNT, 0, 262 *2);
	if (bTmp) set_csr(DRV1_FCR4, SMF_EN);


	bTmp = false;
	if (readbit_csr(DRV1_FCR4, SLF1_EN))
	{
		bTmp = true;
		clr_csr(DRV1_FCR4, SLF1_EN);
	}
	NFOC_SLFLT1 = 0;
	NFOC_SLF1IN = 0;
	if (bTmp) set_csr(DRV1_FCR4, SLF1_EN);


	bTmp = false;
	if (readbit_csr(DRV1_FCR4, SLF2_EN))
	{
		bTmp = true;
		clr_csr(DRV1_FCR4, SLF2_EN);
	}
	NFOC_SLFLT2 = 0;
	NFOC_SLF2IN = 0;
	if (bTmp) set_csr(DRV1_FCR4, SLF2_EN);
}
/********************************* END OF FILE *********************************/
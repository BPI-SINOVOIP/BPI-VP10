/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ADC.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define ADC
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include "ADC.h"
#include <Myproject.h>

CurrentOffset mcCurOffset = { 0 };

void ADC_Init(void)
{
	/*************ADC PIN Analog Function Config*********************/
	set_csr(PB_AN, PIN10);		// AD0 CH open--IU-->FOC Trigger mode
	set_csr(PB_AN, PIN13);		// AD1 CH open--IV-->FOC Trigger mode
	set_csr(PB_AN, PIN7);		// AD4 CH open--IBUS/IW-->FOC Trigger mode
	set_csr(PB_AN, PIN0);		// AD2 CH open--DCBUS-->FOC Trigger mode
	
#ifdef TEMP_PIN
  	set_csr(TEMP_AN, TEMP_PIN);		// AD3 CH open--Temp
#endif
  	
#ifdef ANAIN_PIN
	set_csr(ANAIN_AN, ANAIN_PIN);		//AD11 CH open--ANALOGIN2-->General mode
#endif

	/****************************************************************/

	/***********************ADC Channel Enable***********************/
#ifdef ADC1_ENABLEMASK
	set_csr(ADC1_MASK, ADC1_ENABLEMASK);
#endif

	write_csr(ADC1_SCYC, 0x3333);
	/******************ADC Result Alignment***************************
	0:Right Alignment eg:max:0x0fff;
	1:Left-Second MSB Alignment eg:max:0x7ff8;
	*****************************************************************/
	set_csr(ADC1_CR, ADCALI);
	/***********************ADC Interrupt Enable*********************/
	clr_csr(ADC1_CR, ADCIE);
	/***************************ADC Enable***************************/
	set_csr(ADC1_CR, ADCEN);
	/****************************************************************/
}

void ADC2_Init(void)
{
	/*************ADC PIN Analog Function Config*********************/
//	set_csr(PC_AN, PIN0);   //AD0 P20 CH open--IU-->FOC Trigger mode
//	set_csr(PC_AN, PIN3);   //AD1 P23 CH open--IV-->FOC Trigger mode
//	set_csr(PC_AN, PIN4);   //AD2 P24 CH open--DCBUS-->FOC Trigger mode
//	//  set_csr(PC_AN, PIN5);   //AD3 P25 CH open
//	set_csr(PC_AN, PIN7);   //AD4 P27 CH open--IBUS/IW-->FOC Trigger mode

#ifdef TEMP2_PIN
	set_csr(TEMP2_AN, TEMP2_PIN);		// AD3 CH open--Temp
#endif
	/****************************************************************/

	/***********************ADC Channel Enable***********************/
#ifdef ADC2_ENABLEMASK
	set_csr(ADC2_MASK, ADC2_ENABLEMASK); // 
	
	write_csr(ADC2_SCYC, 0x0333);

	/******************ADC Result Alignment***************************
	0:Right Alignment eg:max:0x0fff;
	1:Left-Second MSB Alignment eg:max:0x7ff8;
	*****************************************************************/
    set_csr(ADC2_CR, ADCALI);
	/***********************ADC Interrupt Enable*********************/
    clr_csr(ADC2_CR, ADCIE);
	/***************************ADC Enable***************************/
	set_csr(ADC2_CR, ADCALI | ADCEN);
	/****************************************************************/
	
#endif
}


void UpdateCurrentOffset(void)
{
	int16 CuroffJitter = usSRegHoldBuf[CUROFFJITTER];
	if (CuroffJitter <= 0 || CuroffJitter > 16383)
	{
		CuroffJitter = 1000;
	}

#if ADCOFFSET_HARDWARE_ENABLED > 0

	NFOC_IRLOW = 16384 - CuroffJitter;
	NFOC_IRUPP = 16384 + CuroffJitter;
	NFOC_OSCNT = 0;
	NFOC_OSSUM = 0;

	set_csr(DRV1_FCR2, OFFSET_EN); // 电流基准自动校准使能
	while (readbit_csr(DRV1_FCR2, OFFSET_EN)) {};

#if (HW_ADC_SYNC == ADCSAM_SYNC)
	NFOC2_IRLOW = 16384 - CuroffJitter;
	NFOC2_IRUPP = 16384 + CuroffJitter;
	NFOC2_OSCNT = 0;
	NFOC2_OSSUM = 0;

	set_csr(DRV2_FCR2, OFFSET_EN); // 电流基准自动校准使能
	while (readbit_csr(DRV2_FCR2, OFFSET_EN)) {};

	NFOC_IBREF = NFOC2_IBREF;
#endif

	Fault_CurrentOffset(); // 检查是否有报错
	mcCurOffset.OffsetFlag = 1;

#else

	int16 OffsetCount = 0;
	int16 IuOffset = 0; //Iu的偏置电压
	int32 IuOffsetSum = 0;    //Iu的偏置电压总和
	int16 IvOffset = 0; //Iv的偏置电压
	int32 IvOffsetSum = 0; //Iv的偏置电压总和

	for (OffsetCount = 0; OffsetCount < 500; OffsetCount++)
	{
		Delay_us(100);

		IuOffsetSum += (NFOC_I1 & 0x7ff8);
		IuOffset = IuOffsetSum >> 4;
		IuOffsetSum -= IuOffset;

		IvOffsetSum += (NFOC_I2 & 0x7ff8);
		IvOffset = IvOffsetSum >> 4;
		IvOffsetSum -= IvOffset;
	}


	if (IuOffset > 16384 + CuroffJitter || IuOffset < CuroffJitter)
	{
		Fault_Handler(FaultCurrentOffset, FLAG_CUROFF); // 报错
	}

	NFOC_IAREF = IuOffset;
	NFOC_IBREF = IvOffset;



	mcCurOffset.OffsetFlag = 1;

#endif // #if ADCOFFSET_HARDWARE_ENABLED > 0
}


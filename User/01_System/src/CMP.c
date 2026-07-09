/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : CMP.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define CMP
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include "MyProject.h"


void CMP3_Init(void)
{
	/******CMP3 port analog function settings*******/
	#if(Compare_InputMode == Single_Input)
	{
		set_csr(PB_AN, PIN7);				//CMP3 Pin set to analog mode  +
		clr_csr(CMP_CR1, CMP3MOD1);			//00: Single positive input mode, PB7 connects to positive input; 01: Dual comparator mode, PB10 and PB13 connect to positive inputs;
		clr_csr(CMP_CR1, CMP3MOD0);	        //1X: Three comparator mode, PB7, PB10 and PB13 connect to positive inputs;
	}
	#elif(Compare_InputMode == Double_Input)
	{
		set_csr(PB_AN, PIN10 | PIN13);		//CMP3 Pin set to analog mode  +
		clr_csr(CMP_CR1, CMP3MOD1);			//00: Single positive input mode, PB7 connects to positive input; 01: Dual comparator mode, PB10 and PB13 connect to positive inputs;
		set_csr(CMP_CR1, CMP3MOD0);	        //1X: Three comparator mode, PB7, PB10 and PB13 connect to positive inputs;
	}
	#elif(Compare_InputMode == Three_Input)
	{
		set_csr(PB_AN, PIN7 | PIN13 | PIN10); //CMP3 Pin set to analog mode  +
		set_csr(CMP_CR1, CMP3MOD1);			//00: Single positive input mode, PB7 connects to positive input; 01: Dual comparator mode, PB10 and PB13 connect to positive inputs;
		clr_csr(CMP_CR1, CMP3MOD0);	        //1X: Three comparator mode, PB7, PB10 and PB13 connect to positive inputs;
	}
	#endif	//end Compare_InputMode

	#if(Compare_Source == Compare_Hardware) //If Compare_Mode is set to Compare_Hardware where hardware sets the over-current threshold, then the threshold comes from hardware, so the DAC must be turned off
	{
		clr_csr(DAC_CR, DACEN);
	}
	#elif(Compare_Source == Compare_DAC)
	{
		/**Enable PB14 analog function and digital output, used for testing**/
//		set_csr(PB_AN, PIN14);
//		set_csr(PB_OE, PIN14);
		/**********DAC Enable******************/
		set_csr(DAC_CR, DACEN);    //Enable DAC0 output
		/******************************
		0: Normal mode, DAC output voltage range is 0 to VREF
		1: Half-voltage conversion mode, DAC output voltage range is VHALF to VREF
		****************************/
		set_csr(DAC_CR, DACMOD);
		/**********Set DAC over-current value, discard low-bit precision*****************/
#if FUNC_EEPROM_ENABLED
		uint16 temp = usSRegHoldBuf[HARDCURRENT] >> 5;
		if (temp > 511)
			temp = 511;
		write_csr(DAC_DR0, temp);
#else
		write_csr(DAC_DR0, 511);// Temporarily set to maximum value to avoid false triggering caused by input current voltage fluctuations after motor enable
#endif
	}
	#endif	//end Compare_Mode
	clr_csr(CMP_CR1, CMP3HYS);	//CMP3 HYS Enable   0: No hysteresis 1: -9mV hysteresis
	/*-------------------------------------------------------------------------------------------------
	MOE configuration when hardware protection is triggered: hardware disables driver output; in typical applications MOE auto-clear should be enabled
	00--MOE not auto-clear
	01--MOE auto-clear
	-------------------------------------------------------------------------------------------------*/
	clr_csr(DRV1_CR, MOEMD1);
	set_csr(DRV1_CR, MOEMD0);
	/*-------------------------------------------------------------------------------------------------
	Current protection time filter width
	00- No filtering
	01- 4 CPU clocks
	10- 8 CPU clocks
	11- 16 CPU clocks
	-------------------------------------------------------------------------------------------------*/
	set_csr(CMP_CR3, CMP3FSEL1);	 //CMP3 filter coefficient configuration
	set_csr(CMP_CR3, CMP3FSEL0);

	clr_csr(CMP_IFR, CMP3IF);

	clr_csr(CMP_CR0, CMP3IM1);	//CMP3 interrupt mode configuration (non-00 means interrupt enabled by default, no separate enable bit is needed)
	set_csr(CMP_CR0, CMP3IM0);	//00-->No interrupt  01-->Rising edge interrupt  10-->Falling edge interrupt   11-->Rising/Falling edge interrupt
	
//	write_csr(IP4, FO_CMP3_INT_PRI);			// DRV1 interrupt (interrupt number 8) priority level is 5, priority lower than over-current protection

	set_csr(CMP_CR1, CMP3EN);	//CMP3 Enable
	/*********************************/
}
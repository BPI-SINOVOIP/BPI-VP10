/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : AMP.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define AMP
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include <Myproject.h>

void AMP_Init(void)
{
	set_csr(PB_AN, PIN5);               //AMP0 Pin set to analog mode  +
	set_csr(PB_AN, PIN6);               //AMP0 Pin set to analog mode  -
	set_csr(PB_AN, PIN7);               //AMP0 Pin set to analog mode  O

	clr_csr(AMP_CR0, AMP0MGND);         //Disable internal grounding of the amplifier negative input
	clr_csr(PB_OE, PIN6);               //Force PB_OE[6] to 0 to put PB6 into analog mode

	set_csr(PB_AN, PIN8);               //AMP1 Pin set to analog mode  +
	set_csr(PB_AN, PIN9);               //AMP1 Pin set to analog mode  -
	set_csr(PB_AN, PIN10);              //AMP1 Pin set to analog mode  O

	clr_csr(AMP_CR0, AMP12MGND);        //Disable internal grounding of the amplifier negative input
	clr_csr(PB_OE, PIN9);               //Force PB_OE[9] to 0 to put PB9 into analog mode

	set_csr(PB_AN, PIN11);              //AMP2 Pin set to analog mode  +
	set_csr(PB_AN, PIN12);              //AMP2 Pin set to analog mode  -
	set_csr(PB_AN, PIN13);              //AMP2 Pin set to analog mode  O

	clr_csr(AMP_CR0, AMP12MGND);		//Disable internal grounding of the amplifier negative input
	clr_csr(PB_OE, PIN12);              //Force PB_OE[12] to 0 to put PB12 into analog mode
	

#if (HW_AMP_MODE == AMP_NOMAL)      //External amplification
	
	//000-->Genaral AMP 001-->2X 010-->4X 011-->8X 100-->16X 101-->32X Others-->32X
	/**********AMP0 PGA SET************/
	clr_csr(AMP_CR1, AMP0GAIN2);        //0x80
	clr_csr(AMP_CR1, AMP0GAIN1);        //0x40
	clr_csr(AMP_CR1, AMP0GAIN0);        //0x20
	/*********AMP1/2 PGA SET***********/
	clr_csr(AMP_CR1, AMPPH12GAIN2);		//0x20
	clr_csr(AMP_CR1, AMPPH12GAIN1);		//0x10
	clr_csr(AMP_CR1, AMPPH12GAIN0);		//0x08
	/*********************************/
	
#else
	
#if (HW_AMP_GAIN == AMP4x)
	clr_csr(AMP_CR1, AMP0GAIN2);
	clr_csr(AMP_CR1, AMP0GAIN1);
	set_csr(AMP_CR1, AMP0GAIN0);

	clr_csr(AMP_CR1, AMPPH12GAIN2);
	clr_csr(AMP_CR1, AMPPH12GAIN1);
	set_csr(AMP_CR1, AMPPH12GAIN0);
	
#elif (HW_AMP_GAIN == AMP8x)
	clr_csr(AMP_CR1, AMP0GAIN2);
	set_csr(AMP_CR1, AMP0GAIN1);
	clr_csr(AMP_CR1, AMP0GAIN0);

	clr_csr(AMP_CR1, AMPPH12GAIN2);
	set_csr(AMP_CR1, AMPPH12GAIN1);
	clr_csr(AMP_CR1, AMPPH12GAIN0);

#elif (HW_AMP_GAIN == AMP16x)
	clr_csr(AMP_CR1, AMP0GAIN2);
	set_csr(AMP_CR1, AMP0GAIN1);
	set_csr(AMP_CR1, AMP0GAIN0);

	clr_csr(AMP_CR1, AMPPH12GAIN2);
	set_csr(AMP_CR1, AMPPH12GAIN1);
	set_csr(AMP_CR1, AMPPH12GAIN0);

#elif (HW_AMP_GAIN == AMP20x)
	set_csr(AMP_CR1, AMP0GAIN2);
	clr_csr(AMP_CR1, AMP0GAIN1);
	clr_csr(AMP_CR1, AMP0GAIN0);

	set_csr(AMP_CR1, AMPPH12GAIN2);
	clr_csr(AMP_CR1, AMPPH12GAIN1);
	clr_csr(AMP_CR1, AMPPH12GAIN0);
#endif

#endif

	set_csr(AMP_CR0, AMP2EN);			//AMP2 Enable
	set_csr(AMP_CR0, AMP1EN);			//AMP1 Enable
	set_csr(AMP_CR0, AMP0EN);			//AMP0 Enable
	/*********************************/
}



void VREFConfigInit(void)
{
	/************************VREF&VHALF Config************************/
#if (HW_ADC_VREF == VREF3_0)
	{
		set_csr(VREF_VHALF_CR, VREFSEL1);     //00-->4.5V   01-->VDD5
		clr_csr(VREF_VHALF_CR, VREFSEL0);     //10-->3.0V   11-->4.0V
	}
#elif (HW_ADC_VREF == VREF4_0)
	{
		set_csr(VREF_VHALF_CR, VREFSEL1);     //00-->4.5V   01-->VDD5
		set_csr(VREF_VHALF_CR, VREFSEL0);     //10-->3.0V   11-->4.0V
	}
#elif (HW_ADC_VREF == VREF4_5)
	{
		clr_csr(VREF_VHALF_CR, VREFSEL1);     //00-->4.5V   01-->VDD5
		clr_csr(VREF_VHALF_CR, VREFSEL0);     //10-->3.0V   11-->4.0V
	}
#elif (HW_ADC_VREF == VREF5_0)
	{
		clr_csr(VREF_VHALF_CR, VREFSEL1);     //00-->4.5V   01-->VDD5
		set_csr(VREF_VHALF_CR, VREFSEL0);     //10-->3.0V   11-->4.0V
	}
#endif

#if (VREF_OUT_EN)
	set_csr(PD_AN, PIN5);                      //VREF Voltage -->PD5 Output: whether to output to PD5 pin; output must be configured accordingly
	set_csr(PD_OE, PIN5);                      //VREF Voltage -->PD5 Output: whether to output to PD5 pin
	set_csr(VREF_VHALF_CR, VREFEN);
#endif
#if (VHALF_OUT_EN)
	set_csr(PD_AN, PIN2);
	set_csr(VREF_VHALF_CR, VHALFEN);
#endif
	/* ---------------------------------------------------------------------- */
}
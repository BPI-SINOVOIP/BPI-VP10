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
	set_csr(PB_AN, PIN5);               //AMP0 Pin设置为模拟模式  +
	set_csr(PB_AN, PIN6);               //AMP0 Pin设置为模拟模式  -
	set_csr(PB_AN, PIN7);               //AMP0 Pin设置为模拟模式  O

	clr_csr(AMP_CR0, AMP0MGND);         // 禁止运放反向输入端内部接地
	clr_csr(PB_OE, PIN6);               //PB_OE[6]强制为0，让PB6进入模拟模式

	set_csr(PB_AN, PIN8);               //AMP1 Pin设置为模拟模式  +
	set_csr(PB_AN, PIN9);               //AMP1 Pin设置为模拟模式  -
	set_csr(PB_AN, PIN10);              //AMP1 Pin设置为模拟模式  O

	clr_csr(AMP_CR0, AMP12MGND);        // 禁止运放反向输入端内部接地
	clr_csr(PB_OE, PIN9);               //PB_OE[9]强制为0，让PB9进入模拟模式

	set_csr(PB_AN, PIN11);              //AMP2 Pin设置为模拟模式  +
	set_csr(PB_AN, PIN12);              //AMP2 Pin设置为模拟模式  -
	set_csr(PB_AN, PIN13);              //AMP2 Pin设置为模拟模式  O

	clr_csr(AMP_CR0, AMP12MGND);		// 禁止运放反向输入端内部接地
	clr_csr(PB_OE, PIN12);              //PB_OE[12]强制为0，让PB12进入模拟模式
	

#if (HW_AMP_MODE == AMP_NOMAL)      //外部放大
	
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
	set_csr(PD_AN, PIN5);                      //VREF Voltage -->PD5 Output 是否输出到PD5引脚，需同步配置输出
	set_csr(PD_OE, PIN5);                      //VREF Voltage -->PD5 Output 是否输出到PD5引脚
	set_csr(VREF_VHALF_CR, VREFEN);
#endif
#if (VHALF_OUT_EN)
	set_csr(PD_AN, PIN2);
	set_csr(VREF_VHALF_CR, VHALFEN);
#endif
	/* ---------------------------------------------------------------------- */
}

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
	/******CMP3 端口模拟功能设置*******/
	#if(Compare_InputMode == Single_Input)
	{
		set_csr(PB_AN, PIN7);				//CMP3 Pin设置为模拟模式  +
		clr_csr(CMP_CR1, CMP3MOD1);			//00：单正输入端模式，PB7接正输入端；01: 双比较器模式，PB10和PB13接正输入端；
		clr_csr(CMP_CR1, CMP3MOD0);	        //1X：3比较器模式，PB7、PB10和PB13接正输入端；
	}
	#elif(Compare_InputMode == Double_Input)
	{
		set_csr(PB_AN, PIN10 | PIN13);		//CMP3 Pin设置为模拟模式  +
		clr_csr(CMP_CR1, CMP3MOD1);			//00：单正输入端模式，PB7接正输入端；01: 双比较器模式，PB10和PB13接正输入端；
		set_csr(CMP_CR1, CMP3MOD0);	        //1X：3比较器模式，PB7、PB10和PB13接正输入端；
	}
	#elif(Compare_InputMode == Three_Input)
	{
		set_csr(PB_AN, PIN7 | PIN13 | PIN10); //CMP3 Pin设置为模拟模式  +
		set_csr(CMP_CR1, CMP3MOD1);			//00：单正输入端模式，PB7接正输入端；01: 双比较器模式，PB10和PB13接正输入端；
		clr_csr(CMP_CR1, CMP3MOD0);	        //1X：3比较器模式，PB7、PB10和PB13接正输入端；
	}
	#endif	//end Compare_InputMode

	#if(Compare_Source == Compare_Hardware) //若Compare_Mode选择Compare_Hardware硬件设置硬件过流值，则过流值来自硬件，则需关闭DAC
	{
		clr_csr(DAC_CR, DACEN);
	}
	#elif(Compare_Source == Compare_DAC)
	{
		/**PB14使能其模拟功能，使能数字输出，用于测试**/
//		set_csr(PB_AN, PIN14);
//		set_csr(PB_OE, PIN14);
		/**********DAC Enable******************/
		set_csr(DAC_CR, DACEN);    //使能DAC0输出
		/******************************
		0: 正常模式，DAC输出电压范围为0到VREF
		1: 半电压转换模式，DAC输出电压范围为VHALF到VREF
		****************************/
		set_csr(DAC_CR, DACMOD);
		/**********设置DAC过流值,舍弃低位精度*****************/
#if FUNC_EEPROM_ENABLED
		uint16 temp = usSRegHoldBuf[HARDCURRENT] >> 5;
		if (temp > 511)
			temp = 511;
		write_csr(DAC_DR0, temp);
#else
		write_csr(DAC_DR0, 511);// 暂时设为最大值，避免输入电流在电机使能后电压值跳动导致误触发
#endif
	}
	#endif	//end Compare_Mode
	clr_csr(CMP_CR1, CMP3HYS);	//CMP3 HYS Enable   0：无迟滞1：-9mV迟滞
	/*-------------------------------------------------------------------------------------------------
	触发硬件保护后硬件关闭驱动输出MOE配置， 常规应用需要使能MOE自动清零
	00--MOE不自动清零
	01--MOE自动清零
	-------------------------------------------------------------------------------------------------*/
	clr_csr(DRV1_CR, MOEMD1);
	set_csr(DRV1_CR, MOEMD0);
	/*-------------------------------------------------------------------------------------------------
	电流保护时间滤波宽度
	00-不滤波
	01-4cpu clock
	10-8cpu clock
	11-16cpu clock
	-------------------------------------------------------------------------------------------------*/
	set_csr(CMP_CR3, CMP3FSEL1);	 //CMP3滤波系数配置
	set_csr(CMP_CR3, CMP3FSEL0);

	clr_csr(CMP_IFR, CMP3IF);

	clr_csr(CMP_CR0, CMP3IM1);	//CMP3 中断模式配置（非00即默认中断使能，不再需要单独的使能位）
	set_csr(CMP_CR0, CMP3IM0);	//00-->不产生中断  01-->上升沿产生中断  10-->下降沿产生中断   11-->上升/下降沿产生中断
	
//	write_csr(IP4, FO_CMP3_INT_PRI);			// DRV1中断(中断号8) 优先级别为5，优先级低于过流保护

	set_csr(CMP_CR1, CMP3EN);	//CMP3 Enable
	/*********************************/
}

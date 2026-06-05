/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FreqDiv.c
 * Author        : Victor.jin
 * Date          : 2024-04-07
 * Description   : 分频输出
 *
 * Record        :
 * V1.0, 2024-04-07, Victor.jin: Created file
 */


/********************************************************************************
* Header Definition
********************************************************************************/
#include <Myproject.h>


#if EXCTRL_ENCOUT_ENABLED

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
FreqDivTypedef FreqDiv;


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/
void FreqDiv_Init(void);
void FreqDiv_Handler(void);

/*---------------------------------------------------------------------------*/
/* Name     :   
/* Input    :   NO
/* Output   :   NO
/* Description:
/*---------------------------------------------------------------------------*/
void FreqDiv_Init(void)
{
	FreqDiv.OUT_SourceSel = usSRegHoldBuf[ENCOUTMODE] & 0x03;				// 0-禁止输出 1-编码器分频输出 2-编码器同步输出 3-脉冲指令同步输出
	FreqDiv.OUT_PhaseSel = (usSRegHoldBuf[ENCOUTMODE] & 0x04) >> 2;			// 0-A超前B		1-B超前A
	FreqDiv.OUT_Z_ModeSel = (usSRegHoldBuf[ENCOUTMODE] & 0x08) >> 3;		// 0-每圈/每个极距产生一个Z信号		1-实际反馈产生Z信号
	FreqDiv.OUT_Z_PolaritySel = (usSRegHoldBuf[ENCOUTMODE] & 0x10) >> 4;	// 0-Z信号高电平有效	1-Z信号低电平有效

	FreqDiv.OUT_FreqDivPulse = ((uint32)usSRegHoldBuf[ENCOUTRES_H] << 16) | usSRegHoldBuf[ENCOUTRES_L];	// 编码器分频脉冲数
	FreqDiv.OUT_Z_PulseInterval = FreqDiv.OUT_FreqDivPulse / 4;	// Z信号产生的周期，每单圈分频脉冲数产生一个

#if 1
	/*** 无flash情况下的临时赋初值的变量，后期可注释 ***/
	FreqDiv.OUT_FreqDivPulse = 20000;
	FreqDiv.OUT_Z_PulseInterval = FreqDiv.OUT_FreqDivPulse / 4;
	FreqDiv.OUT_SourceSel = 0;
	FreqDiv.OUT_PhaseSel = 0;
	FreqDiv.OUT_Z_ModeSel = 0;
	FreqDiv.OUT_Z_PolaritySel = 0;
	/***************************************************/
#endif
	
	// QEP输出模式加载DR配置
	clr_csr(TIM5_CR1, T5_CNTR_CLR_EN);	// 0-每个主时钟都更新DR值，1-Driver1载波中断DCIF到来时更新DR值
	
	if (FreqDiv.OUT_SourceSel != 0) // 1-编码器分频输出 2-编码器同步输出 3-脉冲指令同步输出
	{
		/* 改完操作模式后要重新更新DR值和QEP_ARR值，否则会异常 */
		set_csr(TIM5_CR0, T5MOD2);	// 000-->输入捕获模式		001-->输出模式
		clr_csr(TIM5_CR0, T5MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
		clr_csr(TIM5_CR0, T5MOD0);	// 100-->QEP输出模式

		// Timer5 QEP A 输出极性配置
		clr_csr(TIM5_CR2, TIM5_A_EDGE_SEL);	// 0-初始电平为低电平	1-初始电平为高电平
		// Timer5 QEP B 输出极性配置
		set_csr(TIM5_CR2, TIM5_B_EDGE_SEL);	// 0-初始电平为低电平	1-初始电平为高电平

		// 当前时钟频率下，一个输出周期内的计数值。如：48Mh时钟 8kHz中断: 48000000/8000 = 6000
		// ！更改分频输出的周期时需修改此处宏
		write_csr(TIM5_ARR, MAXFREQOUT);

		if (FreqDiv.OUT_SourceSel == 1)			// 1-编码器分频输出
		{
			// Timer5 QEP AB 输出选择
			clr_csr(TIM5_CR2, TIM5_AB_SEL1);		// 00-Timer5计算输出
			clr_csr(TIM5_CR2, TIM5_AB_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入

			// 输出相位选择
			if (FreqDiv.OUT_PhaseSel == 0)		// 0-A超前B
			{
				FreqDiv.OUT_PhaseFlag = 1;
			}
			else							// 1-B超前A
			{
				FreqDiv.OUT_PhaseFlag = -1;
			}
			
			// Z信号模式选择
			if (FreqDiv.OUT_Z_ModeSel == 0)		// 0-每圈/每个极距输出一个Z信号
			{
				// Timer5 QEP Z 输出选择
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5计算输出
				clr_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入

				write_csr(TIM5_QEP_ARR, FreqDiv.OUT_Z_PulseInterval);
			}
			else							// 1-输出Z信号与编码器信号一致
			{
				// Timer5 QEP Z 输出选择
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5计算输出
				set_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入
			}
			// Z信号极性选择
			if (FreqDiv.OUT_Z_PolaritySel == 0)	// 0-Z信号高电平有效
			{
				clr_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
			else							// 1-Z信号低电平有效
			{
				set_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
		}
		else if (FreqDiv.OUT_SourceSel == 2)	// 2-编码器同步输出（单独拎出来是因为在没有QEP编码器输入的时候这个不能用，另外直通的时候也无法更改极性或相位）
		{
			// Timer5 QEP AB 输出选择
			clr_csr(TIM5_CR2, TIM5_AB_SEL1);		// 00-Timer5计算输出
			set_csr(TIM5_CR2, TIM5_AB_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入

			// Z信号模式选择
			if (FreqDiv.OUT_Z_ModeSel == 0)		// 0-每圈/每个极距输出一个Z信号
			{
				// Timer5 QEP Z 输出选择
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5计算输出
				clr_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入

				write_csr(TIM5_QEP_ARR, FreqDiv.OUT_Z_PulseInterval);
			}
			else							// 1-输出Z信号与编码器信号一致
			{
				// Timer5 QEP Z 输出选择
				clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5计算输出
				set_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入
			}
			// Z信号极性选择
			if (FreqDiv.OUT_Z_PolaritySel == 0)	// 0-Z信号高电平有效
			{
				clr_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
			else							// 1-Z信号低电平有效
			{
				set_csr(TIM5_CR1, T5Z_EDGE_SEL);
			}
		}
		else if (FreqDiv.OUT_SourceSel == 3)	// 3-脉冲指令同步输出
		{
			// Timer5 QEP AB 输出选择
			set_csr(TIM5_CR2, TIM5_AB_SEL1);		// 00-Timer5计算输出
			clr_csr(TIM5_CR2, TIM5_AB_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入

			/* 此处设为仿真输出且QEP_ARR清零使Z信号不输出 */
			clr_csr(TIM5_CR2, TIM5_Z_SEL1);		// 00-Timer5计算输出
			clr_csr(TIM5_CR2, TIM5_Z_SEL0);		// 01-直通输出T2的输入		10-直通输出T6的输入

			clr_csr(TIM5_CR1, T5Z_EDGE_SEL);	// Z极性选择（0 -高电平有效；1 -低电平有效）
			write_csr(TIM5_QEP_ARR, 0);
		}
	}
	else	// 0-禁止输出
	{
		/* 禁止输出模式下可作为编码器输出做全闭环功能，后续可在这里加编码器输入的剩余配置 */
		clr_csr(TIM5_CR0, T5MOD2);	// 000-->输入捕获模式		001-->输出模式
		set_csr(TIM5_CR0, T5MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
		set_csr(TIM5_CR0, T5MOD0);	// 100-->QEP输出模式
	}
}



/*---------------------------------------------------------------------------*/
/* Name     :
/* Input    :   NO
/* Output   :   NO
/* Description:
/*---------------------------------------------------------------------------*/
void FreqDiv_Handler(void) // --- 6.6us (修改数据溢出bug，时间从2us加到6.6us，20231215更新)
{
	if (FreqDiv.OUT_SourceSel != 0) // 1-编码器分频输出 2-编码器同步输出 3-脉冲指令同步输出
	{
		if (mcFocCtrl.EncRes != 0)	// 除数为0情况下，数字算出来结果为-1，目前软件规避
		{
			FreqDiv.OUT_PulseDecimal = (int64)QEP.MT_Qep_Margin_Delta * FreqDiv.OUT_FreqDivPulse;					// 本拍输出的脉冲数含小数(放大后) = 本拍输入脉冲差值*单圈分频输出总数
			FreqDiv.OUT_PulseDelta = (FreqDiv.OUT_PulseDecimal + FreqDiv.OUT_PulseRemain) / (int32)mcFocCtrl.EncRes;	// 本拍输出的脉冲数实际值 = (本拍输出的脉冲数含小数(放大后) + 上拍小数余数(放大后)) / 单圈编码器输入总数

			if (FreqDiv.OUT_FreqDivPulse < mcFocCtrl.EncRes && FreqDiv.OUT_PulseDelta < 0)
				FreqDiv.OUT_PulseDelta -= 1;																	// 当输出分频数小于单圈分辨率时，需要在第0拍也引入一个脉冲，即第一次反转就产生一个负向脉冲，否则会损失一个脉冲

			FreqDiv.OUT_PulseRemain += FreqDiv.OUT_PulseDecimal - FreqDiv.OUT_PulseDelta * mcFocCtrl.EncRes;			// 本拍小数余数(放大后) = 上拍小数余数(放大后) + 本拍输出的脉冲数含小数(放大后) - 本拍输出的脉冲数实际值*单圈编码器输入总数 (OUT_PulseDelta前需要考虑是否加强制转换成int64类型，目前没加测试未出错)
		}
		else
		{
			FreqDiv.OUT_PulseDelta = 0;
		}

		if (FreqDiv.OUT_PhaseSel == 0)		// 一个Drv中断周期内输出的脉冲数 写正数就是A超前B，写负数就是B超前A
		{
			FreqDiv.OUT_PulseDelta = FreqDiv.OUT_PulseDelta;
		}
		else
		{
			FreqDiv.OUT_PulseDelta = -FreqDiv.OUT_PulseDelta;
		}
	}
	else
	{
		FreqDiv.OUT_PulseDelta = 0;
	}
	write_csr(TIM5_DR, FreqDiv.OUT_PulseDelta);	// 每个中断周期内分频输出的脉冲数，写入后下个中断周期更新
}


#endif // #if EXCTRL_ENCOUT_ENABLED

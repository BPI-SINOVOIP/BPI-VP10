/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Timer.c
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define Timer
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#include <Myproject.h>


/*****************************************************************************
 * Function      : Timer2_Init
 * Description   : TIM2初始化，用于编码器A quad B的检测。
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Init(void)
{
	clr_csr(TIM2_CR1, T2EN);	// 清除Timer2使能

	clr_csr(PH_SEL, T2ACT);  	//功能转移，0-->不复用; 1-->PA10
	clr_csr(PH_SEL, T2BCT);		//功能转移，0-->不复用; 1-->PA11

	set_csr(TIM2_CR0, T2PSC2);	// 计数器时钟分频选择
	set_csr(TIM2_CR0, T2PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	set_csr(TIM2_CR0, T2PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K

	clr_csr(TIM2_CR1, T2OCM);   // 0-->QEP&RSD模式;		1-->步进模式
	clr_csr(TIM2_CR0, T2CES);   // QEP模式下：外部中断 INT1（零点）清零脉冲计数器使能 0-->Disable  1-->Enable

	clr_csr(TIM2_CR0, T2MOD2);	// 000-->输入捕获模式		001-->输出模式
	set_csr(TIM2_CR0, T2MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM2_CR0, T2MOD0);	// 100-->QEP输出模式

	clr_csr(TIM2_IER, T2IRE);	// 比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM2_IER, T2IPE);	// 输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM2_IER, T2IFE);	// 计数器上溢中断使能 0-->Disable  1-->Enable
	clr_csr(TIM2_SR, T2IR);    // 清除中断标志
	clr_csr(TIM2_SR, T2IP);    // 清除中断标志
	clr_csr(TIM2_SR, T2IF);    // 清除中断标志
	
	write_csr(IP16, TIM2_INT_PRI);		// TIM2中断(中断号16) 优先级别为3

	clr_csr(TIM2_CR0, T2INM2);	// QEP输入滤波深度选择
	clr_csr(TIM2_CR0, T2INM1);	// 000-->不滤波  001-->1个clk  010-->2个clk  011-->3个clk
	clr_csr(TIM2_CR0, T2INM0);	// 100-->4个clk  101-->5个clk  110-->6个clk  111-->7个clk

	clr_csr(TIM2_CR1, T2_DIR_R);	// QEP&ISD&步进模式专用：当前的方向 0-->正向	1-->反向

	clr_csr(TIM2_CR1, T2QEP_IN_CNTR_CLR); // QEP输入模式，检测到Z信号有效沿是否清零TIMx_CNTR：0-->不清零，1-->清零
	clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP输入模式，Z 信号有效沿：0-->上升沿，1-->下降沿

	write_csr(TIM2_DR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_CNTR, 0);

//	set_csr(TIM2_CR1, T2EN);	//TIM2使能	0-->Disable  1-->Enable
	
}

/*****************************************************************************
 * Function      : Timer2_Enable
 * Description   : TIM2使能，用于编码器A quad B的检测。
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Enable(void)
{
	clr_csr(TIM2_CR1, T2EN);	// TIM2使能    0-->Disable  1-->Enable
	
	set_csr(PH_SEL, T2ACT);  	//功能转移，0-->不复用; 1-->PA10
	set_csr(PH_SEL, T2BCT);		//功能转移，0-->不复用; 1-->PA11
	
	clr_csr(TIM2_CR0, T2MOD2);	// 000-->输入捕获模式		001-->输出模式
	set_csr(TIM2_CR0, T2MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM2_CR0, T2MOD0);	// 100-->QEP输出模式
	
	write_csr(TIM2_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_CNTR, 0);
	
	set_csr(TIM2_CR1, T2EN);	// TIM2使能    0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer2_Disable
 * Description   : TIM2去使能
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Disable(void)
{
	clr_csr(TIM2_CR1, T2EN);	// TIM2使能    0-->Disable  1-->Enable
	
	clr_csr(PH_SEL, T2ACT);  	//功能转移，0-->不复用; 1-->PA10
	clr_csr(PH_SEL, T2BCT);		//功能转移，0-->不复用; 1-->PA11
	
	clr_csr(TIM2_CR0, T2MOD2);	// 000-->输入捕获模式		001-->输出模式
	clr_csr(TIM2_CR0, T2MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM2_CR0, T2MOD0);	// 100-->QEP输出模式
	
	write_csr(TIM2_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_CNTR, 0);
	
#if FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	set_csr(TIM2_CR1, T2EN);	// TIM2使能    0-->Disable  1-->Enable
#endif
}


/*****************************************************************************
 * Function      : Timer2_Filter_Update
 * Description   : TIM2更新滤波器系数，QEP输入滤波深度选择
 * Input         : AqbFilt: T2INM2 | T2INM1 | T2INM0
 *							000-->不滤波  001-->2个clk  010-->3个clk  011-->4个clk
 *							100-->5个clk  101-->6个clk  110-->7个clk  111-->8个clk
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Filter_Update(unsigned short AqbFilt)
{
	uint16 temp = 0;
	if (AqbFilt & 0x01)
		temp += T2INM0;
	if (AqbFilt & 0x02)
		temp += T2INM1;
	if (AqbFilt & 0x04)
		temp += T2INM2;
	reset_csr(TIM2_CR0, T2INM2 | T2INM1 | T2INM0, temp);
}


/*****************************************************************************
 * Function      : Timer2_ZIndexInt_Enable
 * Description   : TIM2 Z Index中断使能
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_ZIndexInt_Enable(void)
{
	clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP输入模式，Z 信号有效沿：0-->上升沿，1-->下降沿
	clr_csr(TIM2_SR, T2IR);		// QEP输入模式: 检测到Z有效沿到来时中断事件标志位
	set_csr(TIM2_IER, T2IRE);	// QEP输入模式: 检测到Z有效沿到来时中断使能 0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer2_ZIndexInt_Disable
 * Description   : TIM2 Z Index中断去使能
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_ZIndexInt_Disable(void)
{
	clr_csr(TIM2_SR, T2IR);		// QEP输入模式: 检测到Z有效沿到来时中断事件标志位
	clr_csr(TIM2_IER, T2IRE);	// QEP输入模式: 检测到Z有效沿到来时中断使能 0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer5_Init
 * Description   : TIM5初始化，用于编码器ABZ1的检测。
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Init(void)
{
	clr_csr(TIM5_CR1, T5EN);	// 清除Timer5使能

	clr_csr(PH_SEL, T5ACT);  	//功能转移，0-->不复用; 1-->PA13
	clr_csr(PH_SEL, T5BCT);		//功能转移，0-->不复用; 1-->PA14

	set_csr(TIM5_CR0, T5PSC2);	// 计数器时钟分频选择
	set_csr(TIM5_CR0, T5PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	set_csr(TIM5_CR0, T5PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K

	clr_csr(TIM5_CR1, T5OCM);   // 0-->QEP&RSD模式;		1-->步进模式
	clr_csr(TIM5_CR0, T5CES);   // QEP模式下：外部中断 INT1（零点）清零脉冲计数器使能 0-->Disable  1-->Enable

	clr_csr(TIM5_CR0, T5MOD2);	// 000-->输入捕获模式		001-->输出模式
	set_csr(TIM5_CR0, T5MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM5_CR0, T5MOD0);	// 100-->QEP输出模式

	clr_csr(TIM5_IER, T5IRE);	// 比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM5_IER, T5IPE);	// 输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM5_IER, T5IFE);	// 计数器上溢中断使能 0-->Disable  1-->Enable
	clr_csr(TIM5_SR, T5IR);    // 清除中断标志
	clr_csr(TIM5_SR, T5IP);    // 清除中断标志
	clr_csr(TIM5_SR, T5IF);    // 清除中断标志

	write_csr(IP16, TIM2_INT_PRI);		// TIM2中断(中断号16) 优先级别为3

	clr_csr(TIM5_CR0, T5INM2);	// QEP输入滤波深度选择
	clr_csr(TIM5_CR0, T5INM1);	// 000-->不滤波  001-->1个clk  010-->2个clk  011-->3个clk
	clr_csr(TIM5_CR0, T5INM0);	// 100-->4个clk  101-->5个clk  110-->6个clk  111-->7个clk

	clr_csr(TIM5_CR1, T5_DIR_R);	// QEP&ISD&步进模式专用：当前的方向 0-->正向	1-->反向

	clr_csr(TIM5_CR1, T5QEP_IN_CNTR_CLR); // QEP输入模式，检测到Z信号有效沿是否清零TIMx_CNTR：0-->不清零，1-->清零
	clr_csr(TIM5_CR1, T5Z_EDGE_SEL); // QEP输入模式，Z 信号有效沿：0-->上升沿，1-->下降沿

	write_csr(TIM5_DR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_CNTR, 0);

	//	set_csr(TIM5_CR1, T5EN);	//TIM5使能	0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer5_Enable
 * Description   : TIM5使能，用于编码器A quad B的检测。
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Enable(void)
{
	clr_csr(TIM5_CR1, T5EN);	// TIM5使能    0-->Disable  1-->Enable

	set_csr(PH_SEL, T5ACT);  	//功能转移，0-->不复用; 1-->PA13
	set_csr(PH_SEL, T5BCT);		//功能转移，0-->不复用; 1-->PA14

	clr_csr(TIM5_CR0, T5MOD2);	// 000-->输入捕获模式		001-->输出模式
	set_csr(TIM5_CR0, T5MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM5_CR0, T5MOD0);	// 100-->QEP输出模式

	write_csr(TIM5_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_CNTR, 0);

	set_csr(TIM5_CR1, T5EN);	// TIM5使能    0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer5_Disable
 * Description   : TIM5去使能
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Disable(void)
{
	clr_csr(TIM5_CR1, T5EN);	// TIM5使能    0-->Disable  1-->Enable

	clr_csr(PH_SEL, T5ACT);  	//功能转移，0-->不复用; 1-->PA10
	clr_csr(PH_SEL, T5BCT);		//功能转移，0-->不复用; 1-->PA11

	clr_csr(TIM5_CR0, T5MOD2);	// 000-->输入捕获模式		001-->输出模式
	clr_csr(TIM5_CR0, T5MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM5_CR0, T5MOD0);	// 100-->QEP输出模式

	write_csr(TIM5_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_CNTR, 0);

	//#if FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	//	set_csr(TIM5_CR1, T5EN);	// TIM5使能    0-->Disable  1-->Enable
	//#endif
}

/*****************************************************************************
 * Function      : Timer5_Filter_Update
 * Description   : TIM5更新滤波器系数，QEP输入滤波深度选择
 * Input         : AqbFilt: T5INM2 | T5INM1 | T5INM0
 *							000-->不滤波  001-->2个clk  010-->3个clk  011-->4个clk
 *							100-->5个clk  101-->6个clk  110-->7个clk  111-->8个clk
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Filter_Update(unsigned short AqbFilt)
{
	uint16 temp = 0;
	if (AqbFilt & 0x01)
		temp += T5INM0;
	if (AqbFilt & 0x02)
		temp += T5INM1;
	if (AqbFilt & 0x04)
		temp += T5INM2;
	reset_csr(TIM5_CR0, T5INM2 | T5INM1 | T5INM0, temp);
}


/*****************************************************************************
 * Function      : Timer5_ZIndexInt_Enable
 * Description   : TIM5 Z Index中断使能
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_ZIndexInt_Enable(void)
{
	clr_csr(TIM5_CR1, T5Z_EDGE_SEL); // QEP输入模式，Z 信号有效沿：0-->上升沿，1-->下降沿
	clr_csr(TIM5_SR, T5IR);		// QEP输入模式: 检测到Z有效沿到来时中断事件标志位
	set_csr(TIM5_IER, T5IRE);	// QEP输入模式: 检测到Z有效沿到来时中断使能 0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer5_ZIndexInt_Disable
 * Description   : TIM5 Z Index中断去使能
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_ZIndexInt_Disable(void)
{
	clr_csr(TIM5_SR, T5IR);		// QEP输入模式: 检测到Z有效沿到来时中断事件标志位
	clr_csr(TIM5_IER, T5IRE);	// QEP输入模式: 检测到Z有效沿到来时中断使能 0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer6_Init
 * Description   : TIM6初始化，用于脉冲方向输入。
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer6_Init(void)
{
	clr_csr(TIM6_CR1, T6EN);

	set_csr(PH_SEL, T6ACT1);  	// PA7(A-DIR)
	set_csr(PH_SEL, T6BCT);		// PA8(B-PULSE)		QEP2I-PD3

	clr_csr(TIM6_CR0, T6PSC2);	// 计数器时钟分频选择
	clr_csr(TIM6_CR0, T6PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	clr_csr(TIM6_CR0, T6PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K

	clr_csr(TIM6_CR0, T6CES);   // 外部中断 INT1（零点）清零脉冲计数器使能 0-->Disable  1-->Enable

	clr_csr(TIM6_IER, T6IRE);	// 比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM6_IER, T6IPE);	// 输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM6_IER, T6IFE);	// 计数器上溢中断使能 0-->Disable  1-->Enable

	clr_csr(TIM6_CR0, T6MOD2);	// 000-->输入捕获模式		001-->输出模式
	set_csr(TIM6_CR0, T6MOD1);	// 010-->输入计数模式		011-->QEP输入或步进模式
	set_csr(TIM6_CR0, T6MOD0);	// 100-->QEP输出模式

	set_csr(TIM6_CR1, T6OCM);   // 0-->QEP&RSD模式;		1-->步进模式

	clr_csr(TIM6_CR1, T6SS);	// 步进模式选择：0-脉冲方向，1-CW/CCW

	clr_csr(TIM6_CR0, T6DIRIN);	// Timer6方向输入极性选择 0-低电平正转，高电平反转；1-低电平反转，高电平正转

	clr_csr(TIM6_CR0, T6INM2);	// QEP输入滤波深度选择
	clr_csr(TIM6_CR0, T6INM1);	// 000-->不滤波  001-->1个clk  010-->2个clk  011-->3个clk
	clr_csr(TIM6_CR0, T6INM0);	// 100-->4个clk  101-->5个clk  110-->6个clk  111-->7个clk

	//	clr_csr(TIM6_CR1, T6DIR_R);	// QEP&ISD&步进模式专用：当前的方向 0-->正向	1-->反向
	write_csr(TIM6_CNTR, 0x00);
	write_csr(TIM6_DR, 0xFFFFFFFF); // 32bit

	set_csr(TIM6_CR1, T6EN);	// TIM6使能	0-->Disable  1-->Enable
}

void Timer6_Reset(void)
{
	write_csr(TIM6_CNTR, 0);
}

/*****************************************************************************
 * Function      : Timer3_Init
 * Description   : TIM3初始化，作为modbus的计时中断
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer3_Init(void)
{
    clr_csr(PH_SEL, T3CT1);    //功能转移，00-->不复用; 01-->PA8
    clr_csr(PH_SEL, T3CT0);    //功能转移，10-->PA0;    11-->PA2

#if (MCU_CLOCK == FREQ_48M)
	set_csr(TIM3_CR0, T3PSC2);	//计数器时钟分频选择
	set_csr(TIM3_CR0, T3PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	set_csr(TIM3_CR0, T3PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K
#elif(MCU_CLOCK == FREQ_24M)
	set_csr(TIM3_CR0, T3PSC2);	//计数器时钟分频选择
	set_csr(TIM3_CR0, T3PSC1);	// 000-->24M	001-->12M	010-->6M	011-->3M
	clr_csr(TIM3_CR0, T3PSC0);	// 100-->1.5M	101-->750K	110-->375K	111-->187.5K
#endif

	clr_csr(TIM3_CR0, T3OCM);   //输出模式：比较模式选择 0： TIMx__CNTR ≤ TIMx__DR，输出 0； TIMx__CNTR > TIMx__DR，输出 1
	set_csr(TIM3_CR0, T3OPM);	//0-->计数器不停止		1-->单次模式
	set_csr(TIM3_CR0, T3MOD);	//0-->Timer模式			1-->输出模式

	set_csr(TIM3_IER, T3IRE);	//比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM3_IER, T3IPE);	//输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM3_IER, T3IFE);	//计数器上溢中断使能 0-->Disable  1-->Enable
	clr_csr(TIM3_SR, T3IR);    //清除中断标志
	clr_csr(TIM3_SR, T3IP);    //清除中断标志
	clr_csr(TIM3_SR, T3IF);    //清除中断标志

	write_csr(IP17, TIM3_INT_PRI);       //中断优先级为2

	clr_csr(TIM3_CR0, T3FE1);	//输入噪声脉宽选择
	clr_csr(TIM3_CR0, T3FE0);	//00-->不滤波	01-->4cycles  10-->8cycles  11-->16cycles

	write_csr(TIM3_CNTR, 0x00);
	write_csr(TIM3_DR, 0x00);
	write_csr(TIM3_ARR, 0xFFFF);

	clr_csr(TIM3_CR1, T3EN);	//TIM3使能	0-->Disable  1-->Enable
}

void Timer3_Enable(void)
{
	write_csr(TIM3_CNTR, 0);
	set_csr(TIM3_CR1, T3EN);	//TIM3使能    0-->Disable  1-->Enable
}


void Timer3_Disable(void)
{
	write_csr(TIM3_CNTR, 0);
	clr_csr(TIM3_CR1, T3EN);    //TIM3使能    0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer4_Init
 * Description   : TIM4初始化，用于位置比较输出0
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer4_Init(void)
{
	clr_csr(TIM4_CR1, T4EN);	//TIM4使能	0-->Disable  1-->Enable

	set_csr(PH_SEL, T4CT1);		//功能转移, 00-->不复用, 01-->PA0
	set_csr(PH_SEL, T4CT0);		//功能转移，10-->PA2,    11-->PD3

	set_csr(TIM4_CR0, T4PSC2);	//计数器时钟分频选择
	set_csr(TIM4_CR0, T4PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	clr_csr(TIM4_CR0, T4PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	set_csr(TIM4_CR0, T4OCM);   //输出模式：比较模式选择 0： TIMx__CNTR ≤ TIMx__DR，输出 0； TIMx__CNTR > TIMx__DR，输出 1
	set_csr(TIM4_CR0, T4OPM);	//0-->计数器不停止		1-->单次模式
	set_csr(TIM4_CR0, T4MOD);	//0-->Timer模式			1-->输出模式

	clr_csr(TIM4_IER, T4IRE);	//比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IPE);	//输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IFE);	//计数器上溢中断使能 0-->Disable  1-->Enable

	clr_csr(TIM4_CR0, T4FE1);	//输入噪声脉宽选择
	clr_csr(TIM4_CR0, T4FE0);	//00-->不滤波	01-->4cycles  10-->8cycles  11-->16cycles

	write_csr(TIM4_CNTR, 0);
	write_csr(TIM4_DR, 0);
	write_csr(TIM4_ARR, 0xFFFF);

	// 先不使能，由比较输出触发使能
//	set_csr(TIM4_CR1, T4EN);	//TIM4使能	0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer4_Init
 * Description   : TIM4初始化，用于位置比较输出0
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer4_PWM_Init(void)
{
	clr_csr(TIM4_CR1, T4EN);	//TIM4使能	0-->Disable  1-->Enable

	set_csr(PH_SEL, T4CT1);		//功能转移, 00-->不复用, 01-->PA0
	clr_csr(PH_SEL, T4CT0);		//功能转移，10-->PA2,    11-->PD3

	clr_csr(TIM4_CR0, T4PSC2);	//计数器时钟分频选择
	set_csr(TIM4_CR0, T4PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	set_csr(TIM4_CR0, T4PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	clr_csr(TIM4_CR0, T4OCM);   //输入捕获模式：有效沿选择
	clr_csr(TIM4_CR0, T4OPM);	//0-->计数器不停止		1-->单次模式
	clr_csr(TIM4_CR0, T4MOD);	//0-->输入捕获模式			1-->输出模式

	clr_csr(TIM4_IER, T4IRE);	//比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IPE);	//输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IFE);	//计数器上溢中断使能 0-->Disable  1-->Enable

	clr_csr(TIM4_CR0, T4FE1);	//输入噪声脉宽选择
	clr_csr(TIM4_CR0, T4FE0);	//00-->不滤波	01-->4cycles  10-->8cycles  11-->16cycles

	write_csr(TIM4_CNTR, 0);
	write_csr(TIM4_DR, 0);
	write_csr(TIM4_ARR, 0);

	// 先不使能，由软件触发使能
	//	set_csr(TIM4_CR1, T4EN);	//TIM4使能	0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer7_Init
 * Description   : TIM7初始化，用于位置比较输出1
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer7_Init(void)
{
	clr_csr(TIM7_CR1, T7EN);	//TIM7使能	0-->Disable  1-->Enable

	set_csr(PH_SEL, T7CT1);		//功能转移, 00-->不复用, 01-->PA1
	set_csr(PH_SEL, T7CT0);		//功能转移，10-->PA3,    11-->PD1

	set_csr(TIM7_CR0, T7PSC2);	//计数器时钟分频选择
	set_csr(TIM7_CR0, T7PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	clr_csr(TIM7_CR0, T7PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	set_csr(TIM7_CR0, T7OCM);   //输出模式：比较模式选择 0： TIMx__CNTR ≤ TIMx__DR，输出 0； TIMx__CNTR > TIMx__DR，输出 1
	set_csr(TIM7_CR0, T7OPM);	//0-->计数器不停止		1-->单次模式
	set_csr(TIM7_CR0, T7MOD);	//0-->Timer模式			1-->输出模式

	clr_csr(TIM7_IER, T7IRE);	//比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM7_IER, T7IPE);	//输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM7_IER, T7IFE);	//计数器上溢中断使能 0-->Disable  1-->Enable

	clr_csr(TIM7_CR0, T7FE1);	//输入噪声脉宽选择
	clr_csr(TIM7_CR0, T7FE0);	//00-->不滤波	01-->4cycles  10-->8cycles  11-->16cycles


	write_csr(TIM7_CNTR, 0);
	write_csr(TIM7_DR, 0);
	write_csr(TIM7_ARR, 0xFFFF);

	// 先不使能，由比较输出触发使能
//	set_csr(TIM7_CR1, T7EN);	//TIM7使能	0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer8_Init
 * Description   : TIM8初始化，用于输出制动斩波
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer8_Init(void)
{
	clr_csr(TIM8_CR1, T8EN);	//TIM8使能	0-->Disable  1-->Enable

	clr_csr(PH_SEL, T8CT1);		//功能转移, 00-->不复用
	set_csr(PH_SEL, T8CT0);		//功能转移，01-->PA9， 10-->PB2

	clr_csr(TIM8_CR0, T8PSC2);	//计数器时钟分频选择
	clr_csr(TIM8_CR0, T8PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	clr_csr(TIM8_CR0, T8PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	set_csr(TIM8_CR0, T8OCM);   //输出模式：比较模式选择 0： TIMx__CNTR ≤ TIMx__DR，输出 0； TIMx__CNTR > TIMx__DR，输出 1
	clr_csr(TIM8_CR0, T8OPM);	//0-->计数器不停止		1-->单次模式
	set_csr(TIM8_CR0, T8MOD);	//0-->Timer模式			1-->输出模式

	clr_csr(TIM8_IER, T8IRE);	//比较匹配中断/脉宽检测中断0-->Disable  1-->Enable
	clr_csr(TIM8_IER, T8IPE);	//输入Timer PWM周期检测中断使能 0-->Disable  1-->Enable
	clr_csr(TIM8_IER, T8IFE);	//计数器上溢中断使能 0-->Disable  1-->Enable

	clr_csr(TIM8_CR0, T8FE1);	//输入噪声脉宽选择
	clr_csr(TIM8_CR0, T8FE0);	//00-->不滤波	01-->4cycles  10-->8cycles  11-->16cycles


	write_csr(TIM8_CNTR, 0);
	write_csr(TIM8_DR, 0);
	write_csr(TIM8_ARR, MAXREGENDUTY);

	set_csr(TIM8_CR1, T8EN);	//TIM8使能	0-->Disable  1-->Enable
}

void Timer_1ms_Init(void)
{
	/***********SYSTICK定时器配置*******************/
	write_csr(SYST_ARR, 47999);// 1kHz

	write_csr(IP15, 0x3);			// DRV1中断(中断号15) 优先级别为3
	set_csr(SYST_SR, SYSTEN);        //1ms定时中断使能

}

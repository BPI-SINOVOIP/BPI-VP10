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
 * Description   : TIM2 initialization, for encoder A quad B detection.
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Init(void)
{
	clr_csr(TIM2_CR1, T2EN);	// Clear Timer2 enable

	clr_csr(PH_SEL, T2ACT);  	//Function remap: 0-->no remap; 1-->PA10
	clr_csr(PH_SEL, T2BCT);		//Function remap: 0-->no remap; 1-->PA11

	set_csr(TIM2_CR0, T2PSC2);	// Counter clock prescaler select
	set_csr(TIM2_CR0, T2PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	set_csr(TIM2_CR0, T2PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K

	clr_csr(TIM2_CR1, T2OCM);   // 0-->QEP&RSD mode;		1-->Stepping mode
	clr_csr(TIM2_CR0, T2CES);   // QEP mode: external interrupt INT1 (zero) clear pulse counter enable: 0-->Disable, 1-->Enable

	clr_csr(TIM2_CR0, T2MOD2);	// 000-->Input capture mode		001-->Output mode
	set_csr(TIM2_CR0, T2MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM2_CR0, T2MOD0);	// 100-->QEPOutput mode

	clr_csr(TIM2_IER, T2IRE);	// Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM2_IER, T2IPE);	// Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM2_IER, T2IFE);	// Counter overflow interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM2_SR, T2IR);    // Clear interrupt flag
	clr_csr(TIM2_SR, T2IP);    // Clear interrupt flag
	clr_csr(TIM2_SR, T2IF);    // Clear interrupt flag

	clr_csr(TIM2_CR0, T2INM2);	// QEP input filter depth select
	clr_csr(TIM2_CR0, T2INM1);	// 000-->No filter  001-->1 cycles  010-->2 cycles  011-->3 cycles
	clr_csr(TIM2_CR0, T2INM0);	// 100-->4 cycles  101-->5 cycles  110-->6 cycles  111-->7 cycles

	clr_csr(TIM2_CR1, T2_DIR_R);	// QEP&ISD&Stepping modespecific: current direction 0-->forward	1-->reverse

	clr_csr(TIM2_CR1, T2QEP_IN_CNTR_CLR); // QEP input mode: when Z signal valid edge detected, clear TIMx_CNTR: 0-->no clear, 1-->clear
	clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP input mode, Z signal valid edge: 0-->rising edge, 1-->falling edge

	write_csr(TIM2_DR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_CNTR, 0);

//	set_csr(TIM2_CR1, T2EN);	//TIM2 enable	0-->Disable  1-->Enable
	
}

/*****************************************************************************
 * Function      : Timer2_Enable
 * Description   : TIM2 enable, for encoder A quad B detection.
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Enable(void)
{
	clr_csr(TIM2_CR1, T2EN);	// TIM2 enable    0-->Disable  1-->Enable
	
	set_csr(PH_SEL, T2ACT);  	//Function remap: 0-->no remap; 1-->PA10
	set_csr(PH_SEL, T2BCT);		//Function remap: 0-->no remap; 1-->PA11
	
	clr_csr(TIM2_CR0, T2MOD2);	// 000-->Input capture mode		001-->Output mode
	set_csr(TIM2_CR0, T2MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM2_CR0, T2MOD0);	// 100-->QEPOutput mode
	
	write_csr(TIM2_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_CNTR, 0);
	
	set_csr(TIM2_CR1, T2EN);	// TIM2 enable    0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer2_Disable
 * Description   : TIM2 disable
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_Disable(void)
{
	clr_csr(TIM2_CR1, T2EN);	// TIM2 enable    0-->Disable  1-->Enable
	
	clr_csr(PH_SEL, T2ACT);  	//Function remap: 0-->no remap; 1-->PA10
	clr_csr(PH_SEL, T2BCT);		//Function remap: 0-->no remap; 1-->PA11
	
	clr_csr(TIM2_CR0, T2MOD2);	// 000-->Input capture mode		001-->Output mode
	clr_csr(TIM2_CR0, T2MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM2_CR0, T2MOD0);	// 100-->QEPOutput mode
	
	write_csr(TIM2_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM2_CNTR, 0);
	
#if FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	set_csr(TIM2_CR1, T2EN);	// TIM2 enable    0-->Disable  1-->Enable
#endif
}


/*****************************************************************************
 * Function      : Timer2_Filter_Update
 * Description   : TIM2 update filter coefficient, QEP input filter depth select
 * Input         : AqbFilt: T2INM2 | T2INM1 | T2INM0
 *							000-->No filter  001-->2 cycles  010-->3 cycles  011-->4 cycles
 *							100-->5 cycles  101-->6 cycles  110-->7 cycles  111-->8 cycles
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
 * Function      : Timer2_ZIndexCap_Enable
 * Description   : TIM2 Z Index capture enable
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer2_ZIndexCap_Enable(void)
{
	clr_csr(TIM2_CR1, T2Z_EDGE_SEL); // QEP input mode, Z signal valid edge: 0-->rising edge, 1-->falling edge
	clr_csr(TIM2_SR, T2IR);		// QEP input mode: interrupt event flag when Z valid edge arrives
}


/*****************************************************************************
 * Function      : Timer5_Init
 * Description   : TIM5 initialization, for encoder ABZ1 detection.
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Init(void)
{
	clr_csr(TIM5_CR1, T5EN);	// Clear Timer5 enable

	clr_csr(PH_SEL, T5ACT);  	//Function remap: 0-->no remap; 1-->PA13
	clr_csr(PH_SEL, T5BCT);		//Function remap: 0-->no remap; 1-->PA14

	set_csr(TIM5_CR0, T5PSC2);	// Counter clock prescaler select
	set_csr(TIM5_CR0, T5PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	set_csr(TIM5_CR0, T5PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K

	clr_csr(TIM5_CR1, T5OCM);   // 0-->QEP&RSD mode;		1-->Stepping mode
	clr_csr(TIM5_CR0, T5CES);   // QEP mode: external interrupt INT1 (zero) clear pulse counter enable: 0-->Disable, 1-->Enable

	clr_csr(TIM5_CR0, T5MOD2);	// 000-->Input capture mode		001-->Output mode
	set_csr(TIM5_CR0, T5MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM5_CR0, T5MOD0);	// 100-->QEPOutput mode

	clr_csr(TIM5_IER, T5IRE);	// Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM5_IER, T5IPE);	// Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM5_IER, T5IFE);	// Counter overflow interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM5_SR, T5IR);    // Clear interrupt flag
	clr_csr(TIM5_SR, T5IP);    // Clear interrupt flag
	clr_csr(TIM5_SR, T5IF);    // Clear interrupt flag

	clr_csr(TIM5_CR0, T5INM2);	// QEP input filter depth select
	clr_csr(TIM5_CR0, T5INM1);	// 000-->No filter  001-->1 cycles  010-->2 cycles  011-->3 cycles
	clr_csr(TIM5_CR0, T5INM0);	// 100-->4 cycles  101-->5 cycles  110-->6 cycles  111-->7 cycles

	clr_csr(TIM5_CR1, T5_DIR_R);	// QEP&ISD&Stepping modespecific: current direction 0-->forward	1-->reverse

	clr_csr(TIM5_CR1, T5QEP_IN_CNTR_CLR); // QEP input mode: when Z signal valid edge detected, clear TIMx_CNTR: 0-->no clear, 1-->clear
	clr_csr(TIM5_CR1, T5Z_EDGE_SEL); // QEP input mode, Z signal valid edge: 0-->rising edge, 1-->falling edge

	write_csr(TIM5_DR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_CNTR, 0);

	//	set_csr(TIM5_CR1, T5EN);	//TIM5 enable	0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer5_Enable
 * Description   : TIM5 enable, for encoder A quad B detection.
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Enable(void)
{
	clr_csr(TIM5_CR1, T5EN);	// TIM5 enable    0-->Disable  1-->Enable

	set_csr(PH_SEL, T5ACT);  	//Function remap: 0-->no remap; 1-->PA13
	set_csr(PH_SEL, T5BCT);		//Function remap: 0-->no remap; 1-->PA14

	clr_csr(TIM5_CR0, T5MOD2);	// 000-->Input capture mode		001-->Output mode
	set_csr(TIM5_CR0, T5MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM5_CR0, T5MOD0);	// 100-->QEPOutput mode

	write_csr(TIM5_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_CNTR, 0);

	set_csr(TIM5_CR1, T5EN);	// TIM5 enable    0-->Disable  1-->Enable
}


/*****************************************************************************
 * Function      : Timer5_Disable
 * Description   : TIM5 disable
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_Disable(void)
{
	clr_csr(TIM5_CR1, T5EN);	// TIM5 enable    0-->Disable  1-->Enable

	clr_csr(PH_SEL, T5ACT);  	//Function remap: 0-->no remap; 1-->PA10
	clr_csr(PH_SEL, T5BCT);		//Function remap: 0-->no remap; 1-->PA11

	clr_csr(TIM5_CR0, T5MOD2);	// 000-->Input capture mode		001-->Output mode
	clr_csr(TIM5_CR0, T5MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM5_CR0, T5MOD0);	// 100-->QEPOutput mode

	write_csr(TIM5_ARR, 0xFFFFFFFF); // 32bit
	write_csr(TIM5_CNTR, 0);

	//#if FUNC_PROBE_ENABLED > 0 || FUNC_PCOM_ENABLED > 0
	//	set_csr(TIM5_CR1, T5EN);	// TIM5 enable    0-->Disable  1-->Enable
	//#endif
}

/*****************************************************************************
 * Function      : Timer5_Filter_Update
 * Description   : TIM5 update filter coefficient, QEP input filter depth select
 * Input         : AqbFilt: T5INM2 | T5INM1 | T5INM0
 *							000-->No filter  001-->2 cycles  010-->3 cycles  011-->4 cycles
 *							100-->5 cycles  101-->6 cycles  110-->7 cycles  111-->8 cycles
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
 * Function      : Timer5_ZIndexCap_Enable
 * Description   : TIM5 Z Index capture enable
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer5_ZIndexCap_Enable(void)
{
	clr_csr(TIM5_CR1, T5Z_EDGE_SEL); // QEP input mode, Z signal valid edge: 0-->rising edge, 1-->falling edge
	clr_csr(TIM5_SR, T5IR);		// QEP input mode: interrupt event flag when Z valid edge arrives
}


/*****************************************************************************
 * Function      : Timer6_Init
 * Description   : TIM6 initialization, for pulse direction input.
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer6_Init(void)
{
	clr_csr(TIM6_CR1, T6EN);

	set_csr(PH_SEL, T6ACT1);  	// PA7(A-DIR)
	set_csr(PH_SEL, T6BCT);		// PA8(B-PULSE)		QEP2I-PD3

	clr_csr(TIM6_CR0, T6PSC2);	// Counter clock prescaler select
	clr_csr(TIM6_CR0, T6PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	clr_csr(TIM6_CR0, T6PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K

	clr_csr(TIM6_CR0, T6CES);   // external interrupt INT1 (zero point)clear pulse counter enable 0-->Disable  1-->Enable

	clr_csr(TIM6_IER, T6IRE);	// Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM6_IER, T6IPE);	// Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM6_IER, T6IFE);	// Counter overflow interrupt enable 0-->Disable  1-->Enable

	clr_csr(TIM6_CR0, T6MOD2);	// 000-->Input capture mode		001-->Output mode
	set_csr(TIM6_CR0, T6MOD1);	// 010-->Input count mode		011-->QEPinput orStepping mode
	set_csr(TIM6_CR0, T6MOD0);	// 100-->QEPOutput mode

	set_csr(TIM6_CR1, T6OCM);   // 0-->QEP&RSD mode;		1-->Stepping mode

	clr_csr(TIM6_CR1, T6SS);	// Stepping mode select: 0-pulse direction, 1-CW/CCW

	clr_csr(TIM6_CR0, T6DIRIN);	// Timer6 direction input polarity: 0-Low=forward,High=reverse; 1-Low=reverse,High=forward

	clr_csr(TIM6_CR0, T6INM2);	// QEP input filter depth select
	clr_csr(TIM6_CR0, T6INM1);	// 000-->No filter  001-->1 cycles  010-->2 cycles  011-->3 cycles
	clr_csr(TIM6_CR0, T6INM0);	// 100-->4 cycles  101-->5 cycles  110-->6 cycles  111-->7 cycles

	//	clr_csr(TIM6_CR1, T6DIR_R);	// QEP&ISD&Stepping modespecific: current direction 0-->forward	1-->reverse
	write_csr(TIM6_CNTR, 0x00);
	write_csr(TIM6_DR, 0xFFFFFFFF); // 32bit

	set_csr(TIM6_CR1, T6EN);	// TIM6 enable	0-->Disable  1-->Enable
}

void Timer6_Reset(void)
{
	write_csr(TIM6_CNTR, 0);
}

/*****************************************************************************
 * Function      : Timer3_Init
 * Description   : TIM3 initialization, as Modbus timer interrupt
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer3_Init(void)
{
    clr_csr(PH_SEL, T3CT1);    //Function remap: 00-->no remap; 01-->PA8
    clr_csr(PH_SEL, T3CT0);    //Function remap: 10-->PA0; 11-->PA2

#if (MCU_CLOCK == FREQ_48M)
	set_csr(TIM3_CR0, T3PSC2);	//Counter clock prescaler select
	set_csr(TIM3_CR0, T3PSC1);	// 000-->48M	001-->24M	010-->12M	011-->6M
	set_csr(TIM3_CR0, T3PSC0);	// 100-->3M		101-->1.5M	110-->750K	111-->375K
#elif(MCU_CLOCK == FREQ_24M)
	set_csr(TIM3_CR0, T3PSC2);	//Counter clock prescaler select
	set_csr(TIM3_CR0, T3PSC1);	// 000-->24M	001-->12M	010-->6M	011-->3M
	clr_csr(TIM3_CR0, T3PSC0);	// 100-->1.5M	101-->750K	110-->375K	111-->187.5K
#endif

	clr_csr(TIM3_CR0, T3OCM);   //Output mode: compare mode select 0: TIMx__CNTR <= TIMx__DR, output 0; TIMx__CNTR > TIMx__DR, output 1
	set_csr(TIM3_CR0, T3OPM);	//0-->counter not stopped		1-->One-shot mode
	set_csr(TIM3_CR0, T3MOD);	//0-->Timer mode			1-->Output mode

	set_csr(TIM3_IER, T3IRE);	//Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM3_IER, T3IPE);	//Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM3_IER, T3IFE);	//Counter overflow interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM3_SR, T3IR);    //Clear interrupt flag
	clr_csr(TIM3_SR, T3IP);    //Clear interrupt flag
	clr_csr(TIM3_SR, T3IF);    //Clear interrupt flag

	write_csr(IP17, TIM3_INT_PRI);       //Interrupt priority: 2

	clr_csr(TIM3_CR0, T3FE1);	//Input noise pulse width select
	clr_csr(TIM3_CR0, T3FE0);	//00-->No filter	01-->4cycles  10-->8cycles  11-->16cycles

	write_csr(TIM3_CNTR, 0x00);
	write_csr(TIM3_DR, 0x00);
	write_csr(TIM3_ARR, 0xFFFF);

	clr_csr(TIM3_CR1, T3EN);	//TIM3 enable	0-->Disable  1-->Enable
}

void Timer3_Enable(void)
{
	write_csr(TIM3_CNTR, 0);
	set_csr(TIM3_CR1, T3EN);	//TIM3 enable    0-->Disable  1-->Enable
}


void Timer3_Disable(void)
{
	write_csr(TIM3_CNTR, 0);
	clr_csr(TIM3_CR1, T3EN);    //TIM3 enable    0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer4_Init
 * Description   : TIM4 initialization, for position compare output 0
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer4_Init(void)
{
	clr_csr(TIM4_CR1, T4EN);	//TIM4 enable	0-->Disable  1-->Enable

	set_csr(PH_SEL, T4CT1);		//Function remap: 00-->no remap, 01-->PA0
	set_csr(PH_SEL, T4CT0);		//Function remap: 10-->PA2, 11-->PD3

	set_csr(TIM4_CR0, T4PSC2);	//Counter clock prescaler select
	set_csr(TIM4_CR0, T4PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	clr_csr(TIM4_CR0, T4PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	set_csr(TIM4_CR0, T4OCM);   //Output mode: compare mode select 0: TIMx__CNTR <= TIMx__DR, output 0; TIMx__CNTR > TIMx__DR, output 1
	set_csr(TIM4_CR0, T4OPM);	//0-->counter not stopped		1-->One-shot mode
	set_csr(TIM4_CR0, T4MOD);	//0-->Timer mode			1-->Output mode

	clr_csr(TIM4_IER, T4IRE);	//Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IPE);	//Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IFE);	//Counter overflow interrupt enable 0-->Disable  1-->Enable

	clr_csr(TIM4_CR0, T4FE1);	//Input noise pulse width select
	clr_csr(TIM4_CR0, T4FE0);	//00-->No filter	01-->4cycles  10-->8cycles  11-->16cycles

	write_csr(TIM4_CNTR, 0);
	write_csr(TIM4_DR, 0);
	write_csr(TIM4_ARR, 0xFFFF);

	// Not enabled initially, triggered by compare output
//	set_csr(TIM4_CR1, T4EN);	//TIM4 enable	0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer4_Init
 * Description   : TIM4 initialization, for position compare output 0
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer4_PWM_Init(void)
{
	clr_csr(TIM4_CR1, T4EN);	//TIM4 enable	0-->Disable  1-->Enable

	set_csr(PH_SEL, T4CT1);		//Function remap: 00-->no remap, 01-->PA0
	clr_csr(PH_SEL, T4CT0);		//Function remap: 10-->PA2, 11-->PD3

	clr_csr(TIM4_CR0, T4PSC2);	//Counter clock prescaler select
	set_csr(TIM4_CR0, T4PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	set_csr(TIM4_CR0, T4PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	clr_csr(TIM4_CR0, T4OCM);   //Input capture mode: valid edge select
	clr_csr(TIM4_CR0, T4OPM);	//0-->counter not stopped		1-->One-shot mode
	clr_csr(TIM4_CR0, T4MOD);	//0-->Input capture mode			1-->Output mode

	clr_csr(TIM4_IER, T4IRE);	//Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IPE);	//Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM4_IER, T4IFE);	//Counter overflow interrupt enable 0-->Disable  1-->Enable

	clr_csr(TIM4_CR0, T4FE1);	//Input noise pulse width select
	clr_csr(TIM4_CR0, T4FE0);	//00-->No filter	01-->4cycles  10-->8cycles  11-->16cycles

	write_csr(TIM4_CNTR, 0);
	write_csr(TIM4_DR, 0);
	write_csr(TIM4_ARR, 0);

	// Not enabled initially, triggered by software
	//	set_csr(TIM4_CR1, T4EN);	//TIM4 enable	0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer7_Init
 * Description   : TIM7 initialization, for position compare output 1
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer7_Init(void)
{
	clr_csr(TIM7_CR1, T7EN);	//TIM7 enable	0-->Disable  1-->Enable

	set_csr(PH_SEL, T7CT1);		//Function remap, 00-->noremap, 01-->PA1
	set_csr(PH_SEL, T7CT0);		//Function remap: 10-->PA3, 11-->PD1

	set_csr(TIM7_CR0, T7PSC2);	//Counter clock prescaler select
	set_csr(TIM7_CR0, T7PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	clr_csr(TIM7_CR0, T7PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	set_csr(TIM7_CR0, T7OCM);   //Output mode: compare mode select 0: TIMx__CNTR <= TIMx__DR, output 0; TIMx__CNTR > TIMx__DR, output 1
	set_csr(TIM7_CR0, T7OPM);	//0-->counter not stopped		1-->One-shot mode
	set_csr(TIM7_CR0, T7MOD);	//0-->Timer mode			1-->Output mode

	clr_csr(TIM7_IER, T7IRE);	//Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM7_IER, T7IPE);	//Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM7_IER, T7IFE);	//Counter overflow interrupt enable 0-->Disable  1-->Enable

	clr_csr(TIM7_CR0, T7FE1);	//Input noise pulse width select
	clr_csr(TIM7_CR0, T7FE0);	//00-->No filter	01-->4cycles  10-->8cycles  11-->16cycles


	write_csr(TIM7_CNTR, 0);
	write_csr(TIM7_DR, 0);
	write_csr(TIM7_ARR, 0xFFFF);

	// Not enabled initially, triggered by compare output
//	set_csr(TIM7_CR1, T7EN);	//TIM7 enable	0-->Disable  1-->Enable
}

/*****************************************************************************
 * Function      : Timer8_Init
 * Description   : TIM8 initialization, for braking chopper output
 * Input         : void
 * Output        : None
 * Return        : void
 *****************************************************************************/
void Timer8_Init(void)
{
	clr_csr(TIM8_CR1, T8EN);	//TIM8 enable	0-->Disable  1-->Enable

	clr_csr(PH_SEL, T8CT1);		//Function remap, 00-->noremap
	set_csr(PH_SEL, T8CT0);		//Function remap: 01-->PA9, 10-->PB2

	clr_csr(TIM8_CR0, T8PSC2);	//Counter clock prescaler select
	clr_csr(TIM8_CR0, T8PSC1);	//000-->24M		001-->12M		010-->6M	011-->3M
	clr_csr(TIM8_CR0, T8PSC0);	//100-->1.5M	101-->750K		110-->375K	111-->187.5K

	set_csr(TIM8_CR0, T8OCM);   //Output mode: compare mode select 0: TIMx__CNTR <= TIMx__DR, output 0; TIMx__CNTR > TIMx__DR, output 1
	clr_csr(TIM8_CR0, T8OPM);	//0-->counter not stopped		1-->One-shot mode
	set_csr(TIM8_CR0, T8MOD);	//0-->Timer mode			1-->Output mode

	clr_csr(TIM8_IER, T8IRE);	//Compare match / pulse width detect interrupt0-->Disable  1-->Enable
	clr_csr(TIM8_IER, T8IPE);	//Input timer PWM period detect interrupt enable 0-->Disable  1-->Enable
	clr_csr(TIM8_IER, T8IFE);	//Counter overflow interrupt enable 0-->Disable  1-->Enable

	clr_csr(TIM8_CR0, T8FE1);	//Input noise pulse width select
	clr_csr(TIM8_CR0, T8FE0);	//00-->No filter	01-->4cycles  10-->8cycles  11-->16cycles


	write_csr(TIM8_CNTR, 0);
	write_csr(TIM8_DR, 0);
	write_csr(TIM8_ARR, MAXREGENDUTY);

	set_csr(TIM8_CR1, T8EN);	//TIM8 enable	0-->Disable  1-->Enable
}

void Timer_1ms_Init(void)
{
	/***********SYSTICK timer configuration*******************/
	write_csr(SYST_ARR, 47999);// 1kHz

	write_csr(IP15, 0x3);			// DRV1interrupt(IRQ15) priority: 3
	set_csr(SYST_SR, SYSTEN);        //1ms timer interrupt enable

}

/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Timer.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define Timer
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __TIMER_H__
#define __TIMER_H__


/*************************************************************************************///External Function
extern void Timer2_Init(void);
extern void Timer5_Init(void);
extern void Timer6_Init(void);

extern void Timer3_Init(void);
extern void Timer4_Init(void);
extern void Timer4_PWM_Init(void);
extern void Timer7_Init(void);
extern void Timer8_Init(void);
extern void Timer_1ms_Init(void);

extern void Timer2_Enable(void);
extern void Timer2_Disable(void);
extern void Timer2_Filter_Update(unsigned short AqbFilt);
extern void Timer2_ZIndexInt_Enable(void);
extern void Timer2_ZIndexInt_Disable(void);

extern void Timer5_Enable(void);
extern void Timer5_Disable(void);
extern void Timer5_Filter_Update(unsigned short AqbFilt);
extern void Timer5_ZIndexInt_Enable(void);
extern void Timer5_ZIndexInt_Disable(void);

extern void Timer3_Enable(void);
extern void Timer3_Disable(void);

extern void Timer6_Reset(void);

extern void QEP_OutModeInit(void);

#endif

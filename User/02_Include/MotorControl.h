/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorControl.h
 * Author        : Summer
 * Date          : 2023-05-11
 * Description   : 载波中断和位置环中断函数
 *
 * Record        :
 * V1.0, 2023-05-11, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTORCONTROL_H__
#define __MOTORCONTROL_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "fu7502.h"
#include "Math.h"



/*************************************************************************************///External Function
extern void ServoControl_Isr(void);
extern void PosControl_Isr(void);


#ifdef __cplusplus
}
#endif

#endif
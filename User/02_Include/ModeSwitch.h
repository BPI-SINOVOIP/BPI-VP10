/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ModeSwitch.h
 * Author        : Victor.jin
 * Date          : 2024-01-18
 * Description   : 模式切换
 *
 * Record        :
 * V1.0, 2024-01-18, Victor.jin: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MODESWITCH_H__
#define __MODESWITCH_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"


/*************************************************************************************///External Function
typedef struct
{
	uint8 FirOnPower;             // 第一次上电标志位
	uint8 SwitchFlag;             // 模式切换标志位
	uint16 RunMod;                 // 运行模式
	uint16 RunModLatch;            // 运行模式锁存
} ModeSWPTypedef;



extern ModeSWPTypedef ModeSW;


extern void ModeSW_Init(void);
extern void ModeSW_Update(void);
extern void RunMode_Update(void);


#ifdef __cplusplus
}
#endif


#endif

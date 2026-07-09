/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ModeSwitch.h
 * Author        : Victor.jin
 * Date          : 2024-01-18
 * Description   : Mode switching
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
	uint8 FirOnPower;             // First power-on flag
	uint8 SwitchFlag;             // Mode switch flag
	uint16 RunMod;                 // Run mode
	uint16 RunModLatch;            // Run mode latch
} ModeSWPTypedef;



extern ModeSWPTypedef ModeSW;


extern void ModeSW_Init(void);
extern void ModeSW_Update(void);
extern void RunMode_Update(void);


#ifdef __cplusplus
}
#endif


#endif
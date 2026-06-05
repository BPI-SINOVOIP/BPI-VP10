/*
 * Copyright (c) 2017-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FocControl.h
 * Author        : Fortior Application Team
 * Date          : 2017-04-11
 * Description   : define motor contorl parameter
 *
 * Record        :
 * V1.0, 2017-04-11, Fortior Application Team: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FOCCONTROL_H_
#define __FOCCONTROL_H_


/* Exported types ------------------------------------------------------------*/

// 中断优先级
#define FO_INT_PRI			( 7 ) // 硬件过流保护中断
#define FO_CMP3_INT_PRI		( 7 ) // 硬件过流保护中断
#define EXTERN1_INT_PRI		( 6 ) // 外部中断
#define DRVPIF_INT_PRI		( 4 ) // 保护中断
#define FOC_INT_PRI			( 5 ) // 载波中断
#define DMA0_INT_PRI		( 3 ) // 串口DMA中断
#define TIM2_INT_PRI		( 2 ) // Z信号中断
#define TIM3_INT_PRI		( 4 ) // 位置环中断
#define MEFSM_INT_PRI		( 6 ) // ME中断
#define CAN_INT_PRI			( 2 ) // CAN接收中断


typedef enum
{
	mcReady = 0,
	mcIdle = 1,
	mcDisable = 2,
	mcPhaseFind = 3,
	mcHome = 4,
	mcStart = 5,
	mcRun = 6,
	mcStop = 7,
	mcFault = 8,
	mcUpFlash = 9,
	mcDownFlash = 10,
	mcMotorIdentify = 11,
} MotStaType;

typedef union
{
	uint8 SetMode;                                     // 整个配置模式使能位
	struct
	{
		uint8 ChargeSetFlag : 1;                 // 预定位配置标志位
		uint8 PhaseFindSetFlag : 1;                 //
		//    	uint8 HomeSetFlag : 1;                 //
		uint8 AutoPhaseFindSetFlag : 1;
		uint8 AutoHomeSetFlag : 1;                 //
		uint8 AutoEnableSetFlag : 1;                 //
		uint8 StopSetFlag : 1;                 //
		uint8 BrakeFlag : 1;                 // 启动停车标志位
		uint8 IdentifySetFlag : 1;
	} SetFlag;
} MotStaM;



/* Exported variables --------------------------------------------------------------------*/
extern uint8 mcState;
extern MotStaM McStaSet;


/* Exported functions --------------------------------------------------------------------*/
extern void MC_Control(void);


#endif

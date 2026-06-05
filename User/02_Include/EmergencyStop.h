/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : EmergencyStop.h
 * Author        : Zougi.Zou
 * Date          : 2025-4-24
 * Description   : Emergency Stop Function
 *
 * Record        :
 * V1.0, 2025-4-24, Zougi.Zou: Created file
 */

#ifndef __EMERGENCYSTOP_H__
#define __EMERGENCYSTOP_H__

/* Define to prevent recursive inclusion -------------------------------------*/

// Definition of register DISMODE
#define DYNBRK_OFF                                    (0x0000)          // rw-- 动态制动模式-无动态制动
#define DYNBRK_FAULT								  (0x0001)          // rw-- 动态制动模式-只有报错时动态制动
#define DYNBRK_ALWAYS								  (0x0002)          // rw-- 动态制动模式-任何时候都动态制动

#define DISSTOP_COAST                                 (0x0000)          // rw-- 停车方式-自由停车
#define DISSTOP_RAMP                                  (0x0004)          // rw-- 停车方式-斜坡停车
#define DISSTOP_ZERO                                  (0x0008)          // rw-- 停车方式-零速停车

#define DYNBRKMODE                                    (0x0003)          // rw-- 动态制动模式
#define DISSTOPMODE                                   (0x000C)          // rw-- 停车方式


// Emergencystop state machine
#define EMER_IDLE						(0)             //
#define EMER_DEC						(1)             //
#define EMER_STOP						(2)             //
#define EMER_DISABLE					(3)             //
#define EMER_FINISH						(4)             //


#define DISDECSCALE						(6)             // 减速度放大
		
typedef struct
{
	uint8 State;				// 状态机
	uint8 StateLatch;			// 状态机锁存
	uint8 StartStopFlag;        // 开始减速标志
	uint8 DecStopFlag;			// 速度命令切换标志
	uint8 StartBrakeFlag;       // 开始动态制动标志
	uint16 TimeCounter;			// 停机计数
	uint16 TimeOutCounter;		// 停机超时计数
	int16 DisSpeed;				// 停机速度阈值
	int16 BrakeArrMax;
	int32 BrakeArr;
	int32 VelValue;
	int32 VelInc;
} EmergencyStopTypeDef;


extern EmergencyStopTypeDef mcEmergencyStop;

extern void Motor_DynamicBrake_Init(void);
extern void Motor_DynamicBrake_realize(void);
extern void Do_EmergencyStop(void);
extern void RampStop_Init(void);
extern int16 RampStop_realize(void);
extern void Do_DisableServo(void);
extern void EmergencyStop_TimeCount(void);

#endif  //__EMERGENCYSTOP_H__

/*** (C) Copyright 2011-2022 Fortior Technology Co., Ltd. ***/

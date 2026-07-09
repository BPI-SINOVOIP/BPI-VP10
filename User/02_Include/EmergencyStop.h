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
#define DYNBRK_OFF                                    (0x0000)          // rw-- Dynamic brake mode - no dynamic braking
#define DYNBRK_FAULT								  (0x0001)          // rw-- Dynamic brake mode - dynamic braking only on fault
#define DYNBRK_ALWAYS								  (0x0002)          // rw-- Dynamic brake mode - dynamic braking at all times

#define DISSTOP_COAST                                 (0x0000)          // rw-- Stop method - coast
#define DISSTOP_RAMP                                  (0x0004)          // rw-- Stop method - ramp stop
#define DISSTOP_ZERO                                  (0x0008)          // rw-- Stop method - zero-speed stop

#define DYNBRKMODE                                    (0x0003)          // rw-- Dynamic brake mode
#define DISSTOPMODE                                   (0x000C)          // rw-- Stop method


// Emergencystop state machine
#define EMER_IDLE						(0)             //
#define EMER_DEC						(1)             //
#define EMER_STOP						(2)             //
#define EMER_DISABLE					(3)             //
#define EMER_FINISH						(4)             //


#define DISDECSCALE						(6)             // Deceleration scale
		
typedef struct
{
	uint8 State;				// State machine
	uint8 StateLatch;			// State machine latch
	uint8 StartStopFlag;        // Start deceleration flag
	uint8 DecStopFlag;			// Speed command switch flag
	uint8 StartBrakeFlag;       // Start dynamic brake flag
	uint16 TimeCounter;			// Stop counter
	uint16 TimeOutCounter;		// Stop timeout counter
	int16 DisSpeed;				// Stop speed threshold
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
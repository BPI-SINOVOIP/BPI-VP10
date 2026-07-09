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

// Interrupt priorities
#define FO_INT_PRI			( 7 ) // Hardware overcurrent protection interrupt
#define FO_CMP3_INT_PRI		( 7 ) // Hardware overcurrent protection interrupt
#define EXTERN1_INT_PRI		( 6 ) // External interrupt
#define DRVPIF_INT_PRI		( 4 ) // Protection interrupt
#define FOC_INT_PRI			( 5 ) // Carrier interrupt
#define DMA0_INT_PRI		( 3 ) // Serial port DMA interrupt
#define TIM3_INT_PRI		( 4 ) // Position loop interrupt
#define MEFSM_INT_PRI		( 6 ) // ME interrupt
#define CAN_INT_PRI			( 2 ) // CAN receive interrupt


typedef enum
{
	mcReady = 0,
	mcIdle = 1,
	mcDisable = 2,
	mcPhaseFind = 3,
	mcHome = 4,
	mcStart = 5,
	mcRun = 6,
	mcFault = 8,
	mcUpFlash = 9,
	mcDownFlash = 10,
	mcMotorIdentify = 11,
} MotStaType;

typedef union
{
	uint8 SetMode;                                     // Overall configuration mode enable bits
	struct
	{
		uint8 ChargeSetFlag : 1;                 // Pre-positioning configuration flag bit
		uint8 PhaseFindSetFlag : 1;                 //
		//    	uint8 HomeSetFlag : 1;                 //
		uint8 AutoPhaseFindSetFlag : 1;
		uint8 AutoHomeSetFlag : 1;                 //
		uint8 AutoEnableSetFlag : 1;                 //
		uint8 StopSetFlag : 1;                 // 
		uint8 BrakeFlag : 1;                 // Start/Stop flag bit
		uint8 IdentifySetFlag : 1;
	} SetFlag;
} MotStaM;



/* Exported variables --------------------------------------------------------------------*/
extern uint8 mcState;
extern MotStaM McStaSet;


/* Exported functions --------------------------------------------------------------------*/
extern void MC_Control(void);


#endif
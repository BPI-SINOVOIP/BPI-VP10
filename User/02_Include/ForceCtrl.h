/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ForceCtrl.h
 * Author        : Victor.jin
 * Date          : 2024-01-18
 * Description   : Force control
 *
 * Record        :
 * V1.0, 2024-01-18, Victor.jin: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FORCECTRL_H__
#define __FORCECTRL_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"

// Force control mode switch
#define FCMODE_DISABLE					(0)             // Disable force control function
#define FCMODE_OPENLOOP_ONCE			(1)             // Open-loop force control single-run mode
#define FCMODE_OPENLOOP_REPEAT			(2)             // Open-loop force control repeat mode
#define FCMODE_CLOSEDLOOP_ONCE			(3)             // Closed-loop force control single-run mode
#define FCMODE_CLOSEDLOOP_REPEAT		(4)             // Closed-loop force control repeat mode

#define READY                           (0)
#define START                           (1)
#define SUCESS                          (2)

// Force control state machine
#define FC_POS_FAST_FALL				(0)
#define FC_SPD_SLOW_FALL				(1)
#define FC_TOQ_HOLDING					(2)
#define FC_SPD_SLOW_RISE				(3)
#define FC_POS_FAST_RISE				(4)
#define FC_ERROR_RISE				    (5)


/*************************************************************************************///External Function


typedef struct
{
	uint8 Status; 
	uint8 StatusLast;
	uint8 CtrlModePre; 
	uint8 SwitchCompFlag; 
	uint8 RollbackFlag;
	uint8 ForceZero_EN; 
	
	uint16 MoveDis_H;
	uint16 MoveDis_L;
	int16 TestCmdPort;
	int16 TestIncPort;
	
	uint8 RepeatFlag; 
	uint8 PauseFlag;  
	uint16 TimeCounter;	
	uint16 TimeCounter_EN;	
	uint16 ResetCnt;  

	int16 SwitchCurCmd;	
	int16 SwitchFrcComp;
	int16 SwitchCurComp;
	int16 FrcAdjustComp;
	int16 FrcFdb;
	int16 Test;

} ForceCtrlPTypedef;



extern ForceCtrlPTypedef ForceCtrl;


extern void ForceCtrl_Init(void);
extern void ForceCtrl_Clr(void);
extern void ForceCtrl_Update(void);
extern void ForceCtrl_RunInit(void);



#ifdef __cplusplus
}
#endif


#endif
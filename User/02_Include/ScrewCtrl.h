/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ScrewCtrl.h
 * Author        : wynn.wang
 * Date          : 2025-01-18
 * Description   : 电批
 *
 * Record        :
 * V1.0, 2025-01-18, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __SCREWCTRL_H__
#define __SCREWCTRL_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"



// Ele Screwing
#define NO_SCREW_STEP                   (0)
#define SCREW_NEAR_STEP                 (1)
#define SCREW_IN_STEP                   (2)
#define SCREW_HOLD_STEP                 (3)
#define SCREW_QUIT_STEP                 (4)
#define SCREW_SUSS_STEP                 (5)

#define READY                           (1)
#define RUNING                          (2)
#define DONE                            (3)
#define ERROR                           (4)

#define NOWARN                          (0)
#define NEAROVERTIME                    (1)
#define ENTEROVERTIME                   (2)
#define HOLDROVERTIME                   (3)
#define QUITFAIL                        (4)
#define POSYESTOQNO                     (5)
#define POSNOTOQYES                     (6)
#define POSNOTOQNO                      (7)

#define WAVEINCMAX                      (65535)
#define ESCNUM                          (24)
/*************************************************************************************///External Function



typedef struct
{
	uint8 ScrewStep; 
	uint8 ScrewStepLatch;
	uint8 ScrewStatus;
	uint8 RunMod;  
	uint8 FirstFlag;
	uint8 PauseFlag;

	uint16 MoveDis_H;
	uint16 MoveDis_L;
	int16 TestCmdPort; 
	int16 TestToqHold;
	int16 TestIqMax;
	int16 TestIqMin; 
	int16 SampleIqMax;
	int16 SampleIqMin; 
	uint16 TestRatioHold;
	uint16 TestSpdHold; 
	uint16 MotionEn; 
	uint16 MotionEn_Pre; 
	int16 SwitchCurCmd;
	int16 TestIncPort;

	uint16 CtrlModePre;
	uint16 ScrewSusCnt;
	uint16 ScrewPyInCnt;
	uint16 ScrewPnIyCnt;
	uint16 ScrewPnInCnt;
	uint16 ScrewLowCnt;
	uint16 ScrewHighCnt;
	uint16 ScrewFinaCnt; 
	uint16 SampleCnt; 
	uint16 NearCntHold; 
	uint16 EnterCntHold; 
	uint16 FinaCntHold;
	uint16 OverTimeHold;
	uint16 SerialInStatus; 
	uint16 MotionStatus;
	
	int32 ScrewRatio; 
	int32 TestNowAngle;
	int32 TestLastAngle;
	
} EleScrewTypedf;


extern EleScrewTypedf ScrewCtrl;


extern void ScrewCtrl_RunInit(void);
extern void ScrewCtrl_Sample(void);
extern void ScrewCtrl_Update(void);
extern void ScrewCtrl_ProtectWarn(void);

extern void ScrewNear_Process(uint16 ScrewNum);
extern void ScrewIn_Process(uint16 ScrewNum);
extern void ScrewHold_Process(uint16 ScrewNum);
extern void ScrewQuit_Process(uint16 ScrewNum);
extern void ScrewCtrl_StateMachine(uint16 ScrewNum);



#ifdef __cplusplus
}
#endif


#endif

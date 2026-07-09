/*
 * Copyright (c) 2026-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorFunc.h
 * Author        : Summer
 * Date          : 2026-05-06
 * Description   : Invoke algorithm modules
 *
 * Record        :
 * V1.0, 2026-05-06, Summer: Created file
 */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __MOTOR_FUNC_H__
#define __MOTOR_FUNC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <Myproject.h>


#define CURRENTBACK_FREQ            (POSCTRL_FREQUENCY)
// Function code update
#define FOLDBACKSON      ((int16)usSRegHoldBuf[FOLDBACKEN])        // 1: enabled 0: disabled
#define DELAYTIME        (((int32)usSRegHoldBuf[FBDELAYTIME_H] << 16) | (uint16)usSRegHoldBuf[FBDELAYTIME_L])  // Peak current delay time ms (1 to 2400s)  (hardware unit is 0.1ms)
#define RECOVERYTIME     (((int32)usSRegHoldBuf[FBRECOVERYTIME_H] << 16) | (uint16)usSRegHoldBuf[FBRECOVERYTIME_L])  // Recovery time ms
#define TIMECONSTANT     (((int32)usSRegHoldBuf[FBTIMECONSTANT_H] << 16) | (uint16)usSRegHoldBuf[FBTIMECONSTANT_L])  // Time constant ms (1s to 1200s)(hardware unit is 0.1ms)

#define MOTORDRIVE       ((int16)usSRegHoldBuf[RMSCURRENT])        // Continuous current value
#define MOTORPEAK        ((int16)usSRegHoldBuf[PEAKCURRENT])       // Peak current value
#define FAULTHOLDVALUE   ((int16)usSRegHoldBuf[FBFAULTHOLDVALUE])  // Fault current threshold
#define WARNHOLDVAL      ((int16)usSRegHoldBuf[FBWARNHOLDVAL])     // Warning current threshold


extern FeedBackCfgTypedef FeedBackCfg;
extern ErrCorCfgTypedef ErrCorCfg;
extern FriCmpCfgTypedef FriCmpCfg;
extern CurrBackCfgTypedef CurrBackCfg;
extern SoftCfgTypedef SoftCfg;
extern ScopeCfgTypeDef ScopeCfg;

#if FUNC_NTF_MODE == 1
extern VibrationCfgTypedef VibrationCfg[2];
#else
extern VibrationCfgTypedef VibrationCfg[1];
#endif


/*************************************************************************************///External Function
extern void ElecAngCal_Init(void);
extern void PI_Control_Init(PIControlSimple* p);
extern void FeedBackOnLoad_Demo_Init(void);
extern void NTF_Demo_Init(void);
extern void ErrorCorrection_Demo_Init(void);
extern void FricCmp_Demo_Init(void);
extern void CurrBack_Demo_Init(void);
extern void FieldSoftControl_Demo_Init(void);
extern void Scope_Init(void);
extern void Scope_Update(void);


#ifdef __cplusplus
}
#endif

#endif
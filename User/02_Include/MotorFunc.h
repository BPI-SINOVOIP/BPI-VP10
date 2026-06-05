/*
 * Copyright (c) 2026-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : MotorFunc.h
 * Author        : Summer
 * Date          : 2026-05-06
 * Description   : 调用算法模块
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


#define CURRENTBACK_FREQ            ( CURCTRL_FREQUENCY )
// 功能码更新
#define FOLDBACKSON      ((int16)usSRegHoldBuf[FOLDBACKEN])        // 1：使能 0：禁止
#define DELAYTIME        (((int32)usSRegHoldBuf[FBDELAYTIME_H] << 16) | (uint16)usSRegHoldBuf[FBDELAYTIME_L])  // 峰值电流延迟时间 ms (1 to 2400s)  (硬件化是0.1ms)
#define RECOVERYTIME     (((int32)usSRegHoldBuf[FBRECOVERYTIME_H] << 16) | (uint16)usSRegHoldBuf[FBRECOVERYTIME_L])  // 恢复时间 ms
#define TIMECONSTANT     (((int32)usSRegHoldBuf[FBTIMECONSTANT_H] << 16) | (uint16)usSRegHoldBuf[FBTIMECONSTANT_L])  // 时间常数 ms (1s to 1200s)(硬件化是0.1ms)

#define MOTORDRIVE       ((int16)usSRegHoldBuf[RMSCURRENT])        // 持续电流值
#define MOTORPEAK        ((int16)usSRegHoldBuf[PEAKCURRENT])       // 峰值电流值
#define FAULTHOLDVALUE   ((int16)usSRegHoldBuf[FBFAULTHOLDVALUE])  // 故障电流阈值
#define WARNHOLDVAL      ((int16)usSRegHoldBuf[FBWARNHOLDVAL])     // 警告电流阈值


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
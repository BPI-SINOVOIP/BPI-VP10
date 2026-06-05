/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Feedback.h
 * Author        : wynn.wang
 * Date          : 2025-01-16
 * Description   : Full closed loop control Function
 *
 * Record        :
 * V1.0, 2025-01-16, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FEEDBACK_H__
#define __FEEDBACK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Math.h"
#include "Filter.h"


// OnLoadFlag
#define FEEDBACK_MOTOR				( 0 )	// 电机反馈
#define FEEDBACK_LOAD				( 1 )   // 负载反馈


// 按照外环的分辨率低于内环的分辨率确定的Q格式
// 否则Q格式的位数要修改
#define LOADCOEF                    ( 20 )
#define MOTORCOEF                   ( 10 )


/* ------ FeedBack Config Type ------ */
typedef struct
{
	uint8  mcStateRunFlag;
	const uint8* pMode;                   // 全闭环模式  0:内环 1:外环 2:内外环切换（功能码）
	const uint8* pPosLoopEnable;		  // 位置环使能标志位

	
	const int16* pMixErrClrRpm;           // 混合偏差清0圈数（功能码）
	const uint32* pLoadFeedPulse;         // 电机旋转一圈外部编码器的脉冲数（功能码）
	const int32* pMixErrMaxValue;         // 内、外环偏差的差值超过该值时应该报警（功能码）
	const int32* pLoadActualAngle;        // 外环实时位置
	const int32* pMotorActualAngle;		  // 内环实时位置
	const int32* pTargetAngle;
	const int32* pTargetRef;

	int32 LoadEncRes;				// 外环分辨率
	int32 EncRes;					// 内环分辨率
	int16 PosCtrlFreq;				// 位置环控制频率
	int16 LPFFreq;					// 外环抑振滤波器

} FeedBackCfgTypedef;


/*************************************************************************************///External Function
extern void FeedBackOnLoad_Init(const FeedBackCfgTypedef * cfg);
extern void FeedBackOnLoad_Clr(void);
extern void FeedBackOnLoad_Update();
extern int32 PosErrCalc_realize();
extern int32 FeedBackMixErrCheck();
extern int32 LoadPosFdbCalc_realize();

extern uint8 Feedback_GetOnLoadFlag(void);
extern uint8 Feedback_GetMixErrOverFlag(void);
extern int64 Feedback_GetLoadToMotorCoef(void);
extern int64 Feedback_GetMotorToLoadCoef(void);

#ifdef __cplusplus
}
#endif

#endif
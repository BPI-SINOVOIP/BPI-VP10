/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : SoftControl.h
 * Author        : wynn.wang
 * Date          : 2025-04-20
 * Description   : 柔顺控制
 *
 * Record        :
 * V1.0, 2025-04-20, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __SOFTCONTROL_H__
#define __SOFTCONTROL_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "fu7502.h"
#include "Math.h"
#include "Filter.h"
#include "PIControl.h"
#include "ToqFeedForward.h"


/*************************************************************************************///External Function
/* ------ Soft Control Type ------ */
#define SC_MODE_OFF					(0)			// 关闭
#define SC_LOCAL_IMPEDANCE          (1)			// 阻抗控制（本地）
#define SC_LOCAL_ADMITTANCE         (2)			// 导纳控制（本地）
#define SC_WorkMode                 ((int16)usSRegHoldBuf[SOFTCTRLWORMOD])

typedef struct
{
	uint16 WorkMode;
	int16 VelLimMax;
	int16 VelLimMin;
	int16 CurLimMax;
	int16 CurLimMin;
	int16 VelLmt;

	uint16 ForceConst;
	uint16 CurCoe;
	uint16 PeinPosRange;

	int16 RmsCurrent;
	int16 MotorMaxSpd;
	uint16 CurCtrlFreq;
	uint16 VelCtrlFreq;
	uint16 PosCtrlFreq;

	const uint16* pCompMode; // 阻抗控制补偿位置定位误差的模式
	const int16* pActVel;
	const int16* pActCur;
	const int16* pSpdFF;
	const int32* pTargetRef;
	const int32* pThetaErr;
	const int32* pTargetReftoSpd;
	const uint32* pSKp;
	const uint32* pSKi;
	const uint32* pSKd;
	const int16* pSXPosCmd;
	const int16* pSXPosAct;
	const int16* pSXForceCmd;
	const int16* pSXForceAct;
} SoftCfgTypedef;




extern void FieldSoftControl_Init(SoftCfgTypedef* cfg);
extern void FieldSoftControl_PIDUpdate(void);
extern void FieldSoftControl_Clr(void);
extern int16 FieldSoftControl_realize(int32 thetaErr);
extern int16 FieldSoftControl_TiffCalc(void);
extern void FieldSoftControl_AccActCalc(void);
extern uint8 FieldSoftControl_GetSwToPosFlag(void);
extern uint8 FieldSoftControl_GetSwToPosDoneFlag(void);

#ifdef __cplusplus
}
#endif

#endif
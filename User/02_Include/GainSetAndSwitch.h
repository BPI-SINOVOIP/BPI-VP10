/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : GainSetAndSwitch.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : 增益切换
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __GAINSETANDSWITCH_H__
#define __GAINSETANDSWITCH_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "fu7502.h"
#include "Math.h"
#include "PIControl.h"
#include "Customer.h"

#ifndef CURMOD
#define CURMOD						   ( 1 )
#endif

#ifndef VELMOD
#define VELMOD						   ( 2 )
#endif

#ifndef POSMOD
#define POSMOD                         ( 4 )
#endif


/*************************************************************************************///External Function
typedef enum {
	GNSWCTRL_POS,
	GNSWCTRL_SPD,
} GNSWCtrlType;


typedef struct
{
	const uint16* pVp;				 // 速度环比例Kp
	const uint16* pVi;				 // 速度环积分Ki
	const uint16* pVp2;				 // 速度环比例Kp2
	const uint16* pVi2;				 // 速度环积分Ki2

	const uint16* pPp;				 // 速度环比例Kp
	const uint16* pPi;				 // 速度环积分Ki
	const uint16* pPp2;				 // 速度环比例Kp2
	const uint16* pPi2;				 // 速度环积分Ki2

	const uint16* pVfr;				 //
	const uint16* pVfr2;			 //

	const uint16* pGnSWDlyTm;             // 增益切换延迟时间

	const uint16* pGnSWPAccTm;           // 位置环增益切换延迟时间（第一增益向第二增益切换）
	const uint16* pGnSWPDecTm;           // 位置环增益切换延迟时间（第二增益向第一增益切换）
	const uint16* pGnSWVAccTm;           // 速度环增益切换延迟时间（第一增益向第二增益切换）
	const uint16* pGnSWVDecTm;           // 速度环增益切换延迟时间（第二增益向第一增益切换）

	const int16* pGnSwLvl;				  // 增益切换等级
	const int16* pGnSwHysteresis;		  // 增益切换迟滞
	const int16* pRmsCurrent;             // 额定电流
	const int16* pMaxSpeed;               // 最大速度

	const int16* pIqRef;                  // 转矩指令
	const int16* pVelRef;                 // 速度指令
	const int16* pActVel;				  // 实际速度
	const int32* pPosRef;				  // 位置指令
	const int32* pPosErr;                 // 位置偏差

	int16 PosCtrlFreq;				// 位置环频率
	int16 VelCtrlFreq;				// 速度环频率

	const uint8* pRunMod;					// 运行模式
	const uint8* pGnSWMode;               // 增益切换模式
	uint8 GnSwitch;					// IO控制增益切换
	uint8 InPos;					// 到位情况

} GnSWPCfgTypedef;


typedef struct GnSWPIGainTypedef_t GnSWPIGainTypedef;

extern void GainSW_Init(const GnSWPCfgTypedef* cfg);
extern void GainSW_realize(const GnSWPCfgTypedef* cfg);
extern void GainSW_Update(const GnSWPCfgTypedef* cfg);
extern void GainSW_UpdateIsr(const GnSWPCfgTypedef* cfg);
extern void GainSwitching_realize(PIControl* p, GNSWCtrlType type);
extern void GetGnFir(PIControl* p);
extern GnSWPIGainTypedef* GainSW_GetSWVelParam(void);
extern GnSWPIGainTypedef* GainSW_GetSWPosParam(void);

#ifdef __cplusplus
}
#endif

#endif

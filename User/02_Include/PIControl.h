/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PIControl.h
 * Author        : wynn.wang
 * Date          : 2025-04-20
 * Description   : 实现PI控制器核心功能，包括参数初始化、控制量计算、积分限幅等
 *
 * Record        :
 * V1.0, 2025-04-20, wynn.wang: 初始版本，实现基本PI控制算法
 */


#ifndef __PICONTROL_H__
#define __PICONTROL_H__

#include "fu7502.h"
#include "Parameter.h"


#define VP_RANK  (10)
#define KP_RANK  (12)
#define KI_RANK  (15)
#define DKPI_RANK  (KI_RANK - VP_RANK)
#define UPFLAG (1)
#define DOWNFLAG (2)

/*************************************************************************************///External Function
typedef struct GnSWPIGainTypedef_t GnSWPIGainTypedef;

typedef struct
{
	int16 ActualValue;             // 实际值
	int16 PreCmdValue;			   // 上次目标速度
	int16 ErrValue;                // 差值E(k)
	int16 PreErrValue;             // 上一次差值E(k-1)
	uint16 PreKi;
	uint16 Kp;                     // 比例Kp
	uint16 Ki;                     // 比例Ki
	uint16 Kp1;                    // 比例Kp
	uint16 Ki1;                    // 比例Ki
	uint16 Kvf;
	uint16 Kvf1;		           // PDFF kvf 参数
	uint16 Kvf2;
	uint16 Kp2;                    // 比例Kp2
	uint16 Ki2;                    // 比例Ki
	uint16 LimitFlag;
	uint16 KiLimitFlag;
	uint32 Kf;		               // PDFF kvf
	
	// 硬件速度PI可以不需要以下几个变量
	int16 ValueMin;                // 限幅最小值
	int16 ValueMax;                // 限幅最大值
	int32 ValueMin32;              // 限幅最小值
	int32 ValueMax32;              // 限幅最大值
	int32 Valuetemp1;
	int32 Valuetemp3;
	int32 Valuetemp4;
	int32 ValuetempKp;
	int32 ValuetempKi;
	
//#if FUNC_GAINSW_ENABLED
	GnSWPIGainTypedef* pGnSW;

	int32 KiValueMax;
	int32 KiValueMin;	
	int32 GnKfCoef;                // 增益切换kf系数
	
	uint16 GnSWTmAccCnt;  // 增益切换计数器（第一增益向第二增益切换）
	uint16 GnSWTmDecCnt;  // 增益切换计数器（第二增益向第一增益切换）
	uint16 GnSWDlyTmCnt;  // 增益切换延迟计数器
	uint16 GnSWState;     // 增益切换状态机
	uint16 GnSWStateLatch;
	uint16 AutoFlag;
//#endif //#if FUNC_GAINSW_ENABLED

	int16 ValueMinBuffer;			//限幅最小值缓存
	int16 ValueMaxBuffer;			//限幅最大值缓存
	int16 SetLimitEn;				//限幅开关
	uint16 KpQSel;                  // 比例Kp的Q值选项
	uint16 KiQSel;			        // 比例Ki的Q值选项
	int8 KpQVal;			        // 比例Kp的Q值
	int8 KiQVal;			        // 比例Ki的Q值
} PIControl;


typedef struct
{
	const uint16* pKp;             // 比例Kp
	const uint16* pKi;             // 比例Ki
	uint16 LimitFlag;
	int16 DeSatur;				   // 积分饱和值
	int16 ErrValue;                // 差值E(k)
	uint8 KpRank;                  // 
	uint8 KiRank;                  //

	int32 ValueMin32;              // 限幅最小值
	int32 ValueMax32;              // 限幅最大值
	int32 Valuetemp1;
	int32 Valuetemp3;
	int32 Valuetemp4;
	int32 ValuetempKi;
} PIControlSimple;


extern PIControl PID_Speed;
extern PIControl PID_Pos;
extern PIControlSimple PID_Force;



extern void PI_Init(void);
extern void PI_Clear(void);
extern int16 PI_Spd_realize(int16 Cmd, int16 Act);
extern int16 PI_Pos_realize(int32 ErrValue);
extern void PI_Spd_UpdateLimit(int16 Max, int16 Min);
extern void PI_Spd_ResetLimit();
extern void PI_Update();
extern void Hard_PI_Init(void);
extern void Hard_PI_Clear(void);
extern int16 Hard_PI_Spd_realize(int16 Cmd, int16 Act);
extern void Hard_PI_Gain_Update();

extern void PI_Toq_Clear(void);
extern void PI_Spd_Clear(void);
#endif

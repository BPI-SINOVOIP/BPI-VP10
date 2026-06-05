/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Hall.h
 * Author        : Jamie
 * Date          : 2022-10-12
 * Description   : define some new method of Hall.
 *
 * Record        :
 * V1.0, 2022-10-12, Jamie: Created file
 */


#ifndef __HALL_H_
#define __HALL_H_
/* Define to prevent recursive inclusion -------------------------------------*/
#include "Parameter.h"

/*! \brief If Firmware do hall learning calculation is enabled. 0-Software do it; 1- Firmware do it. */
#define HALL_LEARN_CALCULATION_ENABLED					( 0 )

/* Hall pin definition */
#define HA_GPIO							(PB)
#define HA_PIN							(PIN3)
#define HA_OE							(PB_OE)
#define HA_PU							(PB_PU)

#define HB_GPIO							(PB)
#define HB_PIN							(PIN1)
#define HB_OE							(PB_OE)
#define HB_PU							(PB_PU)

#define HC_GPIO							(PB)
#define HC_PIN							(PIN4)
#define HC_OE							(PB_OE)
#define HC_PU							(PB_PU)


/* 电角度定义 */
#define DEGREE_SUM                      (uint32)(163840) // DEGREE_60 * 15


// Definition of register HALLMODE
#define HALLMODE_LEARNOK				(0x0080)          //
#define HALLMODE_DIR					(0x0008)          //
#define HALLMODE_HCINV					(0x0004)          //
#define HALLMODE_HBINV					(0x0002)          //
#define HALLMODE_HAINV                  (0x0001)          //

typedef struct
{
#if HALL_LEARN_CALCULATION_ENABLED	
	uint16 LearnHallTheta[6];              // 记录Hall变化沿的电角度
	uint8 LearnHallStatus[6];             // Hall学习状态
	int16 OffsetThetaPos;                 // 补偿角的偏置角(正向运动)
	int16 OffsetThetaNeg;                 // 补偿角的偏置角(反向运动)
	uint8 LearnMoveDirFlag;               // 运动方向标志
#else	
	uint16 *pLearnHallTheta;              // 记录Hall变化沿的电角度
	uint8* pLearnHallStatus;              // Hall学习状态
#endif
	
	uint8 Error;                          // 故障类型 1:存在全零情况
	uint8 HallStepCnt;                    // 计数
	uint8 MCDivFlag;                      // Hall方向颠倒
	uint8 Mode;                           // Hall关系，对应6种Hall组合
	uint8 ThetaCalcFlag;                  // 启动角度校准标志
	uint8 LastHallStatus;                 // 上次角度Hall状态
	uint8 NowHallStatus;                  // 此次角度Hall状态
	int16 FOCThetaStart;                  // 初始电角度
	int16 OffsetTheta;                    // 叠加补偿角的偏置角
	
#if ENCODER_SEL_HALLSONLY_ENABLED > 0
	uint8 HallStatusPre;                 // 上次角度Hall状态
	uint8 HallStatus;					 // 此次角度Hall状态
	uint8 LowSpeedStatus;				 // 低速状态，对应Hall定时器计数溢出时和方向切换时，这时候都无法计算正确的角速度
	int16 HallTheta;					 // 当前Hall原始电角度
	int16 HallThetaOut;					 // 当前Hall加上偏置后的电角度
	int16 HallAngle;					 // Hall插值角度中间值
	int32 HallAngleOut;					 // Hall插值角度
	int16 InterpltDltRef;				 // Hall插值角度增量
	int16 InterpltDltRefLatch;			 // Hall插值角度增量锁存
	uint16 StillCounter;				 // Hall出现变化的时间计数
	uint16 StillPeriod;					 // Hall出现变化的时间总和
	uint16 StillPeriodLatch;			 // Hall出现变化的时间缓存
	int16 InterpltInputLatch;			 // Hall插值输入缓存
	uint16 ExcCnt;						 // Hall插值的时间计数
	int32 InterpltOutput;				 // Hall插值输出结果
	int32 InterpltOutputLatch;			 // Hall插值输出结果缓存
	int32 InterpltOutputFlt;			 // Hall插值输出结果滤波后
	int64 InterpltOutputFlt_k;			 // 低通滤波器中间值
	int16 InterpltOutputDelta;			 // 低通滤波器输入，即插值位置的差分值
#endif
	
} HallTypeDef;

extern HallTypeDef mcHall;

extern void Hall_Init(void);
extern void DoHallLearning(void);
extern void UpdateHallPhaseMode(void);
extern int16 UpdateHallOffsetTheta(uint8 Dir);
extern void HallPinInit(void);
extern uint8 GetHallStatus();
extern uint8 GetHallStatus2(uint8 hallinput);
extern void UpdateHallTheta(void);
extern void UpdateHallTheta_Isr(void);
extern int32 UpdateHallsOnlyAngle(void);
extern int16 GetHallsOnlyElecAngle(void);

#endif

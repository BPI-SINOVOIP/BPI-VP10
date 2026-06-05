/*
 * Copyright (c) 2024-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Waveform.h
 * Author        : Summer
 * Date          : 2024-10-09
 * Description   : Base function for velocity/ current loop waveform.
 *
 * Record        :
 * V1.0, 2024-10-09, Summer: Created file
 */


#ifndef __WAVEFORM_H_
#define __WAVEFORM_H_

#include "fu7502.h"

// WAVETYPE
#define WAVE_CONST										( 0 )          // constant value
#define WAVE_TRAP										( 1 )          // trap wave: 没有停止段
#define WAVE_SIN										( 2 )          // sin wave
#define WAVE_CHIRP										( 3 )          // chirp wave
#define WAVE_TRAPEXT									( 4 )          // trap wave extended: 有停止段

// 状态机
#define WSTEP_POSACC                                    ( 0 )
#define WSTEP_POSDEC                                    ( 1 )
#define WSTEP_NEGACC                                    ( 2 )
#define WSTEP_NEGDEC                                    ( 3 )
#define WSTEP_WAIT										( 4 )
#define WSTEP_HOLD										( 5 )


// SerialIn Velocity/Current
typedef struct
{
	uint8 State;	// 0-加速段  1-加速后匀速段  2-减速段  3-减速后匀速段  4-无匀速段
	uint8 NextState;
	uint8 Status;
	uint8 Scale;
	uint8 WaveType;
	uint16 WaveCmdLatch;
	uint32 TimeCounter;
	int32 Value;
	int32 TestCmd;
	int32 TestInc;
	uint32 WaitTime; // 等待时间
	uint32 DwellTime; // 停顿时间
	uint32 PosConstTime; // 正向匀速时间
	uint32 NegConstTime; // 反向匀速时间
	int32 CycleCounter; // 重复次数
} SigGenTypeDef;


typedef struct
{
	uint16 SweepFrequencyStep;			// 扫频步进角
	uint16 SweepFrequencyValue;			// 正弦波输出频率
	uint16 Index;						// 实际输入正弦波角度
	uint16 Vs;							// 实际输入正弦波幅值
	int16 Out;							// 计算结果
} SINSWEEP_Typedef;


typedef struct
{
	uint32 LinCoe;						// 一次项系数
	uint32 QuadCoe;						// 二次项系数
	uint16 Index;						// 时间计数
	uint16 Amp;							// Chirp幅值
	uint16 Point;						// Chirp点数
} CHIRPSWEEP_Typedef;

extern SigGenTypeDef mcSigGen;
extern SINSWEEP_Typedef SinSweep;
extern CHIRPSWEEP_Typedef ChirpSweep;


extern void Motor_SerialIn_Init(void);
extern void Motor_SerialIn_StartMove(void);
extern void Motor_SerialIn_StartSuspend(void);
extern void Motor_SerialIn_StartDeceleration(void);
extern int16 Motor_SerialIn_Handler(void);
extern void SinSweepFreInit(uint16 workLoop);
extern int16 SinSweepFre(void);
extern void ChirpSweepFreInit(uint16 workLoop);
extern int16 ChirpSweepFre(void);
extern void Motor_TuningSignal_Handler(int16* id, int16* iq);

#endif
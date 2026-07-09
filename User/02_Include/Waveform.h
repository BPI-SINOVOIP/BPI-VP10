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
#define WAVE_TRAP										( 1 )          // trap wave: no dwell segment
#define WAVE_SIN										( 2 )          // sin wave
#define WAVE_CHIRP										( 3 )          // chirp wave
#define WAVE_TRAPEXT									( 4 )          // trap wave extended: has dwell segment

// State machine
#define WSTEP_POSACC                                    ( 0 )
#define WSTEP_POSDEC                                    ( 1 )
#define WSTEP_NEGACC                                    ( 2 )
#define WSTEP_NEGDEC                                    ( 3 )
#define WSTEP_WAIT										( 4 )
#define WSTEP_HOLD										( 5 )

// SCALE SHIFT
#define VEL_SCALE_SHIFT									( 8 )
#define CUR_SCALE_SHIFT									( 0 )
#define FRC_SCALE_SHIFT									( 12 )

// SerialIn Velocity/Current
typedef struct
{
	uint8 State;	// 0-acceleration phase  1-constant speed after acceleration  2-deceleration phase  3-constant speed after deceleration  4-no constant speed segment
	uint8 NextState;
	uint8 Status;
	uint8 Scale;
	uint8 WaveType;
	uint16 WaveCmdLatch;
	uint32 TimeCounter;
	int32 Value;
	int32 TestCmd;
	int32 TestInc;
	uint32 WaitTime; // Waiting time
	uint32 DwellTime; // Dwell time
	uint32 PosConstTime; // Forward constant-speed time
	uint32 NegConstTime; // Reverse constant-speed time
	int32 CycleCounter; // Repeat count
} SigGenTypeDef;


typedef struct
{
	uint16 SweepFrequencyStep;			// Sweep step angle
	uint16 SweepFrequencyValue;			// Sine wave output frequency
	uint16 Index;						// Actual input sine wave angle
	uint16 Vs;							// Actual input sine wave amplitude
	int16 Out;							// Calculated result
} SINSWEEP_Typedef;


typedef struct
{
	uint32 LinCoe;						// Linear coefficient
	uint32 QuadCoe;						// Quadratic coefficient
	uint16 Index;						// Time counter
	uint16 Amp;							// Chirp amplitude
	uint16 Point;						// Chirp point count
} CHIRPSWEEP_Typedef;

extern SigGenTypeDef mcSigGen;
extern SINSWEEP_Typedef SinSweep;
extern CHIRPSWEEP_Typedef ChirpSweep;


extern void Motor_SerialIn_Update(void);
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
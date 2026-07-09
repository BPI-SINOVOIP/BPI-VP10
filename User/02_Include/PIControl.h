/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : PIControl.h
 * Author        : wynn.wang
 * Date          : 2025-04-20
 * Description   : Implements the core functionality of the PI controller, including parameter initialization, control calculation, integral limiting, etc.
 *
 * Record        :
 * V1.0, 2025-04-20, wynn.wang: Initial version, implements the basic PI control algorithm
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
	int16 ActualValue;             // Actual value
	int16 PreCmdValue;			   // Previous target speed
	int16 ErrValue;                // Error value E(k)
	int16 PreErrValue;             // Previous error value E(k-1)
	uint16 PreKi;
	uint16 Kp;                     // Proportional Kp
	uint16 Ki;                     // Integral Ki
	uint16 Kp1;                    // Proportional Kp
	uint16 Ki1;                    // Integral Ki
	uint16 Kvf;
	uint16 Kvf1;		           // PDFF kvf parameter
	uint16 Kvf2;
	uint16 Kp2;                    // Proportional Kp2
	uint16 Ki2;                    // Integral Ki
	uint16 LimitFlag;
	uint16 KiLimitFlag;
	uint32 Kf;		               // PDFF kvf
	
	// The following variables may not be needed for hardware speed PI
	// The hardware speed PI may not need the following variables
	int16 ValueMin;                // Minimum saturation value
	int16 ValueMax;                // Maximum saturation value
	int32 ValueMin32;              // Minimum saturation value
	int32 ValueMax32;              // Maximum saturation value
	int32 Valuetemp1;
	int32 Valuetemp3;
	int32 Valuetemp4;
	int32 ValuetempKp;
	int32 ValuetempKi;
	
//#if FUNC_GAINSW_ENABLED
	GnSWPIGainTypedef* pGnSW;

	int32 KiValueMax;
	int32 KiValueMin;	
	int32 GnKfCoef;                // Gain switch kf coefficient
	
	uint16 GnSWTmAccCnt;  // Gain switch counter (first gain to second gain)
	uint16 GnSWTmDecCnt;  // Gain switch counter (second gain to first gain)
	uint16 GnSWDlyTmCnt;  // Gain switch delay counter
	uint16 GnSWState;     // Gain switch state machine
	uint16 GnSWStateLatch;
	uint16 AutoFlag;
//#endif //#if FUNC_GAINSW_ENABLED

	uint16 KpQSel;                  // Q value option for proportional Kp
	uint16 KiQSel;			        // Q value option for integral Ki
	int8 KpQVal;			        // Q value of proportional Kp
	int8 KiQVal;			        // Q value of integral Ki
} PIControl;


typedef struct
{
	const uint16* pKp;             // Proportional Kp
	const uint16* pKi;             // Integral Ki
	uint16 LimitFlag;
	int16 DeSatur;				   // Integral saturation value
	int16 ErrValue;                // Error value E(k)
	uint8 KpRank;                  // 
	uint8 KiRank;                  // 

	int32 ValueMin32;              // Minimum saturation value
	int32 ValueMax32;              // Maximum saturation value
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
extern void PI_Update();
extern void PI_Spd_Gain_Update();
extern int16 PI_Pos_realize(int32 ErrValue);

extern void PI_Toq_Clear(void);
extern void PI_Spd_Clear(void);
#endif
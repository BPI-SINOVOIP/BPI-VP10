/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : FieldWeaken.h
 * Author        : wynn.wang
 * Date          : 2025-03-18
 * Description   : Field weakening control
 *
 * Record        :
 * V1.0, 2025-03-18, wynn.wang: Created file
 */

/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __FTELDWEAKEN_H_
#define __FTELDWEAKEN_H_
#include <Myproject.h>

#define FW_MODE_ZERO                (0)
#define FW_MODE_ONE                 (1)
#define WEAKENMODE                  (FW_MODE_ONE)

#define Weaken_UsRef_Q15            _Q15(0.90) // 19005
#define Weaken_KP_Q12               _Q12(0.12) // 16629
#define Weaken_KI_Q15               _Q15(0.06) // 983

#define _2PI                        (3.1415926 * 2)                      // 2 PI value
#define _Pole_Pairs                 ((int16)usSRegHoldBuf[POLES] / 2)    // number of pole pairs
#define _Ke                         ((int32)usSRegHoldBuf[BEMFCONST] * 1000.0 * _2PI / 128.0 / 60.0) // (V/KRPM) back EMF constant 7.6
#define _LQ                         ((int16)usSRegHoldBuf[INDUCTANCE] / 2)   // Q-axis inductance/2 (mH * 256)
#define _LD                         ((int16)usSRegHoldBuf[DINDUCTANCE] / 2)  // D-axis inductance/2 (mH * 256)
#define _Psi                        (float)((int32) _Ke * 207.84 * 1.414 / 1.732 / 1000.0 / 2.0 / 1.732 / _Pole_Pairs / _2PI) // sqrt(2/3)ke/pp 0.01185

#define SAMP_FREQ                   (PWM_FREQUENCY * 1000)
#define TPWM_VALUE                  (1.0  / SAMP_FREQ)
#define UsLpfK				        (50.0)
#define UsLpfK_Q15                  _Q15(_2PI * UsLpfK * TPWM_VALUE) // 643

#define Weaken_RatCurrent_Q15       ((int16)usSRegHoldBuf[RMSCURRENT])
#define Weaken_ThertaMax0_Q15       _Q15(0.0)
#define Weaken_ThertaMin0_Q15       MAX(I_Value(-0.8 * _Psi * 1000.0 * 256.0 / _LD), (-1.0 * Weaken_RatCurrent_Q15)) // -5174

#define Weaken_IdRefLimit_Q15		I_Value(-0.8 * _Psi * 1000.0 * 256.0 / _LD) // -22

typedef struct
{
	int16 Weaken_CncVel;
	int16 Weaken_Theta;
	int16 kp;
	int16 ki;
	int16 UsLpfk;
	
	int32 Weaken_FocUsRef;
	int32 Weaken_FocUsFed;
	int32 Weaken_FocUsFedFlt;
	int32 Weaken_FocUsErr;
	

    int32 Weaken_DeltaIdRef;
    int32 Weaken_IdRefTemp;
    int32 Weaken_IdRefLimit;
    int32 Weaken_MaxLmt;
    int32 Weaken_MinLmt;
    
    int32 Weaken_IsRef;
    int32 Weaken_IdRef;
    int32 Weaken_IqRef; 
    int32 Weaken_IMaxRef;
    int32 Weaken_IqMaxRef;
    int32 Weaken_IqRefLmtPos;
    int32 Weaken_IqRefLmtNeg;
    
    int32 Weaken_IsMaxReal;
    int32 Weaken_IsMax;
    	   	
} FieldWeakenParameter;

extern FieldWeakenParameter  mcFieldWeakenControl;

extern void FieldWeakenUsPIInit(void);
extern void FieldWeakenGetIdRefAndIqRef(void);
extern void FieldWeakenControlInit(void);
extern void FieldWeakenIqRefAdjust(void);

#endif
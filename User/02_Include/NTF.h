/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : NTF.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : End-point vibration suppression
 *
 * Record        :
 * V1.0, 2023-08-11, wynn.wang: Created file
 */



/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __NTF_H__
#define __NTF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fu7502.h"
#include "Math.h"

/*! \brief If vibration suppression is enabled:
 * 0 - Mode1 + AntiVib1;
 * 1 - Mode1 + AntiVib1 + AntiVib2;
 * 2 - Mode1 + Mode2 + Mode3 + AntiVib1
 */
#define FUNC_NTF_MODE					( 1 )

/* ------ Speed FeedForward Type ------ */
#define NTF_MODE_OFF					( 0 )
#define NTF_MODE_ONE					( 1 )
#define NTF_MODE_TWO					( 2 )
#define NTF_MODE_THREE					( 3 )

#define NTF1NUM							( 0 )
#define NTF2NUM							( 1 )

#define NTF_Q1_SHIFT					( 23 )


/*************************************************************************************///External Function

typedef struct
{
	int32 SampFreq;                //Sampling frequency
	int32 NotchFreq;               //Notch filter center frequency
	int16 NotchSharp;			   //Filter sharpness
	int16 NotchGain;			   //Damping gain
		
	int32 NumCoeff[3];             //Numerator coefficients of the notch filter
	int32 DenCoeff[3];             //Denominator coefficients of the notch filter

	int8 Mode;
} VibrationCfgTypedef;


/*---------------------------------------------------------------------------
 * Name		:	NTF_Init
 * Input	:	cfg - configuration parameters
 * Output	:	No
 * Description:	Initialize vibration suppression
 *---------------------------------------------------------------------------*/
extern void NTF_Init(VibrationCfgTypedef* cfg);


/*---------------------------------------------------------------------------
 * Name		:	NTF_realize
 * Input	:	PosRef - position command increment
 * Output	:	Position command increment after vibration suppression
 * Description:	Position command increment processed by vibration suppression
 *---------------------------------------------------------------------------*/
extern int32 NTF_realize(int32 PosRef);


/*---------------------------------------------------------------------------
 * Name		:	NTF_Rst
 * Input	:	No
 * Output	:	No
 * Description:	Reset vibration suppression
 *---------------------------------------------------------------------------*/
extern void NTF_Rst(void);

#ifdef __cplusplus
}
#endif

#endif
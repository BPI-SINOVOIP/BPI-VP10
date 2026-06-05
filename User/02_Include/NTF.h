/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : NTF.h
 * Author        : wynn.wang
 * Date          : 2023-08-11
 * Description   : 末端抖动抑制
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
#define NTF_MODE_OFF					(0)
#define NTF_MODE_ONE					(1)
#define NTF_MODE_TWO					(2)
#define NTF_MODE_THREE					(3)

#define NTF1NUM							(0)
#define NTF2NUM							(1)

#define NTF_Q1_SHIFT					(23)


/*************************************************************************************///External Function

typedef struct
{
	int32 SampFreq;                //采样频率
	int32 NotchFreq;               //分子滤波中心频率
	int16 NotchSharp;			   //滤波锐度
	int16 NotchGain;			   //阻尼增益
		
	int32 NumCoeff[3];             //陷波器的分子系数
	int32 DenCoeff[3];             //陷波器的分母系数

	int8 Mode;
} VibrationCfgTypedef;


extern void NTF_Init(VibrationCfgTypedef* cfg);
extern int32 NTF_realize(int32 PosRef);
extern void NTF_Rst(void);

#ifdef __cplusplus
}
#endif

#endif
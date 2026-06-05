/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : OutputFilter.h
 * Author        : Summer
 * Date          : 2023-08-23
 * Description   : 转矩滤波器
 *
 * Record        :
 * V1.0, 2023-08-23, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __OUTPUTFILTER_H__
#define __OUTPUTFILTER_H__

#include "fu7502.h"

/*************************************************************************************///External Function
//#define M_PI                                            (3.1415926535897932384626433832795)
//滤波器数量
#define OUTPUTFILTER_FILTNUM							(4)

/* 滤波器类型 */
#define OUTPUTFILTER_NOFILT								(0)
#define OUTPUTFILTER_ONELPF								(1)
#define OUTPUTFILTER_2NDLPF								(2)
#define OUTPUTFILTER_NOTCH								(3)

// Definition of register OUTFILTQFAC
#define OUTFILT1UPDATE									( 0x0100 )     // rw-- Rising edge = update filter1 coefficients


extern void OutputFilter_Init(void);
extern void OutputFilter_RunModeUpdate(void);
extern void OutputFilter_CoeUpdate(void);

#endif
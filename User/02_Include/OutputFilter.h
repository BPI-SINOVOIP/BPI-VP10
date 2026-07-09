/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : OutputFilter.h
 * Author        : Summer
 * Date          : 2023-08-23
 * Description   : Torque filter
 *
 * Record        :
 * V1.0, 2023-08-23, Summer: Created file
 */


/* Define to prevent recursive inclusion -------------------------------------------------------- */
#ifndef __OUTPUTFILTER_H__
#define __OUTPUTFILTER_H__

#include "fu7502.h"

/*************************************************************************************///External Function

// Number of filters
#define OUTPUTFILTER_FILTNUM							(4)

// Filter types
#define OUTPUTFILTER_NOFILT								(0)
#define OUTPUTFILTER_ONELPF								(1)
#define OUTPUTFILTER_2NDLPF								(2)
#define OUTPUTFILTER_NOTCH								(3)
#define OUTPUTFILTER_BIQUAD								(4)
#define OUTPUTFILTER_LEADLAG							(5)
#define OUTPUTFILTER_DLEADLAG							(6)

// Definition of register OUTFILTQFAC
#define OUTFILT1UPDATE									( 0x0100 )     // rw-- Rising edge = update filter1 coefficients

// Definition of register OUTFILTCTRL
#define OUTCTRL_FILTMASK1								(0x000F) // bit0 - bit3: type of filter 1
#define OUTCTRL_FILTMASK2								(0x00F0) // bit4 - bit7: type of filter 2
#define OUTCTRL_FILTMASK3								(0x0F00) // bit8 - bit11: type of filter 3
#define OUTCTRL_FILTMASK4								(0xF000) // bit12 - bit15: type of filter 4



extern void OutputFilter_Init(void);
extern void OutputFilter_RunModeUpdate(void);
extern void OutputFilter_CoeUpdate(void);

#endif
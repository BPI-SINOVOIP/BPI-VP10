/*
 * Copyright (c) 2022-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : ADC.h
 * Author        : Fortior Application Team
 * Date          : 2022-09-21
 * Description   : define ADC
 *
 * Record        :
 * V1.0, 2022-09-21, Fortior Application Team: Created file
 */

#ifndef __ADC_H__
#define __ADC_H__

#include "fu7502.h"
#include "Parameter.h"


#define ADCDR_IA			(ADC1_DR0)
#define ADCDR_IB			(ADC1_DR1)
#define ADCDR_VBUS			(ADC1_DR2)


#if (HARDWARE_VERSION == HARDWARE_FPGA_HIGHVOL_SWITCH || HARDWARE_VERSION == HARDWARE_FPGA_LOWVOL_SWITCH)
#define ADCDR_ANAIN			(ADC1_DR6)				// 模拟量输入
#define ADCDR_TEMP			(ADC1_DR3)				// NTC温度测量

#define ADC1_ENABLEMASK		(CH6EN | CH3EN)

#define ANAIN_AN			(PB_AN)
#define ANAIN_PIN			(PIN3)

#define TEMP_AN				(PB_AN)
#define TEMP_PIN			(PIN14)

#elif (HARDWARE_VERSION == HARDWARE_LOWVOL_SWITCH)
#define ADCDR_ANAIN			(ADC1_DR11)				// 模拟量输入
#define ADCDR_TEMP			(ADC1_DR3)				// NTC温度测量

#define ADC1_ENABLEMASK		(CH11EN | CH3EN)

#define ANAIN_AN			(PC_AN)
#define ANAIN_PIN			(PIN14)

#define TEMP_AN				(PB_AN)
#define TEMP_PIN			(PIN14)

#elif (HARDWARE_VERSION == HARDWARE_LOWVOL_DELTAROBOT_SWITCH)
#define ADCDR_ANAIN			(ADC3_DR2)
#define ADCDR_TEMP			(ADC1_DR3)

#define ADC1_ENABLEMASK		(CH3EN)

#define ANAIN_AN			(PC_AN)
#define ANAIN_PIN			(PIN11)

#define TEMP_AN				(PB_AN)
#define TEMP_PIN			(PIN14)

#else // 没有NTC和模拟量输入
#define ADC1_ENABLEMASK		(0)
#endif

typedef struct
{
	bool OffsetFlag;                  //偏置电压结束标志位
} CurrentOffset;

extern CurrentOffset mcCurOffset;

/************************************************* *****************************///External Function
extern void ADC_Init(void);
extern void ADC2_Init(void);
extern void UpdateCurrentOffset(void);

#endif
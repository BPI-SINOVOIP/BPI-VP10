/********************************************************************************
/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Temperature.h
 * Author        : Summer
 * Date          : 2025-09-05
 * Description   : Driver temperature
 *
 * Record        :
 * V1.0, 2025-09-05, Summer: Created file
 */


#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

// Include external header file.
#include "fu7502.h"
#include "Parameter.h"


// Lookup Table length of KNTC0603
#define TEMPTABLE_LEN								( 25 )

// Lookup Table length of MCU TSD
#define TEMPTABLETSD_LEN							( 16 )


extern void UpdateTemperature(void);
extern uint16 TemperatureCalc(uint16 InputTempAD);


#endif
/*
 * Copyright (c) 2023-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DeadTimeCompensation.h
 * Author        : ThinkPad
 * Date          : 2023-6-4
 * Description   : This file contains Dead Time Compensation.
 *
 * Record        :
 * V1.0, 2023-6-4, Summer: Created file
 */

#ifndef __DEADTIMECOMPENSATION_H__
#define __DEADTIMECOMPENSATION_H__

#include "fu7502.h"
#include "Customer.h"




extern void DeadTimeCompensationInit(int16 DeadCompCurr);
extern void DeadTimeCompensationController(int16 Theta, int16 Id, int16 Iq);

#endif



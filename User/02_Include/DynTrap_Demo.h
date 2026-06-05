/*
 * Copyright (c) 2026-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DynTrapDemo.h
 * Author        : Summer
 * Date          : 2026-4-7
 * Description   : Trapezoidal velocity Profile Generator Demo
 *
 * Record        :
 * V1.0, 2026-4-7, Summer: Created file
 */

#ifndef DYN_TRAP_DEMO_H
#define DYN_TRAP_DEMO_H

#include <Myproject.h>
#include "DynTrap.h"

typedef struct {
	int32 encRes;
	int32 maxVelLatch;
	int32 maxAccLatch;
	int32 velocity;
	int32 acceleration;
} SetTrapTypeDef;


extern SetTrapTypeDef mcSetTrap;


extern void DynTrap_Demo_Init();
extern void DynTrap_Demo_Update(int32 targetPos, uint32 maxVel, uint32 maxAcc);
extern int32 DynTrap_Demo_Next();


#endif

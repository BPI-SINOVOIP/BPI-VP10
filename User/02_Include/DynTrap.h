/*
 * Copyright (c) 2025-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DynTrap.h
 * Author        : Summer
 * Date          : 2025-12-19
 * Description   : Trapezoidal velocity Profile Generator
 *
 * Record        :
 * V1.0, 2025-12-19, Summer: Created file
 */


#ifndef DYN_TRAP_H
#define DYN_TRAP_H


#include "fu7502.h"
#include "Math.h"


// Allocated memory size (bytes)
#define DYNTRAP_MEM_SIZE						( 120 )
// Velocity/acceleration scaling factor 2^16
#define DYNTRAP_VEL_SCALE						( 16 )
#define DYNTRAP_VEL_MASK						((1 << DYNTRAP_VEL_SCALE) - 1)


typedef struct DynTrapTypeDef_t DynTrapTypeDef;


/*---------------------------------------------------------------------------
 * Name		:	DynTrap_Init
 * Input	:	memory_buffer - Externally pre-allocated memory of DynTrapTypeDef size
 *				initPos - Absolute initial position value for trapezoidal profile planning
 * Output	:	Pointer to the configured DynTrapTypeDef instance
 * Description:	Initialize online trapezoidal profile planning functionality
 *---------------------------------------------------------------------------*/
DynTrapTypeDef* DynTrap_Init(void* memory_buffer, int32 initPos);


/*---------------------------------------------------------------------------
 * Name		:	DynTrap_Update
 * Input	:	pm - Valid trapezoidal profile control instance pointer returned by DynTrap_Init on success
 *				targetPos - New absolute target position
 *				maxVel - Maximum motion speed, unit: count/cycle
 *				maxAcc - Maximum absolute acceleration during accel/decel phases, unit: count/cycle^2
 * Output	:	None
 * Description: Update target position, maximum velocity, and maximum acceleration online	
 *---------------------------------------------------------------------------*/
void DynTrap_Update(DynTrapTypeDef * pm, int32 TargetPos, uint32 maxVel, uint32 maxAcc);


/*---------------------------------------------------------------------------
 * Name		:	DynTrap_Next
 * Input	:	pm - Valid trapezoidal profile control instance pointer returned by DynTrap_Init on success
 * Output	:	Absolute planned position output value calculated for this cycle
 * Description: Calculate the next planned position; call this function at fixed time intervals
 *---------------------------------------------------------------------------*/
int32 DynTrap_Next(DynTrapTypeDef * pm);


#endif
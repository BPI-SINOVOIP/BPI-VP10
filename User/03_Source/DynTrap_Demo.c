/*
 * Copyright (c) 2026-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : DynTrapDemo.c
 * Author        : Summer
 * Date          : 2026-4-7
 * Description   : Trapezoidal velocity Profile Generator Demo
 *
 * Record        :
 * V1.0, 2026-4-7, Summer: Created file
 */

/********************************************************************************
* Header Definition
********************************************************************************/
#include <math.h>
#include "DynTrap_Demo.h"

#if COMM_CAN_PDO_ENABLED

/********************************************************************************
* Macro & Structure Definition
*******************************************************************************/
uint8 my_dyntrap_mem[DYNTRAP_MEM_SIZE] = { 0 };
DynTrapTypeDef * mcTrap;
SetTrapTypeDef mcSetTrap;


/********************************************************************************
* Internal Routine Prototypes
********************************************************************************/

/*---------------------------------------------------------------------------*/
/* Name     :   DynTrap_Demo_Init
/* Input    :   NO
/* Output   :   NO
/* Description: 初始化变量及当前位置
/*---------------------------------------------------------------------------*/
void DynTrap_Demo_Init()
{
	int32 actPos;
	memset(&mcSetTrap, 0, sizeof(SetTrapTypeDef));

#if FUNC_FEEDBACKONLOAD_ENABLED
	if (FEEDBACK_LOAD == Feedback_GetOnLoadFlag() )
	{
		actPos = ((int32)usSRegInBuf[SFBACTPOS_H] << 16) | (uint16)usSRegInBuf[SFBACTPOS_L];
		mcSetTrap.encRes = ((int32)usSRegHoldBuf[SFBENCRES_H] << 16) | (uint16)usSRegHoldBuf[SFBENCRES_L];
	}
	else
#endif
	{
		actPos = ((int32)usSRegInBuf[ACTPOS_H] << 16) | (uint16)usSRegInBuf[ACTPOS_L];
		mcSetTrap.encRes = ((int32)usSRegHoldBuf[ENCRES_H] << 16) | (uint16)usSRegHoldBuf[ENCRES_L];
		mcSetTrap.encRes = (int64) mcSetTrap.encRes * 1000 / (((int32)usSRegHoldBuf[PITCH_H] << 16) | (uint16)usSRegHoldBuf[PITCH_L]);
	}
	
	mcTrap = DynTrap_Init(my_dyntrap_mem, actPos);
}


/*---------------------------------------------------------------------------*/
/* Name     :   DynTrap_Demo_Update
/* Input    :   NO
/* Output   :   NO
/* Description: 更新目标位置、最大速度(mm/s、rpm)、最大加速度(mm/s^2、rps^2)
/*---------------------------------------------------------------------------*/
void DynTrap_Demo_Update(int32 targetPos, uint32 maxVel, uint32 maxAcc)
{
	if (mcSetTrap.maxVelLatch != maxVel)  // 最大速度发生变化
	{
		mcSetTrap.maxVelLatch = maxVel;
		int64 maxvel = ((int64) mcSetTrap.maxVelLatch << DYNTRAP_VEL_SCALE) * (mcSetTrap.encRes) / PROFILE_FREQUENCY; // mm/s -> count/cycle; rps -> count/cycle
		if (GetReg(usSRegHoldBuf[DRIVEMODE], MODE_MOTORTYPE)) // Rotary Motor
		{
			mcSetTrap.velocity = maxvel / 60;   // rpm -> rps
		}
		else
		{
			mcSetTrap.velocity = maxvel;
		}
		mcSetTrap.velocity = maxvel;
		if (mcSetTrap.velocity < 1)
			mcSetTrap.velocity = 1;
	}

	if(mcSetTrap.maxAccLatch != maxAcc) // 最大加速度发生变化
	{
		mcSetTrap.maxAccLatch = maxAcc;
		// mm/s^2 -> count/cycle^2; rps^2 -> count/cycle^2
		mcSetTrap.acceleration = ((int64) mcSetTrap.maxAccLatch << DYNTRAP_VEL_SCALE) * (mcSetTrap.encRes) / PROFILE_FREQUENCY / PROFILE_FREQUENCY; 
		if (mcSetTrap.acceleration < 1)
			mcSetTrap.acceleration = 1;
	}

	DynTrap_Update(mcTrap, targetPos, mcSetTrap.velocity, mcSetTrap.acceleration);
}


/*---------------------------------------------------------------------------*/
/* Name     :   DynTrap_Demo_Next
/* Input    :   NO
/* Output   :   NO
/* Description: 计算下一个规划位置next position set point
/*---------------------------------------------------------------------------*/
int32 DynTrap_Demo_Next()
{
	return DynTrap_Next(mcTrap);
}


#endif
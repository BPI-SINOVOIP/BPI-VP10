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


// 分配的内存大小(字节)
#define DYNTRAP_MEM_SIZE						( 120 )
// 速度/加速度的放大倍数2^16
#define DYNTRAP_VEL_SCALE						( 16 )
#define DYNTRAP_VEL_MASK						((1 << DYNTRAP_VEL_SCALE) - 1)


typedef struct DynTrapTypeDef_t DynTrapTypeDef;


/*---------------------------------------------------------------------------
 * Name		:	DynTrap_Init
 * Input	:	memory_buffer - 外部预先分配的DynTrapTypeDef大小内存
 *				initPos - 梯形波规划的绝对初始位置值
 * Output	:	指向已配置完成的 DynTrapTypeDef 实例的指针
 * Description:	初始化在线规划梯形波曲线功能
 *---------------------------------------------------------------------------*/
DynTrapTypeDef* DynTrap_Init(void* memory_buffer, int32 initPos);


/*---------------------------------------------------------------------------
 * Name		:	DynTrap_Update
 * Input	:	pm - DynTrap_Init 成功返回的有效梯形波控制实例指针
 *				targetPos - 新绝对目标位置
 *				maxVel - 最大运动速度, 单位：count/cyclle
 *				maxAcc - 加/减速阶段最大绝对值加速度, 单位：count/cycle^2
 * Output	:	无
 * Description: 在线更新目标位置、最大速度、最大加速度	
 *---------------------------------------------------------------------------*/
void DynTrap_Update(DynTrapTypeDef * pm, int32 TargetPos, uint32 maxVel, uint32 maxAcc);


/*---------------------------------------------------------------------------
 * Name		:	DynTrap_Next
 * Input	:	pm - DynTrap_Init 成功返回的有效梯形波控制实例指针
 * Output	:	本周期计算出的绝对规划位置输出值
 * Description: 计算下一个规划位置，固定时间间隔调用该函数
 *---------------------------------------------------------------------------*/
int32 DynTrap_Next(DynTrapTypeDef * pm);


#endif

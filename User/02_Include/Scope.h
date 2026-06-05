/*
 * Copyright (c) 2021-2026 Fortior Technology Co., Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * File Name     : Scope.h
 * Author        : Summer
 * Date          : 2021-11-15
 * Description   : Base function for scope control.
 *
 * Record        :
 * V1.0, 2021-11-15, Summer: Created file
 */


#ifndef __SCOPE_H_
#define __SCOPE_H_

#include "fu7502.h"


#define CHANNELNUM										(6)          // scope channel number

#define SINGLESAMPLE									(0)          // single step sample
#define CONTINUOUSSAMPLE								(1)          // continuous sample

// Definition of SAMPLESTATUS
#define SAMPLESTATUS_ERROR								(0x0003)          // 
#define SAMPLESTATUS_OVER								(0x0002)          // 
#define SAMPLESTATUS_SAMPLE								(0x0001)          // 
#define SAMPLESTATUS_IDLE								(0x0000)          // 

// Definition of BUFFERSTATUS
#define BUFFERSTATUS_ALLREADY							(0x0010)          // 
#define BUFFERSTATUS_HALFREADY							(0x0008)          // 
#define BUFFERSTATUS_EMPTY								(0x0000)          //


#define SCOPE_SAMPLESTATUS_MASK							(0x0007)          //
#define SCOPE_BUFFERSTATUS_MASK							(0x0018)          //


// Definition of SCOPE_TRIGDIR
#define SCOPE_TRIGDIR_RISING							(0x0010)
#define SCOPE_TRIGDIR_FALLING							(0x0020)
#define SCOPE_TRIGDIR_EQUAL								(0x0000)


// Definition of register SCOPECTRL
#define SCOPE_SPEC									   0x8000          // rw-- 0 = Special; 1 = normal mode
#define SCOPE_TRIGEN								   0x0040          // rw-- 0 = trigger disable; 1 = trigger enable
#define SCOPE_TRIGDIR								   0x0030          // rw-- 0 = trigger when above Threshold; 1 = trigger when below Threshold
#define SCOPE_TRIGBITS		                           0x0008          // rw-- 0 = trigger variable 16 bit; 1 = trigger variable 32 bit
#define SCOPE_MODE		                               0x0004          // rw-- 0 = SINGLE; 1 = CONTINUOUS
#define SCOPE_START                                    0x0002          // rw-- rising dege = start scoping; 1 = stop scoping
#define SCOPE_EN									   0x0001          // rw-- 0 = disable scoping; 1 = enable scoping


// Definition of register SCOPESTATUS
#define SPSTATUS_BUFFER1							   0x0010          //
#define SPSTATUS_BUFFER0							   0x0008          //
#define SPSTATUS_SAMPLE2							   0x0004          //
#define SPSTATUS_SAMPLE1							   0x0002          //
#define SPSTATUS_SAMPLE0                               0x0001          //


#ifndef GetReg
#define GetReg(reg, val1)               ((reg) & (val1))						// 获取reg中val1的值
#endif

#ifndef ReadBit
#define ReadBit(reg, val)               (((reg) & (val)) != 0)                  // 判断reg中val对应的位是否为1
#endif


typedef struct
{
	uint16 BufferSize;
	uint16 ScopeCtrl;
	uint16 ScopeInterval;
	uint16 ScopeNum;
	uint8 Channel;   // Sample Channel
	const uint16* pScopeCtrl;
	uint16* pScopeData;
	const uint16* pScopeAddr[CHANNELNUM];
	const int16* pScopeTriAddr16;
	const int32* pScopeTriAddr32;
	int32 TriggerLevel;
	uint16 TriggerPrePoints;
} ScopeCfgTypeDef;


/*---------------------------------------------------------------------------
 * Name		:	Scope_UpdateMode
 * Input	:	cfg - 示波器配置参数
 *				pTrigStatus - 示波器触发采样状态
 * Output	:	示波器采样状态
 * Description:	Initialize Scope.
 *---------------------------------------------------------------------------*/
extern uint16 Scope_UpdateMode(ScopeCfgTypeDef* cfg, uint16* pTrigStatus);


/*---------------------------------------------------------------------------
 * Name		:	Scope_DoSample
 * Input	:	pTrigStatus - 示波器触发采样状态
 * Output	:	示波器采样状态
 * Description:	每隔固定的时间更新示波器采样
 *---------------------------------------------------------------------------*/
extern uint16 Scope_DoSample(uint16* pTrigStatus);


/*---------------------------------------------------------------------------
 * Name		:	Scope_GetDataReadyFlag
 * Input	:	usRegAddress - 示波器采样的起始位置
 * Output	:	示波器采样完成状态
 * Description:	判断示波器采样是否完成
 *---------------------------------------------------------------------------*/
extern uint8 Scope_GetDataReadyFlag(uint16 usRegAddress);

#endif